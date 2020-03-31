#ifndef RENDERER_H
#define RENDERER_H
#include "../../models/Model.h"
#include "../../include/MinionCamera.h"

#include <string>
#include <vector>

class Renderer
{
public:
	virtual void QueueModel(Model* m)
	{
		if (!m->ShouldRender())
			return;

		if (this->modelQueueLenght < this->modelQueue.size())
		{
			this->modelQueue[modelQueueLenght] = m;
			this->modelQueueLenght++;
		}
		else
		{
			this->modelQueue.push_back(m);
			this->modelQueueLenght++;
		}
	}
	virtual void ProcessRenderQueue(std::shared_ptr<MinionCamera>& camera)
	{
		for (size_t i = 0; i < this->modelQueueLenght; i++)
		{
			// Render & stuff
			this->modelQueue[i]->Draw();
		}

		// Every model is processed, set counter to 0
		this->modelQueueLenght = 0;
	}
	virtual void ClearRenderQueue()
	{
		std::fill(this->modelQueue.begin(), this->modelQueue.end(), nullptr);
		this->modelQueueLenght = 0;
	}

protected:
	std::vector<Model*> modelQueue;
	unsigned int modelQueueLenght = 0;
};


#endif // !RENDERER
