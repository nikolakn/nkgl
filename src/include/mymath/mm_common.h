#ifndef mm_common_h
#define mm_common_h

#include <iostream>
#include <cmath>
#include <algorithm>
#include <assert.h>

//makes sure only explicit cast is available between vecn and float/double etc.
#define MYMATH_STRICT_GLSL 0
#define MYMATH_DOUBLE_PRECISION 0

namespace mymath
{
  namespace impl
  {
    typedef int post; //this serves as a flag that an increment is a post increment
  }

  static const float pi = 3.1415926535897932384626433832795f;
  static const float two_pi = 2.0f * pi;
  static const float pi_div_180 = pi / 180.0f;
  static const float inv_pi_div_180 = 180.0f / pi;

#define MYMATH_INVERSESQRT( t ) \
  inline t inversesqrt( const t& a ) \
  { \
    return 1 / std::sqrt( a ); \
  }

#define MYMATH_STEP( t ) \
  inline t step( const t& a, const t& b ) \
  { \
    return b < a ? 0 : 1; \
  }

#define MYMATH_MIX( t ) \
  inline t mix( const t& a, const t& b, const t& c ) \
  { \
    return a * ( 1 - c ) + b * c; \
  }

#define MYMATH_FRACT( t ) \
  inline t fract( const t& a ) \
  { \
    return a - floor( a ); \
  }

#define MYMATH_ATAN( t ) \
  inline t atan( const t& a, const t& b ) \
  { \
    return std::atan( b / a ); \
  }

#define MYMATH_CLAMP( t ) \
  inline t clamp( const t& a, const t& b, const  t& c ) \
  { \
    return std::min( std::max( a, b ), c ); \
  }

#define MYMATH_SMOOTHSTEP( t ) \
  inline t smoothstep( const t& a, const t& b, const t& c ) \
  { \
    float u = ( c - a ) / ( b - a ); \
    u = clamp( u, 0, 1 ); \
    return u * u * ( 3 - 2 * u ); \
  }

#define MYMATH_FMA( t ) \
  inline t fma( const t& a, const t& b, const t& c ) \
  { \
    return a * b + c; \
  }

  inline float radians( const float& degrees )
  {
    return degrees * pi_div_180;
  }

  inline float degrees( const float& radians )
  {
    return radians * inv_pi_div_180;
  }

#define MYMATH_SIGN( t ) \
  inline t sign( const t& num ) \
  { \
    if( num > 0 ) \
    { \
      return 1; \
    } \
    else if( num < 0 ) \
    { \
      return -1; \
    } \
    else \
    { \
      return num; \
    } \
  }

#define MYMATH_ASINH( t ) \
  inline t asinh( const t& num ) \
  { \
    return std::log( num + std::sqrt( num * num + 1 ) ); \
  }

#define MYMATH_ACOSH( t ) \
  inline t acosh( const t& num ) \
  { \
    return std::log( num + std::sqrt( num * num - 1 ) ); \
  }

#define MYMATH_ATANH( t ) \
  inline t atanh( const t& num ) \
  { \
    return std::log( ( 1 + num ) / ( 1 - num ) ) / 2; \
  }

#define MYMATH_LOG2( t ) \
  inline t log2( const t& num ) \
  { \
    return std::log( num ) / std::log( 2 ); \
  }

#define MYMATH_TRUNC( t ) \
  inline t trunc( const t& num ) \
  { \
    return num < 0 ? -floor( -num ) : floor( num ); \
  }

#define MYMATH_ROUND( t ) \
  inline t round( const t& num ) \
  { \
    if( num < 0 ) \
    { \
      return t( int( num - 0.5 ) ); \
    } \
    else \
    { \
      return t( int( num + 0.5 ) ); \
    } \
  }

  inline bool isnan( const float& num )
  {

    return std::isnan( num );

  }

  inline bool isinf( const float& num )
  {
    return std::isinf( num );
  }

#define MYMATH_MIN( t ) \
  inline t min( const t& a, const t& b ) \
  { \
    return std::min( a, b ); \
  }

#define MYMATH_MAX( t ) \
  inline t max( const t& a, const t& b ) \
  { \
    return std::max( a, b ); \
  }

  MYMATH_INVERSESQRT( float )
  MYMATH_STEP( float )
  MYMATH_MIX( float )
  MYMATH_FRACT( float )
  MYMATH_ATAN( float )
  MYMATH_CLAMP( float )
  MYMATH_SMOOTHSTEP( float )
  MYMATH_FMA( float )
  MYMATH_SIGN( float )
  MYMATH_ASINH( float )
  MYMATH_ACOSH( float )
  MYMATH_ATANH( float )
  MYMATH_LOG2( float )
  MYMATH_TRUNC( float )
  MYMATH_ROUND( float )
  MYMATH_MIN( float )
  MYMATH_MAX( float )

#if MYMATH_DOUBLE_PRECISION == 1
  static const double dpi = 3.1415926535897932384626433832795;
  static const double dtwo_pi = 2.0 * dpi;
  static const double dpi_div_180 = dpi / 180.0;
  static const double dinv_pi_div_180 = 180.0 / dpi;

  inline double radians( const double& degrees )
  {
    return degrees * dpi_div_180;
  }

  inline double degrees( const double& radians )
  {
    return radians * dinv_pi_div_180;
  }

  inline bool isnan( const double& num )
  {
#ifdef _WIN32
    return _isnan( num ) != 0;
#else
    return std::isnan( num );
#endif
  }

  inline bool isinf( const double& num )
  {
#ifdef _WIN32
    return _fpclass( num ) == _FPCLASS_NINF || _fpclass( num ) == _FPCLASS_PINF;
#else
    return std::isinf( num );
#endif
  }

  MYMATH_INVERSESQRT( double )
  MYMATH_STEP( double )
  MYMATH_MIX( double )
  MYMATH_FRACT( double )
  MYMATH_ATAN( double )
  MYMATH_CLAMP( double )
  MYMATH_SMOOTHSTEP( double )
  MYMATH_FMA( double )
  MYMATH_SIGN( double )
  MYMATH_ASINH( double )
  MYMATH_ACOSH( double )
  MYMATH_ATANH( double )
  MYMATH_LOG2( double )
  MYMATH_TRUNC( double )
  MYMATH_ROUND( double )
  MYMATH_MIN( double )
  MYMATH_MAX( double )
#endif
}

namespace mm = mymath;

#endif


