/*---------------- Vector2.h ---------------------------

   2D Vector Class Library Header
   Copyright 1994-2008, Bill Leonard

   The author will not be liable for any bug, error, omission,
   defect, deficiency, or nonconformity in this software. The author
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
