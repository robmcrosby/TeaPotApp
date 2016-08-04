//
//  Vector.h
//  TeaPot
//
//  Created by Robert Crosby on 8/4/16.
//  Copyright © 2016 Robert Crosby. All rights reserved.
//

#ifndef Vector_h
#define Vector_h

#include <cmath>
#include <iostream>
#include <string>

#define CHAR_BUFF_SIZE 128
#define SWAP_ROWS(a, b) {float *tmp = a; a = b; b = tmp;}


const float Pi = 4 * std::atan(1.0f);
const float TwoPi = 2 * Pi;
const float RadToDeg = 180.0f / Pi;
const float DegToRad = Pi / 180.0f;

template <typename T>
struct Vector2
{
  Vector2(): x(0), y(0) {}
  Vector2(T x, T y): x(x), y(y) {}
  Vector2(const std::string &str): x(0), y(0) {parse(str);}
  
  template <typename I>
  Vector2(const Vector2<I> &v): x(v.x), y(v.y) {}
  
  template <typename I>
  void operator=(const Vector2<I> v) {x = v.x; y = v.y;}
  
  Vector2 yx() const {return Vector2(y, x);}
  T dot(const Vector2& v) const {return x * v.x + y * v.y;}
  Vector2 max(const Vector2 &v) const
  {
    Vector2 vec;
    vec.x = x < v.x ? v.x : x;
    vec.y = y < v.y ? v.y : y;
    return vec;
  }
  Vector2 min(const Vector2 &v) const
  {
    Vector2 vec;
    vec.x = x < v.x ? x : v.x;
    vec.y = y < v.y ? y : v.y;
    return vec;
  }
  Vector2 clamp(const Vector2 &v1, const Vector2 &v2) const {return min(v1.max(v2)).max(v1.min(v2));}
  
  static Vector2 Max(const Vector2 &v1, const Vector2 &v2) {return v1.max(v2);}
  static Vector2 Min(const Vector2 &v1, const Vector2 &v2) {return v1.min(v2);}
  static Vector2 Clamp(const Vector2 &v, const Vector2 &v1, const Vector2 &v2) {return v.clamp(v1, v2);}
  
  Vector2 mod() const
  {
    Vector2 vec;
    vec.x = x<0 ? 1+(x-(long)x) : 1<x ? x-(long)x : x;
    vec.y = y<0 ? 1+(y-(long)y) : 1<y ? y-(long)y : y;
    return vec;
  }
  T* ptr() {return &x;}
  const T* ptr() const {return &x;}
  
  T& operator[](int index) {return (&x)[index];}
  const T& operator[](int index) const {return (&x)[index];}
  
  Vector2 operator+(const Vector2& v) const {return Vector2(x + v.x, y + v.y);}
  Vector2 operator-(const Vector2& v) const {return Vector2(x - v.x, y - v.y);}
  Vector2 operator*(const Vector2& v) const {return Vector2(x * v.x, y * v.y);}
  Vector2 operator/(const Vector2& v) const {return Vector2(v.x?x/v.x:v.x, v.y?y/v.y:v.y);}
  
  Vector2 operator*(T s) const {return Vector2(x * s, y * s);}
  Vector2 operator/(T s) const
  {
    if (s)
      return Vector2(x / s, y / s);
    std::cerr << "divide by zero" << std::endl;
    return *this;
  }
  
  void operator+=(const Vector2& v) {*this = *this + v;}
  void operator-=(const Vector2& v) {*this = *this - v;}
  void operator*=(const Vector2& v) {*this = *this * v;}
  void operator/=(const Vector2& v) {*this = *this / v;}
  
  void operator*=(T s) {*this = *this * s;}
  void operator/=(T s) {*this = *this / s;}
  
  T lengthSquared()    const {return x * x + y * y;}
  T length()           const {return sqrt(lengthSquared());}
  Vector2 normalized() const {return *this / length();}
  
  void normalize() {this = *this / length();}
  
  bool operator==(const Vector2& v) const {return x == v.x && y == v.y;}
  bool operator!=(const Vector2& v) const {return x != v.x || y != v.y;}
  bool operator<=(const Vector2& v) const {return x <= v.x && y <= v.y;}
  bool operator>=(const Vector2& v) const {return v <= *this;}
  
  bool operator<(const Vector2& v) const {return x < v.x && y < v.y;}
  bool operator>(const Vector2& v) const {return v < *this;}
  
  Vector2 lerp(T t, const Vector2& v) const {return *this * (1 - t) + v * t;}
  
  T distanceSquared(const Vector2& v) const {return (*this - v).LengthSquared();}
  T distance(const Vector2& v) const {return (*this - v).Length();}
  
  bool parse(const std::string &str)
  {
    float fx = 0.0f, fy = 0.0f;
    int res = sscanf(str.c_str(), " %f , %f", &fx, &fy);
    
    x = (T)fx;
    y = (T)fy;
    return res = 2;
  }
  
  friend std::ostream &operator<<(std::ostream &os, const Vector2 &v) {return os << "<" << v.x << ", " << v.y << ">";}
  
  static std::string ToString(const Vector2<int> &v)
  {
    char buffer[CHAR_BUFF_SIZE];
    snprintf(buffer, CHAR_BUFF_SIZE, "%i,%i", v.x, v.y);
    return std::string(buffer);
  }
  
  static bool IsPowerOfTwo(T val)
  {
    unsigned int iVal = val;
    return !(val - (T)iVal) && (iVal != 0) && !(iVal & (iVal - 1));
  }
  bool isPowerOfTwo() const {return IsPowerOfTwo(x) && IsPowerOfTwo(y);}
  
  static Vector2 Random() {return Vector2((T)rand(), (T)rand());}
  static Vector2 RandMax() {return Vector2((T)RAND_MAX, (T)RAND_MAX);}
  
  union {T x; T r; T w; T start;};
  union {T y; T g; T h; T end;};
};


template <typename T>
struct Vector3 {
  Vector3(): x(0), y(0), z(0) {}
  Vector3(T x, T y, T z): x(x), y(y), z(z) {}
  Vector3(const Vector2<T> &v, T z): x(v.x), y(v.y), z(z) {}
  Vector3(T x, const Vector2<T> &v): x(x), y(v.y), z(v.z) {}
  Vector3(const std::string &str): x(0), y(0), z(0) {parse(str);}
  
