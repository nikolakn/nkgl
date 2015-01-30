#ifndef mm_frame_h
#define mm_frame_h

#include "mm_util.h"

namespace mymath
{
  template< typename t >
  class frame
  {
    private:

    protected:

    public:
      impl::vec4i<t> near_ul, near_ll, near_ur, near_lr;
      impl::vec4i<t> far_ul, far_ll, far_ur, far_lr;

      impl::mat4i<t> projection_matrix;

      void set_ortographic( const t& left, const t& right, const t& bottom, const t& top, const t& near1, const t& far1 )
      {
        projection_matrix = ortographic( left, right, bottom, top, near1, far1 );

        near_ul = impl::vec4i<t>( left, top, near1, ( t )1 );
        near_ll = impl::vec4i<t>( left, bottom, near1, ( t )1 );
        near_ur = impl::vec4i<t>( right, top, near1, ( t )1 );
        near_lr = impl::vec4i<t>( right, bottom, near1, ( t )1 );
        far_ul = impl::vec4i<t>( left, top, far1, ( t )1 );
        far_ll = impl::vec4i<t>( left, bottom, far1, ( t )1 );
        far_ur = impl::vec4i<t>( right, top, far1, ( t )1 );
        far_lr = impl::vec4i<t>( right, bottom, far1, ( t )1 );
      }

      void set_perspective( const t& fovy, const t& aspect, const t& near1, const t& far1 )
      {
        projection_matrix = impl::mat4i<t>( 1 );

        t top = near1 * std::tan( fovy * ( t )0.5 );
        t bottom = -top;
        t left = bottom * aspect;
        t right = -left;

        projection_matrix[0].x = ( ( t )2 * near1 ) / ( right - left );
        projection_matrix[1].y = ( ( t )2 * near1 ) / ( top - bottom );
        projection_matrix[2].x = ( right + left ) / ( right - left );
        projection_matrix[2].y = ( top + bottom ) / ( top - bottom );
        projection_matrix[2].z = -( far1 + near1 ) / ( far1 - near1 );
        projection_matrix[2].w = -( t )1;
        projection_matrix[3].z = -( ( t )2 * far1 * near1 ) / ( far1 - near1 );
        projection_matrix[3].w = ( t )0;

        t ftop = far1 * std::tan( fovy * ( t )0.5 );
        t fbottom = -ftop;
        t fleft = fbottom * aspect;
        t fright = -fleft;

        near_ul = impl::vec4i<t>( left, top, -near1, ( t )1 );
        near_ll = impl::vec4i<t>( left, bottom, -near1, ( t )1 );
        near_ur = impl::vec4i<t>( right, top, -near1, ( t )1 );
        near_lr = impl::vec4i<t>( right, bottom, -near1, ( t )1 );
        far_ul = impl::vec4i<t>( fleft, ftop, -far1, ( t )1 );
        far_ll = impl::vec4i<t>( fleft, fbottom, -far1, ( t )1 );
        far_ur = impl::vec4i<t>( fright, ftop, -far1, ( t )1 );
        far_lr = impl::vec4i<t>( fright, fbottom, -far1, ( t )1 );
      }
  };
}

#endif
