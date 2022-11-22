#pragma once
#ifndef SCENE_H
#define SCENE_H

namespace Sushi {
	namespace Scene {
		constexpr char SCENE_2D = 101;
		constexpr char SCENE_3D = 102;
		constexpr char SCENE_3D_MULTI_DRAW = 103;
		constexpr char POST_PROCESS_ENABLED = 104;
		constexpr char POST_PROCESS_DISABLED = 105;

		struct SceneDescription
		{
			const char sceneDimension;
			const char cameraNumbers;
			const char ppEnabled;
		};
	}
}

#endif // !SCENE_H1
