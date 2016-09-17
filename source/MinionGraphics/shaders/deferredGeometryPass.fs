#version 430

in  vec3 color;
layout (location=0) out vec4 fragColor;

void main(void)
{
	fragColor = vec4(color, 1.0);
}

//in vec4 position;
//in vec3 normals;
//in mat4 TBN;
//uniform sampler2D tDiffuse;
//
//void main(void)
//{
//	gl_FragData[0] = vec4(texture2D(tDiffuse, gl_TexCoord[0].st).rgb, 0);
//	gl_FragData[1] = vec4(position.xyz, 0);
//	gl_FragData[2] = vec4(normals.xyz, 0);
//}
