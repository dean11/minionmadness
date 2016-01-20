#ifndef MINION_SPRITE_H
#define MINION_SPRITE_H

class MinionSprite
{
public:
	virtual bool CreateSprite(float x, float y, float w, float h, const char* texture) = 0;

private:

};


#endif // !MINION_SPRITE
