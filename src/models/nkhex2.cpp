#include "nkhex2.h"
#include <FreeImage.h>
NkHex2::NkHex2()
{

}

void NkHex2::init()
{
    FreeImage_Initialise(true);

    box = createHex();
    glBindVertexArray( box );
    positions.resize( 1 ); //make some space
    glGenBuffers( 1, &position_vbo ); //gen vbo
    glBindBuffer( GL_ARRAY_BUFFER, position_vbo ); //bind vbo
    //glBufferData( GL_ARRAY_BUFFER, sizeof( vec4 ) * positions.size(), &positions[0][0], GL_STATIC_DRAW );
    glBufferData( GL_ARRAY_BUFFER, sizeof( vec4 ) * positions.size(), &positions[0][0], GL_STATIC_DRAW );
    GLuint location = 3;
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
    this->LoadShaders();

    gbuffer_instanced_mvp_mat_loc = glGetUniformLocation( program, "mvp" );
    gbuffer_instanced_normal_mat_loc = glGetUniformLocation( program, "normal_mat" );
    gbuffer_instanced_view = glGetUniformLocation( program, "view" );

    gbuffer_instanced_mvp_mat_loc_sel = glGetUniformLocation( programsel, "mvp" );
    gbuffer_instanced_normal_mat_loc_sel = glGetUniformLocation( programsel, "normal_mat" );
    gbuffer_instanced_view_sel = glGetUniformLocation( programsel, "view" );

    //gbuffer_instanced_pos = glGetUniformLocation( gbuffer_instanced_shader, "pos" );
    //if(!hextex.loadTexture2D("./data/textures/hextex.png", true)){
    //    cout << "texture load error" << endl;
    //}
    //hextex.setFiltering(TEXTURE_FILTER_MAG_BILINEAR, TEXTURE_FILTER_MIN_BILINEAR_MIPMAP);
    tex = this->loadTexture("./data/textures/hextex.png");
}

void NkHex2::render(glm::mat4 *ProjectionMatrix, glm::mat4 *mModelView)
{
    glUseProgram(program);

    //glEnable(GL_LINE_SMOOTH);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //instanced rendering
    glUniformMatrix4fv(gbuffer_instanced_mvp_mat_loc, 1, GL_FALSE, glm::value_ptr(*ProjectionMatrix));
    glUniformMatrix4fv(gbuffer_instanced_view, 1, GL_FALSE, glm::value_ptr(*mModelView));
    glBindVertexArray( box );

    //glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex);
    //glBindSampler(iTextureUnit, uiSampler);
   // glEnableVertexAttribArray(2);
    //store positions in the buffer
    /*
    for( int c = 0; c < size; ++c )
    {
      for( int d = 0; d < size; ++d )
      {
        positions[c * size + d] = vec4( c*3-size, 0, -d*3, 0 );
      }
    }
    */
    //upload the instance data
    glBindBuffer( GL_ARRAY_BUFFER, position_vbo ); //bind vbo
    //you need to upload sizeof( vec4 ) * number_of_cubes bytes, DYNAMIC_DRAW because it is updated per frame

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_vbo);
    glDrawElementsInstanced( GL_TRIANGLE_FAN, 8, GL_UNSIGNED_INT, 0, HEX_SIZE);
    glBindSampler(0,0);
    glBindVertexArray( 0 );
    glUseProgram(0);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
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
void NkHex2::renderSel(glm::mat4 *ProjectionMatrix, glm::mat4 *mModelView)
{
    glUseProgram(programsel);

    //glEnable(GL_LINE_SMOOTH);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //instanced rendering
    glUniformMatrix4fv(gbuffer_instanced_mvp_mat_loc_sel, 1, GL_FALSE, glm::value_ptr(*ProjectionMatrix));
    glUniformMatrix4fv(gbuffer_instanced_view_sel, 1, GL_FALSE, glm::value_ptr(*mModelView));
    glBindVertexArray( box );

    //glActiveTexture(GL_TEXTURE0);
    //glBindTexture(GL_TEXTURE_2D, tex);
    //glBindSampler(iTextureUnit, uiSampler);


    //upload the instance data
    glBindBuffer( GL_ARRAY_BUFFER, position_vbo ); //bind vbo
    //you need to upload sizeof( vec4 ) * number_of_cubes bytes, DYNAMIC_DRAW because it is updated per frame

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_vbo);
    glDrawElementsInstanced( GL_TRIANGLE_FAN, 8, GL_UNSIGNED_INT, 0, HEX_SIZE);
    glBindSampler(0,0);
    glBindVertexArray( 0 );
    glUseProgram(0);

}
void NkHex2::releaseScene()
{
}

