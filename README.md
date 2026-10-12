# COLMAP for colonoscopy 2

A research derivative of [COLMAP for colonoscopy](https://github.com/UZ-SLAMLab/colmap_for_colonoscopy),
with temporal-window reconstruction, discarded-track diagnostics and corrected
feature handling and model export. This is **Pipeline A** in the
Synthetic Deformable Tubular Benchmark study. It is maintained by
**Íñigo Cirauqui-Viloria** and is separate from official COLMAP and the study's
[COLMAP 4.2.0 Pipeline B](https://github.com/icirauqui/colmap).

The maintained branch is **`main`**. The corrected source release is
[`3.7-colonoscopy.1`](https://github.com/icirauqui/colmap_for_colonoscopy_2/tree/3.7-colonoscopy.1).
The program's inherited version string remains `3.7`; identify this fork's tag
or commit as well. See [FORK_CHANGES.md](FORK_CHANGES.md) for source lineage,
corrections, regression controls and scientific execution boundaries.

## Dataset and reproducibility material

- [Synthetic Deformable Tubular Benchmark](https://doi.org/10.57967/hf/10850):
  scientific data version 1.0.0, public naming/package edition `v1.0.1`.
- [Reproducibility material](https://doi.org/10.57967/hf/10851): `v1.1.0`,
  with frozen protocols, source/control records, qualified runtime archives,
  final feature databases, models, predictions and evaluation records.
- [LumenMorph](https://github.com/icirauqui/LumenMorph): the separate synthetic
  data generator and evaluation tools.

The resource provides controlled synthetic observations. Reconstruction
disagreement and discarded tracks are diagnostics; neither uniquely measures
physical tissue deformation or establishes clinical validity.

## Features retained in this release

- Calibrated two-view geometry and guided matching inherited from the original
  colonoscopy adaptation.
- Storage and display of discarded points and tracks, and tracking of points
  that re-enter the reconstruction.
- Temporal-window reconstruction through the CLI `mapper_bundle` command and
  the GUI's bundled reconstruction workflow.
- Import of numbered model directories and a separate `global` reconstruction,
  including `gui --import_path_multiple`.
- Standard COLMAP model reading plus optional discarded-point extensions;
  accurate text export and opt-in lossless binary-pose conversion.

## Build and test

Clone the fixed source release:

```bash
git clone --branch 3.7-colonoscopy.1 https://github.com/icirauqui/colmap_for_colonoscopy_2.git
cd colmap_for_colonoscopy_2
```

This fork uses a C++17 compiler and the Ceres 2.x manifold API. It also requires
CMake, Boost program-options/filesystem/graph/test, Eigen, FreeImage, glog,
OpenGL and GLEW development libraries. GUI builds additionally require Qt5;
CUDA and CGAL are optional. The inherited [installation guide](doc/install.rst)
provides dependency background; its historical compiler/Ceres instructions
must be read with the requirements above.

Example CPU-only CLI configuration, using a separate local installation prefix:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_INSTALL_PREFIX="$PWD/install" \
  -DGUI_ENABLED=OFF -DOPENGL_ENABLED=OFF -DCUDA_ENABLED=OFF \
  -DCGAL_ENABLED=OFF -DTESTS_ENABLED=ON
cmake --build build --parallel 4
ctest --test-dir build --output-on-failure \
  -R '^(util/random_test|feature/sift_test|feature/utils_test|base/database_test|base/reconstruction_test)$'
build/src/exe/colmap -h
```

Enable `GUI_ENABLED` and `OPENGL_ENABLED` to build the retained Qt interface.
Official COLMAP binaries do not contain this fork's changes. This configuration
describes a source build; the study's exact source/compiler/dependency/runtime
and CPU contracts are recorded separately in the reproducibility material.
Publishing this release does not assert a new native build or experiment.

Lossless conversion of stored binary pose values is explicit:

```bash
build/src/exe/colmap model_converter \
  --input_path /path/to/binary_model --output_path /path/to/text_model \
  --output_type TXT --preserve_raw_poses 1
```

This mode accepts binary input and TXT output. Default reading/conversion keeps
the inherited quaternion normalization behavior.

## Attribution, citation and licensing

The original colonoscopy adaptation is by **José Daniel Subías Sarrato**,
developed at UZ-SLAMLab under José María Martínez Montiel. It accompanies
[his 2021 bachelor's thesis](https://zaguan.unizar.es/record/106905/files/TAZ-TFG-2021-2094.pdf).
Subsequent bundled reconstruction and diagnostic developments accompany
Íñigo Cirauqui-Viloria's 2022 master's thesis, *Deformable Structure from Motion
in medical endoscopy sequences*, University of Zaragoza. COLMAP is originally
by **Johannes Schönberger and contributors**. Cite the relevant original work,
including Schönberger and Frahm, *Structure-from-Motion Revisited*, CVPR 2016,
[doi:10.1109/CVPR.2016.445](https://doi.org/10.1109/CVPR.2016.445), and identify
this derivative's tag or commit. [CITATION.cff](CITATION.cff) supplies fork metadata.

Existing license files are preserved: the repository-level [LICENSE](LICENSE)
contains GPL version 3; [COPYING.txt](COPYING.txt) contains COLMAP's original
BSD notice. Vendored components retain their respective notices in `lib/` and
`src/ui/media/`; see also [the inherited license guide](doc/license.rst).
No blanket license change to inherited or third-party material is made here.
