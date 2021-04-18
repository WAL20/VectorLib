/* -------- Vector3.h -----------

   3D Vector Class Library Header
   Copyright 1994-2008,2021 Bill Leonard

   The author will not be liable for any bug, error, omission,
   defect, deficiency, or nonconformity in this software. The author
   also disclaims all implied warranties, including without limitation
   warranties of merchantability, performance, and fitness for a
   particular purpose. This software is provided "as is" and the user
   assumes the entire risk as to its quality and performance.

*/
 

#ifndef VECTOR3_H
#define VECTOR3_H

#define ORIGIN Position(0,0,0)
#define XAXIS Direction(1,0,0)
#define YAXIS Direction(0,1,0)
#define ZAXIS Direction(0,0,1)

class Position ;
class Direction ;
class Transform;

class Vector3 {
   public:
      scalar x ;
      scalar y ;
      scalar z ;

			/// Create a vector (0,0,0).
      Vector3() ;
			/// Create a vector (a,b,c)
      Vector3(scalar a, scalar b, scalar c) ;
			/// Create a copy of another Vector3.
      Vector3(Vector3 const& v) ;
			/// Create a 3d version of a 2d vector. (z=0).
      Vector3(Vector2 const& v) ;

			/// Coerce THIS vector to a Position.
      operator Position() const ;
			/// Coerce THIS vector to a Direction.
      operator Direction() const ;

			/// Assign values to coordinates.
      Vector3& set(scalar a, scalar b, scalar c) ;
			/// Get the length (magnitude) of THIS.
      scalar len() const ;
			/// Normalize THIS (to unit vector), return former length.
      scalar norm() ;

			/// Add THIS plus v: THIS + v.
      Vector3  operator+ (Vector3 const& v) const ;   // Addition
			/// Add v to THIS: THIS = THIS + v.
      Vector3& operator+=(Vector3 const& v) ;
			/// Subtract THIS minus v: THIS - v.
      Vector3  operator- (Vector3 const& v) const ;   // Subtraction
			/// Subtract v from THIS: THIS = THIS - v.
      Vector3& operator-=(Vector3 const& v) ;
			/// Negate THIS: -THIS;
      Vector3  operator- () const ;                   // Negation
			/// Scale THIS: THIS * s.
      Vector3  operator* (scalar s) const ;     // Scale
			/// Scale THIS: THIS = THIS * s.
      Vector3& operator*=(scalar s) ;
			/// Scale THIS: s * THIS.
      friend Vector3 operator* (scalar s, Vector3 const& v) ; // Scale
			/// Scale THIS: THIS * 1/s.
      Vector3  operator/ (scalar s) const ;
			/// Scale THIS: THIS = THIS * 1/s.
      Vector3& operator/=(scalar s) ;
			/// Return the cross product of THIS with v.
      Vector3  cross     (Vector3 const& v) const ;
			/// Calculate the dot product of THIS with v.
      scalar   dot       (Vector3 const& v) const ;
			/// Calculate the dot product of THIS with a unit/Direction vector d.
      scalar   dot       (Direction const& v) const ;
			/// Coordinate-by-coordinate multiplication: THIS.x * v.x, THIS.y * v.y, THIS.z * v.z.      
      Vector3  operator* (Vector3 const& v) const ;
			/// Coordinate-by-coordinate multiplication: THIS.x = THIS.x * v.x, etc.
      Vector3& operator*=(Vector3 const& v) ;         // coord-by-coord
			/// Smallest magnitude coordinate (absolute value) of THIS.
      scalar   minCoord  () const ;                   // min coord
			/// Largest magnitude coordinate (absolute value) of THIS.
      scalar   maxCoord  () const ;                   // max coord
		  /// The axis of largest magnitude (in case of tie: x, then y, then z)
	  Direction majorAxis () const;
		  /// The axis of smallest magnitude (in case of tie: x, then y, then z)
	  Direction minorAxis () const;
			/// Sum of all 3 coordinates (useful for color representation arithmetic).
      scalar	sumCoord () const {return (x + y + z);} ;		// sum of coords
   } ;

class Position {
   public:
      scalar x ;
      scalar y ;
      scalar z ;

			/// Create a position vector located at the ORIGIN: (0,0,0).
      Position() ;
			/// Create a position at (a,b,c).
      Position(scalar a, scalar b, scalar c) ;

			/// Assign values to coordinates.
      Position& set(scalar a, scalar b, scalar c);

