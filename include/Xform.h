/* -------- Xform.h -----------

   Transform Class Library Header
   Copyright 1994-2008,2021 Bill Leonard

   The author will not be liable for any bug, error, omission,
   defect, deficiency, or nonconformity in this software. The author
   also disclaims all implied warranties, including without limitation
   warranties of merchantability, performance, and fitness for a
   particular purpose. This software is provided "as is" and the user
   assumes the entire risk as to its quality and performance.

*/
 
#ifndef TRANSFORM_H
#define TRANSFORM_H


class Vector4 {

   public:
      scalar x ;
      scalar y ;
      scalar z ;
      scalar w ;

      Vector4() ;
      Vector4(scalar a, scalar b, scalar c, scalar d) ;

			/// Convert THIS to Vector3 (drop homogeneous coordinate).
      operator Vector3() const ;
			/// Convert THIS to Position (divide through by homogeneous coordinate).
      operator Position() const ;
			/// Convert THIS to Direction (drop homogeneous coordinate, normalize).
      operator Direction() const ;

			/// Assign values to coordinates.
      Vector4& set(scalar a, scalar b, scalar c, scalar d) ;
			/// Calculate dot product of THIS vector and another.
      scalar dot(Vector4 const& v) const ;
			/// Standardize THIS (divide through by homogeneous coordinate).
      Vector4 stdz() ;
			/// Convert a 3d vector to homogeneous form (w = 0).
      friend Vector4 VectorH(Vector3 const& v3) ;
			/// Convert a Position to Homogeneous form (w = 1).
      friend Vector4 VectorH(Position const& p) ;
			/// Convert a Direction to homogeneous form (w = 0).
      friend Vector4 VectorH(Direction const& d) ;
	} ;

class Transform {
   public:
      scalar xform[4][4] ;

      Transform() ;
      Transform(Transform const& mx) ;
      Transform(Vector4 const& r0, Vector4 const& r1,
                Vector4 const& r2, Vector4 const& r3) ;
      Transform(Vector3 const& r0, Vector3 const& r1,
                Vector3 const& r2, Vector3 const& r3) ;

			/// Set THIS transform matrix to identity.
      void Identity() ;
			/// Extract column c from THIS transform. (0 <= c <= 3)
      Vector4 col(int c) const ;
			/// Extract row r from THIS transform. (0 <= r <= 3)
      Vector4 row(int r) const ;
			/// Set row r of THIS transform from a homogeneous vector v. (0 <= r <= 3)
	  Transform setRow(int r, Vector4 const& v) ;
			/// Set row r of THIS transform from a 3d vector v. (0 <= r <= 3)
	  Transform setRow(int r, Vector3 const& v) ;
			/// Set column c of THIS transform from a homogeneous vector v. (0 <= c <= 3)
	  Transform setCol(int c, Vector4 const& v) ;
			/// Set column c of THIS transform from a 3d vector v. (0 <= c <= 3)
	  Transform setCol(int c, Vector3 const& v) ;
			/// Return the transpose of THIS transform matrix.
	  Transform transpose() const ;
			/// Return the inverse of THIS transform matrix. (Assumed to be well-conditioned.)
      Transform inverse() const ;
      
			/// Multiply THIS transform matrix times another. (THIS * mx)
      Transform operator*(Transform const& mx) const ;
			/// Multiply THIS transform matrix times another. Replace THIS. (THIS <- THIS * mx)
      Transform& operator*=(Transform const& mx) ;
			/// Add THIS transform matrix with another. (THIS + mx)
      Transform operator+(Transform const& mx) const ;
			/// Add THIS transform matrix with another. Replace THIS. (THIS <- THIS + mx)
      Transform& operator+=(Transform const& mx) ;

			/// Multiply THIS transform matrix by a scalar value. (THIS * s)
      Transform operator*(scalar const& s) const ;
			/// Multiply THIS transform matrix by a scalar value. Replace THIS. (THIS <- THIS * s)
      Transform& operator*=(scalar const& s) ;
			/// Multiply THIS transform matrix by a scalar value. (s * THIS)
      friend Transform operator*(scalar const& s, Transform const& mx) ;

			/// Multiply THIS transform matrix times a homogeneous vector. (THIS * v)
      Vector4 operator*(Vector4 const& v) const ;
			/// Multiply THIS transform matrix times a position vector. (THIS * p)
      Position operator*(Position const& p) const ;
			/// Multiply THIS transform matrix times a direction vector. (THIS * d)
      Direction operator*(Direction const& d) const ;
			/// Multiply a homogeneous vector times THIS transform matrix. (v * THIS)
      friend Vector4 operator*(Vector4 const& v, Transform const& mx) ;
			/// Multiply a position vector times THIS transform matrix. (p * THIS)
      friend Position operator*(Position const& p, Transform const& mx) ;
			/// Multiply a direction vector times THIS transform matrix. (d * THIS)
      friend Direction operator*(Direction const& d, Transform const& mx) ;

	   // Graphics transform constructions.
	   // These functions concatenate operations.
			/// Concatenate a translation to THIS transform matrix.
      Transform& translate(Vector3 const& v) ;
			/// Concatenate a scaling operation to THIS.
      Transform& scale(Vector4 const& s) ;
			/// Concatenate a rotation about the X axis.
      Transform& rotateX(scalar radians) ;  // *this is rotated
			/// Concatenate a rotation about the Y axis.
      Transform& rotateY(scalar radians) ;
			/// Concatenate a rotation about the Z axis.
      Transform& rotateZ(scalar radians) ;

	   // More Graphics transform constructions.
	   // These functions DO NOT concatenate operations.
			/// Set THIS transform matrix to rotate about selected axis by radians.
      Transform& setRotate(Direction const& axis, scalar radians) ;
			/// Set THIS transform matrix to rotate one direction vector into another about a mutually perpendicular axis.
      Transform& setRotate(Direction const& d1, Direction const& d2) ;
			/// Set THIS transform matrix to rotate one direction vector into another about x-, y- and z- axes.
      Transform& setRotateGimbal(Direction const& d1, Direction const& d2) ;
			
      Transform& set(Direction const& rx,
                     Direction const& ry,
                     Direction const& rz,
                     Vector4 const& s,
                     Position const& t) ;

   } ;

#endif
