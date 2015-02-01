#version 330

uniform mat4 mvp; 
uniform mat4 view;
uniform mat3 normal_mat;

layout(location=0) in vec4 in_vertex; //cube vertex position
layout(location=1) in vec3 in_normal; //cube face normal
layout(location=2) in vec2 in_tex; //texture
//layout(location=2) in vec4 pos; //instance data, unique to each object (instance)
flat out int InstanceID;
out vec3 normal;
out vec2 pass_TextureCoord;

void main()
{
	vec4 vr= in_vertex;
	int N=200;
	int red=(gl_InstanceID/N);
        vr.z += red*0.18;
	if (red%2!=0)
                vr.x += 0.2*(gl_InstanceID%N);
	else
                vr.x += 0.2*(gl_InstanceID%N)+0.1;
		
  normal = normal_mat * in_normal;
  // gl_Position = mvp * view * vec4(vr.xyz + pos.xyz, 1); 
  gl_Position = mvp * view * vr; 
  pass_TextureCoord = in_tex;
  InstanceID = gl_InstanceID; 
}

 
