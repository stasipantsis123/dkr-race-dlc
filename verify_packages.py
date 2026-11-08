#!/usr/bin/env python3
"""Verify supplied archive and payload hashes. Does not test gameplay."""
import hashlib
import json
from pathlib import Path
import zipfile

root = Path(__file__).resolve().parent
checks = json.loads((root / "validation/PACKAGE-CHECKS.json").read_text())
for expected in checks:
    path = root / "packages" / expected["file"]
    data = path.read_bytes()
    assert len(data) == expected["bytes"], f"Size mismatch: {path.name}"
    assert hashlib.sha256(data).hexdigest() == expected["sha256"], f"Archive hash mismatch: {path.name}"
    with zipfile.ZipFile(path) as package:
        assert package.testzip() is None, f"Archive integrity failure: {path.name}"
        assert set(package.namelist()) == set(expected["payload_sha256"]), f"Unexpected archive contents: {path.name}"
        for name, sha256 in expected["payload_sha256"].items():
            assert hashlib.sha256(package.read(name)).hexdigest() == sha256, f"Payload hash mismatch: {path.name}/{name}"
        manifest = json.loads(package.read("manifest.json"))
        assert manifest["id"] == expected["id"], f"Track ID mismatch: {path.name}"
        assert manifest["builtFrom"] == "us.v80", f"Unexpected game-data profile: {path.name}"
    print(f"PASS: {path.name}")
print("Package bytes verified. Importer and gameplay tests were not run by this script.")
