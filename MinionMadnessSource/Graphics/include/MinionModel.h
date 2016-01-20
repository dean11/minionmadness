#ifndef MINION_MODEL_H
#define MINION_MODEL_H

class MinionModel
{
public:
	virtual void	Render() = 0;
	virtual void	Animate() = 0;

	virtual void	SetPosition(float x, float y, float z) = 0;
	virtual void	SetRotation(float x, float y, float z) = 0;

	virtual void	AddPosition(float x, float y, float z) = 0;
	virtual void	AddRotation(float x, float y, float z) = 0;

	virtual void	SetVisibleStatus(bool visible) = 0;
	virtual void	SetAnimateStatus(bool animate) = 0;
	virtual void	SetCollisionStatus(bool animate) = 0;

	virtual bool	SetDiffuseTexture(const char* filename) = 0;
	virtual bool	SetNormalsTexture(const char* filename) = 0;
	virtual bool	SetSpecularTexture(const char* filename) = 0;

};


#endif // !MINION_MODEL
