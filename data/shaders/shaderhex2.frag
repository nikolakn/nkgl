#version 330
uniform sampler2D gSampler;
flat in int InstanceID;
in vec3 normal;
in vec2 pass_TextureCoord;


out vec4 color; //normals go here

void main()
{
  //color = vec4(0.5,0,0,1);
  color = texture2D(gSampler, pass_TextureCoord);
}