			/// Convert Position to Vector3
      friend Vector3 Vector(Position const& p) ;
			/// Add a displacement v to THIS position.
      Position  operator +  (Vector3 const& v) const ;
			/// Move THIS position by a displacement v.
      Position& operator += (Vector3 const& v) ;
			/// Subtract a displacement v from THIS position.
      Position  operator -  (Vector3 const& v) const ;
			/// Find the displacement between THIS position and position p.
      Vector3   operator -  (Position const& p) const ;
			/// Move THIS position by subtracting a displacement v.
      Position& operator -= (Vector3 const& v) ;
			/// Calculate the dot product of THIS position and unit vector d.
      scalar    dot         (Direction const& d) const ;
			/// Calculate the scaled position: THIS * s.
      Position  operator *  (scalar s) const ;
			/// Calculate the scaled position: THIS * 1/s.
      Position  operator /  (scalar s) const ;
			/// Calculate the scaled position: s * THIS.
      friend Position operator* (scalar s, Position const& p) ;  // scale
			/// Smallest magnitude coordinate (absolute value) of THIS.
      scalar   minCoord  () const ;                   // min coord
			/// Largest magnitude coordinate (absolute value) of THIS.
      scalar   maxCoord  () const ;                   // max coord
		  /// The axis of largest magnitude (in case of tie: x, then y, then z)
	  Direction majorAxis () const;
		  /// The axis of smallest magnitude (in case of tie: x, then y, then z)
	  Direction minorAxis () const;

} ;


class Direction {
   public:
      scalar x ;
      scalar y ;
      scalar z ;

			/// Create a NULL unit/direction vector.
      Direction() ;
			/// Create a unit/direction vector: (a,b,c) / |(a,b,c)|.
      Direction(scalar a, scalar b, scalar c) ;

			/// Assign values to coordinates.
      Direction& set(scalar a, scalar b, scalar c) ;

			/// Convert THIS Direction to Vector3
      friend Vector3 Vector(Direction const& d) ;
			/// Add THIS plus a unit/direction vector.
      Direction  operator +  (Direction const& d) const ;
			/// Add a unit/direction vector to THIS unit/direction vector.
      Direction& operator += (Direction const& d) ;
			/// Subtract a unit/direction from THIS unit/direction vector.
      Direction  operator -  (Direction const& d) const ;
			/// Subtract a unit/direction from THIS unit/direction vector.
      Direction& operator -= (Direction const& d) ;
			/// Find the reverse direction of THIS.
      Direction  operator -  () const ;
			/// Calculate the displacement of a distance s in THIS direction or scale THIS unit vector by s.
      Vector3    operator *  (scalar s) const ;
			/// Calculate THIS unit/direction vector scaled by 1/s.
      Vector3    operator /  (scalar s) const ;
			/// Calculate the displacement of a distance s in THIS direction or scale THIS unit vector by s.
      friend Vector3 operator* (scalar s, Direction const& d) ;
			/// Determine the cross product between THIS unit/direction vector and another.
      Vector3    cross       (Direction const& d) const ;
			/// Find the projection of THIS unit/direction vector on a vector v.
      scalar     dot         (Vector3 const& v) const ;
			/// Find the cosine of the angle between THIS and another unit/direction vector.
      scalar     dot         (Direction const& v) const ;
			/// Get the smallest coordinate magnitude of THIS unit/direction vector.
      scalar     minCoord    () const ;
			/// Get the largest coordinate magnitude of THIS unit/direction vector.
      scalar     maxCoord    () const ;
		  /// The axis of largest magnitude (in case of tie: x, then y, then z)
	  Direction majorAxis () const;
		  /// The axis of smallest magnitude (in case of tie: x, then y, then z)
	  Direction minorAxis () const;
			/// THIS unit/direction vector length can be 1 or 0.
      scalar     len() const ;
			/// Coerce THIS unit/direction vector to be unit length. Return former length.
      scalar	norm() ;
			/// Find the angle in radians between THIS unit/direction vector and another.
      scalar angle(Direction const& d2) const ;
  } ;

			/// Calculate the determinant of a 3x3 matrix.
scalar det(Vector3 const& v1,		//	| v1.x v2.x v3.x |
					 Vector3 const& v2,		//	| v1.y v2.y v3.y |
					 Vector3 const& v3) ;	//	| v1.z v2.z v3.z |

#endif