  template <typename I>
  Vector3(const Vector3<I> &v): x(v.x), y(v.y), z(v.z) {}
  
  template <typename I>
  void operator=(const Vector3<I> v) {x = v.x; y = v.y; z = v.z;}
  
  Vector2<T> xy() const {return Vector2<T>(x, y);}
  Vector2<T> yx() const {return Vector2<T>(y, x);}
  Vector3 zyx() const {return Vector3(z, y, x);}
  
  T dot(const Vector3& v) const {return x * v.x + y * v.y + z * v.z;}
  Vector3 cross(const Vector3& v) const {return Vector3(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x);}
  Vector3 max(const Vector3 &v) const
  {
    Vector3 vec;
    vec.x = x < v.x ? v.x : x;
    vec.y = y < v.y ? v.y : y;
    vec.z = z < v.z ? v.z : z;
    return vec;
  }
  Vector3 min(const Vector3 &v) const
  {
    Vector3 vec;
    vec.x = x < v.x ? x : v.x;
    vec.y = y < v.y ? y : v.y;
    vec.z = z < v.z ? z : v.z;
    return vec;
  }
  Vector3 clamp(const Vector3 &v1, const Vector3 &v2) const {return min(v1.max(v2)).max(v1.min(v2));}
  
  static Vector3 Max(const Vector3 &v1, const Vector3 &v2) {return v1.max(v2);}
  static Vector3 Min(const Vector3 &v1, const Vector3 &v2) {return v1.min(v2);}
  static Vector3 Clamp(const Vector3 &v, const Vector3 &v1, const Vector3 &v2) {return v.clamp(v1, v2);}
  
  T* ptr() {return &x;}
  const T* ptr() const {return &x;}
  
  T& operator[](int index) {return (&x)[index];}
  const T& operator[](int index) const {return (&x)[index];}
  
  Vector3 operator+(const Vector3& v) const {return Vector3(x + v.x, y + v.y, z + v.z);}
  Vector3 operator-(const Vector3& v) const {return Vector3(x - v.x, y - v.y, z - v.z);}
  Vector3 operator*(const Vector3& v) const {return Vector3(x * v.x, y * v.y, z * v.z);}
  Vector3 operator/(const Vector3& v) const {return Vector3(v.x?x/v.x:v.x, v.y?y/v.y:v.y, v.z?y/v.z:v.z);}
  
  Vector3 operator*(T s) const {return Vector3(x * s, y * s, z * s);}
  Vector3 operator/(T s) const
  {
    if (s)
      return Vector3(x / s, y / s, z / s);
    std::cerr << "divide by zero" << std::endl;
    return *this;
  }
  Vector3 operator-() const {return Vector3(-x, -y, -z);}
  
  void operator+=(const Vector3& v) {*this = *this + v;}
  void operator-=(const Vector3& v) {*this = *this - v;}
  void operator*=(const Vector3& v) {*this = *this * v;}
  void operator/=(const Vector3& v) {*this = *this / v;}
  
  void operator*=(T s) {*this = *this * s;}
  void operator/=(T s) {*this = *this / s;}
  
  T lengthSquared()    const {return x * x + y * y + z * z;}
  T length()           const {return sqrt(lengthSquared());}
  Vector3 normalized() const {return *this / length();}
  
  void normalize() {*this /= length();}
  
  bool operator==(const Vector3& v) const {return x == v.x && y == v.y && z == v.z;}
  bool operator!=(const Vector3& v) const {return x != v.x || y != v.y || z != v.z;}
  bool operator<=(const Vector3& v) const {return x <= v.x && y <= v.y && z <= v.z;}
  bool operator>=(const Vector3& v) const {return v <= *this;}
  
  bool operator<(const Vector3& v) const {return x < v.x && y < v.y && z < v.z;}
  bool operator>(const Vector3& v) const {return v < *this;}
  
  Vector3 lerp(T t, const Vector3& v) const {return *this * (1 - t) + v * t;}
  
  bool parse(const std::string &str)
  {
    float fx = 0.0f, fy = 0.0f, fz = 0.0f;
    int res = sscanf(str.c_str(), " %f , %f , %f", &fx, &fy, &fz);
    
    x = (T)fx;
    y = (T)fy;
    z = (T)fz;
    return res = 3;
  }
  
  static Vector3 Random() {return Vector3((T)rand(), (T)rand(), (T)rand());}
  static Vector3 RandMax() {return Vector3((T)RAND_MAX, (T)RAND_MAX, (T)RAND_MAX);}
  
  friend std::ostream &operator<<(std::ostream &os, const Vector3 &v)
  {
    return os << "<" << v.x << ", " << v.y << ", " << v.z << ">";
  }
  
  union {T x; T r;};
  union {T y; T g;};
  union {T z; T b;};
};

template <typename T>
struct Vector4 {
  Vector4(): x(0), y(0), z(0), w(0) {}
  Vector4(T x, T y, T z, T w): x(x), y(y), z(z), w(w) {}
  Vector4(const std::string &str): x(0), y(0), z(0), w(0) {parse(str);}
  
  Vector4(const Vector2<T> &v, T z, T w): x(v.x), y(v.y), z(z), w(w) {}
  Vector4(T x, const Vector2<T> &v, T w): x(x), y(v.y), z(v.z), w(w) {}
  Vector4(T x, T y, const Vector2<T> &v): x(x), y(y), z(v.z), w(v.w) {}
  Vector4(const Vector2<T> &v1, const Vector2<T> &v2): x(v1.x), y(v1.y), z(v2.x), w(v2.y) {}
  
  Vector4(const Vector3<T> &v, T w): x(v.x), y(v.y), z(v.z), w(w) {}
  Vector4(T x, const Vector3<T> &v): x(x), y(v.x), z(v.y), w(v.z) {}
  
  template <typename I>
  Vector4(const Vector4<I> &v): x(v.x), y(v.y), z(v.z), w(v.w) {}
  
  template <typename I>
  void operator=(const Vector4<I> v) {x = v.x; y = v.y; z = v.z; w = v.w;}
  
