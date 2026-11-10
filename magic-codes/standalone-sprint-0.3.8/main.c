/* Experimental DKR-R 1.0.15 companion. No replacement/guest-source edits. */
#ifdef SPRINT_FINISH_TEST
#include "tests/sdk_shim.h"
#else
#include <dkr/development.h>
#include <dkr/game.h>
#endif
#include <dkr/json_read.h>

typedef unsigned char U8;
typedef unsigned short U16;
enum { TRACKS = 2, CATALOGUE_LIMIT = 1024, NODE_BYTES = 0x3c };
static int supported_revision(unsigned revision) { return revision == 77 || revision == 80; }
static const char* const course_ids[TRACKS] = {
    "dkrmap:tricky-standalone-race-us-v80",
    "dkrmap:bluey-standalone-race-us-v80"
};
static const unsigned main_counts[TRACKS] = {44, 30};
static const unsigned terminal_nodes[TRACKS] = {38, 24};
static const unsigned geometries[TRACKS] = {39, 1};
static const unsigned vehicles[TRACKS] = {0, 1};
/* The SDK catalogue content is sha256(pack_track_lab(source)), not ZIP bytes.
 * US v80 has55 stock level models; Track Lab appends custom models and rewrites
 * the matching course header to55+ordinal. The32767-record limit means a
 * highest possible model index of32766.
 * Only the complete r11, r12 and public v1 packages below may use that custom allocation range.
 * Logical course/carrier, header, node and terminal guards remain mandatory. */
static const char tricky_r11_content[] = "39f56873a2eb6f3aff810620ac1b1c9c6202b7f7f021365e5984b2027d4527da";
static const char tricky_r12_content[] = "a2f480f92ab5f3bae8588c67feee5993d63e3d979f7ac21c8934dc1ca6104171";
static const char tricky_v1_content[] = "2b427d3291986d70633b8b72225756bd2b75148605bea2893c874198fbd45245";
static unsigned carriers[TRACKS], found[TRACKS], tricky_r11_verified;
static int geometry_matches(unsigned track, unsigned geometry) {
    return geometry == geometries[track] ||
        (track == 0 && tricky_r11_verified && geometry >= 55 && geometry <= 32766);
}
static unsigned catalogue_index, catalogue_done, failed, enabled, guard_logged;
static DkrU32 game_mode, map_id, level_header, time_trial;
static DkrU32 main_count, total_count, nodes, start_timer;
/* Bounded diagnostics only. Never used to decide or perform a repair. */
typedef struct FinishObservation {
    DkrU32 object, racer;
    unsigned map, track, first_seen, complete;
} FinishObservation;
static FinishObservation observations[8];
static void clear_observations(void) {
    for (unsigned i = 0; i < 8; ++i) observations[i] = (FinishObservation){0};
}
static void normal_music_unload(void);
static void parking_boot(void);
static void parking_unload(void);
static char catalogue_json[4096];
static DkrJsonToken catalogue_tokens[64];

static int guest_range(DkrU32 address, unsigned bytes, unsigned alignment) {
    return address >= 0x80000400U && address <= 0x80800000U &&
        bytes <= 0x80800000U - address && !(address & (alignment - 1U));
}
static DkrU32 read_native(DkrU32 address, unsigned bytes) {
#ifdef SPRINT_FINISH_TEST
    return sprint_test_read(address, bytes);
#else
    if (bytes == 1) return *(const volatile U8*)address;
    if (bytes == 2) return *(const volatile U16*)address;
    return *(const volatile DkrU32*)address;
#endif
}
static void write_lap(DkrU32 address, U8 lap) {
#ifdef SPRINT_FINISH_TEST
    sprint_test_write(address, lap);
#else
    *(volatile U8*)address = lap;
#endif
}
static int signed_byte(DkrU32 address) {
    const unsigned value = read_native(address, 1);
    return value < 128 ? (int)value : (int)value - 256;
}
static DkrU32 symbol(const char* name, unsigned bytes, unsigned alignment) {
    const DkrU32 address = (DkrU32)(unsigned long)dkr_game_symbol(name);
    if (dkr_game_symbol_size(name) < bytes || !guest_range(address, bytes, alignment)) return 0;
    return address;
}
static void stop_scanning(void) {
    failed = 1;
    catalogue_done = 0;
    dkr_log("Experimental sprint finish inactive: course catalogue did not validate.");
}
DKR_CALLBACK(on_boot) void sprint_finish_boot(void) {
    parking_unload();
    Dkr2Session session = {.size = sizeof(Dkr2Session)};
    enabled = 0;
    clear_observations();
    catalogue_done = catalogue_index = failed = guard_logged = tricky_r11_verified = 0;
    for (unsigned i = 0; i < TRACKS; ++i) carriers[i] = found[i] = 0;
    /* Offline-only, US v77/v80, explicitly enabled. No speculative online claim. */
    dkr_log("Experimental sprint activation: candidate 0.3.8 loaded; Bluey/Tricky normal-music gameplay guard.");
    if (dkr_setting_number("enabled") != 1.0) {
        dkr_log("Experimental sprint activation: inactive, numeric enabled option is not 1. Enable the package AND set its option to 1, then restart.");
        return;
    }
    if (dkr2_session(&session) != DKR2_OK || !supported_revision(session.revision) || session.online) {
        dkr_log("Experimental sprint activation: inactive, requires an available offline US v77 or v80 session.");
        return;
    }
    game_mode = symbol("gGameMode", 4, 4);
    map_id = symbol("gMapId", 4, 4);
    level_header = symbol("gCurrentLevelHeader", 4, 4);
    time_trial = symbol("gIsTimeTrial", 1, 1);
    main_count = symbol("gNumberOfMainCheckpoints", 4, 4);
    total_count = symbol("gNumberOfTotalCheckpoints", 4, 4);
    nodes = symbol("gTrackCheckpoints", 4, 4);
    start_timer = symbol("gRaceStartTimer", 4, 4);
    if (!game_mode || !map_id || !level_header || !time_trial || !main_count ||
        !total_count || !nodes || !start_timer) {
        dkr_log("Experimental sprint activation: inactive, a required course/gameplay symbol is unavailable.");
        return;
    }
    enabled = 1;
    parking_boot();
}
/* Resolve exact logical Track Lab IDs to unique allocated level IDs, not menu
 * positions or stock carriers. Spread scanning over ticks to bound VM work.
 * Complete enumeration before mutating; malformed/duplicate entries fail shut.
 * These globals are ordinary rewindable mod guest memory. */
