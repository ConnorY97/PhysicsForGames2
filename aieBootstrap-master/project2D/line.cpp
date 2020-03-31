#include "line.h"

line::line(const glm::vec2& a_normal /* = { 0.0f, 1.0f }*/,
			const float a_distance /*= 0.0f*/)  : 
	PhysicsObject(ShapeType::line),
	m_normal(a_normal),
	m_distanceFromOrigin(a_distance)
{
	set_normal(m_normal);
}

const glm::vec2 line::get_normal() const
{
	return m_normal;
}

void line::set_normal(const glm::vec2& a_normal)
{
	if (glm::length(a_normal) <= 0)
	{

	}
	else
	{
		m_normal = glm::normalize(a_normal); 
	}
}

const float line::get_distance() const
{
	return m_distanceFromOrigin;
}

void line::set_distance(const float a_distance)
{
	m_distanceFromOrigin = a_distance;
}

void line::makeGizmo()
{
	glm::vec2 centrePoint = m_normal * m_distanceFromOrigin;
	glm::vec2 drawDirection(m_normal.y, -m_normal.x); 
	aie::Gizmos::add2DLine(centrePoint + (drawDirection * 500.0f), 
							centrePoint - (drawDirection * 500.0f), 
							glm::vec4(1.0f));
}