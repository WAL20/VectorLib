/* -------- Vector3.cpp -----------

   3D Vector Class Library
   Copyright 1994-2008,2021 Bill Leonard

   The author will not be liable for any bug, error, omission,
   defect, deficiency, or nonconformity in this software. The author
   also disclaims all implied warranties, including without limitation
   warranties of merchantability, performance, and fitness for a
   particular purpose. This software is provided "as is" and the user
   assumes the entire risk as to its quality and performance.


*/

#include <vector.h>

Vector3::Vector3()
   : x(0), y(0), z(0) {
   }

Vector3::Vector3(scalar a, scalar b, scalar c)
   : x(a), y(b), z(c) {
   }

Vector3::Vector3(Vector3 const& v)
   : x(v.x), y(v.y), z(v.z) {
   }

Vector3::Vector3(Vector2 const& v)
   : x(v.x), y(v.y), z(0) {
   }

Vector3& Vector3::set(scalar a, scalar b, scalar c) {
   x = a ;
   y = b ;
   z = c ;
   return *this ;
   }

scalar Vector3::len() const {
   return sqrt(x*x + y*y + z*z) ;
   }

scalar Vector3::norm() {
   scalar l = len() ;
   *this /=l ;
   return l ;
   }

Vector3::operator Position() const {
   return Position(x,y,z) ;
   }

Vector3::operator Direction() const {
   return Direction(x,y,z) ;
   }

Vector3 Vector3::operator+(Vector3 const& v) const {
   return Vector3(x+v.x, y+v.y, z+v.z) ;
   }

Vector3& Vector3::operator+=(Vector3 const& v) {
   x += v.x ;
   y += v.y ;
   z += v.z ;
   return *this ;
   }

Vector3 Vector3::operator-(Vector3 const& v) const {
   return Vector3(x-v.x, y-v.y, z-v.z) ;
   }

Vector3& Vector3::operator-=(Vector3 const& v) {
   x -= v.x ;
   y -= v.y ;
   z -= v.z ;
   return *this ;
   }

Vector3 Vector3::operator-() const {
   return Vector3(-x, -y, -z) ;
   }

Vector3 Vector3::operator*(scalar s) const {
   return Vector3((s*x), (s*y), (s*z)) ;
   }

Vector3& Vector3::operator*=(scalar s) {
   x *= s ;
   y *= s ;
   z *= s ;
   return *this ;
   }

Vector3 Vector3::operator/(scalar s) const {
   if (s != 0.0) {
      return Vector3((x/s), (y/s), (z/s)) ;
      }
   else
      return *this ;
   }

Vector3& Vector3::operator/=(scalar s) {
   if (s != 0.0) {
      x /= s ;
      y /= s ;
      z /= s ;
      }
   return *this ;
   }

scalar Vector3::dot(Vector3 const& v) const {
   return x*v.x + y*v.y + z*v.z ;
   }

Vector3 Vector3::cross(Vector3 const& v) const
   { return Vector3(y*v.z - z*v.y,
                    z*v.x - x*v.z,
                    x*v.y - y*v.x) ; }

scalar Vector3::dot(Direction const& d) const {
   return x*d.x + y*d.y + z*d.z ;
   }

Vector3 Vector3::operator *(Vector3 const& v) const {
    return Vector3(x*v.x, y*v.y, z*v.z) ;
   }

Vector3& Vector3::operator *=(Vector3 const& v) {
   x*=v.x ;
   y*=v.y ;
   z*=v.z ;
   return *this ;
   }

Vector3 operator*(scalar s, Vector3 const& v)
   {return Vector3((s*v.x), (s*v.y), (s*v.z)) ; }

scalar Vector3::maxCoord() const {
	return (MAX(ABS(x),MAX(ABS(y),ABS(z))));
   }

scalar Vector3::minCoord() const {
	return (MIN(ABS(x),MIN(ABS(y),ABS(z))));
   }

Direction Vector3::majorAxis() const {
	Direction axis;
	if (ABS(x) >= ABS(y))
		if (ABS(x) >= ABS(z))
			axis = XAXIS;
		else
			axis = ZAXIS;
	else
		if (ABS(y) >= ABS(z))
			axis = YAXIS;
		else
			axis = ZAXIS;
	return axis;
}

Direction Vector3::minorAxis() const {
	Direction axis;
	if (ABS(x) <= ABS(y))
		if (ABS(x) <= ABS(z))
			axis = XAXIS;
		else
			axis = ZAXIS;
	else
		if (ABS(y) <= ABS(z))
			axis = YAXIS;
		else
			axis = ZAXIS;
	return axis;
}

Position::Position()
   : x(0), y(0), z(0) {
   }

Position::Position(scalar a, scalar b, scalar c)
   : x(a), y(b), z(c) {
   }

Position& Position::set(scalar a, scalar b, scalar c) {
   x = a ;
   y = b ;
   z = c ;
   return *this ;
   }

Vector3 Vector(Position const& p) {
   return Vector3(p.x,p.y,p.z) ;
   }

Position Position::operator + (Vector3 const& v) const {
   return Position(x + v.x, y + v.y, z + v.z) ;
   }

Position& Position::operator += (Vector3 const& v) {
   x += v.x ;
   y += v.y ;
   z += v.z ;
   return *this ;
   }

Position Position::operator - (Vector3 const& v) const {
   return Position(x - v.x, y - v.y, z - v.z) ;
   }

Vector3 Position::operator - (Position const& p) const {
   return Vector3(x - p.x, y - p.y, z - p.z) ;
   }

Position& Position::operator -= (Vector3 const& v) {
   x -= v.x ;
   y -= v.y ;
   z -= v.z ;
   return *this ;
   }

scalar Position::dot(Direction const& d) const {
   return x*d.x + y*d.y + z*d.z ;
   }

