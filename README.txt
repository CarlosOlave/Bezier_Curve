Files included:
===============
1) main_t05m01.cpp
2) BezierType.cpp
3) BezierType.h
4) Camera.cpp
5) Camera.h
6) Point.cpp
7) Point.h
8) SceneReader.cpp
9) SceneReader.h
10) Utility.h

Files Description:
==================

1) main_t05m01.cpp
 - Is the main executable file.
2) BezierType.cpp and BezierType.h
 - Data Structure for a Bezier Curve and Surface. In addition
 - the implementation of De Casteljau algorithm.
3) Camera.cpp and Camera.h
 - Specification for the camera in 3d space. In addition 
 - the functionality for CCW/CW rotations and MoveCloser/MoverAway.
4) Point.cpp and Point.h
 - Data structure for a single point.
5) SceneReader.cpp and SceneReader.h
 - Reads a .scene file.

Make:
=====
- Doing a make command will create maint05_m01 executable.

Execution:
==========
executable file_path
i.e.
 - main_t05m01 /Users/Bezier_Curve/files/test.scene


Extra:
======
- The KEY_UP will display individual curves/surfaces.
	i.e. If file contains 2 curves and 1 surface pressing KEY_UP
	     will display curve1 , curve2, surface1, and all images.
	