  Vector2<T> xy() const {return Vector2<T>(x, y);}
  Vector2<T> yx() const {return Vector2<T>(y, x);}
  Vector3<T> xyz() const {return Vector3<T>(x, y, z);}
  Vector3<T> zyx() const {return Vector3<T>(z, y, x);}
  Vector3<T> yzw() const {return Vector3<T>(y, z, w);}
  Vector4 wzyx() const {return Vector4(w, z, y, x);}
  T dot(const Vector4& v) const {return x * v.x + y * v.y + z * v.z + w * v.w;}
  
  Vector4 max(const Vector4 &v) const
  {
    Vector4 vec;
    vec.x = x < v.x ? v.x : x;
    vec.y = y < v.y ? v.y : y;
    vec.z = z < v.z ? v.z : z;
    vec.w = w < v.w ? v.w : w;
    return vec;
  }
  Vector4 min(const Vector4 &v) const
  {
    Vector4 vec;
    vec.x = x < v.x ? x : v.x;
    vec.y = y < v.y ? y : v.y;
    vec.z = z < v.z ? y : v.z;
    vec.w = w < v.w ? w : v.w;
    return vec;
  }
  Vector4 clamp(const Vector4 &v1, const Vector4 &v2) const {return min(v1.max(v2)).max(v1.min(v2));}
  
  static Vector4 Max(const Vector4 &v1, const Vector4 &v2) {return v1.max(v2);}
  static Vector4 Min(const Vector4 &v1, const Vector4 &v2) {return v1.min(v2);}
  static Vector4 Clamp(const Vector4 &v, const Vector4 &v1, const Vector4 &v2) {return v.clamp(v1, v2);}
  
  T* ptr() {return &x;}
  const T* ptr() const {return &x;}
  
  T& operator[](int index) {return (&x)[index];}
  const T& operator[](int index) const {return (&x)[index];}
  
  Vector4 operator+(const Vector4& v) const {return Vector4(x + v.x, y + v.y, z + v.z, w + v.w);}
  Vector4 operator-(const Vector4& v) const {return Vector4(x - v.x, y - v.y, z - v.z, w - v.w);}
  Vector4 operator*(const Vector4& v) const {return Vector4(x * v.x, y * v.y, z * v.z, w * v.w);}
  Vector4 operator/(const Vector4& v) const {return Vector4(v.x?x/v.x:v.x, v.y?y/v.y:v.y, v.z?z/v.z:v.z, v.w?w/v.w:v.w);}
  
  Vector4 operator*(T s) const {return Vector4(x * s, y * s, z * s, w * s);}
  Vector4 operator/(T s) const
  {
    if (s)
      return Vector4(x / s, y / s, z / s, w / s);
    std::cerr << "divide by zero" << std::endl;
    return *this;
  }
  
  void operator+=(const Vector4& v) {*this = *this + v;}
  void operator-=(const Vector4& v) {*this = *this - v;}
  void operator*=(const Vector4& v) {*this = *this * v;}
  void operator/=(const Vector4& v) {*this = *this / v;}
  
  void operator*=(T s) {*this = *this * s;}
  void operator/=(T s) {*this = *this / s;}
  
  T lengthSquared()    const {return x * x + y * y + z * z + w * w;}
  T length()           const {return sqrt(lengthSquared());}
  Vector4 normalized() const {return *this / length();}
  
  void normalize() {this = *this / length();}
  void swap(Vector4 &other)
  {
    Vector4 tmp = *this;
    *this = other;
    other = tmp;
  }
  
  bool operator==(const Vector4& v) const {return x == v.x && y == v.y && z == v.z && w == v.w;}
  bool operator!=(const Vector4& v) const {return x != v.x || y != v.y || z != v.z || w != v.w;}
  bool operator<=(const Vector4& v) const {return x <= v.x && y <= v.y && z <= v.z && w <= v.w;}
  bool operator>=(const Vector4& v) const {return v <= *this;}
  
  bool operator<(const Vector4& v) const {return x < v.x && y < v.y && z < v.z && w < v.w;}
  bool operator>(const Vector4& v) const {return v < *this;}
  
  Vector4 lerp(T t, const Vector4& v) const {return *this * (1 - t) + v * t;}
  
  bool parse(const std::string &str)
  {
    float fx = 0.0f, fy = 0.0f, fz = 0.0f, fw = 0.0f;
    int res = sscanf(str.c_str(), " %f , %f , %f , %f", &fx, &fy, &fz, &fw);
    
    x = (T)fx;
    y = (T)fy;
    z = (T)fz;
    w = (T)fw;
    return res = 4;
  }
  
  friend std::ostream &operator<<(std::ostream &os, const Vector4 &v)
  {
    return os << "<" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ">";
  }
  
  static std::string ToString(const Vector4<float> &v)
  {
    char buffer[CHAR_BUFF_SIZE];
    snprintf(buffer, CHAR_BUFF_SIZE, "%.4f,%.4f,%.4f,%.4f", v.x, v.y, v.z, v.w);
    return std::string(buffer);
  }
  
  static Vector4 Random() {return Vector4((T)rand(), (T)rand(), (T)rand(), (T)rand());}
  static Vector4 RandMax() {return Vector4((T)RAND_MAX, (T)RAND_MAX, (T)RAND_MAX, (T)RAND_MAX);}
  
  union {T x; T r;};
  union {T y; T g;};
  union {T z; T b;};
  union {T w; T a;};
};


typedef Vector2<int> ivec2;
typedef Vector3<int> ivec3;
typedef Vector4<int> ivec4;

typedef Vector2<float> vec2;
typedef Vector3<float> vec3;
typedef Vector4<float> vec4;




template <typename T>
struct Matrix2
{
  Matrix2(): x(1, 0), y(0, 1) {}
  Matrix2(const T* m)
  {
    x.x = m[0]; x.y = m[1];
    y.x = m[2]; y.y = m[3];
  }
  template <typename I>
  Matrix2(const Matrix2<I> &m): x(m.x), y(m.y) {}
  
  T determinant() const {return x.x * y.y - x.y * y.x;}
  Matrix2 inverse() const
  {
    Matrix2 m = *this;
    T det = determinant();
    if (det != static_cast<T>(0))
    {
      det = static_cast<T>(1)/det;
      m.x.x =  y.y * det;  m.x.y = -x.y * det;
      m.y.x = -y.x * det;  m.y.y =  x.x * det;
    }
    else
      std::cerr << "Cannot Invert Matrix: " << std::endl << *this;
    return m;
  }
  Matrix2 transposed() const
  {
    Matrix2 m = *this;
    m.x.y = y.x;
    m.y.x = x.y;
    return m;
  }
  
