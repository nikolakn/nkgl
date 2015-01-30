#version 330

uniform mat4 mvp; 
uniform mat4 view;
uniform mat3 normal_mat;

layout(location=0) in vec4 in_vertex; //cube vertex position
layout(location=1) in vec3 in_normal; //cube face normal
layout(location=2) in vec4 pos; //instance data, unique to each object (instance)

out vec3 normal;
flat out int InstanceID; 

void main()
{
	int N=200;
	int red=(gl_InstanceID/N);
	in_vertex.z += red*0.18;
	if (red%2!=0)
		in_vertex.x += 0.2*(gl_InstanceID%N);
	else
		in_vertex.x += 0.2*(gl_InstanceID%N)+0.1;
		
  normal = normal_mat * in_normal;
  // gl_Position = mvp * view * vec4(in_vertex.xyz + pos.xyz, 1); 
  gl_Position = mvp * view * in_vertex; 
  //pass_TextureCoord = in_TextureCoord;
  InstanceID = gl_InstanceID; 
}

 