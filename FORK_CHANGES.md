# Source lineage and corrections

This repository derives from [UZ-SLAMLab/colmap_for_colonoscopy](https://github.com/UZ-SLAMLab/colmap_for_colonoscopy),
which adapts COLMAP's calibrated geometry and guided matching to colonoscopy.
Subsequent thesis developments retain bundled reconstruction, discarded-track
diagnostics, recovered-point tracking and multiple-model GUI import. The
inherited COLMAP source/version family is **3.7**, not COLMAP 4.2.0.

The maintained branch is `main`; source release **`3.7-colonoscopy.1`** includes
the existing corrected development branch and this publication documentation.
Integration preserves every tracked file from the former main branch. The
development branch was ahead of main rather than a divergent alternative;
no main-only feature was dropped during integration.

## Corrections integrated from the development branch

| Area | Change | Principal files |
|---|---|---|
| Build compatibility | C++17, Ceres manifold API and modern dependency discovery; corrections to vendored PoissonRecon operators | `CMakeLists.txt`, `cmake/CMakeConfig.cmake.in`, `src/CMakeLists.txt`, `src/estimators/pose.cc`, `src/optim/bundle_adjustment.cc`, `lib/PoissonRecon/` |
| Temporal windows | One-based starting IDs; exposed `Mapper.bundle_start_image_id`; correct complete-window count; prevent duplicate global-relaxation passes; CLI `mapper_bundle` enables the bundle workflow | `src/controllers/incremental_mapper.cc`, `src/sfm/incremental_mapper.{cc,h}`, `src/util/option_manager.cc`, `src/exe/sfm.cc` |
| Diagnostics and model I/O | Correct discarded-point storage access and track ratios; preserve optional discarded-point models while accepting standard models; correct discarded-track statistics | `src/base/reconstruction.{cc,h}` |
| Triangulation metadata | Update exactly successful track elements, with bounds checks; preserve recursively created tracks; repair database lifetime | `src/sfm/incremental_triangulator.cc`, `src/sfm/incremental_mapper.cc`, `src/base/reconstruction.cc` |
| GUI and project setup | Preserve dialog import and add explicit multiple-import paths; select numbered/global models while excluding metadata directories; expose project database/image paths | `src/exe/gui.cc`, `src/ui/main_window.{cc,h}` |
| CPU/GPU matching | Apply configured maximum-match limits to CPU matches; refresh GPU keypoint locations independently of descriptor updates | `src/feature/sift.cc` |
| Random state (A-RNG1) | Share the CLI default seed; use COLMAP's thread-local engine for FLANN sampling/shuffling instead of process-global resets | `src/util/random.{cc,h}`, `lib/FLANN/` |
| Empty descriptors (A-SIFT1) | Initialize VLFeat's descriptor buffer when a boundary feature leaves it unwritten; preserve empty RootSIFT rows as finite zeros | `src/feature/sift.cc`, `src/feature/utils.cc` |
| Precise export (A-EXPORT1/2) | Seventeen-significant-digit text output; explicit binary-to-TXT mode that preserves raw quaternion doubles without renormalizing them | `src/base/reconstruction.{cc,h}`, `src/exe/model.cc` |

Inspect the complete code delta relative to the retained former main commit:

```bash
git diff 0b98a1c645a1fbab290607e05904cf07635c7afa..3.7-colonoscopy.1 -- CMakeLists.txt cmake lib src
```

Public test temporary-directory prefixes use the benchmark namespace `sdtube`.
That naming change does not change assertions, source algorithms or numerical
constants. Original execution receipts and source identities are retained
privately and distinguished from public naming copies.

## Regression evidence and execution profiles

The retained qualified source-only cold build passed five native suites:
`util/random_test`, `feature/sift_test`, `feature/utils_test`,
`base/database_test` and `base/reconstruction_test`. Relevant controls include
`TestFLANNSeedIsolation`, `TestSharedDefaultSeed`, empty descriptor normalization,
`TestExactTextRoundTripPrecision` and `TestBinaryToTextPreservesRawPoseDoubles`.
Negative controls detect the earlier random-state/empty-descriptor defects.

All algorithm, native-test and build files match the qualified source capsule
after public naming normalization. Of its 819 members, **817 are byte-identical**;
`README.md` now supplies this publication documentation and `src/util/version.h`
is a generated build identifier. Additional fork documentation and citation
metadata are separate from the capsule. These documentation and test temporary-
directory naming updates do not constitute a new native test run.

The current reconstruction profile is **A-SIFT1** on top of **A-RNG1**.
Export profiles **A-EXPORT1** and **A-EXPORT2** are separately qualified utilities:
adding conversion code to this release does not change the frozen inference
binaries or replace their hashes. Stage source/executable identities, inherited
matching gates, numerical options, seeds, one-thread settings and homogeneous
CPU affinity are recorded in the [reproducibility material](https://doi.org/10.57967/hf/10851).
Earlier failed, interrupted and superseded profiles remain identified as such.
The observed exact repetitions apply to those finite contracts, not arbitrary
hardware, dependencies, threading, GPU configurations or clinical acquisitions.

The [dataset DOI](https://doi.org/10.57967/hf/10850) identifies the observations
and annotations; it does not identify this source release. The scientific study
continues to cite the original COLMAP work and the colonoscopy adaptation.
