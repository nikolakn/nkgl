#include "nkhex2.h"

NKHex2::NKHex2()
{
}

void NKHex2::init()
{
    size = 100;
    framework frm;
    box = create_hex();
    glBindVertexArray( box );
    positions.resize( size * size ); //make some space
    glGenBuffers( 1, &position_vbo ); //gen vbo
    glBindBuffer( GL_ARRAY_BUFFER, position_vbo ); //bind vbo

    GLuint location = 2;
    GLint components = 4;
    GLenum type = GL_FLOAT;
    GLboolean normalized = GL_FALSE;
    GLsizei datasize = sizeof( vec4 );
    char* pointer = 0; //no other components
    GLuint divisor = 1; //instanced

    glEnableVertexAttribArray( location ); //tell the location
    glVertexAttribPointer( location, components, type, normalized, datasize, pointer ); //tell other data
    glVertexAttribDivisor( location, divisor ); //is it instanced?

    program = 0;


    frm.load_shader( program, GL_VERTEX_SHADER, "./data/shaders/shaderhex2.vert" );
    frm.load_shader( program, GL_FRAGMENT_SHADER, "./data/shaders/shaderhex2.frag" );

    gbuffer_instanced_mvp_mat_loc = glGetUniformLocation( program, "mvp" );
    gbuffer_instanced_normal_mat_loc = glGetUniformLocation( program, "normal_mat" );
    gbuffer_instanced_view = glGetUniformLocation( program, "view" );
    //gbuffer_instanced_pos = glGetUniformLocation( gbuffer_instanced_shader, "pos" );
    glBindVertexArray( 0 );
}

void NKHex2::render(glm::mat4 *ProjectionMatrix, glm::mat4 *mModelView)
{
    glUseProgram(program);
    glEnable(GL_LINE_SMOOTH);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //instanced rendering
    glUniformMatrix4fv(gbuffer_instanced_mvp_mat_loc, 1, GL_FALSE, glm::value_ptr(*ProjectionMatrix));
    glUniformMatrix4fv(gbuffer_instanced_view, 1, GL_FALSE, glm::value_ptr(*mModelView));
    glBindVertexArray( box );

    //store positions in the buffer
    for( int c = 0; c < size; ++c )
    {
      for( int d = 0; d < size; ++d )
      {
        positions[c * size + d] = vec4( c*3-size, 0, -d*3, 0 );
      }
    }

    //upload the instance data
    glBindBuffer( GL_ARRAY_BUFFER, position_vbo ); //bind vbo
    //you need to upload sizeof( vec4 ) * number_of_cubes bytes, DYNAMIC_DRAW because it is updated per frame
    glBufferData( GL_ARRAY_BUFFER, sizeof( vec4 ) * positions.size(), &positions[0][0], GL_DYNAMIC_DRAW );

    glDrawElementsInstanced( GL_TRIANGLE_FAN, 8, GL_UNSIGNED_INT, 0, positions.size() );
    glBindVertexArray( 0 );
    glUseProgram(0);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    /* pojedinacno
    for( int c = 0; c < size; ++c )
    {
      for( int d = 0; d < size; ++d )
      {
        glUniform4f( gbuffer_instanced_pos , c * 3 - size, 0, -d * 3, 0 );
        //glUniform4f( gbuffer_pos_loc, c * 3 - size, -2, -d * 3, 0 );
        glDrawElements( GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0 );
      }
    }
    */
}

void NKHex2::releaseScene()
{
}

GLuint NKHex2::create_hex() const
{
  vector<vec3> vertices;
  vector<vec3> normals;
  vector<unsigned int> indices;
  GLuint vao = 0;
  GLuint vertex_vbo = 0, normal_vbo = 0, index_vbo = 0;

  //up
  float hx = hexw/2;
  float ym = hexh/3;
  float yh = hexh-ym;
  vertices.push_back( vec3( 0, 0, 0 ) );
  vertices.push_back( vec3( -hx,0,  ym ) );
  vertices.push_back( vec3( 0, 0, yh ) );
  vertices.push_back( vec3( hx, 0, ym ) );
  vertices.push_back( vec3( hx, 0, -ym ) );
  vertices.push_back( vec3( 0, 0,-yh ) );
  vertices.push_back( vec3( -hx, 0, -ym) );

  indices.push_back( 0 );
  indices.push_back( 1 );
  indices.push_back( 2 );

  indices.push_back( 3 );
  indices.push_back( 4 );
  indices.push_back( 5 );
  indices.push_back( 6 );
  indices.push_back( 1 );

  normals.push_back( vec3( 0, 1, 0 ) );
  normals.push_back( vec3( 0, 1, 0 ) );
  normals.push_back( vec3( 0, 1, 0 ) );
  normals.push_back( vec3( 0, 1, 0 ) );
  normals.push_back( vec3( 0, 1, 0 ) );
  normals.push_back( vec3( 0, 1, 0 ) );
  normals.push_back( vec3( 0, 1, 0 ) );
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
