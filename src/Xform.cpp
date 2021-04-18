/* -------- Xform.cpp -----------

   Transform Class Library
   Copyright 1994-2008,2021 Bill Leonard

   The author will not be liable for any bug, error, omission,
   defect, deficiency, or nonconformity in this software. The author
   also disclaims all implied warranties, including without limitation
   warranties of merchantability, performance, and fitness for a
   particular purpose. This software is provided "as is" and the user
   assumes the entire risk as to its quality and performance.

*/

#include "vector.h"

Vector4::Vector4() {
   x = y = z = w = 0 ;
   }

Vector4::Vector4(scalar a, scalar b, scalar c, scalar d) {
   x = a ;
   y = b ;
   z = c ;
   w = d ;
   }

Vector4::operator Vector3() const {
   return Vector3(x,y,z) ;
   }

Vector4::operator Position() const {
   if (w != 0)
      return Position(x/w,y/w,z/w) ;
   else
      return Position(x,y,z) ;
   }

Vector4::operator Direction() const {
   return Direction(x,y,z) ;
   }

Vector4& Vector4::set(scalar a, scalar b,
                  scalar c, scalar d) {
   x = a ;
   y = b ;
   z = c ;
   w = d ;
   return *this ;
   }

scalar Vector4::dot(Vector4 const& v) const {
   return x*v.x + y*v.y + z*v.z + w*v.w ;
   }

Vector4 Vector4::stdz() {
   if (w != 0) {
      x /= w ;
      y /= w ;
      z /= w ;
      }
   w = 1 ;
   return *this ;
   }

Vector4 VectorH(Vector3 const& v) {
   return Vector4(v.x,v.y,v.z,0) ;
   }
Vector4 VectorH(Position const& p) {
   return Vector4(p.x,p.y,p.z,1) ;
   }
Vector4 VectorH(Direction const& d) {
   return Vector4(d.x, d.y,d.z,0) ;
   }


/* -----------------------------------------------------------
 *  Create an identity transform matrix.
 */
Transform::Transform() {
   Identity() ;
   }

/* -----------------------------------------------------------
 *  Create a transform matrix from another
 */
Transform::Transform(Transform const& mx) {
   for (int i = 0 ; i < 4 ; i++)
      for (int j = 0 ; j < 4 ; j++ )
         xform[i][j] = mx.xform[i][j] ;
   }


/* -----------------------------------------------------------
 *  Create a transform matrix from 4 row vectors.
 */
Transform::Transform(Vector4 const& r0, Vector4 const& r1,
                     Vector4 const& r2, Vector4 const& r3) {
   xform[0][0] = r0.x ;
   xform[0][1] = r0.y ;
   xform[0][2] = r0.z ;
   xform[0][3] = r0.w ;

   xform[1][0] = r1.x ;
   xform[1][1] = r1.y ;
   xform[1][2] = r1.z ;
   xform[1][3] = r1.w ;

   xform[2][0] = r2.x ;
   xform[2][1] = r2.y ;
   xform[2][2] = r2.z ;
   xform[2][3] = r2.w ;

   xform[3][0] = r3.x ;
   xform[3][1] = r3.y ;
   xform[3][2] = r3.z ;
   xform[3][3] = r3.w ;

   }

/* -----------------------------------------------------------
 *  Create a transform matrix from 4 row vectors.
 */
Transform::Transform(Vector3 const& r0, Vector3 const& r1,
                     Vector3 const& r2, Vector3 const& r3) {
   xform[0][0] = r0.x ;
   xform[0][1] = r0.y ;
   xform[0][2] = r0.z ;
   xform[0][3] = 0 ;

   xform[1][0] = r1.x ;
   xform[1][1] = r1.y ;
   xform[1][2] = r1.z ;
   xform[1][3] = 0 ;

   xform[2][0] = r2.x ;
   xform[2][1] = r2.y ;
   xform[2][2] = r2.z ;
   xform[2][3] = 0 ;

   xform[3][0] = r3.x ;
   xform[3][1] = r3.y ;
   xform[3][2] = r3.z ;
   xform[3][3] = 1 ;

   }

/* -----------------------------------------------------------
 *  Set a transform to an identity matrix.
 */
void Transform::Identity() {
     for (int i = 0 ; i < 4 ; i++ ) {
         for (int j = 0 ; j < 4 ; j++ )
            xform[i][j] = 0 ;
         xform[i][i] = 1 ;
         }
     }

/* -----------------------------------------------------------
 * Extract a column vector.
 */
Vector4 Transform::col(int c) const {
   Vector4 v(xform[0][c], xform[1][c], xform[2][c], xform[3][c]) ;
   return v ;
   }

