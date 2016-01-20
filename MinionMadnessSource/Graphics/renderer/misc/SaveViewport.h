#ifndef SAVE_VIEWPORT_H
#define SAVE_VIEWPORT_H

#include <glew.h>

class SaveViewport
{
public:
	SaveViewport()
	{
		GLint m_viewport[4];

		glGetIntegerv(GL_VIEWPORT, m_viewport);
		this->x = m_viewport[0];
		this->y = m_viewport[1];
		this->w = m_viewport[2];
		this->h = m_viewport[3];
	}
	virtual~SaveViewport()
	{
		glViewport(this->x, this->y, this->w, this->h);
	}

private:
	int x, y, w, h;
};


#endif // !SAVE_VIEWPORT
