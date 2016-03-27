#version 330 core

layout(location = 0) in  vec3 vertPos;
layout(location = 1) in  vec3 vertCol;

out vec3 color;

void main(void)
{
	color = vertCol;
	gl_Position = vec4(vertPos, 1.0);
}