DKR_CALLBACK(on_frame) void sprint_finish_catalogue(void) {
    if (!enabled || failed || catalogue_done) return;
    for (unsigned batch = 0; batch < 4; ++batch) {
        const int size = dkr2_catalogue("courses", catalogue_index, catalogue_json, sizeof(catalogue_json));
        if (size == DKR2_END) {
            if (found[0] && found[1] && carriers[0] == carriers[1]) { stop_scanning(); return; }
            catalogue_done = 1;
            dkr_log(found[1] ? "Experimental sprint activation: course catalogue complete; Bluey identity resolved."
                            : "Experimental sprint activation: course catalogue complete; Bluey not present.");
            return;
        }
        if (catalogue_index >= CATALOGUE_LIMIT || size <= 1 ||
            (unsigned)size > sizeof(catalogue_json) || catalogue_json[size - 1] != '\0' ||
            dkr_json_parse(catalogue_json, (unsigned)size - 1, catalogue_tokens, 64) < 0) {
            stop_scanning(); return;
        }
        const int id = dkr_json_member(catalogue_json, catalogue_tokens, 0, "id");
        const int carrier = dkr_json_member(catalogue_json, catalogue_tokens, 0, "carrier");
        const int vehicle = dkr_json_member(catalogue_json, catalogue_tokens, 0, "default_vehicle");
        unsigned number, default_vehicle;
        if (id < 0 || carrier < 0 || vehicle < 0 ||
            !dkr_json_u32(catalogue_json, &catalogue_tokens[carrier], &number) ||
            !dkr_json_u32(catalogue_json, &catalogue_tokens[vehicle], &default_vehicle)) {
            stop_scanning(); return;
        }
        for (unsigned track = 0; track < TRACKS; ++track) {
            if (!dkr_json_equal(catalogue_json, &catalogue_tokens[id], course_ids[track])) continue;
            if (found[track] || number < 65 || number > 32767 || default_vehicle != vehicles[track]) {
                stop_scanning(); return;
            }
            if (track == 0) {
                const int content = dkr_json_member(catalogue_json, catalogue_tokens, 0, "content");
                tricky_r11_verified = content >= 0 &&
                    (dkr_json_equal(catalogue_json, &catalogue_tokens[content], tricky_r11_content) ||
                     dkr_json_equal(catalogue_json, &catalogue_tokens[content], tricky_r12_content) ||
                     dkr_json_equal(catalogue_json, &catalogue_tokens[content], tricky_v1_content));
            }
            found[track] = 1;
            carriers[track] = number;
        }
        ++catalogue_index;
    }
}
DKR_CALLBACK(on_scene_unload) void sprint_finish_unload(void) { parking_unload(); guard_logged = 0; clear_observations(); }

/* Match the CURRENT target before increment, like the nearby native branch.
 * Native race_check_finish retains ownership of finish flag, order and results.
 * Read entry context explicitly; no exit-hook argument assumptions. */
