#version 430

layout(location = 0) in  vec3 vertPos;
layout(location = 1) in  vec3 vertCol;

out vec3 color;

void main(void)
{
	color = vertCol;
	gl_Position = vec4(vertPos, 1.0);
}


//in vec3 normals;
//in vec4 position;
//uniform mat4 ModelMatrix;
//uniform mat4 WorldMatrix;
//
//void main(void)
//{
//	// Move the normals back from the camera space to the world space
//	mat3 worldRotationInverse = transpose(mat3(WorldMatrix));
//
//	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
//	gl_TexCoord[0] = gl_MultiTexCoord0;
//	normals = normalize(worldRotationInverse * gl_NormalMatrix * gl_Normal);
//	position = gl_ModelViewMatrix * gl_Vertex;
//	gl_FrontColor = vec4(1.0, 1.0, 1.0, 1.0);
//}