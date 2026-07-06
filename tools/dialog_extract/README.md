# Dialog resource extractor

Parses `RT_DIALOG` resources directly out of a PE file's `.rsrc` section —
control IDs, window classes, and caption text — without executing the
binary. Used to recover field labels from the companion `.dat` editor
tools found alongside `GunBound.gme` (`Asuka.exe` for `characterdata.dat`,
`mishato_English.exe` for `itemdata.dat`, `Shinji.exe` for `stage.dat`):
their MFC dialogs' captions are in Korean and directly name what each
on-disk field means, which the game client's own code never reveals (see
`FILEFORMATS.md`'s `characterdata.dat`/`itemdata.dat` sections for the
recovered field semantics).

Requires `pefile` (`pip install pefile`).

Usage:
```
python3 parse_dialogs.py /path/to/SomeTool.exe
```

Handles both classic `DIALOG` and `DIALOGEX` resource template formats.
