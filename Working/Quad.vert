#version 450

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec2 a_Uvs;
layout (location = 2) in vec4 a_Color;
layout (location = 3) in vec2 a_Tiling;
layout (location = 4) in float a_TexureIndex;


out vec4 v_Color;
out vec2 v_Uvs;
out flat float v_TextureIndex;
out vec3 v_Position;
out vec2 v_Tiling;

uniform mat4 u_ProjectionMatrix;	//From object space into world space.
void main()
{
	v_Color = a_Color;
	v_Uvs = a_Uvs;
	
	v_TextureIndex = a_TexureIndex;
	v_Tiling = a_Tiling;
	v_Position = a_Position;
	
	gl_Position = u_ProjectionMatrix * vec4(a_Position, 1);
}