GLuint NkHex2::createHex()
{
  vector<vec3> vertices;
  vector<vec3> normals;
  vector<vec2> texture;
  vector<unsigned int> indices;
  GLuint vao = 0;
  GLuint vertex_vbo = 0, normal_vbo = 0, index_vbo=0, tex_vbo=0;

  //up
  float hx = HEX_WIDTH/2;
  float ym = HEX_HEIGHT/3;
  float yh = HEX_HEIGHT-ym;
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

  texture.push_back(vec2(0.5,0.5));
  texture.push_back(vec2(0,0.2));
  texture.push_back(vec2(0.5,0));
  texture.push_back(vec2(1,0.2));
  texture.push_back(vec2(1,0.8));
  texture.push_back(vec2(0.5,1));
  texture.push_back(vec2(0,0.8));

  glGenVertexArrays( 1, &vao );
  glBindVertexArray( vao );

  glGenBuffers( 1, &vertex_vbo );
  glBindBuffer( GL_ARRAY_BUFFER, vertex_vbo );
  glBufferData( GL_ARRAY_BUFFER, sizeof( float ) * vertices.size() * 3, &vertices[0][0],GL_STATIC_DRAW );
  glEnableVertexAttribArray( 0 );
  glVertexAttribPointer( 0, 3, GL_FLOAT, 0, 0, 0 );

  glGenBuffers( 1, &normal_vbo );
  glBindBuffer( GL_ARRAY_BUFFER, normal_vbo );
  glBufferData( GL_ARRAY_BUFFER, sizeof( float ) * normals.size() * 3, &normals[0][0], GL_STATIC_DRAW );
  glEnableVertexAttribArray( 1 );
  glVertexAttribPointer( 1, 3, GL_FLOAT, 0, 0, 0 );

  glGenBuffers( 1, &tex_vbo );
  glBindBuffer( GL_ARRAY_BUFFER, tex_vbo );
  glBufferData( GL_ARRAY_BUFFER, sizeof( float ) * texture.size() * 2, &texture[0][0], GL_STATIC_DRAW );
  glEnableVertexAttribArray( 2 );
  glVertexAttribPointer( 2, 2, GL_FLOAT, 0, 0, 0 );

  glGenBuffers( 1, &index_vbo );
  glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, index_vbo );
  glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( unsigned int ) * indices.size(), &indices[0], GL_STATIC_DRAW );
  //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glBindVertexArray( 0 );

  return vao;
}
// Method to load an image into a texture using the freeimageplus library. Returns the texture ID or dies trying.
GLuint NkHex2::loadTexture(string filenameString, GLenum minificationFilter, GLenum magnificationFilter)
{
    //glGetError();
    // Get the filename as a pointer to a const char array to play nice with FreeImage
    const char* filename = filenameString.c_str();

    // Determine the format of the image.
    // Note: The second paramter ('size') is currently unused, and we should use 0 for it.
    FREE_IMAGE_FORMAT format = FreeImage_GetFileType(filename , 0);

    // Image not found? Abort! Without this section we get a 0 by 0 image with 0 bits-per-pixel but we don't abort, which
    // you might find preferable to dumping the user back to the desktop.
    if (format == -1)
    {
        cout << "Could not find image: " << filenameString << " - Aborting." << endl;
        exit(-1);
    }

    // Found image, but couldn't determine the file format? Try again...
    if (format == FIF_UNKNOWN)
    {
        cout << "Couldn't determine file format - attempting to get from file extension..." << endl;

        // ...by getting the filetype from the filename extension (i.e. .PNG, .GIF etc.)
        // Note: This is slower and more error-prone that getting it from the file itself,
        // also, we can't use the 'U' (unicode) variant of this method as that's Windows only.
        format = FreeImage_GetFIFFromFilename(filename);

        // Check that the plugin has reading capabilities for this format (if it's FIF_UNKNOWN,
        // for example, then it won't have) - if we can't read the file, then we bail out =(
        if ( !FreeImage_FIFSupportsReading(format) )
        {
            cout << "Detected image format cannot be read!" << endl;
            exit(-1);
        }
    }

    // If we're here we have a known image format, so load the image into a bitap
    FIBITMAP* bitmap = FreeImage_Load(format, filename);

    // How many bits-per-pixel is the source image?
    int bitsPerPixel =  FreeImage_GetBPP(bitmap);

    // Convert our image up to 32 bits (8 bits per channel, Red/Green/Blue/Alpha) -
    // but only if the image is not already 32 bits (i.e. 8 bits per channel).
    // Note: ConvertTo32Bits returns a CLONE of the image data - so if we
    // allocate this back to itself without using our bitmap32 intermediate
    // we will LEAK the original bitmap data, and valgrind will show things like this:
    //
    // LEAK SUMMARY:
    //  definitely lost: 24 bytes in 2 blocks
    //  indirectly lost: 1,024,874 bytes in 14 blocks    <--- Ouch.
    //
    // Using our intermediate and cleaning up the initial bitmap data we get:
    //
    // LEAK SUMMARY:
    //  definitely lost: 16 bytes in 1 blocks
    //  indirectly lost: 176 bytes in 4 blocks
    //
    // All above leaks (192 bytes) are caused by XGetDefault (in /usr/lib/libX11.so.6.3.0) - we have no control over this.
    //
    FIBITMAP* bitmap32;
    if (bitsPerPixel == 32)
    {
        //cout << "Source image has " << bitsPerPixel << " bits per pixel. Skipping conversion." << endl;
        bitmap32 = bitmap;
    }
    else
    {
        //cout << "Source image has " << bitsPerPixel << " bits per pixel. Converting to 32-bit colour." << endl;
        bitmap32 = FreeImage_ConvertTo32Bits(bitmap);
    }

    // Some basic image info - strip it out if you don't care
    int imageWidth  = FreeImage_GetWidth(bitmap32);
    int imageHeight = FreeImage_GetHeight(bitmap32);
    //cout << "Image: " << filenameString << " is size: " << imageWidth << "x" << imageHeight << "." << endl;

    // Get a pointer to the texture data as an array of unsigned bytes.
    // Note: At this point bitmap32 ALWAYS holds a 32-bit colour version of our image - so we get our data from that.
    // Also, we don't need to delete or delete[] this textureData because it's not on the heap (so attempting to do
    // so will cause a crash) - just let it go out of scope and the memory will be returned to the stack.
    GLubyte* textureData = FreeImage_GetBits(bitmap32);

    // Generate a texture ID and bind to it
    GLuint tempTextureID;
    glGenTextures(1, &tempTextureID);
    glBindTexture(GL_TEXTURE_2D, tempTextureID);

    // Construct the texture.
    // Note: The 'Data format' is the format of the image data as provided by the image library. FreeImage decodes images into
    // BGR/BGRA format, but we want to work with it in the more common RGBA format, so we specify the 'Internal format' as such.
    glTexImage2D(GL_TEXTURE_2D,    // Type of texture
                 0,                // Mipmap level (0 being the top level i.e. full size)
                 GL_RGBA,          // Internal format
                 imageWidth,       // Width of the texture
                 imageHeight,      // Height of the texture,
                 0,                // Border in pixels
                 GL_BGRA,          // Data format
                 GL_UNSIGNED_BYTE, // Type of texture data
                 textureData);     // The image data to use for this texture

    // Specify our minification and magnification filters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minificationFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magnificationFilter);

    // If we're using MipMaps, then we'll generate them here.
    // Note: The glGenerateMipmap call requires OpenGL 3.0 as a minimum.
    if (minificationFilter == GL_LINEAR_MIPMAP_LINEAR   ||
        minificationFilter == GL_LINEAR_MIPMAP_NEAREST  ||
        minificationFilter == GL_NEAREST_MIPMAP_LINEAR  ||
        minificationFilter == GL_NEAREST_MIPMAP_NEAREST)
    {
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    // Check for OpenGL texture creation errors
    GLenum glError = glGetError();
    if(glError)
    {
        cout << "There was an error loading the texture: "<< filenameString << endl;

        switch (glError)
        {
            case GL_INVALID_ENUM:
                cout << "Invalid enum." << endl;
                break;

            case GL_INVALID_VALUE:
                cout << "Invalid value." << endl;
                break;

            case GL_INVALID_OPERATION:
                cout << "Invalid operation." << endl;

            default:
                cout << "Unrecognised GLenum." << endl;
                break;
        }

        //cout << "See https://www.opengl.org/sdk/docs/man/html/glTexImage2D.xhtml for further details." << endl;
    }

    // Unload the 32-bit colour bitmap
    FreeImage_Unload(bitmap32);

    // If we had to do a conversion to 32-bit colour, then unload the original
    // non-32-bit-colour version of the image data too. Otherwise, bitmap32 and
    // bitmap point at the same data, and that data's already been free'd, so
    // don't attempt to free it again! (or we'll crash).
    if (bitsPerPixel != 32)
    {
        FreeImage_Unload(bitmap);
    }

    // Finally, return the texture ID
    return tempTextureID;
}
/**
* bind shaders with constants in compile time
* to avoid duplicate it through code.
*/
void NkHex2::LoadShaders(){
    //shaders
    std::string n = std::to_string(HEX_LINE_NUM);
    std::string sidex = std::to_string(HEX_WIDTH);
    std::string sidey = std::to_string(HEX_HEIGHT);
    string vertexShaderSource = {
        "#version 330\n"
        "uniform mat4 mvp;\n"
        "uniform mat4 view;\n"
        "uniform mat3 normal_mat;\n"
        "layout(location=0) in vec4 in_vertex;\n"
        "layout(location=1) in vec3 in_normal;\n"
        "layout(location=2) in vec2 in_tex;\n"
        "flat out int InstanceID;\n"
        "out vec3 normal;\n"
        "out vec2 pass_TextureCoord;\n"
        "void main()\n"
        "{\n"
        "  vec4 vr= in_vertex;\n"
        "  int N="+n+";\n"
        "  int red=(gl_InstanceID/N);\n"
        "  vr.z += red*"+sidey+";\n"
        "  if (red%2!=0)\n"
        "    vr.x += "+sidex+"*(gl_InstanceID%N);\n"
        "  else\n"
        "    vr.x += "+sidex+"*(gl_InstanceID%N)+0.1;\n"
        "  normal = normal_mat * in_normal;\n"
        "  gl_Position = mvp * view * vr;\n"
        "  pass_TextureCoord = in_tex;\n"
        "  InstanceID = gl_InstanceID;\n"
        "}\n"
    };
    string fragmentShaderSource = {
        "#version 330\n"
        "uniform sampler2D gSampler;\n"
        "flat in int InstanceID;\n"
        "in vec3 normal;\n"
        "in vec2 pass_TextureCoord;\n"
        "out vec4 color;\n"
        "void main()\n"
        "{\n"
        "   color = texture2D(gSampler, pass_TextureCoord);\n"
        "}\n"
    };


    string selvertexShaderSource = {
        "#version 330\n"
        "uniform mat4 mvp;\n"
        "uniform mat4 view;\n"
        "uniform mat3 normal_mat;\n"
        "layout(location=0) in vec4 in_vertex;\n"
        "layout(location=1) in vec3 in_normal;\n"
        "layout(location=2) in vec2 in_tex;\n"
        "flat out int InstanceID;\n"
        "out vec4 pass_color;\n"
        "void main()\n"
        "{\n"
        "  vec4 vr= in_vertex;\n"
        "  int N="+n+";\n"
        "  int red=(gl_InstanceID/N);\n"
        "int col=(gl_InstanceID%N);\n"
        "  vr.z += red*"+sidey+";\n"
        "  if (red%2!=0)\n"
        "    vr.x += "+sidex+"*(gl_InstanceID%N);\n"
        "  else\n"
        "    vr.x += "+sidex+"*(gl_InstanceID%N)+0.1;\n"
        "  gl_Position = mvp * view * vr;\n"
        "if (red >= 128)\n"
        "    red=red+1;\n"
        "if (col >=128)\n"
        "    col=col+1;	\n"
        "float redf= red/256.0;\n"
        "float colf= col/256.0;\n"
        "pass_color =  vec4(redf,colf,0.5,1);\n"
        "  InstanceID = gl_InstanceID;\n"
        "}\n"
    };
    string selfragmentShaderSource = {
        "#version 330\n"
        "uniform sampler2D gSampler;\n"
        "flat in int InstanceID;\n"
        "in vec4 pass_color;\n"
        "out vec4 color;\n"
        "void main()\n"
        "{\n"
        "   color = pass_color;\n"
        "}\n"
    };

    framework frm;
    frm.load_string_shader(vertexShaderSource, program, GL_VERTEX_SHADER);
    frm.load_string_shader(fragmentShaderSource, program, GL_FRAGMENT_SHADER);

    frm.load_string_shader(selvertexShaderSource, programsel, GL_VERTEX_SHADER);
    frm.load_string_shader(selfragmentShaderSource, programsel, GL_FRAGMENT_SHADER);
}
