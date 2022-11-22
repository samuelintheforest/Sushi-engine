#include "Physics.h"
#include <iostream>
#include <random>

float Sushi::Physics::constrain(float n, float low, float high)
{
	if (n >= high)
	{
		return high;
	}
	else if (n <= low) {
		return low;
	}

	return n;
}

float Sushi::Physics::SweptAABB(Box b1, Box b2, float& normalx, float& normaly)
{
	float xInvEntry, yInvEntry;
	float xInvExit, yInvExit;

	// find the distance between the objects on the near and far sides for both x and y 
	if (b1.vel.x > 0.0f)
	{
		xInvEntry = b2.pos.x - (b1.pos.x + b1.size.x);
		xInvExit = (b2.pos.x + b2.size.x) - b1.pos.x;
	}
	else
	{
		xInvEntry = (b2.pos.x + b2.size.x) - b1.pos.x;
		xInvExit = b2.pos.x - (b1.pos.x + b1.size.x);
	}

	if (b1.vel.y > 0.0f)
	{
		yInvEntry = b2.pos.y - (b1.pos.y + b1.size.y);
		yInvExit = (b2.pos.y + b2.size.y) - b1.pos.y;
	}
	else
	{
		yInvEntry = (b2.pos.y + b2.size.y) - b1.pos.y;
		yInvExit = b2.pos.y - (b1.pos.y + b1.size.y);
	}

	// find time of collision and time of leaving for each axis (if statement is to prevent divide by zero) 
	float xEntry, yEntry;
	float xExit, yExit;

	if (b1.vel.x == 0.0f)
	{
		xEntry = -std::numeric_limits<float>::infinity();
		xExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		xEntry = xInvEntry / b1.vel.x;
		xExit = xInvExit / b1.vel.x;
	}

	if (b1.vel.y == 0.0f)
	{
		yEntry = -std::numeric_limits<float>::infinity();
		yExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		yEntry = yInvEntry / b1.vel.y;
		yExit = yInvExit / b1.vel.y;
	}

	// find the earliest/latest times of collisionfloat 
	float entryTime = std::max(xEntry, yEntry);
	float exitTime = std::min(xExit, yExit);

	// if there was no collision
	if ((entryTime > exitTime) || (xEntry < 0.0f && yEntry < 0.0f) || (xEntry > 1.0f || yEntry > 1.0f))
	{

		normalx = 0.0f;
		normaly = 0.0f;
		return 1.0f;
	} 
	
	else // if there was a collision 
	{
		// calculate normal of collided surface
		if (xEntry > yEntry)
		{
			if (xInvEntry < 0.0f)
			{
				normalx = 1.0f;
				normaly = 0.0f;
			}
			else
			{
				normalx = -1.0f;
				normaly = 0.0f;
			}
		}
		else
		{
			if (yInvEntry < 0.0f)
			{
				normalx = 0.0f;
				normaly = 1.0f;
			}
			else
			{
				normalx = 0.0f;
				normaly = -1.0f;
			}
		} // return the time of collisionreturn entryTime; 


		


	}





	//return 0.0f;
}

bool Sushi::Physics::AABBCheck(Box b1, Box b2)
{
	return !(b1.pos.x + b1.size.x < b2.pos.x || 
		b1.pos.x > b2.pos.x + b2.size.x || 
		b1.pos.y + b1.size.y < b2.pos.y || 
		b1.pos.y > b2.pos.y + b1.size.y);
}

Sushi::Physics::Box Sushi::Physics::GetSweptBroadphaseBox(Sushi::Physics::Box b)
{
	Sushi::Physics::Box broadphasebox;
	broadphasebox.pos.x = b.vel.x > 0 ? b.pos.x : b.pos.x + b.vel.x;
	broadphasebox.pos.y = b.vel.y > 0 ? b.pos.y : b.pos.y + b.vel.y;
	broadphasebox.size.x = b.vel.x > 0 ? b.vel.x + b.size.x : b.size.x - b.vel.x;
	broadphasebox.size.y = b.vel.y > 0 ? b.vel.y + b.size.y : b.size.y - b.vel.y;

	return broadphasebox;
}

bool Sushi::Physics::Ray_Rect(const glm::vec2& ray_origin, const glm::vec2& ray_dir, const Sushi::Physics::Box* target, glm::vec2& contact_point, glm::vec2& contact_normal, float& t_hit_near)
{
	contact_normal = { 0,0 };
	contact_point = { 0,0 };

	// Cache division
	glm::vec2 invdir = 1.0f / ray_dir;

	// Calculate intersections with rectangle bounding axes
	glm::vec2 t_near = (target->pos - ray_origin) * invdir;
	glm::vec2 t_far = (target->pos + target->size - ray_origin) * invdir;

	if (std::isnan(t_far.y) || std::isnan(t_far.x)) return false;
	if (std::isnan(t_near.y) || std::isnan(t_near.x)) return false;

	// Sort distances
	if (t_near.x > t_far.x) std::swap(t_near.x, t_far.x);
	if (t_near.y > t_far.y) std::swap(t_near.y, t_far.y);

	// Early rejection		
	if (t_near.x > t_far.y || t_near.y > t_far.x) return false;

	// Closest 'time' will be the first contact
	t_hit_near = std::max(t_near.x, t_near.y);

	// Furthest 'time' is contact on opposite side of target
	float t_hit_far = std::min(t_far.x, t_far.y);

	// Reject if ray direction is pointing away from object
	if (t_hit_far < 0)
		return false;

	// Contact point of collision from parametric line equation
	contact_point = ray_origin + t_hit_near * ray_dir;

	if (t_near.x > t_near.y)
		if (invdir.x < 0)
			contact_normal = { 1, 0 };
		else
			contact_normal = { -1, 0 };
	else if (t_near.x < t_near.y)
		if (invdir.y < 0)
			contact_normal = { 0, 1 };
		else
			contact_normal = { 0, -1 };

	// Note if t_near == t_far, collision is principly in a diagonal
	// so pointless to resolve. By returning a CN={0,0} even though its
	// considered a hit, the resolver wont change anything.
	return true;
}

