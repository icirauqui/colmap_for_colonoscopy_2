COLMAP FOR COLONOSCOPY 2
======


About
-----

This COLMAP version has been modified aiming to identify and analize the pressence of tissue deformation in medical procedures,
it stores the 3D points discarded by the Bundle Adjustement due to not complying with the rigidity asumption.

**Modified Files:**

All changes can be identified by commented snippet "ICxx": 

IC01 - Store pointes removed because of large reprojection error or small triangulation angle

* colmap/src/base/reconstruction.h
* colmap/src/base/reconstruction.cc
* colmap/src/exe/reconstruction.cc

IC02 - Draw IC01 points in images.

 * colmap/src/base/database.h
 * colmap/src/base/database.cc
 * colmap/src/ui/image_viewer_widget.h
 * colmap/src/ui/image_viewer_widget.cc
 * colmap/src/ui/database_management_widget.cc

IC03 - Add batched reconstruction option to gui

* colmap/src/ui/main_window.h
* colmap/src/ui/main_window.cc
* colmap/src/controllers/incremental_mapper.h
* colmap/src/controllers/incremental_mapper.cc
* colmap/src/sfm/incremental_mapper.h
* colmap/src/sfm/incremental_mapper.cc
* colmap/src/estimators/two_view_geometry.cc
* colmap/src/feature/sift.cc
* colmap/src/ui/start_reconstruction_bundle_widget_.h    (new file)
* colmap/src/ui/start_reconstruction_bundle_widget_.cc   (new file)

IC04 - Track reborn 3D points.

* colmap/src/base/reconstruction.h
* colmap/src/base/reconstruction.cc
* colmap/src/exe/reconstruction.cc

IC05 - Draw all keypoints segregating triangulated, draw projection of 3D points, draw reprojection error.

* colmap/src/ui/database_management_widget.cc

IC06 - Matching by epipolar geometry instead of image distortion.

* colmap/src/estimators/two_view_geometry.cc
* colmap/src/feature/matching.cc
* colmap/src/sfm/incremental_mapper.h
* colmap/src/feature/sift.h
* colmap/src/feature/sift.cc

IC07 - Add bundled mapper option to command line

* colmap/src/exe/colmap.cc
* colmap/src/exe/sfm.h
* colmap/src/exe/sfm.cc
* colmap/src/util/option_manager.cc




About (fork)
-----

Project forked from:
   https://github.com/UZ-SLAMLab/colmap_for_colonoscopy

This COLMAP version has been modified for work with colonoscopy images. Now COLMAP only estimate
calibrated geometries and discart those that don't have a minimun inliers number. This implicated
estimate the **Esential** matrix using **RANSAC** and the undistortionated key points coordinates. To make 
posible an implementation of **Guided Matching**, the **Fundamental** matrix is calculated using the intrinsic matrix **K**.

**Modified Files:**

* colmap/src/estimators/two_view_geometry.cc
* colmap/src/estimators/two_view_geometry.h
* colmap/src/feature/matching.cc
* colmap/src/feature/sift.cc
* colmap/sfm/incremental_mapper.cc



