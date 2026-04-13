# Engineering Design Principles: 2D Circle Image Registration

| Stage | Name | Input | Output |
|-------|------|-------|--------|
| 1 | Generate PNG Images | Circle parameters (diameter, centre) | `img1.png`, `img2.png` |
| 2 | Attach Metadata & Convert | PNG files + user-supplied metadata | `img1.nrrd`, `img2.nrrd` |
| 3 | Set Fixed / Moving Images | Two NRRD/NIfTI/DCM files | Labelled fixed and moving images |
| 4 | Determine Transform Type | Fixed + moving images | Initialised transform |
| 5 | Apply Transform | Initialised transform | Optimised transform |
| 6 | Evaluate Mean Squared Distance | Fixed image + transformed moving image | MSD score |


## Whys
1 — Generate png| Simple synthetic ground truth; PNG used for initial generation 
2 — Convert | User supplies spacing, origin, direction; PNG cannot store physical metadata; downstream must work in mm 
3 — Fix/Moving | img1 = fixed, img2 = moving (default); swappable via CLI flags
6 — Metric | Mean Squared Distance | Same modality, matched intensities; MSD is fast