bool Sushi::Physics::Point_Rect(const glm::vec2& point, const Sushi::Physics::Box* rectangle)
{
	return (
		point.x >= rectangle->pos.x && 
		point.y >= rectangle->pos.y && 
		point.x < rectangle->pos.x + rectangle->size.x && 
		point.y < rectangle->pos.y + rectangle->size.y
	);
}

bool Sushi::Physics::Rect_Rect(const Sushi::Physics::Box* r1, const Sushi::Physics::Box* r2)
{
	return (
		r1->pos.x < r2->pos.x + r2->size.x && 
		r1->pos.x + r1->size.x > r2->pos.x && 
		r1->pos.y < r2->pos.y + r2->size.y && 
		r1->pos.y + r1->size.y > r2->pos.y
	);
}

bool Sushi::Physics::DynamicRectVsRect(const Sushi::Physics::Box* r_dynamic, const float fTimeStep, const Sushi::Physics::Box& r_static, glm::vec2& contact_point, glm::vec2& contact_normal, float& contact_time)
{
	// Check if dynamic rectangle is actually moving - we assume rectangles are NOT in collision to start
	if (r_dynamic->vel.x == 0 && r_dynamic->vel.y == 0)
		return false;

	// Expand target rectangle by source dimensions
	Sushi::Physics::Box expanded_target;
	expanded_target.pos = r_static.pos - r_dynamic->size / 2.f;
	expanded_target.size = r_static.size + r_dynamic->size;

	if (Sushi::Physics::Ray_Rect(r_dynamic->pos + r_dynamic->size / 2.f, r_dynamic->vel * fTimeStep, &expanded_target, contact_point, contact_normal, contact_time))
		return (contact_time >= 0.0f && contact_time < 1.0f);
	else
		return false;
}

bool Sushi::Physics::ResolveDynamicRectVsRect(Sushi::Physics::Box* r_dynamic, const float fTimeStep, Sushi::Physics::Box* r_static)
{

	glm::vec2 contact_point, contact_normal;
	float contact_time = 0.0f;
	if (DynamicRectVsRect(r_dynamic, fTimeStep, *r_static, contact_point, contact_normal, contact_time))
	{
		if (contact_normal.y > 0) r_dynamic->contact[0] = r_static; else nullptr;
		if (contact_normal.x < 0) r_dynamic->contact[1] = r_static; else nullptr;
		if (contact_normal.y < 0) r_dynamic->contact[2] = r_static; else nullptr;
		if (contact_normal.x > 0) r_dynamic->contact[3] = r_static; else nullptr;

		r_dynamic->vel += contact_normal * glm::vec2(std::abs(r_dynamic->vel.x), std::abs(r_dynamic->vel.y)) * (1 - contact_time);
		return true;
	}

	return false;
}

float Sushi::Physics::Approach(float flGoal, float flCurrent, float dt)
{
	float flDifference = flGoal - flCurrent;

	if (flDifference > dt)
		return flCurrent + dt;
	if (flDifference < -dt)
		return flCurrent - dt;

	return flGoal;
}

Sushi::Physics::Attractor::Attractor(float x, float y, float m)
{
	pos.x = x;
	pos.y = y;
	mass = m;
	size = sqrt(mass) * 2;
	pos = glm::vec2(x - size / 2, y - size / 2);
}

Sushi::Physics::Attractor::~Attractor()
{
}

void Sushi::Physics::Attractor::attract(Mover* mov_obj)
{
	glm::vec2 force = pos - mov_obj->pos;
	float distanceSq = constrain((force.x * force.x + force.y + force.y), 100, 1000);
	float G = 1;

	float strength = G * (mass * mov_obj->mass) / distanceSq;
	force = glm::normalize(force);
	//std::cout << force.x << ", " << force.y << std::endl;
	force *= strength;
	mov_obj->applyForce(force);
	
}

Sushi::Physics::Mover::Mover(float x, float y, float m)
{
	mass = m;
	
	size = sqrt(m) * 2;
	pos = glm::vec2(x - size / 2, y - size / 2);

	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_real_distribution<float> random_velocity_x(-1.00, 1.00); // distribution in range [1, 6]
	std::uniform_real_distribution<float> random_velocity_y(-1.00, 1.00); // distribution in range [1, 6]

	vel.x = random_velocity_x(rng);
	vel.y = random_velocity_y(rng);
	vel *= 5;
}

Sushi::Physics::Mover::~Mover()
{
}

void Sushi::Physics::Mover::update(float dt)
{
	vel += acc;
	pos += vel;
	acc = glm::vec2(0.0f, 0.0f);

}

void Sushi::Physics::Mover::applyForce(glm::vec2& force)
{
	glm::vec2 f = force / mass;
	acc += f;
}