/* -----------------------------------------------------------
 * Extract a row vector.
 */
Vector4 Transform::row(int r) const {
   return Vector4(xform[r][0],xform[r][1],xform[r][2],xform[r][3]) ;
   }


/* -----------------------------------------------------------
 * Set a row vector.
 */
Transform Transform::setRow(int r, Vector4 const& v) {
	xform[r][0] = v.x ;
	xform[r][1] = v.y ;
	xform[r][2] = v.z ;
	xform[r][3] = v.w ;
	return *this ;
}
Transform Transform::setRow(int r, Vector3 const& v) {
	xform[r][0] = v.x ;
	xform[r][1] = v.y ;
	xform[r][2] = v.z ;
	xform[r][3] = 0. ;
	return *this ;
}
/* -----------------------------------------------------------
 * Set a column vector.
 */
Transform Transform::setCol(int c, Vector4 const& v) {
	xform[0][c] = v.x ;
	xform[1][c] = v.y ;
	xform[2][c] = v.z ;
	xform[3][c] = v.z ;
	return *this ;
}
Transform Transform::setCol(int c, Vector3 const& v) {
	xform[0][c] = v.x ;
	xform[1][c] = v.y ;
	xform[2][c] = v.z ;
	xform[3][c] = 0. ;
	return *this ;
}

/** -----------------------------------------------------------
 * Multiply a transform matrix times a (column) vector.
 **/
Vector4 Transform::operator*(Vector4 const& v) const {
   Vector4 vrow[4] ;
   for (int i=0 ; i < 4 ; i++)
      vrow[i].set(xform[i][0],
                  xform[i][1],
                  xform[i][2],
                  xform[i][3]) ;
   Vector4 vres(vrow[0].dot(v),vrow[1].dot(v),vrow[2].dot(v),vrow[3].dot(v)) ;
   return vres ;
   }

/** -----------------------------------------------------------
 * Transform a vector. (Multiply a row vector times
 * a transform matrix.)
 **/
Vector4 operator*(Vector4 const& v, Transform const& mx) {
   Vector4 vr(v.dot(mx.col(0)),
               v.dot(mx.col(1)),
               v.dot(mx.col(2)),
               v.dot(mx.col(3))) ;
   return vr ;
   }

/** -----------------------------------------------------------
 * Post transform a position vector. (Multiply a transform
 * matrix times a column vector.) We create a temporary
 * Vector4 from the position vector where the homogeneous
 * coordinate is 1.
 **/
Position Transform::operator*(Position const& p) const {
   return (*this * (VectorH(p))) ;
   }

/** -----------------------------------------------------------
 * Post transform a direction vector. (Multiply a transform
 * matrix times a column vector.) We create a temporary
 * Vector4 from the direction vector where the homogeneous
 * coordinate is 0.
 **/
Direction Transform::operator*(Direction const& d) const {
   return (*this * (VectorH(d))) ;
   }

/** -----------------------------------------------------------
 * Transform a position vector. (Multiply a row vector
 * times a transform matrix.) We create a temporary
 * Vector4 from the position vector where the homogenous
 * coordinate is 1.
 **/
Position operator*(Position const& p, Transform const& mx) {
   return (VectorH(p)*mx) ;
   }

/** -----------------------------------------------------------
 * Transform a direction vector. (Multiply a row vector
 * times a transform matrix.) We create a temporary
 * Vector4 from the direction vector where the homogenous
 * coordinate is 0.
 **/
Direction operator*(Direction const& d, Transform const& mx) {
   return (VectorH(d)*mx) ;
   }

/* -----------------------------------------------------------
   Simple transforms - Cumulative

   Source: Graphics Gems, Glassner

 */

// From Graphics Gems I, p478
Transform& Transform::translate(Vector3 const& v) {
   for (int i = 0 ; i < 4 ; i++) {
       xform[i][0] += xform[i][3] * v.x ;	// 
       xform[i][1] += xform[i][3] * v.y ;
       xform[i][2] += xform[i][3] * v.z ;
       }
   return *this ;
   }

// From Graphics Gems I, p478
Transform& Transform::scale(Vector4 const& s) {
   Vector3 s1(s.x*s.w, s.y*s.w, s.z*s.w) ;
   for (int i = 0 ; i < 4 ; i++) {
      xform[i][0] *= s1.x ;
      xform[i][1] *= s1.y ;
      xform[i][2] *= s1.z ;
      }
   return *this ;
   }

