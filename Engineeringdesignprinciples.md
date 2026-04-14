# Engineering Design Principles: 2D Circle Image Registration

## Pipeline Overview

| Stage | Name | Input | Output |
|-------|------|-------|--------|
| 1a | Generate Images | Circle parameters (diameter, centre, spacing, origin, direction cosines) | `img1.nrrd`, `img2.nrrd` |
| 1b | Resample to Common Space | Moving image + reference image | `img2_resampled.nrrd` |
| 2 | Set Fixed / Moving Images | Two NRRD files in common physical space | Labelled fixed and moving images |
| 3 | Translation Transform | Fixed + moving images | Optimised 2D translation parameters |
| 4 | Evaluate Mean Squared Distance | Fixed image + transformed moving image | MSD score |

---

## Whys

### Stage 1a — Generate Images

Synthetic binary circle images are generated from user-supplied physical parameters: diameter, centre position in mm, pixel spacing, physical origin, and direction cosines. Each image is saved as both PNG (pixel data only) and NRRD (pixel data plus full physical metadata). 

### Stage 1b — Resample to Common Physical Space

Before any registration metric can be evaluated, both images must share the same pixel grid: 

### Stage 2 — Set Fixed / Moving Images

img1 is designated the fixed (reference) image and img2 the moving image. 

### Stage 3 — Translation Transform (ImageRegistration1.cxx)

The registration algorithm is taken directly from `ImageRegistration1.cxx` in the ITK Examples (`Examples/RegistrationITKv4/`). It uses three fixed components:
A circle is rotationally symmetric. Rotating a circle produces an identical circle, so rotation is undetectable by any intensity-based metric. 

## Algorithm
The pipeline (generate → resample → register) correctly aligns two binary circle images of different sizes and positions using a translation transform, mean squares metric, and gradient descent optimiser.
