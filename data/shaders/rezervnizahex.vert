#version 330

uniform mat4 mvp;
uniform mat4 view;
uniform mat3 normal_mat;
uniform vec4 pos;

layout(location=0) in vec4 in_vertex;
layout(location=1) in vec3 in_normal;

out vec3 normal;

void main()
{
  normal = normal_mat * in_normal;
  gl_Position = mvp*view * vec4(in_vertex.xyz + pos.xyz, 1);
}