// From Graphics Gems I, p478
Transform& Transform::rotateX(scalar radians) {
	if (radians == 0.)
		return *this ;
   const scalar c = cos(radians) ;
   const scalar s = sin(radians) ;
   scalar t ;
   for (int i = 0 ; i < 4 ; i++) {
	   t = xform[i][1] ;
	   xform[i][1] = t*c - xform[i][2] * s ;
	   xform[i][2] = t*s + xform[i][2] * c ;
	   }
   return *this ;
   }

// From Graphics Gems I, p478
Transform& Transform::rotateY(scalar radians) {
	if (radians == 0.)
		return *this ;
   const scalar c = cos(radians) ;
   const scalar s = sin(radians) ;
   scalar t ;
   for (int i = 0 ; i < 4 ; i++) {
	   t = xform[i][0] ;
	   xform[i][0] = t*c + xform[i][2] * s ;
	   xform[i][2] = xform[i][2] * c - t*s ;
	   }
   return *this ;
   }

// From Graphics Gems I, p478
Transform& Transform::rotateZ(scalar radians) {
	if (radians == 0.)
		return *this ;
   const scalar c = cos(radians) ;
   const scalar s = sin(radians) ;
   scalar t ;
   for (int i = 0 ; i < 4 ; i++) {
	   t = xform[i][0] ;
	   xform[i][0] = t*c - xform[i][1] * s ;
	   xform[i][1] = t*s + xform[i][1] * c ;
	   }
   return *this ;
   }

/** -----------------------------------------------------------
 *   Set a transform matrix given rotation vectors, scale vector,
 *   and a translation vector.
 *   Use this routine to transform a figure from canonical form
 *   to an arbitrary position and orientation. The canonical figure
 *   is scaled and rotated then translated to the desired position.
 *   The scale multiplies the "size" of the figure (usually unity) to
 *   the desired size (independently in x, y, z, plus a "global" scale).
 *   Rotation turns the axes of the figure away from the world axes.
 *   Translation moves the figure away from the origin.
 *   rx, ry, and rz should be mutually perpendicular else ????
 *   (ref: Foley & Van Dam)
 **/
Transform& Transform::set(Direction const& rx,
                          Direction const& ry,
                          Direction const& rz,
                          Vector4 const& s,
                          Position const& t) {
   scalar a, b, c, d ;
   Position lastRow ;

   a = s.x ; b = s.y ; c = s.z ;

   // The following is equivalent to (S x R) x T
   // where each is a sparse 4x4 matrix.
   xform[0][0] = rx.x * a ;
   xform[1][0] = rx.y * b ;
   xform[2][0] = rx.z * c ;

   xform[0][1] = ry.x * a ;
   xform[1][1] = ry.y * b ;
   xform[2][1] = ry.z * c ;

   xform[0][2] = rz.x * a ;
   xform[1][2] = rz.y * b ;
   xform[2][2] = rz.z * c ;

   d = s.w ;
   if (d != 0)
      d = 1/d ;

   xform[3][0] = t.x * d ;
   xform[3][1] = t.y * d ;
   xform[3][2] = t.z * d ;

   xform[0][3] = xform[1][3] = xform[2][3] = 0 ;
   xform[3][3] = d ;

   return *this ;
   }

/*------------------------------------------------------------
 * Set the elements of transform matrix from an axis of rotation
 * and the sin and cosine of the rotation angle.
 * This routine isn't intended for general use but rather as
 * code common to the next two functions.
 *   (ref. Rogers & Adams p55)
 */
void setElements(Transform& mx, Direction const& axis,
                 scalar sinTheta, scalar cosTheta) {
   const scalar oneMinusCos = 1 - cosTheta ;

   scalar sq ;
   scalar xy = axis.x*axis.y ;
   scalar xz = axis.x*axis.z ;
   scalar yz = axis.y*axis.z ;

   sq = axis.x*axis.x ;
   mx.xform[0][0] = sq + (1-sq)*cosTheta ;
   mx.xform[0][1] = xy*oneMinusCos + axis.z*sinTheta ;
   mx.xform[0][2] = xz*oneMinusCos - axis.y*sinTheta ;
   mx.xform[0][3] = 0 ;

   sq = axis.y*axis.y ;
   mx.xform[1][0] = xy*oneMinusCos - axis.z*sinTheta ;
   mx.xform[1][1] = sq + (1-sq)*cosTheta ;
   mx.xform[1][2] = yz*oneMinusCos + axis.x*sinTheta ;
   mx.xform[1][3] = 0 ;

   sq = axis.z*axis.z ;
   mx.xform[2][0] = xz*oneMinusCos + axis.y*sinTheta ;
   mx.xform[2][1] = yz*oneMinusCos - axis.x*sinTheta ;
   mx.xform[2][2] = sq + (1-sq)*cosTheta ;
   mx.xform[2][3] = 0 ;

   mx.xform[3][0] =
   mx.xform[3][1] =
   mx.xform[3][2] = 0 ;
   mx.xform[3][3] = 1 ;
   }