Position  Position::operator *  (scalar s) const {
   return Position(s * x, s * y, s * z) ;
   }

Position Position::operator/(scalar s) const {
   if (s != 0.0) {
      return Position((x/s), (y/s), (z/s)) ;
      }
   else
      return *this ;
   }

Position operator* (scalar s, Position const& p) {
   return Position(s * p.x, s * p.y, s * p.z) ;
   }

scalar Position::maxCoord() const {
	return (MAX(ABS(x),MAX(ABS(y),ABS(z))));
   }

scalar Position::minCoord() const {
	return (MIN(ABS(x),MIN(ABS(y),ABS(z))));
   }

Direction Position::majorAxis() const {
	Direction axis;
	if (ABS(x) >= ABS(y))
		if (ABS(x) >= ABS(z))
			axis = XAXIS;
		else
			axis = ZAXIS;
	else
		if (ABS(y) >= ABS(z))
			axis = YAXIS;
		else
			axis = ZAXIS;
	return axis;
}

Direction Position::minorAxis() const {
	Direction axis;
	if (ABS(x) <= ABS(y))
		if (ABS(x) <= ABS(z))
			axis = XAXIS;
		else
			axis = ZAXIS;
	else
		if (ABS(y) <= ABS(z))
			axis = YAXIS;
		else
			axis = ZAXIS;
	return axis;
}

Direction::Direction()
   : x(0), y(0), z(0) {
   }

Direction::Direction(scalar a, scalar b, scalar c)
   : x(a), y(b), z(c) {
   norm() ;
   }

Vector3 Vector(const Direction& d) {
   return Vector3(d.x,d.y,d.z) ;
   }

Direction& Direction::operator += (Direction const& d) {
   x += d.x ;
   y += d.y ;
   z += d.z ;
   norm() ;
   return *this ;
   }

Direction Direction::operator + (Direction const& d) const {
   return Direction (x + d.x, y + d.y, z + d.z) ;
   }

Direction& Direction::operator -= (Direction const& d) {
   x -= d.x ;
   y -= d.y ;
   z -= d.z ;
   norm() ;
   return *this ;
   }

Direction Direction::operator - (Direction const& d) const {
   return Direction (x - d.x, y - d.y, z - d.z) ;
   }

Direction Direction::operator- () const {
   return Direction(-x, -y, -z) ;
   }

Direction& Direction::set(scalar a, scalar b, scalar c) {
   x = a ;
   y = b ;
   z = c ;
   norm() ;
   return *this ;
   }

scalar Direction::norm() {
   scalar l = sqrt(x*x + y*y + z*z) ;
   if ((l != 0) && (l != 1.)) {
      x /= l ;
      y /= l ;
      z /= l ;
      }
   return l;
   }

scalar Direction::dot(Direction const& d) const {
   return x*d.x + y*d.y + z*d.z ;
   }

Vector3 Direction::cross(Direction const& d) const
   { return Vector3(y*d.z - z*d.y,
                    z*d.x - x*d.z,
                    x*d.y - y*d.x) ; }

scalar Direction::dot(Vector3 const& v) const {
   return x*v.x + y*v.y + z*v.z ;
   }

scalar Direction::minCoord() const {
	return MIN(ABS(x),MIN(ABS(y),ABS(z)));
   }

scalar Direction::maxCoord() const {
	return MAX(ABS(x),MAX(ABS(y),ABS(z)));
   }

Direction Direction::majorAxis() const {
	Direction axis;
	if (ABS(x) >= ABS(y))
		if (ABS(x) >= ABS(z))
			axis = XAXIS;
		else
			axis = ZAXIS;
	else
		if (ABS(y) >= ABS(z))
			axis = YAXIS;
		else
			axis = ZAXIS;
	return axis;
}

Direction Direction::minorAxis() const {
	Direction axis;
	if (ABS(x) <= ABS(y))
		if (ABS(x) <= ABS(z))
			axis = XAXIS;
		else
			axis = ZAXIS;
	else
		if (ABS(y) <= ABS(z))
			axis = YAXIS;
		else
			axis = ZAXIS;
	return axis;
}

scalar Direction::len() const {
   return sqrt(x*x + y*y + z*z) ;
   }

Vector3 operator* (scalar s, Direction const& d) {
   return Vector3(s*d.x, s*d.y, s*d.z) ;
   }

Vector3 Direction::operator * (scalar s) const {
   return Vector3(s*x, s*y, s*z) ;
   }

Vector3 Direction::operator / (scalar s) const {
   if (s != 0.0) {
	   return Vector3(x/s, y/s, z/s) ;
      }
   else
      return Vector3(x,y,z) ;
   }

/**--------------------------------------------------------
 * Calculate the angle between two vectors.
 * The angle is the arctangent of:
 *    the vector magnitude of:
 *       the cross product of d1 and d2
 *    divided by:
 *       the dot product of d1 and d2.
 *
 * ATAN2 takes 2 arguments so that we avoid division.
 * Since the vectors must be normalized, the parameters
 * are given as direction vectors.
 **/
scalar Direction::angle(Direction const& d2) const {
   Vector3 v3 ;

   v3 = this->cross(d2) ; // We need the length, use ordinary vector
   return (atan2(v3.len(),dot(d2))) ;
   }

scalar det(Vector3 const& v1,	//	| v1.x v2.x v3.x |
		   Vector3 const& v2,	//	| v1.y v2.y v3.y |
		   Vector3 const& v3) { //	| v1.z v2.z v3.z |

	scalar d = v1.x * (v2.y * v3.z - v3.y * v2.z)
			 - v2.x * (v1.y * v3.z - v3.y * v1.z)
			 + v3.x * (v1.y * v2.z - v2.y * v1.z) ;

	return d ;
	}

