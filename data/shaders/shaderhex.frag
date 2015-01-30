#version 330

in vec3 normal;

layout(location=0) out vec4 color; //normals go here

void main()
{
  color = vec4(0.5,0,0,1);
}