/** -----------------------------------------------------------
 * Set a rotation transform matrix from an axis of rotation and
 * an angle of rotation.
 * (ref: Haines)
 **/
Transform& Transform::setRotate(Direction const& axis,
                                scalar radians) {
   const scalar sinTheta = sin(radians) ;
   const scalar cosTheta = cos(radians) ;

   setElements(*this, axis, sinTheta, cosTheta) ;
   return *this ;
   }

/** -----------------------------------------------------------
 * Set a rotation transform matrix that will rotate one
 * direction vector into another. (This rotates about an axis
 * perpendicular to both vectors and may introduce undesirable
 * rotations about one of the vectors. See setRotateGimbal().)
 * (Ref: Rogers & Adams)
 **/
Transform& Transform::setRotate(Direction const& d1, Direction const& d2) {
   Vector3 axis(d1.cross(d2)) ; // We need length, use Vector3
   scalar sinTheta = axis.norm() ;
   scalar cosTheta = d1.dot(d2) ;

   setElements(*this, axis, sinTheta, cosTheta) ;
   return *this ;
   }

/** -----------------------------------------------------------
 *    Set a rotation transform which will rotate one direction
 * vector into another via gimbal-type movements. This can
 * be used to change camera orientation without introducing
 * rotations about its viewing axis. Rotation is about its
 * own horizontal and vertical axes.
 *    First, find the normalized projections of d1 and d2
 * onto the xz plane.
 *    Rotate d1 into proj(d1) about an axis parallel to the xz
 * plane and perpendicular to d1 - the local x axis. This
 * rotates the local y axis into the vertical.
 *    Then rotate proj(d1) into proj(d2) about an axis perpendicular
 * to both proj(d1) and proj(d2) - the local (now vertical) y axis.
 * This rotates the local horizontal axis, too.
 *    Then rotate proj(d2) into d2 about an axis parallel to the xz
 * plane and perpendicular to d2 - the local horizontal axis again.
 *    If the projection of the first direction vector degenerates to
 * a point (ie, proj(0,1,0)), use (0,0,-1) instead. The local x- and
 * y-axes are therefore defined (maybe wrong, but defined).
 *    If the projection of the second vector is degenerate, force its
 * projection to (0,0,-1). This way, we can carry the local x- and y-
 * axes along with the rotations.
 *    If both projections are degenerate, the rotations will go from
 * the y axis to the z axis back to the y axis - the transform will be
 * an identity matrix.
 * (ref: WAL)
 **/
Transform& Transform::setRotateGimbal(Direction const& d1, Direction const& d2) {
   Direction pr_d1(d1), pr_d2(d2) ;
   Transform m1, m2, m3, m4 ;

   // Project d1 onto the xz plane.
   pr_d1.y = 0 ;
   // If pr_d1 is not degenerate, rotate d1 into pr_d1.
   // Otherwise, use d1 instead of its projection
   if (!pr_d1.len()) {
      pr_d1.x = pr_d1.y = 0 ;
      pr_d1.z = -1 ;
      }

   pr_d1.norm() ;
   m1.setRotate(d1, pr_d1) ;

   // Project d2 onto the xz plane.
   pr_d2.y = 0 ;

   // If pr_d2 is not degenerate, rotate pr_d2 into d2.
   // Otherwise, rotate (0,0,-1) into d2.
   if (!pr_d2.len()) {
       pr_d2.x = pr_d2.y = 0 ;
       pr_d2.z = -1 ;
       }

   pr_d2.norm() ;
   m3.setRotate(pr_d2, d2) ;

   // Rotate pr_d1 into pr_d2.
   // If pr_d1 == -pr_d2, force rotation about y
   scalar d(pr_d1.dot(pr_d2)) ;
   if (d == -1)
      m2.rotateY(PI) ;
   else
      m2.setRotate(pr_d1, pr_d2) ;

   // Concatenate rotations
   *this = m1   // d1 to pr_d1
         * m2   // pr_d1 to pr_d2
         * m3 ; // pr_d2 to d2

   return *this ;
   }

/*--------------------------------------------------------
 * Multiply two transform matrices.
 */