  Matrix2 scaled(T s) const
  {
    Matrix2 m = *this;
    m.x.x *= s;
    m.y.y *= s;
    return m;
  }
  template <typename I>
  Matrix2 scaled(const Vector2<I> &s) const
  {
    Matrix2 m = *this;
    m.x.x *= s.x;
    m.y.y *= s.y;
    return m;
  }
  Matrix2 operator*(const Matrix2 &m) const
  {
    Matrix2 ret;
    ret.x.x = x.x*m.x.x + y.x*m.x.y;
    ret.y.x = x.x*m.y.x + y.x*m.y.y;
    ret.x.y = x.y*m.x.x + y.y*m.x.y;
    ret.y.y = x.y*m.y.x + y.y*m.y.y;
    return ret;
  }
  template <typename I>
  Vector2<I> operator*(const Vector2<I> &b) const
  {
    Vector2<I> v;
    v.x = x.x*b.x + y.x*b.y;
    v.y = x.y*b.x + y.y*b.y;
    return v;
  }
  bool operator==(const Matrix2 &m) const {return x == m.x && y == m.y;}
  bool operator<(const Matrix2 &m) const {return x == m.x ? y < m.y : x < m.x;}
  void operator*=(const Matrix2 &m) {*this = m * *this;}
  T* ptr() {return x.ptr();}
  const T* ptr() const {return x.ptr();}
  
  Vector2<T>& operator[](int index) {return (&x)[index];}
  const Vector2<T>& operator[](int index) const {return (&x)[index];}
  
  friend std::ostream &operator<<(std::ostream &os, const Matrix2 &m)
  {
    os << "[" << m.x.x << ", " << m.y.x << "]" << std::endl;
    os << "[" << m.x.y << ", " << m.y.y << "]" << std::endl;
    return os;
  }
  
  Vector2<T> x;
  Vector2<T> y;
};

template <typename T>
struct Matrix3
{
  Matrix3(): x(1, 0, 0), y(0, 1, 0), z(0, 0, 1) {}
  Matrix3(const T* m)
  {
    x.x = m[0]; x.y = m[1]; x.z = m[2];
    y.x = m[3]; y.y = m[4]; y.z = m[5];
    z.x = m[6]; z.y = m[7]; z.z = m[8];
  }
  template <typename I>
  Matrix3(const Matrix2<I> &m): x(m.x, 0), y(m.y, 0), z(0, 0, 1) {}
  template <typename I>
  Matrix3(const Matrix3<I> &m): x(m.x), y(m.y), z(m.z) {}
  
  T determinant() const
  {
    T det = x.x * y.y * z.z;
    det +=  y.x * z.y * x.z;
    det +=  z.x * x.y * y.z;
    det -=  x.x * z.y * y.z;
    det -=  z.x * y.y * x.z;
    det -=  y.x * x.y * z.z;
    return det;
  }
  Matrix3 inverse() const
  {
    Matrix3 m = *this;
    T det = determinant();
    if (det != static_cast<T>(0))
    {
      det = static_cast<T>(1)/det;
      m.x.x = (y.y * z.z - y.z * z.y) * det;
      m.x.y = (x.z * z.y - x.y * z.z) * det;
      m.x.z = (x.y * y.z - x.z * y.y) * det;
      m.y.x = (y.z * z.x - y.x * z.z) * det;
      m.y.y = (x.x * z.z - x.z * z.x) * det;
      m.y.z = (x.z * y.x - x.x * y.z) * det;
      m.z.x = (y.x * z.y - y.y * z.x) * det;
      m.z.y = (x.y * z.x - x.x * z.y) * det;
      m.z.z = (x.x * y.y - x.y * y.x) * det;
    }
    else
      std::cerr << "Cannot Invert Matrix: " << std::endl << *this;
    return m;
  }
  Matrix3 transposed() const
  {
    Matrix3 m = *this;
    m.x.y = y.x;
    m.x.z = z.x;
    m.y.x = x.y;
    m.y.z = z.y;
    m.z.x = x.z;
    m.z.y = y.z;
    return m;
  }
  Matrix3 scaled(T s) const
  {
    Matrix3 m = *this;
    m.x.x *= s;
    m.y.y *= s;
    m.z.z *= s;
    return m;
  }
  template <typename I>
  Matrix3 scaled(const Vector3<I> &s) const
  {
    Matrix3 m = *this;
    m.x.x *= s.x;
    m.y.y *= s.y;
    m.z.z *= s.z;
    return m;
  }
  Matrix2<T> toMat2() const
  {
    Matrix2<T> m;
    m.x = x.XY();
    m.y = y.XY();
    return m;
  }
  Matrix3 operator*(const Matrix3 &m) const
  {
    Matrix3 ret;
    ret.x.x = x.x*m.x.x + y.x*m.x.y + z.x*m.x.z;
    ret.y.x = x.x*m.y.x + y.x*m.y.y + z.x*m.y.z;
    ret.z.x = x.x*m.z.x + y.x*m.z.y + z.x*m.z.z;
    
    ret.x.y = x.y*m.x.x + y.y*m.x.y + z.y*m.x.z;
    ret.y.y = x.y*m.y.x + y.y*m.y.y + z.y*m.y.z;
    ret.z.y = x.y*m.z.x + y.y*m.z.y + z.y*m.z.z;
    
    ret.x.z = x.z*m.x.x + y.z*m.x.y + z.z*m.x.z;
    ret.y.z = x.z*m.y.x + y.z*m.y.y + z.z*m.y.z;
    ret.z.z = x.z*m.z.x + y.z*m.z.y + z.z*m.z.z;
    return ret;
  }
  template <typename I>
  Vector3<I> operator*(const Vector3<I> &b) const
  {
    Vector3<I> v;
    v.x = x.x*b.x + y.x*b.y + z.x*b.z;
    v.y = x.y*b.x + y.y*b.y + z.y*b.z;
    v.z = x.z*b.x + y.z*b.y + z.z*b.z;
    return v;
  }
  template <typename I>
  Vector2<I> operator*(const Vector2<I> &b) const
  {
    Vector2<I> v;
    v.x = x.x*b.x + y.x*b.y + z.x;
    v.y = x.y*b.x + y.y*b.y + z.y;
    return v;
  }
  bool operator==(const Matrix3 &m) const {return x == m.x && y == m.y && z == m.z;}
  bool operator<(const Matrix3 &m) const {return x == m.x ? y == m.y ? z < m.z : y < m.y : x < m.x;}
  void operator*=(const Matrix3 &m) {*this = m * *this;}
  T* ptr() {return x.ptr();}
  const T* ptr() const {return x.ptr();}
  
