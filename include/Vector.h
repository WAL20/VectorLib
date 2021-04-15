/*--------- Vector.hpp ----------------------------------

   Vector Class Library Header
   Copyright 1994-2008, Bill Leonard

   The author will not be liable for any bug, error, omission,
   defect, deficiency, or nonconformity in this software. The author
   also disclaims all implied warranties, including without limitation
   warranties of merchantability, performance, and fitness for a
   particular purpose. This software is provided "as is" and the user
   assumes the entire risk as to its quality and performance.
*/

/*
	
	See "vector.h".
*/

#ifndef VECTOR_H
#define VECTOR_H

#ifndef scalar
#define scalar double
#endif
#ifndef FRACTION
#define FRACTION(A)     ( (A) - (long)(A) )
#endif
#ifndef EPSILON
#define EPSILON 1e-7
#endif
#ifndef INFINITY
#define INFINITY 1./EPSILON
#endif
#ifndef ABS
#define ABS(a) ((a) < 0 ? -(a) : (a))
#endif
#ifndef SGN
#define SGN(a) ((a) != 0 ? (ABS(a)/(a)) : (0))
#endif
#ifndef MAX
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#endif
#ifndef MIN
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#endif
#ifndef PI
#define PI 3.141592653589793
#endif
#ifndef DEGREES
#define DEGREES(s) ((s) * 180/PI)
#endif
#ifndef RADIANS
#define RADIANS(s) ((s) * PI/180)
#endif

#include <math.h>
#include <Vector2.h>
#include <Vector3.h>
#include <xform.h>


#endif
