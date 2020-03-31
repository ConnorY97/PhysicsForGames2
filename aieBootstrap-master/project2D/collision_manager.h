#pragma once
#include "circle.h"
#include "line.h"
#include "aligned_bounding_box.h"
#include "glm/glm.hpp"


class collision_manager
{
public:
	static glm::vec2 circle_vs_circle(const PhysicsObject* a_circle_A,
									const PhysicsObject* a_circle_B);
	//---------------------------------------------------------------------
	static glm::vec2 aabb_vs_aabb(	const PhysicsObject* a_aabb_A,
									const PhysicsObject* a_aabb_B);
	//---------------------------------------------------------------------
	static glm::vec2 line_vs_line(	const PhysicsObject* a_line_A,
									const PhysicsObject* a_line_B);
	//---------------------------------------------------------------------
	static glm::vec2 aabb_vs_circle(const PhysicsObject* a_aabb,
									const PhysicsObject* a_circle);
	
	static glm::vec2 circle_vs_aabb(const PhysicsObject* a_circle,
									const PhysicsObject* a_aabb);
	//---------------------------------------------------------------------
	static glm::vec2 circle_vs_line(const PhysicsObject* a_circle,
									const PhysicsObject* a_line);

	static glm::vec2 line_vs_circle(const PhysicsObject* a_line,
									const PhysicsObject* a_circle);
	//---------------------------------------------------------------------
	static glm::vec2 aabb_vs_line(	const PhysicsObject* a_aabb,
									const PhysicsObject* a_line);
	static glm::vec2 line_vs_aabb(	const PhysicsObject* a_line,
									const PhysicsObject* a_aabb);
	//---------------------------------------------------------------------

private:
	static glm::vec2 clamp(const glm::vec2& a_vector_2,
						  const glm::vec2& a_min,
						  const glm::vec2& a_max);
};