  Vector3<T>& operator[](int index) {return (&x)[index];}
  const Vector3<T>& operator[](int index) const {return (&x)[index];}
  
  static Matrix3 RotX(T r)
  {
    Matrix3 m;
    m.y.y = m.z.z = cos(r);
    m.y.z = sin(r);
    m.z.y = -m.y.z;
    return m;
  }
  static Matrix3 RotY(T r)
  {
    Matrix3 m;
    m.x.x = m.z.z = cos(r);
    m.z.x = sin(r);
    m.x.z = -m.z.x;
    return m;
  }
  static Matrix3 RotZ(T r)
  {
    Matrix3 m;
    m.x.x = m.y.y = cos(r);
    m.x.y = sin(r);
    m.y.x = -m.x.y;
    return m;
  }
  static Matrix3 Rotate(Vector3<T> r) {return RotZ(r.z) * RotY(r.y) * RotX(r.x);}
  static Matrix3 Trans2d(Vector2<T> t)
  {
    Matrix3 m;
    m.z = Vector3<T>(t, 1);
    return m;
  }
  static Matrix3 Scale(Vector2<T> s)
  {
    Matrix3 m;
    m.x.x = s.x;
    m.y.y = s.y;
    return m;
  }
  static Matrix3 Scale(Vector3<T> s)
  {
    Matrix3 m;
    m.x.x = s.x;
    m.y.y = s.y;
    m.z.z = s.z;
    return m;
  }
  static Matrix3<T> Orthoginalize(const Vector3<T> &fwd, const Vector3<T> &up)
  {
    vec3 f = fwd.normalized();
    vec3 s = up.cross(f).normalized();
    vec3 u = f.cross(s);
    
    Matrix3 m;
    m.x.x = s.x; m.y.x = f.x; m.z.x = u.x;
    m.x.y = s.y; m.y.y = f.y; m.z.y = u.y;
    m.x.z = s.z; m.y.z = f.z; m.z.z = u.z;
    return m;
  }
  
  friend std::ostream &operator<<(std::ostream &os, const Matrix3 &m)
  {
    os << "[" << m.x.x << ", " << m.y.x << ", " << m.z.x << "]" << std::endl;
    os << "[" << m.x.y << ", " << m.y.y << ", " << m.z.y << "]" << std::endl;
    os << "[" << m.x.z << ", " << m.y.z << ", " << m.z.z << "]" << std::endl;
    return os;
  }
  
  Vector3<T> x;
  Vector3<T> y;
  Vector3<T> z;
};

template <typename T>
struct Matrix4 {
  Matrix4(): x(1, 0, 0, 0), y(0, 1, 0, 0), z(0, 0, 1, 0), w(0, 0, 0, 1) {}
  Matrix4(const T* m)
  {
    x.x = m[0]; x.y = m[1]; x.z = m[2]; x.w = m[3];
    y.x = m[4]; y.y = m[5]; y.z = m[6]; y.w = m[7];
    z.x = m[8]; z.y = m[9]; z.z = m[10]; z.w = m[11];
    w.x = m[12]; w.y = m[13]; w.z = m[14]; w.w = m[15];
  }
  template <typename I>
  Matrix4(const Matrix2<I> &m): x(m.x, 0, 0), y(m.y, 0, 0), z(0, 0, 1, 0), w(0, 0, 0, 1) {}
  template <typename I>
  Matrix4(const Matrix3<I> &m): x(m.x, 0), y(m.y, 0), z(m.z, 0), w(0, 0, 0, 1) {}
  template <typename I>
  Matrix4(const Matrix4<I> &m): x(m.x), y(m.y), z(m.z) {}
  
  Matrix4 transposed() const
  {
    Matrix4 m = *this;
    m.x.y = y.x;
    m.x.z = z.x;
    m.x.w = w.x;
    
    m.y.x = x.y;
    m.y.z = z.y;
    m.y.w = w.y;
    
    m.z.x = x.z;
    m.z.y = y.z;
    m.z.w = w.z;
    
    m.w.x = x.w;
    m.w.y = y.w;
    m.w.z = z.w;
    return m;
  }
  
