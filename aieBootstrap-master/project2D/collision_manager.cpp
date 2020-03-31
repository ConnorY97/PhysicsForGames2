#include "collision_manager.h"
#include <cmath>
#include <math.h>

glm::vec2 collision_manager::circle_vs_circle(
	const PhysicsObject* a_circle_A,
	const PhysicsObject* a_circle_B)
{
	const circle* c1 = dynamic_cast<const circle*>(a_circle_A);
	const circle* c2 = dynamic_cast<const circle*>(a_circle_B);

	assert(c1 && c2 && "Circle1 or circle2 was null in collision check");

	glm::vec2 displacement = (c1->getPosition() - c2->getPosition());

	float sum_of_radii = c1->GetRadious() + c2->GetRadious();
	float overLap = (sum_of_radii)-glm::length(displacement); 
	if (overLap > 0.0f)
	{
		return glm::normalize(displacement) * overLap;
	}
	else 
		return glm::vec2(0.0f); 
}
//---------------------------------------------------------------------
glm::vec2 collision_manager::aabb_vs_aabb(const PhysicsObject* a_aabb_A,
	const PhysicsObject* a_aabb_B)
{
	const aligned_bounding_box* a1 = dynamic_cast<const aligned_bounding_box*>(a_aabb_A);
	const aligned_bounding_box* a2 = dynamic_cast<const aligned_bounding_box*>(a_aabb_B);

	const float maxOverlap = 10000000000.0f;
	float overlap = maxOverlap; //<- numeric float limit would be nice 

	glm::vec2 overlapVector = glm::vec2(0.0f);

	//Given A and B are aabbs, lets check each axis for an overlap 
	//Checking x axis----------------------------------------------------
	if (a1->get_max().x > a2->get_min().x)
	{
		float localOverlap = a1->get_max().x - a2->get_max().x;
		if (localOverlap < overlap)
		{
			overlap = localOverlap;
			overlapVector = glm::vec2(overlap, 0.0f);
		}
	}
	else
		return glm::vec2(0.0f);
	if (a1->get_min().x < a2->get_max().x)
	{
		float localOverlap = a1->get_min().x - a2->get_min().x;
		if (localOverlap < overlap)
		{
			overlap = localOverlap;
			overlapVector = glm::vec2(-overlap, 0.0f); 
		}
	}
	else
		return glm::vec2(0.0f);
	//--------------------------------------------------------------------
	//Checking y axis-----------------------------------------------------
	if (a1->get_max().y > a2->get_min().y)
	{
		float localOverlap = a1->get_max().y - a2->get_max().y;
		if (localOverlap < overlap)
		{
			overlap = localOverlap;
			overlapVector = glm::vec2(0.0f, overlap);
		}
	}
	else
		return glm::vec2(0.0f);
	if (a1->get_min().y < a2->get_max().y)
	{
		float localOverlap = a1->get_min().y - a2->get_min().y;
		if (localOverlap < overlap)
		{
			overlap = localOverlap;
			overlapVector = glm::vec2(0.0f, -overlap);
		}
	}
	else
		return glm::vec2(0.0f);
}
//---------------------------------------------------------------------
glm::vec2 collision_manager::line_vs_line(const PhysicsObject* a_line_A,
	const PhysicsObject* a_line_B)
{
	return glm::vec2(0.0f);
}
//---------------------------------------------------------------------
glm::vec2 collision_manager::aabb_vs_circle(const PhysicsObject* a_aabb,
	const PhysicsObject* a_circle)
{
	const aligned_bounding_box* a = dynamic_cast<const aligned_bounding_box*>(a_aabb);
	const circle* c = dynamic_cast<const circle*>(a_circle); 

	glm::vec2 clampledCentre = glm::clamp(c->getPosition(), a->get_min(), a->get_max());

	glm::vec2 displacement = clampledCentre - c->getPosition();

	float overlap = c->GetRadious() - glm::length(displacement);

	if (overlap > 0.0f)
	{
		return glm::normalize(displacement) * overlap;
	}
	else
		return glm::vec2(0.0f); 
}

glm::vec2 collision_manager::circle_vs_aabb(const PhysicsObject* a_circle,
	const PhysicsObject* a_aabb)
{
	return aabb_vs_circle(a_aabb, a_circle);
}
//---------------------------------------------------------------------
glm::vec2 collision_manager::circle_vs_line(const PhysicsObject* a_circle,
	const PhysicsObject* a_line)
{
	const circle* c = dynamic_cast<const circle*>(a_circle);
	const line* l = dynamic_cast<const line*>(a_line);

	assert(c && l && "Circle or line was null in collision check");

	float positionDotNormal = glm::dot(c->getPosition(), l->get_normal());

	float distance = positionDotNormal - (l->get_distance() + c->GetRadious());

	if (distance < 0.0f)
		return l->get_normal() * distance;
	else
		return glm::vec2(0.0f);
}

glm::vec2 collision_manager::line_vs_circle(const PhysicsObject* a_line,
	const PhysicsObject* a_circle)
{
	return circle_vs_line(a_circle, a_line);
}
//---------------------------------------------------------------------
glm::vec2 collision_manager::aabb_vs_line(const PhysicsObject* a_aabb,
	const PhysicsObject* a_line)
{
	const aligned_bounding_box* a = dynamic_cast<const aligned_bounding_box*>(a_aabb); 
	const line* l = dynamic_cast<const line*>(a_line);

	glm::vec2 extents = 0.5f * a->get_extents();
	glm::vec2 extentsNegX = 0.5f * glm::vec2(-a->get_extents().x, a->get_extents().y);

	float dotExtents = glm::dot(extents, l->get_normal()); 
	float dotExtentsNegX = glm::dot(extentsNegX, l->get_normal());

	float radious = fmaxf(fabsf(dotExtents), fabsf(dotExtentsNegX));

	circle projection(a->get_position(), glm::vec2(0.0f), a->getMass(), radious, glm::vec4(0.0f)); 
	return circle_vs_line(&projection, a_line); 

	//return glm::vec2(0.0f);

}

glm::vec2 collision_manager::line_vs_aabb(const PhysicsObject* a_line,
	const PhysicsObject* a_aabb)
{
	return aabb_vs_line(a_aabb, a_line);
}
//---------------------------------------------------------------------

