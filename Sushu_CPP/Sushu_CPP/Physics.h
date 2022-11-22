#pragma once
#ifndef PHYSICS_H
#define PHYSICS_H

#include <limits>
#include <algorithm>
#include <array>
#include <functional>
#include <glm/glm.hpp>


namespace Sushi {
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
			std::array<Sushi::Physics::Box*, 4> contact;
			glm::vec2 velGoal;
		};


		float SweptAABB(Box b1, Box b2, float& normalx, float& normaly);
		bool AABBCheck(Box b1, Box b2);
		Box GetSweptBroadphaseBox(Box b);
		bool Ray_Rect(const glm::vec2 &ray_origin, const glm::vec2 &ray_dir, const Sushi::Physics::Box *target, glm::vec2 &contact_point, glm::vec2 &contact_normal, float& t_hit_near);
		bool Point_Rect(const glm::vec2 &point, const Sushi::Physics::Box *rectangle);
		bool Rect_Rect(const Sushi::Physics::Box* r1, const Sushi::Physics::Box* r2);
		bool DynamicRectVsRect(const Sushi::Physics::Box* r_dynamic, const float fTimeStep, const Sushi::Physics::Box& r_static,
			glm::vec2& contact_point, glm::vec2& contact_normal, float& contact_time);
		bool ResolveDynamicRectVsRect(Sushi::Physics::Box *r_dynamic, const float fTimeStep, Sushi::Physics::Box *r_static);
		float Approach(float flGoal, float flCurrent, float dt);
	}
}


#endif