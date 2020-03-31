#include "Triangle.h"
#include <utilities.h>
using namespace minion;

Triangle::Triangle(const Vec3& v1, const Vec3& v2, const Vec3& v3)
{
	Vec3 positionData[] =
	{
		v1, v2, v3
	};

	auto t = sizeof(positionData);

	float colorData[] = 
	{
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f 
	};

	// Create and populate the buffer objects
	GLuint vboHandles[2];
	glGenBuffers(2, vboHandles);
	GLuint positionBufferHandle = vboHandles[0];
	GLuint colorBufferHandle = vboHandles[1];

	glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positionData), positionData, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colorData), colorData, GL_STATIC_DRAW);

	// Create and set-up the vertex array object
	glGenVertexArrays(1, &vaoHandle);
	glBindVertexArray(vaoHandle);

	glEnableVertexAttribArray(0);  // Vertex position
	glEnableVertexAttribArray(1);  // Vertex color

	glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte *)NULL);

	glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte *)NULL);

	//glDeleteBuffers(NoEdgeUtilies::StaticArray::NumElementsOf(vboHandles), vboHandles);
}
Triangle::~Triangle()
{ }

void Triangle::Draw()
{
	glBindVertexArray(vaoHandle);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}
void Triangle::Release()
{
	if (this->vaoHandle)
		glDeleteVertexArrays(1, &this->vaoHandle);
	this->vaoHandle = 0;
}