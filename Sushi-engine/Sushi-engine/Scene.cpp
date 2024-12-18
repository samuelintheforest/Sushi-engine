#include "Scene.h"

sushi::Scene::Scene(SceneDescription* sceneDesc)
{
	sceneDesc = 0;
}

sushi::Scene::~Scene()
{

}

/*Drawing the scene*/
void sushi::Scene::drawScene()
{
	for (Entity* entity : sceneEntities)
	{
		entity->draw();
	}
}

// /*Adding New Entity members to the scene*/
void sushi::Scene::addNewMember(Entity* entity)
{
	this->sceneEntities.push_back(entity);
	std::cout << sceneEntities.size() << std::endl;
}