DKR_CALLBACK(before_func_8005B818) void sprint_finish_distant(void) {
    DkrGameCall call;
    if (!enabled || failed || !catalogue_done || read_native(game_mode, 4) != 0 ||
        read_native(time_trial, 1) || read_native(start_timer, 4) ||
        !dkr_game_context_read(&call)) return;
    const unsigned map = read_native(map_id, 4);
    unsigned track;
    for (track = 0; track < TRACKS; ++track) if (found[track] && carriers[track] == map) break;
    if (track == TRACKS) return;
    const DkrU32 object = (DkrU32)call.r[4], racer = (DkrU32)call.r[5];
    const DkrU32 header = read_native(level_header, 4), route = read_native(nodes, 4);
    const unsigned count = read_native(main_count, 4), total = read_native(total_count, 4);
    if (!guest_range(object, 0x80, 4) || !guest_range(racer, 0x224, 4) ||
        !guest_range(header, 0xc4, 4) || count != main_counts[track] || total < count || total > 127 ||
        !guest_range(route, total * NODE_BYTES, 4)) return;
    if (read_native(object + 0x64, 4) != racer || read_native(racer, 2) != 0xffffU ||
        read_native(racer + 0x1d8, 1) || read_native(racer + 0x1d6, 1) != vehicles[track] ||
        read_native(header + 0x4b, 1) != 1 || read_native(header + 0x4c, 1) != 0 ||
        read_native(header + 0x4d, 1) != vehicles[track] ||
        !geometry_matches(track, read_native(header + 0x34, 2))) return;
    if (!guard_logged) {
        guard_logged = 1;
        dkr_log(track == 0 ? "Experimental sprint finish: Tricky identity and scene guards matched."
                           : "Experimental sprint finish: Bluey identity and scene guards matched.");
    }
    const int next = signed_byte(racer + 0x192), lane = signed_byte(racer + 0x1ca);
    const unsigned progress = read_native(racer + 0x190, 2);
    if (next != (int)terminal_nodes[track] || lane < 0 || lane > 3 ||
        signed_byte(racer + 0x193) != 0 || !progress || progress >= 0x8000U) return;
    DkrU32 node = route + (unsigned)next * NODE_BYTES;
    const int alternate = signed_byte(node + 0x3a);
    if (read_native(racer + 0x1c8, 1) && alternate != -1) {
        if (alternate < (int)count || alternate >= (int)total) return;
        node = route + (unsigned)alternate * NODE_BYTES;
    }
    if (read_native(node + 0x36 + (unsigned)lane, 1) != 6) return;
    /* Exactly the stock nearby-CPU/player action-6 value: header laps + 1. */
    write_lap(racer + 0x193, 2);
    for (unsigned i = 0; i < 8; ++i) if (!observations[i].racer) {
        observations[i] = (FinishObservation){object, racer, map, track, 0, 0};
        break;
    }
    dkr_log(track == 0 ? "Experimental sprint finish: Tricky distant CPU terminal applied."
                       : "Experimental sprint finish: Bluey distant CPU terminal applied.");
}

/* The copied roster reacquires current-scene object/racer pairs. PLACE in the
 * typed SDK is live racePosition, not finishPosition; read the latter through
 * the already supported bounded guest-memory interface after native ownership
 * has run. First pending observation and final finish are each logged once.
 * This observer never writes any game data or registers. */
static char* append_text(char* out, const char* text) {
    while (*text) *out++ = *text++;
    return out;
}
static char* append_number(char* out, unsigned value) {
    char digits[10]; unsigned count = 0;
    do { digits[count++] = (char)('0' + value % 10); value /= 10; } while (value);
    while (count) *out++ = digits[--count];
    return out;
}
DKR_CALLBACK(after_race_check_finish) void sprint_finish_observe_native(void) {
    if (!enabled || failed || !catalogue_done || read_native(game_mode, 4) != 0 ||
        read_native(time_trial, 1)) return;
    unsigned pending = 0;
    for (unsigned i = 0; i < 8; ++i) if (observations[i].racer && !observations[i].complete) ++pending;
    if (!pending) return;
    const unsigned count = dkr_racer_count(), map = read_native(map_id, 4);
    if (!count || count > 8) return;
    for (unsigned i = 0; i < count; ++i) {
        DkrRacerState current;
        if (!dkr_racer_get(i, &current) || current.player != -1 ||
            !guest_range(current.racer, 0x224, 4)) continue;
        for (unsigned j = 0; j < 8; ++j) {
            FinishObservation* observation = &observations[j];
            if (observation->complete || observation->map != map ||
                observation->racer != current.racer || observation->object != current.object ||
                current.vehicle != vehicles[observation->track] ||
                (observation->first_seen && !current.finished)) continue;
            char line[192]; char* at = append_text(line, "Experimental sprint finish: ");
            at = append_text(at, observation->track == 0 ? "Tricky" : "Bluey");
            at = append_text(at, " native observation racer="); at = append_number(at, current.index);
            at = append_text(at, " lap="); at = append_number(at, current.lap);
            at = append_text(at, " finished="); at = append_number(at, current.finished);
            at = append_text(at, " finish_position="); at = append_number(at, read_native(current.racer + 0x1ac, 2));
            at = append_text(at, " race_position="); at = append_number(at, current.position);
            *at++ = '.'; *at = 0; dkr_log(line);
            observation->first_seen = 1;
            if (current.finished) observation->complete = 1;
        }
    }
}

#include "parking.inc"
#include "normal_music.inc"