  T determinant() const
  {
    T det = x.x * y.y * z.z * w.w + x.x * y.z * z.w * w.y + x.x * y.w * z.y * w.z;
    det  += x.y * y.x * z.w * w.z + x.y * y.z * z.x * w.w + x.y * y.w * z.z * w.x;
    det  += x.z * y.x * z.y * w.w + x.z * y.y * z.w * w.x + x.z * y.w * z.x * w.y;
    det  += x.w * y.x * z.z * w.y + x.w * y.y * z.x * w.z + x.w * y.z * z.y * w.x;
    
    det -= x.x * y.y * z.w * w.z + x.x * y.z * z.y * w.w + x.x * y.w * z.z * w.y;
    det -= x.y * y.x * z.z * w.w + x.y * y.z * z.w * w.x + x.y * y.w * z.x * w.z;
    det -= x.z * y.x * z.w * w.y + x.z * y.y * z.x * w.w + x.z * y.w * z.y * w.x;
    det -= x.w * y.x * z.y * w.z + x.w * y.y * z.z * w.x + x.w * y.z * z.x * w.y;
    return det;
  }
  Matrix4 inverse() const
  {
    Matrix4 m = *this;
    T det = determinant();
    if (det != static_cast<T>(0))
    {
      det = static_cast<T>(1)/det;
      m.x.x = (y.y * z.z * w.w + y.z * z.w * w.y + y.w * z.y * w.z - y.y * z.w * w.z - y.z * z.y * w.w - y.w * z.z * w.y) * det;
      m.x.y = (x.y * z.w * w.z + x.z * z.y * w.w + x.w * z.z * w.y - x.y * z.z * w.w - x.z * z.w * w.y - x.w * z.y * w.z) * det;
      m.x.z = (x.y * y.z * w.w + x.z * y.w * w.y + x.w * y.y * w.z - x.y * y.w * w.z - x.z * y.y * w.w - x.w * y.z * w.y) * det;
      m.x.w = (x.y * y.w * z.z + x.z * y.y * z.w + x.w * y.z * z.y - x.y * y.z * z.w - x.z * y.w * z.y - x.w * y.y * z.z) * det;
      
      m.y.x = (y.x * z.w * w.z + y.z * z.x * w.w + y.w * z.z * w.x - y.x * z.z * w.w - y.z * z.w * w.x - y.w * z.x * w.z) * det;
      m.y.y = (x.x * z.z * w.w + x.z * z.w * w.x + x.w * z.x * w.z - x.x * z.w * w.z - x.z * z.x * w.w - x.w * z.z * w.x) * det;
      m.y.z = (x.x * y.w * w.z + x.z * y.x * w.w + x.w * y.z * w.x - x.x * y.z * w.w - x.z * y.w * w.x - x.w * y.x * w.z) * det;
      m.y.w = (x.x * y.z * z.w + x.z * y.w * z.x + x.w * y.x * z.z - x.x * y.w * z.z - x.z * y.x * z.w - x.w * y.z * z.x) * det;
      
      m.z.x = (y.x * z.y * w.w + y.y * z.w * w.x + y.w * z.x * w.y - y.x * z.w * w.y - y.y * z.x * w.w - y.w * z.y * w.x) * det;
      m.z.y = (x.x * z.w * w.y + x.y * z.x * w.w + x.w * z.y * w.x - x.x * z.y * w.w - x.y * z.w * w.x - x.w * z.x * w.y) * det;
      m.z.z = (x.x * y.y * w.w + x.y * y.w * w.x + x.w * y.x * w.y - x.x * y.w * w.y - x.y * y.x * w.w - x.w * y.y * w.x) * det;
      m.z.w = (x.x * y.w * z.y + x.y * y.x * z.w + x.w * y.y * z.x - x.x * y.y * z.w - x.y * y.w * z.x - x.w * y.x * z.y) * det;
      
      m.w.x = (y.x * z.z * w.y + y.y * z.x * w.z + y.z * z.y * w.x - y.x * z.y * w.z - y.y * z.z * w.x - y.z * z.x * w.y) * det;
      m.w.y = (x.x * z.y * w.z + x.y * z.z * w.x + x.z * z.x * w.y - x.x * z.z * w.y - x.y * z.x * w.z - x.z * z.y * w.x) * det;
      m.w.z = (x.x * y.z * w.y + x.y * y.x * w.z + x.z * y.y * w.x - x.x * y.y * w.z - x.y * y.z * w.x - x.z * y.x * w.y) * det;
      m.w.w = (x.x * y.y * z.z + x.y * y.z * z.x + x.z * y.x * z.y - x.x * y.z * z.y - x.y * y.x * z.z - x.z * y.y * z.x) * det;
    }
    else
      std::cerr << "Cannot Invert Matrix: " << std::endl << *this;
    return m;
  }
  Matrix4 scaled(T s) const
  {
    Matrix4 m = *this;
    m.x.x *= s;
    m.y.y *= s;
    m.z.z *= s;
    return m;
  }
  template <typename I>
  Matrix4 scaled(const Vector3<I> &s) const
  {
    Matrix4 m = *this;
    m.x.x *= s.x;
    m.y.y *= s.y;
    m.z.z *= s.z;
    return m;
  }
  Matrix2<T> toMat2() const
  {
    Matrix2<T> m;
    m.x = x.XY();
    m.y = y.XY();
    return m;
  }
  Matrix3<T> toMat3() const
  {
    Matrix3<T> m;
    m.x = x.xyz();
    m.y = y.xyz();
    m.z = z.xyz();
    return m;
  }
  Matrix4 operator*(T s) const
  {
    Matrix4 ret = *this;
    ret.x *= s;
    ret.y *= s;
    ret.z *= s;
    ret.w *= s;
    return ret;
  }
  Matrix4 operator*(const Matrix4 &m) const
  {
    Matrix4 ret;
    ret.x.x = x.x*m.x.x + y.x*m.x.y + z.x*m.x.z + w.x*m.x.w;
    ret.y.x = x.x*m.y.x + y.x*m.y.y + z.x*m.y.z + w.x*m.y.w;
    ret.z.x = x.x*m.z.x + y.x*m.z.y + z.x*m.z.z + w.x*m.z.w;
    ret.w.x = x.x*m.w.x + y.x*m.w.y + z.x*m.w.z + w.x*m.w.w;
    
    ret.x.y = x.y*m.x.x + y.y*m.x.y + z.y*m.x.z + w.y*m.x.w;
    ret.y.y = x.y*m.y.x + y.y*m.y.y + z.y*m.y.z + w.y*m.y.w;
    ret.z.y = x.y*m.z.x + y.y*m.z.y + z.y*m.z.z + w.y*m.z.w;
    ret.w.y = x.y*m.w.x + y.y*m.w.y + z.y*m.w.z + w.y*m.w.w;
    
    ret.x.z = x.z*m.x.x + y.z*m.x.y + z.z*m.x.z + w.z*m.x.w;
    ret.y.z = x.z*m.y.x + y.z*m.y.y + z.z*m.y.z + w.z*m.y.w;
    ret.z.z = x.z*m.z.x + y.z*m.z.y + z.z*m.z.z + w.z*m.z.w;
    ret.w.z = x.z*m.w.x + y.z*m.w.y + z.z*m.w.z + w.z*m.w.w;
    
    ret.x.w = x.w*m.x.x + y.w*m.x.y + z.w*m.x.z + w.w*m.x.w;
    ret.y.w = x.w*m.y.x + y.w*m.y.y + z.w*m.y.z + w.w*m.y.w;
    ret.z.w = x.w*m.z.x + y.w*m.z.y + z.w*m.z.z + w.w*m.z.w;
    ret.w.w = x.w*m.w.x + y.w*m.w.y + z.w*m.w.z + w.w*m.w.w;
    return ret;
  }
  template <typename I>
  Vector4<I> operator*(const Vector4<I> &b) const
  {
    Vector4<I> v;
    v.x = x.x*b.x + y.x*b.y + z.x*b.z + w.x*b.w;
    v.y = x.y*b.x + y.y*b.y + z.y*b.z + w.y*b.w;
    v.z = x.z*b.x + y.z*b.y + z.z*b.z + w.z*b.w;
    v.w = x.w*b.x + y.w*b.y + z.w*b.z + w.w*b.w;
    return v;
  }
  template <typename I>
  Vector3<I> operator*(const Vector3<I> &b) const
  {
    Vector4<I> v = *this * Vector4<I>(b, 1);
    return v.xyz()/v.w;
  }
  bool operator==(const Matrix4 &m) const {return x == m.x && y == m.y && z == m.z && w == m.w;}
  bool operator<(const Matrix4 &m) const {return x == m.x ? y == m.y ? z == m.z ? w < m.w : z < m.z : y < m.y : x < m.x;}
  void operator*=(const Matrix4 &m) {*this = m * *this;}
  T* ptr() {return x.ptr();}
  const T* ptr() const {return x.ptr();}
  
