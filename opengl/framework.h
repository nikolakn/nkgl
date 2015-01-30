#ifndef framework_h
#define framework_h

#include <GL/glew.h>

//#include <assimp/scene.h>
//#include <assimp/Importer.hpp>
//#include <assimp/postprocess.h>
#include "include/mymath/mymath.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <streambuf>
#include <list>
#include <vector>
#include <map>

using namespace mymath;
using namespace std;

#define INFOLOG_SIZE 4096 + 1
#define STRINGIFY(s) #s

class framework
{

    float fps;
    int frames;
    bool run;
public:
    void compile_shader( const char* text, const GLuint& program, const GLenum& type ) const
    {
      GLchar infolog[INFOLOG_SIZE];

      GLuint id = glCreateShader( type );
      glShaderSource( id, 1, &text, 0 );
      glCompileShader( id );

      GLint success;
      glGetShaderiv( id, GL_COMPILE_STATUS, &success );

      if( !success )
      {
        glGetShaderInfoLog( id, INFOLOG_SIZE, 0, infolog );
        cout << infolog << endl;
      }
      else
      {
        glAttachShader( program, id );
        glDeleteShader( id );
      }
    }

    void link_shader( const GLuint& shader_program ) const
    {
      glLinkProgram( shader_program );

      GLint success;
      glGetProgramiv( shader_program, GL_LINK_STATUS, &success );

      if( !success )
      {
        GLchar infolog[INFOLOG_SIZE];
        glGetProgramInfoLog( shader_program, INFOLOG_SIZE, 0, infolog );
        cout << infolog << endl;
      }

      glValidateProgram( shader_program );

      glGetProgramiv( shader_program, GL_VALIDATE_STATUS, &success );

      if( !success )
      {
        GLchar infolog[INFOLOG_SIZE];
        glGetProgramInfoLog( shader_program, INFOLOG_SIZE, 0, infolog );
        cout << infolog << endl;
      }
    }

  public:




    void load_shader( GLuint& program, const GLenum& type, const string& filename ) const
    {
      ifstream f( filename );

      if( !f ) cout << "Couldn't load shader: " << filename << endl;

      string str( ( istreambuf_iterator<char>( f ) ),
                  istreambuf_iterator<char>() );

      if( !program ) program = glCreateProgram();

      compile_shader( str.c_str(), program, type );
      link_shader( program );
    }

