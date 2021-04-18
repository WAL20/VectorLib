/*---------------- Vector2.h ---------------------------

   2D Vector Class Library Header
   Copyright 1994-2008,2021 Bill Leonard

   The author will not be liable for any bug, error, omission,
   defect,/*--------- Vector.h ----------------------------------

   Vector Class Library Header
   Copyright 1994-2008,2021 Bill Leonard

   The author will not be liable for any bug, error, omission,
   defect, deficiency, or nonconformity in this software. The author
   also disclaims all implied warranties, including without limitation
   warranties of merchantability, performance, and fitness for a
   particular purpose. This software is provided "as is" and the user
   assumes the entire risk as to its quality and performance.
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
 deficiency, or nonconformity in this software. The author
   also disclaims all implied warranties, including without limitation
   warranties of merchantability, performance, and fitness for a
   particular purpose. This software is provided "as is" and the user
   assumes the entire risk as to its quality and performance.

 */

#ifndef VECTOR2_H
#define VECTOR2_H

class Vector2 {
   public:
      scalar x ;
      scalar y ;

      Vector2() ;
      Vector2(scalar sx, scalar sy) ;

      Vector2& set(scalar a, scalar b) ;

			/// Add THIS plus v: THIS + v.
      Vector2  operator+ (Vector2 const& v) const ;
			/// Add v to THIS: THIS = THIS + v.
      Vector2& operator+=(Vector2 const& v) ;
			/// Subtract THIS minus v: THIS - v.
      Vector2  operator- (Vector2 const& v) const ;
			/// Subtract v from THIS: THIS = THIS - v.
      Vector2& operator-=(Vector2 const& v) ;
			/// Negate THIS: -THIS;
      Vector2  operator- () const ;
			/// Scale THIS: THIS * s.
      Vector2  operator* (scalar s) const ;
			/// Scale THIS: THIS = THIS * s.
      Vector2& operator*=(scalar s) ;
			/// Scale THIS: s * THIS.
      friend Vector2 operator* (scalar s, Vector2 const& v) ;
			/// Scale THIS: THIS * 1/s.
      Vector2  operator/ (scalar s) const ;
			/// Scale THIS: THIS = THIS * 1/s.
      Vector2& operator/=(scalar s) ;
	        /// Dot Product of THIS and v: THIS dot v.
      scalar   dot       (Vector2 const& v) const ;
			/// Coordinate-by-coordinate multiplication: THIS.x * v.x, THIS.y * v.y.
      Vector2  operator* (Vector2 const& v) const ;
			/// Coordinate-by-coordinate multiplication: THIS.x = THIS.x * v.x, etc.
      Vector2  operator*=(Vector2 const& v) ;         /// coord-by-coord
			/// Smallest magnitude coordinate (absolute value) of THIS.
      scalar   minCoord() const ;
			/// Largest magnitude coordinate (absolute value) of THIS.
      scalar   maxCoord() const ;
   } ;

#endif
