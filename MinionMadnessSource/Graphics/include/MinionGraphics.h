#ifndef MINIONGRAPHICS_H
#define MINIONGRAPHICS_H

#include "MinionGraphics.h"
#include "MinionModel.h"


/*
*	Initialization information for MinionGraphics
*/
struct MinionGraphicsInitDesc
{
	int windowWidth;
	int windowHeight;
	int windowX;
	int windowY;
	const char* windowName;
	MinionGraphicsInitDesc()
		: windowName("MinionGraphics")
		, windowWidth(640)
		, windowHeight(480)
		, windowX(0)
		, windowY(0)
	{};
};

/*
*	To get a reference of MinionGraphics, use the static function GetGraphicsPointer();
*	Don't forget to releas is when done.
*/
class MinionGraphics
{
public:
	static MinionGraphics* GetGraphicsPointer();

public:
	virtual int InitiateMinionGraphics(const MinionGraphicsInitDesc&) = 0;
	virtual void Release() = 0;
	virtual const char* GetLastError() = 0;

	virtual int SetOption(const char* option, ...) = 0;

	virtual void BeginScene() = 0;
	virtual void EndScene() = 0;

	virtual void BeginGUI() = 0;
	virtual void EndGUI() = 0;

	virtual void BeginText() = 0;
	virtual void EndText() = 0;

	virtual MinionModel* CreateModel(const char* file) = 0;
	virtual MinionModel* CreateModel_Plane(float xsize, float zsize, int xdivs, int zdivs, float smax = 1.0f, float tmax = 1.0f, const char* diffuseTexture = 0) = 0;
	virtual MinionModel* CreateModel_Cube(float width, float height, float depth) = 0;
	virtual MinionModel* CreateModel_Sphere(float radius) = 0;

protected:
	virtual ~MinionGraphics();
};

#endif // !MINIONGRAPHICS