    GLuint create_quad( const vec3& ll, const vec3& lr, const vec3& ul, const vec3& ur ) const
    {
      vector<vec3> vertices;
      vector<vec2> tex_coords;
      vector<unsigned int> indices;
      GLuint vao = 0;
      GLuint vertex_vbo = 0, tex_coord_vbo = 0, index_vbo = 0;

      indices.push_back( 0 );
      indices.push_back( 1 );
      indices.push_back( 2 );

      indices.push_back( 0 );
      indices.push_back( 2 );
      indices.push_back( 3 );

      /*vertices.push_back( vec3( -1, -1, 0 ) );
      vertices.push_back( vec3( 1, -1, 0 ) );
      vertices.push_back( vec3( 1, 1, 0 ) );
      vertices.push_back( vec3( -1, 1, 0 ) );*/
      vertices.push_back( ll );
      vertices.push_back( lr );
      vertices.push_back( ur );
      vertices.push_back( ul );

      tex_coords.push_back( vec2( 0, 0 ) );
      tex_coords.push_back( vec2( 1, 0 ) );
      tex_coords.push_back( vec2( 1, 1 ) );
      tex_coords.push_back( vec2( 0, 1 ) );

      glGenVertexArrays( 1, &vao );
      glBindVertexArray( vao );

      glGenBuffers( 1, &vertex_vbo );
      glBindBuffer( GL_ARRAY_BUFFER, vertex_vbo );
      glBufferData( GL_ARRAY_BUFFER, sizeof( float ) * vertices.size() * 3, &vertices[0][0], GL_STATIC_DRAW );
      glEnableVertexAttribArray( 0 );
      glVertexAttribPointer( 0, 3, GL_FLOAT, 0, 0, 0 );

      glGenBuffers( 1, &tex_coord_vbo );
      glBindBuffer( GL_ARRAY_BUFFER, tex_coord_vbo );
      glBufferData( GL_ARRAY_BUFFER, sizeof( float ) * tex_coords.size() * 2, &tex_coords[0][0], GL_STATIC_DRAW );
      glEnableVertexAttribArray( 1 );
      glVertexAttribPointer( 1, 2, GL_FLOAT, 0, 0, 0 );

      glGenBuffers( 1, &index_vbo );
      glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, index_vbo );
      glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( unsigned int ) * indices.size(), &indices[0], GL_STATIC_DRAW );

      glBindVertexArray( 0 );

      return vao;
    }

    inline GLuint create_box() const
    {
      vector<vec3> vertices;
      vector<vec3> normals;
      vector<unsigned int> indices;
      GLuint vao = 0;
      GLuint vertex_vbo = 0, normal_vbo = 0, index_vbo = 0;

      //front
      vertices.push_back( vec3( -1, -1, 1 ) );
      vertices.push_back( vec3( 1, -1, 1 ) );
      vertices.push_back( vec3( 1, 1, 1 ) );
      vertices.push_back( vec3( -1, 1, 1 ) );

      indices.push_back( 0 );
      indices.push_back( 1 );
      indices.push_back( 2 );

      indices.push_back( 0 );
      indices.push_back( 2 );
      indices.push_back( 3 );

      normals.push_back( vec3( 0, 0, 1 ) );
      normals.push_back( vec3( 0, 0, 1 ) );
      normals.push_back( vec3( 0, 0, 1 ) );
      normals.push_back( vec3( 0, 0, 1 ) );

      //back
      vertices.push_back( vec3( -1, -1, -1 ) );
      vertices.push_back( vec3( 1, -1, -1 ) );
      vertices.push_back( vec3( 1, 1, -1 ) );
      vertices.push_back( vec3( -1, 1, -1 ) );

      indices.push_back( 6 );
      indices.push_back( 5 );
      indices.push_back( 4 );

      indices.push_back( 7 );
      indices.push_back( 6 );
      indices.push_back( 4 );

      normals.push_back( vec3( 0, 0, -1 ) );
      normals.push_back( vec3( 0, 0, -1 ) );
      normals.push_back( vec3( 0, 0, -1 ) );
      normals.push_back( vec3( 0, 0, -1 ) );

      //left
      vertices.push_back( vec3( -1, -1, 1 ) );
      vertices.push_back( vec3( -1, -1, -1 ) );
      vertices.push_back( vec3( -1, 1, 1 ) );
      vertices.push_back( vec3( -1, 1, -1 ) );

      indices.push_back( 10 );
      indices.push_back( 9 );
      indices.push_back( 8 );

      indices.push_back( 11 );
      indices.push_back( 9 );
      indices.push_back( 10 );

      normals.push_back( vec3( -1, 0, 0 ) );
      normals.push_back( vec3( -1, 0, 0 ) );
      normals.push_back( vec3( -1, 0, 0 ) );
      normals.push_back( vec3( -1, 0, 0 ) );

      //right
      vertices.push_back( vec3( 1, -1, 1 ) );
      vertices.push_back( vec3( 1, -1, -1 ) );
      vertices.push_back( vec3( 1, 1, 1 ) );
      vertices.push_back( vec3( 1, 1, -1 ) );

      indices.push_back( 12 );
      indices.push_back( 13 );
      indices.push_back( 14 );

      indices.push_back( 14 );
      indices.push_back( 13 );
      indices.push_back( 15 );

      normals.push_back( vec3( 1, 0, 0 ) );
      normals.push_back( vec3( 1, 0, 0 ) );
      normals.push_back( vec3( 1, 0, 0 ) );
      normals.push_back( vec3( 1, 0, 0 ) );

      //up
      vertices.push_back( vec3( -1, 1, 1 ) );
      vertices.push_back( vec3( 1, 1, 1 ) );
      vertices.push_back( vec3( 1, 1, -1 ) );
      vertices.push_back( vec3( -1, 1, -1 ) );

      indices.push_back( 16 );
      indices.push_back( 17 );
      indices.push_back( 18 );

      indices.push_back( 16 );
      indices.push_back( 18 );
      indices.push_back( 19 );

      normals.push_back( vec3( 0, 1, 0 ) );
      normals.push_back( vec3( 0, 1, 0 ) );
      normals.push_back( vec3( 0, 1, 0 ) );
      normals.push_back( vec3( 0, 1, 0 ) );

      //down
      vertices.push_back( vec3( -1, -1, 1 ) );
      vertices.push_back( vec3( 1, -1, 1 ) );
      vertices.push_back( vec3( 1, -1, -1 ) );
      vertices.push_back( vec3( -1, -1, -1 ) );

      indices.push_back( 22 );
      indices.push_back( 21 );
      indices.push_back( 20 );

      indices.push_back( 23 );
      indices.push_back( 22 );
      indices.push_back( 20 );

      normals.push_back( vec3( 0, -1, 0 ) );
      normals.push_back( vec3( 0, -1, 0 ) );
      normals.push_back( vec3( 0, -1, 0 ) );
      normals.push_back( vec3( 0, -1, 0 ) );

      glGenVertexArrays( 1, &vao );
      glBindVertexArray( vao );

      glGenBuffers( 1, &vertex_vbo );
      glBindBuffer( GL_ARRAY_BUFFER, vertex_vbo );
      glBufferData( GL_ARRAY_BUFFER, sizeof( float ) * vertices.size() * 3, &vertices[0][0], GL_STATIC_DRAW );
      glEnableVertexAttribArray( 0 );
      glVertexAttribPointer( 0, 3, GL_FLOAT, 0, 0, 0 );

      glGenBuffers( 1, &normal_vbo );
      glBindBuffer( GL_ARRAY_BUFFER, normal_vbo );
      glBufferData( GL_ARRAY_BUFFER, sizeof( float ) * normals.size() * 3, &normals[0][0], GL_STATIC_DRAW );
      glEnableVertexAttribArray( 1 );
      glVertexAttribPointer( 1, 3, GL_FLOAT, 0, 0, 0 );

      glGenBuffers( 1, &index_vbo );
      glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, index_vbo );
      glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( unsigned int ) * indices.size(), &indices[0], GL_STATIC_DRAW );

      glBindVertexArray( 0 );

      return vao;
    }

    void get_opengl_error( const bool& ignore = false ) const
    {
      bool got_error = false;
      GLenum error = 0;
      error = glGetError();
      string errorstring = "";

      while( error != GL_NO_ERROR )
      {
        if( error == GL_INVALID_ENUM )
        {
          //An unacceptable value is specified for an enumerated argument. The offending command is ignored and has no other side effect than to set the error flag.
          errorstring += "OpenGL error: invalid enum...\n";
          got_error = true;
        }

        if( error == GL_INVALID_VALUE )
        {
          //A numeric argument is out of range. The offending command is ignored and has no other side effect than to set the error flag.
          errorstring += "OpenGL error: invalid value...\n";
          got_error = true;
        }

        if( error == GL_INVALID_OPERATION )
        {
          //The specified operation is not allowed in the current state. The offending command is ignored and has no other side effect than to set the error flag.
          errorstring += "OpenGL error: invalid operation...\n";
          got_error = true;
        }

        if( error == GL_STACK_OVERFLOW )
        {
          //This command would cause a stack overflow. The offending command is ignored and has no other side effect than to set the error flag.
          errorstring += "OpenGL error: stack overflow...\n";
          got_error = true;
        }

        if( error == GL_STACK_UNDERFLOW )
        {
          //This command would cause a stack underflow. The offending command is ignored and has no other side effect than to set the error flag.
          errorstring += "OpenGL error: stack underflow...\n";
          got_error = true;
        }

        if( error == GL_OUT_OF_MEMORY )
        {
          //There is not enough memory left to execute the command. The state of the GL is undefined, except for the state of the error flags, after this error is recorded.
          errorstring += "OpenGL error: out of memory...\n";
          got_error = true;
        }

        if( error == GL_TABLE_TOO_LARGE )
        {
          //The specified table exceeds the implementation's maximum supported table size.  The offending command is ignored and has no other side effect than to set the error flag.
          errorstring += "OpenGL error: table too large...\n";
          got_error = true;
        }

        error = glGetError();
      }

      if( got_error && !ignore )
      {
        cerr << errorstring;
        return;
      }
    }

    void check_fbo_status( const GLenum& target = GL_FRAMEBUFFER )
    {
      GLenum error_code = glCheckFramebufferStatus( target );

      switch( error_code )
      {
        case GL_FRAMEBUFFER_COMPLETE:
          break;
        case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
          cerr << "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT." << endl;
          break;
        case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT:
          cerr << "GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS." << endl;
          break;
        case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
          cerr << "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT." << endl;
          break;
        case GL_FRAMEBUFFER_UNSUPPORTED:
          cerr << "GL_FRAMEBUFFER_UNSUPPORTED." << endl;
          break;
        case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
          cerr << "GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER." << endl;
          break;
        case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
          cerr << "GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER." << endl;
          break;
        case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
          cerr << "GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE." << endl;
          break;
        case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS_ARB:
          cerr << "GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS." << endl;
          break;
        case GL_FRAMEBUFFER_INCOMPLETE_LAYER_COUNT_ARB:
          cerr << "GL_FRAMEBUFFER_INCOMPLETE_LAYER_COUNT." << endl;
          break;
        case GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT:
          cerr << "GL_FRAMEBUFFER_INCOMPLETE_FORMATS." << endl;
          break;
        default:
          cerr << "Unknown Frame Buffer error cause: " << error_code << endl;
          break;
      }
    }
};

#endif
