#ifndef RENDERER_H
#define RENDERER_H

#ifndef minionstrmerge
#define minionstrmerge(A , B) A B;
#endif

#define SHADER_DIR	"../../../../source/Graphics/shaders/"

#include <string>

class Renderer
{
public:
	virtual void Release() = 0;
	virtual void Clean() {isClean = true;}
	virtual bool IsClean() const {return isClean;}
	virtual const std::string& GetErrorStr() const { return lastError; }

protected:
	bool isClean;
	std::string lastError;
};


#endif // !RENDERER
