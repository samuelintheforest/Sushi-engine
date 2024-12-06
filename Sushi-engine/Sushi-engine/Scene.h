#ifndef SCENE_H
#define SCENE_H


#include "Types.h"
#include "Entity.h"
#include <vector>

namespace sushi {

	typedef struct
	{
		const char sceneDimension;
		const char cameraNumbers;
		const char ppEnabled;
	} SceneDescription;

	constexpr char SCENE_2D = 101;
	constexpr char SCENE_3D = 102;
	constexpr char SCENE_3D_MULTI_DRAW = 103;
	constexpr char POST_PROCESS_ENABLED = 104;
	constexpr char POST_PROCESS_DISABLED = 105;

	class Scene 
	{
	public:
		Scene(SceneDescription* sceneDesc);
		~Scene();
		
		void drawScene();
		void addNewMember(Entity* entity);

	private:
		std::vector<Entity*> sceneEntities;
	};

	

}

#endif // !SCENE_H1
