#ifndef PHYSICS_H
#define PHYSICS_H

#include <limits>
#include <algorithm>
#include <array>
#include <functional>
#include <glm/glm.hpp>


namespace sushi {
	namespace Physics {

		float constrain(float n, float low, float high);
		//struct Box {
		//	// position of top-left corner 
		//	float x, y;

		//	// dimensions 
		//	float w, h;

		//	// velocity 
		//	float vx, vy;
		//};
		class Mover
		{
		public:
			Mover(float x, float y, float m);
			~Mover();
			void update(float dt);
			void applyForce(glm::vec2& force);
			glm::vec2 pos = glm::vec2(0.0f, 0.0f);
			unsigned int size = 0;
			float mass = 0;
		private:
			
			glm::vec2 vel = glm::vec2(0.0f, 0.0f);
			glm::vec2 acc = glm::vec2(0.0f, 0.0f);
		};


		class Attractor
		{
		public:
			Attractor(float x, float y, float m);
			~Attractor();
			void attract(Mover* mov_obj);
			glm::vec2 pos = glm::vec2(0.0f, 0.0f);
			unsigned int size = 0;

		private: 
			
			float mass = 0;
		};

		struct Box
		{
			glm::vec2 pos;
			glm::vec2 size;
			glm::vec3 color;
			glm::vec2 vel;
			std::array<sushi::Physics::Box*, 4> contact;
			glm::vec2 velGoal;
			glm::vec2 prev_pos;
		};


		float SweptAABB(Box b1, Box b2, float& normalx, float& normaly);
		bool AABBCheck(Box b1, Box b2);
		Box GetSweptBroadphaseBox(Box b);
		bool Ray_Rect(const glm::vec2 &ray_origin, const glm::vec2 &ray_dir, const sushi::Physics::Box *target, glm::vec2 &contact_point, glm::vec2 &contact_normal, float& t_hit_near);
		bool Point_Rect(const glm::vec2 &point, const sushi::Physics::Box *rectangle);
		bool Rect_Rect(const sushi::Physics::Box* r1, const sushi::Physics::Box* r2);
		bool DynamicRectVsRect(const sushi::Physics::Box* r_dynamic, const float fTimeStep, const sushi::Physics::Box& r_static,
			glm::vec2& contact_point, glm::vec2& contact_normal, float& contact_time);
		bool ResolveDynamicRectVsRect(sushi::Physics::Box *r_dynamic, const float fTimeStep, sushi::Physics::Box *r_static);
		float Approach(float flGoal, float flCurrent, float dt);
	}
}


#endif