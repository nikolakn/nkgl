#include "nkhex.h"
NkHex::NkHex()
{
}

NkHex::~NkHex()
{

}

void NkHex::init()
{
    size = 100;
    framework frm;
    box = frm.create_box();
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


    frm.load_shader( program, GL_VERTEX_SHADER, "./data/shaders/shaderhex.vert" );
    frm.load_shader( program, GL_FRAGMENT_SHADER, "./data/shaders/shaderhex.frag" );

    gbuffer_instanced_mvp_mat_loc = glGetUniformLocation( program, "mvp" );
    gbuffer_instanced_normal_mat_loc = glGetUniformLocation( program, "normal_mat" );
    gbuffer_instanced_view = glGetUniformLocation( program, "view" );
    //gbuffer_instanced_pos = glGetUniformLocation( gbuffer_instanced_shader, "pos" );
    glBindVertexArray( 0 );

}

void NkHex::render(glm::mat4 *ProjectionMatrix, glm::mat4 *mModelView)
{
    glUseProgram(program);
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

    glDrawElementsInstanced( GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0, positions.size() );
    glBindVertexArray( 0 );
    glUseProgram(0);


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

void NkHex::releaseScene()
{

}
