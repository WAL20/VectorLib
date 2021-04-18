/*
  Vector2.cpp 2D Vector Class
   Copyright 1994-2008, Bill Leonard

   The author will not be liable for any bug, error, omission,
   defect, deficiency, or nonconformity in this software. The author
   also disclaims all implied warranties, including without limitation
   warranties of merchantability, performance, and fitness for a
   particular purpose. This software is provided "as is" and the user
   assumes the entire risk as to its quality and performance.

 */

#include <Vector.h>

Vector2::Vector2() {
   x = y = 0 ;
   }

Vector2::Vector2(scalar sx, scalar sy) {
   x = sx ; y = sy ;
   }

Vector2& Vector2::set(scalar sx, scalar sy) {
   x = sx ; y = sy ;
   return *this ;
   }

Vector2 Vector2::operator+(Vector2 const& v) const {
   return Vector2(x+v.x, y+v.y) ;
   }

Vector2& Vector2::operator+=(Vector2 const& v) {
   x += v.x ;
   y += v.y ;
   return *this ;
   }

Vector2 Vector2::operator-(Vector2 const& v) const {
   return Vector2(x-v.x, y-v.y) ;
   }

Vector2& Vector2::operator-=(Vector2 const& v) {
   x -= v.x ;
   y -= v.y ;
   return *this ;
   }

Vector2 Vector2::operator-() const {
   return Vector2(-x, -y) ;
   }

Vector2 Vector2::operator*(scalar s) const {
   return Vector2((s*x), (s*y)) ;
   }

Vector2& Vector2::operator*=(scalar s) {
   x *= s ;
   y *= s ;
   return *this ;
   }

Vector2 Vector2::operator/(scalar s) const {
   if (s != 0.0) {
      return Vector2((x/s), (y/s)) ;
      }
   else
      return *this ;
   }

Vector2& Vector2::operator/=(scalar s) {
   if (s != 0.0) {
      x /= s ;
      y /= s ;
      }
   return *this ;
   }

scalar Vector2::dot(Vector2 const& v) const {
   return x*v.x + y*v.y  ;
   }

Vector2 Vector2::operator *(Vector2 const& v) const {
    return Vector2(x*v.x, y*v.y) ;
   }

Vector2 Vector2::operator *=(Vector2 const& v) {
   x*=v.x ;
   y*=v.y ;
   return *this ;
   }

Vector2 operator*(scalar s, Vector2 const& v) {
   return Vector2((s*v.x), (s*v.y)) ;
   }

scalar Vector2::maxCoord() const {
   return MAX(ABS(x),ABS(y));
   }

scalar Vector2::minCoord() const {
   return MIN(ABS(x),ABS(y));
   }