Transform Transform::operator*(Transform const& mx) const {
   Transform mr ;
   for (int i = 0 ; i < 4 ; i++)
      for (int j = 0 ; j < 4 ; j++ )
         mr.xform[i][j] = row(i).dot(mx.col(j)) ;
   return mr ;
   }

Transform& Transform::operator*=(Transform const& mx) {
   *this = *this * mx ;
   return *this ;
   }

/*--------------------------------------------------------
 * Add two transform matrices.
 */

Transform Transform::operator+(Transform const& mx) const {
   Transform mr ;
   for (int i = 0 ; i < 4 ; i++)
      for (int j = 0 ; j < 4 ; j++ )
         mr.xform[i][j] = xform[i][j] + mx.xform[i][j] ;
   return mr ;
   }

Transform& Transform::operator+=(Transform const& mx) {
   *this = *this + mx ;
   return *this ;
   }

Transform Transform::operator*(scalar const& s) const {
   Transform mr ;
   for (int i = 0 ; i < 4 ; i++)
      for (int j = 0 ; j < 4 ; j++ )
         mr.xform[i][j] = s * xform[i][j] ;
   return mr ;
   }

Transform& Transform::operator*=(scalar const& s) {
   *this = *this * s ;
   return *this ;
   }

Transform operator*(scalar const& s, Transform const& mx) {
   return mx * s;
   }


Transform Transform::transpose() const {
   return (Transform(col(0), col(1), col(2), col(3))) ;
   }



/*--------------------------------------------------------
   Matrix Inversion

   Source: Graphics Gems II, Arvo

*/

Transform Transform::inverse() const {
   scalar det_1, pos, neg, temp ;
   Transform inv ;

#define ACCUMULATE  \
   if (temp >= 0.)  \
      pos += temp ; \
   else             \
      neg += temp ; \

   pos = neg = 0. ;
   temp = xform[0][0] * xform[1][1] * xform[2][2] ;
   ACCUMULATE
   temp = xform[0][1] * xform[1][2] * xform[2][0] ;
   ACCUMULATE
   temp = xform[0][2] * xform[1][0] * xform[2][1] ;
   ACCUMULATE
   temp = - xform[0][2] * xform[1][1] * xform[2][0] ;
   ACCUMULATE
   temp = - xform[0][1] * xform[1][0] * xform[2][2] ;
   ACCUMULATE
   temp = - xform[0][0] * xform[1][2] * xform[2][1] ;
   ACCUMULATE
   det_1 = pos + neg ;

   temp = det_1 / (pos - neg) ;

   det_1 = 1. / det_1 ;

   inv.xform[0][0] =   (xform[1][1] * xform[2][2] -
                        xform[1][2] * xform[2][1])
                     * det_1 ;
   inv.xform[1][0] = - (xform[1][0] * xform[2][2] -
                        xform[1][2] * xform[2][0])
                     * det_1 ;
   inv.xform[2][0] =   (xform[1][0] * xform[2][1] -
                        xform[1][1] * xform[2][0])
                     * det_1 ;
   inv.xform[0][1] = - (xform[0][1] * xform[2][2] -
                        xform[0][2] * xform[2][1])
                     * det_1 ;
   inv.xform[1][1] =   (xform[0][0] * xform[2][2] -
                        xform[0][2] * xform[2][0])
                     * det_1 ;
   inv.xform[2][1] = - (xform[0][0] * xform[2][1] -
                        xform[0][1] * xform[2][0])
                     * det_1 ;
   inv.xform[0][2] =   (xform[0][1] * xform[1][2] -
                        xform[0][2] * xform[1][1])
                     * det_1 ;
   inv.xform[1][2] = - (xform[0][0] * xform[1][2] -
                        xform[0][2] * xform[1][0])
                     * det_1 ;
   inv.xform[2][2] =   (xform[0][0] * xform[1][1] -
                        xform[0][1] * xform[1][0])
                     * det_1 ;

   inv.xform[3][0] = - (xform[3][0] * inv.xform[0][0] +
                        xform[3][1] * inv.xform[1][0] +
                        xform[3][2] * inv.xform[2][0]) ;
   inv.xform[3][1] = - (xform[3][0] * inv.xform[0][1] +
                        xform[3][1] * inv.xform[1][1] +
                        xform[3][2] * inv.xform[2][1]) ;
   inv.xform[3][2] = - (xform[3][0] * inv.xform[0][2] +
                        xform[3][1] * inv.xform[1][2] +
                        xform[3][2] * inv.xform[2][2]) ;

   inv.xform[0][3] = inv.xform[1][3] = inv.xform[2][3] = 0. ;
   inv.xform[3][3] = 1. ;

   return inv ;
   }