  Vector4<T>& operator[](int index) {return (&x)[index];}
  const Vector4<T>& operator[](int index) const {return (&x)[index];}
  
  static Matrix4 RotX(T r)
  {
    Matrix4 m;
    m.y.y = m.z.z = cos(r);
    m.y.z = sin(r);
    m.z.y = -m.y.z;
    return m;
  }
  static Matrix4 RotY(T r)
  {
    Matrix4 m;
    m.x.x = m.z.z = cos(r);
    m.z.x = sin(r);
    m.x.z = -m.z.x;
    return m;
  }
  static Matrix4 RotZ(T r)
  {
    Matrix4 m;
    m.x.x = m.y.y = cos(r);
    m.x.y = sin(r);
    m.y.x = -m.x.y;
    return m;
  }
  static Matrix4 Rotate(Vector3<T> r) {return RotZ(r.z) * RotY(r.y) * RotX(r.x);}
  
  static Matrix4 Trans3d(Vector3<T> t)
  {
    Matrix4 m;
    m.w = Vector4<T>(t, 1);
    return m;
  }
  static Matrix4 Scale(Vector2<T> s)
  {
    Matrix4 m;
    m.x.x = s.x;
    m.y.y = s.y;
    return m;
  }
  static Matrix4 Scale(Vector3<T> s)
  {
    Matrix4 m;
    m.x.x = s.x;
    m.y.y = s.y;
    m.z.z = s.z;
    return m;
  }
  static Matrix4 Scale(Vector4<T> s)
  {
    Matrix4 m;
    m.x.x = s.x;
    m.y.y = s.y;
    m.z.z = s.z;
    m.w.w = s.w;
    return m;
  }
  static Matrix4 Frustum(T left, T right, T bottom, T top, T near, T far)
  {
    T a = (2 * near) / (right - left);
    T b = (2 * near) / (top - bottom);
    T c = (right + left) / (right - left);
    T d = (top + bottom) / (top - bottom);
    T e = -(far + near) / (far - near);
    T f = (-2 * far * near) / (far - near);
    
    Matrix4 m;
    m.x = Vector4<T>(a, 0, 0, 0);
    m.y = Vector4<T>(0, b, 0, 0);
    m.z = Vector4<T>(c, d, e, -1);
    m.w = Vector4<T>(0, 0, f, 1);
    return m;
  }
  static Matrix4 Ortho(T left, T right, T bottom, T top, T near, T far)
  {
    T a = static_cast<T>(2) / (right - left);
    T b = static_cast<T>(2) / (top - bottom);
    T c = static_cast<T>(-2) / (far - near);
    T d = -(right + left) / (right - left);
    T e = -(top + bottom) / (top - bottom);
    T f = -(far + near) / (far - near);
    
    Matrix4 m;
    m.x = Vector4<T>(a, 0, 0, 0);
    m.y = Vector4<T>(0, b, 0, 0);
    m.z = Vector4<T>(0, 0, c, 0);
    m.w = Vector4<T>(d, e, f, 1);
    return m;
  }
  static Matrix4<T> Orthoginalize(const Vector3<T> &fwd, const Vector3<T> &up)
  {
    vec3 f = fwd.normalized();
    vec3 s = fwd.cross(up).normalized();
    vec3 u = s.cross(f);
    
    Matrix4 m;
    m.x.x = s.x; m.y.x = u.x; m.z.x = f.x;
    m.x.y = s.y; m.y.y = u.y; m.z.y = f.y;
    m.x.z = s.z; m.y.z = u.z; m.z.z = f.z;
    return m;
  }
  static Matrix4<T> Magic(const Vector3<T> &fwd, const Vector3<T> &up, const Vector3<T> &pos)
  {
    return Trans3d(pos) * Orthoginalize(fwd, up);
  }
  static Matrix4<T> LookAt(const Vector3<T> &eye, const Vector3<T> &center, const Vector3<T> &up)
  {
    vec3 f = (center - eye).normalized();
    vec3 s = f.cross(up).normalized();
    vec3 u = s.cross(f);
    
    Matrix4 m;
    m.x.x = s.x; m.y.x = s.y; m.z.x = s.z;
    m.x.y = u.x; m.y.y = u.y; m.z.y = u.z;
    m.x.z = -f.x; m.y.z = -f.y; m.z.z = -f.z;
    
    return m * Trans3d(-eye);
  }
  
  friend std::ostream &operator<<(std::ostream &os, const Matrix4 &m)
  {
    os << "[" << m.x.x << ", " << m.y.x << ", " << m.z.x << ", " << m.w.x << "]" << std::endl;
    os << "[" << m.x.y << ", " << m.y.y << ", " << m.z.y << ", " << m.w.y << "]" << std::endl;
    os << "[" << m.x.z << ", " << m.y.z << ", " << m.z.z << ", " << m.w.z << "]" << std::endl;
    os << "[" << m.x.w << ", " << m.y.w << ", " << m.z.w << ", " << m.w.w << "]" << std::endl;
    return os;
  }
  
  Vector4<T> x;
  Vector4<T> y;
  Vector4<T> z;
  Vector4<T> w;
};

typedef Matrix2<float> mat2;
typedef Matrix3<float> mat3;
typedef Matrix4<float> mat4;




