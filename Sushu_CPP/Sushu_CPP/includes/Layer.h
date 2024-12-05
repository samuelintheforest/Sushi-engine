#ifndef LAYER_H
#define LAYER_H

#include "Entity.h"

/* TODO */

namespace sushi
{

	class Layer : public Entity
	{
	public:
		Layer();
		~Layer();

		void draw() override;

	private:

	};

}

#endif