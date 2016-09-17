#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>

class Texture
{
public:
	Texture();
	virtual~Texture();

	int Create(const char* texture);

	GLuint GetHandle() const;

	operator GLuint(){ return textureHandle; }
	operator GLuint() const{ return textureHandle; }

private:
	GLuint	textureHandle;	// OpenGL texture ID
};


#endif // !TEXTURE
