#ifndef SAVE_VIEWPORT_H
#define SAVE_VIEWPORT_H

#include <glew.h>

class SaveViewport
{
public:
	SaveViewport()
	{
		glGetIntegerv(GL_VIEWPORT, m_viewport);
	}
	virtual~SaveViewport()
	{
		glViewport(m_viewport[0], m_viewport[1], m_viewport[2], m_viewport[3]);
	}

private:
	GLint m_viewport[4];
};


#endif // !SAVE_VIEWPORT
