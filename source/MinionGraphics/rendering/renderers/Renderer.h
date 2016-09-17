#ifndef RENDERER_H
#define RENDERER_H

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
