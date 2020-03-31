#include "aligned_bounding_box.h"
#include <cmath>

const glm::vec2 aligned_bounding_box::DEFAULT_EXTENTS = { 5.0f, 5.0f };

aligned_bounding_box::aligned_bounding_box(	const glm::vec2& a_position /*= vector_2()*/,
											const glm::vec2& a_extents /*= DEFAULT_EXTENTS*/,
											const glm::vec2& a_velocity /*= vector2(0.0f)*/,
											const float a_mass /*= 1.0f*/) :
RigidBody(	ShapeType::aabb,
			a_position,
			a_velocity,
			a_mass)		
{	
	m_extents = a_extents; 
}

const glm::vec2 aligned_bounding_box::get_position() const
{
	return m_position;
}

void aligned_bounding_box::set_position(const glm::vec2& a_position)
{
	m_position = a_position;
}

const glm::vec2 aligned_bounding_box::get_extents() const
{
	return m_extents;
}

void aligned_bounding_box::set_extents(const glm::vec2& a_extents)
{
	m_extents = { abs(a_extents.x), abs(a_extents.y) };
}

const float aligned_bounding_box::get_width() const
{
	return m_width;
}

const float aligned_bounding_box::get_height() const
{
	return m_height;
}

const glm::vec2 aligned_bounding_box::get_min() const
{
	return m_position - 0.5f * m_extents;
}

const glm::vec2 aligned_bounding_box::get_max() const
{
	return m_position + 0.5f * m_extents;
}

void aligned_bounding_box::makeGizmo()
{
	aie::Gizmos::add2DAABB(m_position, (m_extents * 0.5f), glm::vec4(0.0f, 1.0f, 1.0f, 1.0f));
}