#ifndef MINION_MODEL_H
#define MINION_MODEL_H

class MinionModel
{
public:
	virtual void	Render() = 0;
	virtual void	RenderShadow() = 0;
	virtual void	Animate() = 0;
	virtual void	SetPosition(float x, float y, float z) = 0;
	virtual void	SetRotation(float x, float y, float z) = 0;
	virtual void	SetScale(float x, float y, float z) = 0;
	virtual void	SetVisibleStatus(bool visible) = 0;
	virtual void	SetAnimateStatus(bool animate) = 0;
	virtual void	SetCollisionStatus(bool animate) = 0;
	virtual void	SetCastShadowStatus(bool shadow) = 0;
	virtual bool	SetDiffuseTexture(const char* filename) = 0;
	virtual bool	SetNormalsTexture(const char* filename) = 0;
	virtual bool	SetSpecularTexture(const char* filename) = 0;
	virtual void	RelativePosition(float x, float y, float z) = 0;
	virtual void	RelativeRotation(float x, float y, float z) = 0;
	virtual void	RelativeScale(float x, float y, float z) = 0;
	virtual void	GetPosition(float& x, float& y, float& z) const = 0;
	virtual void	GetRotation(float& x, float& y, float& z) const = 0;
	virtual void	GetScale(float& x, float& y, float& z) const = 0;
	virtual bool	ShouldRender() const = 0;
	virtual bool	ShouldAnimate() const = 0;
	virtual bool	ShouldCollide() const = 0;
	virtual bool	ShouldCastShadow() const = 0;

};


#endif // !MINION_MODEL