template <typename T>
struct Quaternion
{
  Quaternion(): x(0), y(0), z(0), w(1) {}
  Quaternion(T x, T y, T z, T w): x(x), y(y), z(z), w(w) {}
  Quaternion(const Vector4<T> &v): x(v.x), y(v.y), z(v.z), w(v.w) {}
  Quaternion(const Vector3<T> &v): x(v.x), y(v.y), z(v.z)
  {
    w = 1.0 - (x*x) - (y*y) - (z*z);
    w = w < 0 ? 0 : -std::sqrt(w);
  }
  Quaternion(Vector3<T> axis, T r)
  {
    axis.normalize();
    w = std::cos(r / 2);
    x = y = z = std::sin(r / 2);
    x *= axis.x;
    y *= axis.y;
    z *= axis.z;
  }
  Quaternion(const Vector3<T> &v0, const Vector3<T> &v1): x(1), y(0), z(0), w(0)
  {
    if (!(v0 == -v1)) {
      T s;
      Vector3<T> c = v0.Cross(v1);
      s = v0.Dot(v1);
      s = std::sqrt((1 + s) * 2);
      
      x = c.x / s;
      y = c.y / s;
      z = c.z / s;
      w = s / 2.0f;
    }
  }
  
  Vector3<T> toVec3() const {return Vector3<T>(x, y, z);}
  Vector4<T> toVec4() const {return Vector4<T>(x, y, z, w);}
  
  T Dot(const Quaternion &q) const {return x * q.x + y * q.y + z * q.z + w * q.w;}
  
  Quaternion operator+(const Quaternion &q) const {return Quaternion(x + q.x, y + q.y, z + q.z, w + q.w);}
  Quaternion operator-(const Quaternion &q) const {return Quaternion(x - q.x, y - q.y, z - q.z, w - q.w);}
  Quaternion operator*(const Quaternion &q) const
  {
    Quaternion ret;
    ret.w = w * q.w - x * q.x - y * q.y - z * q.z;
    ret.x = w * q.x + x * q.w + y * q.z - z * q.y;
    ret.y = w * q.y + y * q.w + z * q.x - x * q.z;
    ret.z = w * q.z + z * q.w + x * q.y - y * q.x;
    ret.normalize();
    return ret;
  }
  Quaternion operator*(T s) const {return Quaternion(x*s, y*s, z*s, w*s);}
  Vector3<T> operator*(const Vector3<T> &v) const
  {
    Quaternion<T> ret = *this * Quaternion<T>(v.x, v.y, v.z, 1) * conjugate();
    return vec3(ret.x, ret.y, ret.z);
  }
  
  void operator+=(const Quaternion &q) {*this = *this + q;}
  void operator-=(const Quaternion &q) {*this = *this - q;}
  void operator*=(const Quaternion &q) {*this = *this * q;}
  void operator*=(T s) {this = *this * s;}
  
  void rotate(const Vector3<T> &v)
  {
    if (v.x != 0)
      *this *= Quaternion(vec3(1, 0, 0), v.x);
    if (v.y != 0)
      *this *= Quaternion(vec3(0, 1, 0), v.y);
    if (v.z != 0)
      *this *= Quaternion(vec3(0, 0, 1), v.z);
  }
  
  T lengthSquared() const {return x * x + y * y + z * z + w * w;}
  T length()        const {return sqrt(lengthSquared());}
  
  Quaternion normalized() const {return *this * (1.0/length());}
  Quaternion conjugate()  const
  {
    Quaternion q(-x, -y, -z, w);
    return q.normalized();
  }
  T norm() const {return x*x + y*y + z*z + w*w;}
  Quaternion scale(T s) const {return Quaternion(x*s, y*s, z*s, w*s);}
  Quaternion inverse() const {return conjugate().scale(1.0/norm());}
  
  void normalize() {*this = normalized();}
  
  bool operator==(const Quaternion &q) const {return x == q.x && y == q.y && z == q.z && w == q.w;}
  bool operator<(const Quaternion &q) const
  {
    return x == q.x ? y == q.y ? z == q.z ? w < q.w : z < q.z : y < q.y : x < q.x;
  }
  Quaternion lerp(T t, const Quaternion &q) const
  {
    Quaternion result = q + (*this - q) * t;
    return result.Normalized();
  }
  Quaternion slerp(T t, const Quaternion &q) const
  {
    const T epsilon = 0.0005f;
    Quaternion result, q2;
    T theta, dot = Dot(q);
    
    if (dot > 1 - epsilon) {
      result = q + (*this - q) * t;
      return result.Normalized();
    }
    
    dot = dot < 0 ? 0 : dot > 1 ? 1 : dot;
    
    theta = std::acos(dot);
    theta *= t;
    
    q2 = (q - *this * dot);
    q2.Normalize();
    
    result = *this * std::cos(theta) + q2 * std::sin(theta);
    return result.Normalized();
  }
  Matrix3<T> toMat3() const
  {
    T s = 2;
    Matrix3<T> m;
    
    T xs, ys, zs;
    T wx, wy, wz;
    T xx, xy, xz;
    T yy, yz, zz;
    xs = x * s;  ys = y * s;  zs = z * s;
    wx = w * xs; wy = w * ys; wz = w * zs;
    xx = x * xs; xy = x * ys; xz = x * zs;
    yy = y * ys; yz = y * zs; zz = z * zs;
    
    m.x = Vector3<T>(1 - (yy + zz), xy + wz, xz - wy);
    m.y = Vector3<T>(xy - wz, 1 - (xx + zz), yz + wx);
    m.z = Vector3<T>(xz + wy, yz - wx, 1 - (xx + yy));
    return m;
  }
  Matrix4<T> toMat4() const {return Matrix4<T>(toMat3());}
  
  friend std::ostream &operator<<(std::ostream &os, const Quaternion &q)
  {
    return os << "(" << q.x << ", " << q.y << ", " << q.z << ", " << q.w << ")";
  }
  
  static Quaternion ParseFloat(const std::string &str)
  {
    Quaternion q;
    sscanf(str.c_str(), " %f , %f , %f , %f", &q.x, &q.y, &q.z, &q.w);
    return q;
  }
  
  T x;
  T y;
  T z;
  T w;
};

typedef Quaternion<float> quat;



#endif /* Vector_h */
