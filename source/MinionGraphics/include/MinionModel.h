#ifndef MINION_MODEL_H
#define MINION_MODEL_H

namespace minion
{
	class MinionModel
	{
	public:
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
		virtual void	RelativeMovement(float x, float y, float z) = 0;
		virtual void	RelativeRotation(float x, float y, float z) = 0;
		virtual void	RelativeScaling(float x, float y, float z) = 0;
		virtual void	GetPosition(float& x, float& y, float& z) const = 0;
		virtual void	GetRotation(float& x, float& y, float& z) const = 0;
		virtual void	GetScale(float& x, float& y, float& z) const = 0;
	};
}



#endif // !MINION_MODEL
