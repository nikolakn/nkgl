#include "nkgltext.h"

NkGlText::NkGlText()
{
    face = 0;
}

NkGlText::~NkGlText()
{
    if (face != 0)
        delete face;
    glDeleteProgram(program);
}

int NkGlText::Init(int w, int h)
{
    m_duzina=w;
    m_visina=h;
    fontfilename = "./data/font/FreeSans.ttf";
    face = new FT_Face();
    ft = new FT_Library();
    /* Initialize the FreeType2 library */
    if (FT_Init_FreeType(ft)) {
        fprintf(stderr, "Could not init freetype library\n");
        return 0;
    }

    /* Load a font */
    if (FT_New_Face(*ft, fontfilename, 0, face)) {
        fprintf(stderr, "Could not open font %s\n", fontfilename);
        return 0;
    }
    program = LoadShaders("./data/shaders/text.v.glsl", "./data/shaders/text.f.glsl");
    if(program == 0){
        std::cout<<"grska shader 1" << std::endl;
        return 0;
    }

    //attribute_coord = get_attrib(program, "coord");
    attribute_coord = glGetAttribLocation(program, "coord");
    uniform_tex = glGetUniformLocation(program, "tex");
    uniform_color = glGetUniformLocation(program, "color");

    if(attribute_coord == -1 || uniform_tex == -1 || uniform_color == -1){
        std::cout<<"grska shader" <<attribute_coord<< uniform_tex <<uniform_color<<  std::endl;
        return 0;
    }
    // Create the vertex buffer object
    glGenBuffers(1, &vbo);

    /* Create texture atlasses for several font sizes */
    a48 = new atlas(face, 48, uniform_tex);
    a24 = new atlas(face, 24, uniform_tex);
    a12 = new atlas(face, 12, uniform_tex);

    return 1;
}

void NkGlText::render()
{
    float sx = 2.0 / m_duzina;
    float sy = 2.0 / m_visina;

    glUseProgram(program);
    glDisable(GL_DEPTH_TEST);
    //glClearColor(1, 1, 1, 1);
    //    glClear(GL_COLOR_BUFFER_BIT);

    /* Enable blending, necessary for our alpha texture */;
    /* White background */
    //glClearColor(1, 1, 1, 1);
    //glClear(GL_COLOR_BUFFER_BIT);

    /* Enable blending, necessary for our alpha texture */
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    GLfloat black[4] = { 0, 0, 0, 1 };
    GLfloat red[4] = { 1, 0, 0, 1 };
    GLfloat transparent_green[4] = { 0, 1, 0, 0.5 };

    /* Set color to black */
    glUniform4fv(uniform_color, 1, black);

    /* Effects of alignment */
    render_text("The Quick Brown Fox Jumps Over The Lazy Dog", a48, -1 + 8 * sx, 1 - 50 * sy, sx, sy);
    render_text("Nikola 123", a48, -1 + 10 * sx, 1 - 130 * sy, sx, sy);

    /* Scaling the texture versus changing the font size */
    render_text("The Small", a48, -1 + 8 * sx, 1 - 170 * sy, sx*0.4 , sy *0.4);
    render_text("The Small Font Sized Fox Jumps Over The Lazy Dog", a24, -1 + 8 * sx, 1 - 200 * sy, sx, sy);
    //render_text("The Tiny Texture Scaled Fox Jumps Over The Lazy Dog", a48, -1 + 8 * sx, 1 - 235 * sy, sx * 0.25, sy * 0.25);
    render_text("The Tiny Font Sized Fox Jumps Over The Lazy Dog", a12, -1 + 8 * sx, 1 - 250 * sy, sx, sy);

    /* Colors and transparency */
    render_text("The Solid Black Fox Jumps Over The Lazy Dog", a48, -1 + 8 * sx, 1 - 430 * sy, sx, sy);

    glUniform4fv(uniform_color, 1, red);
    render_text("The Solid Red Fox Jumps Over The Lazy Dog", a48, -1 + 8 * sx, 1 - 330 * sy, sx, sy);
    render_text("The Solid Red Fox Jumps Over The Lazy Dog", a48, -1 + 28 * sx, 1 - 450 * sy, sx, sy);

    glUniform4fv(uniform_color, 1, transparent_green);
    render_text("The Transparent Green Fox Jumps Over The Lazy Dog", a48, -1 + 8 * sx, 1 - 380 * sy, sx, sy);
    render_text("The Transparent Green Fox Jumps Over The Lazy Dog", a48, -1 + 18 * sx, 1 - 440 * sy, sx, sy);

    glUseProgram(0);
    glEnable(GL_DEPTH_TEST);



}
void NkGlText::render_text(const char *text, atlas * a, float x, float y, float sx, float sy) {
    const uint8_t *p;

    /* Use the texture containing the atlas */
    glBindTexture(GL_TEXTURE_2D, a->tex);
    glUniform1i(uniform_tex, 0);


    /* Set up the VBO for our vertex data */
    glEnableVertexAttribArray(attribute_coord);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(attribute_coord, 4, GL_FLOAT, GL_FALSE, 0, 0);

    point coords[6 * strlen(text)];
    int c = 0;

    /* Loop through all characters */
    for (p = (const uint8_t *)text; *p; p++) {
        /* Calculate the vertex and texture coordinates */
        float x2 = x + a->c[*p].bl * sx;
        float y2 = -y - a->c[*p].bt * sy;
        float w = a->c[*p].bw * sx;
        float h = a->c[*p].bh * sy;

        /* Advance the cursor to the start of the next character */
        x += a->c[*p].ax * sx;
        y += a->c[*p].ay * sy;

        /* Skip glyphs that have no pixels */
        if (!w || !h){
            continue;
        }

        coords[c++] = (point){x2, -y2, a->c[*p].tx, a->c[*p].ty};
        coords[c++] = (point){x2 + w, -y2, a->c[*p].tx + a->c[*p].bw / a->w, a->c[*p].ty};
        coords[c++] = (point) {x2, -y2 - h, a->c[*p].tx, a->c[*p].ty + a->c[*p].bh / a->h};
        coords[c++] = (point) {x2 + w, -y2, a->c[*p].tx + a->c[*p].bw / a->w, a->c[*p].ty};
        coords[c++] = (point) {x2, -y2 - h, a->c[*p].tx, a->c[*p].ty + a->c[*p].bh / a->h};
        coords[c++] = (point) {x2 + w, -y2 - h, a->c[*p].tx + a->c[*p].bw / a->w, a->c[*p].ty + a->c[*p].bh / a->h};
    }

    /* Draw all the character on the screen in one go */

    glBufferData(GL_ARRAY_BUFFER, sizeof coords, coords, GL_DYNAMIC_DRAW);
    glDrawArrays(GL_TRIANGLES, 0, c);

     glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDisableVertexAttribArray(attribute_coord);

}
