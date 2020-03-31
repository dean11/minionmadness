#version 430

layout(location = 0) in  vec3 position;
layout(location = 1) in  vec3 normals;
layout(location = 2) in  vec3 uv;
layout(location = 3) in  vec3 vertCol;

layout(location = 10) uniform mat4 WVP;

out vec3 color;

void main(void)
{
	// Move the normals back from the camera space to the world space
	//mat3 worldRotationInverse = transpose(mat3(WorldMatrix));


	//gl_Position = WVP * vec4(position, 1.0);
	gl_Position = WVP * vec4(position, 1.0);
	//gl_TexCoord[0] = gl_MultiTexCoord0;
	//normals = normalize(worldRotationInverse * gl_NormalMatrix * gl_Normal);
	//position = gl_ModelViewMatrix * gl_Vertex;
	//gl_FrontColor = vec4(1.0, 1.0, 1.0, 1.0);
}