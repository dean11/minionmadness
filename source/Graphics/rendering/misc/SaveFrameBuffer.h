#ifndef SAVE_FRAME_BUFFER_H
#define SAVE_FRAME_BUFFER_H

#include <glew.h>

class SaveFrameBuffer
{
public:
	SaveFrameBuffer()
	{
		glGetIntegerv(GL_FRAMEBUFFER_BINDING, &fbo);
	}
	~SaveFrameBuffer()
	{
		if (fbo != 0)
			glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbo);
	}

private:
	GLint fbo;
};


#endif // !SAVE_FRAME_BUFFER
