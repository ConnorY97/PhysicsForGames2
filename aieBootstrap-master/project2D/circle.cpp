#include "circle.h"
#include <cmath>
#include "collision_manager.h"

circle::circle(glm::vec2 a_position, glm::vec2 a_veloctiy, float a_mass, float a_radious, glm::vec4 a_colour) :
	RigidBody(ShapeType::circle, a_position, a_veloctiy, a_mass),
	m_radius(a_radious),
	m_colour(a_colour)
{}

const float circle::GetRadious() const
{
	return m_radius;
}

void circle::SetRadious(const float a_radius)
{
	m_radius = abs(a_radius);
}

const glm::vec2 circle::getPosition() const
{
	return m_position;
}

void circle::setPosition(const glm::vec2& a_position)
{
	m_position = a_position;
}

void circle::makeGizmo()
{
	aie::Gizmos::add2DCircle(m_position, m_radius, 32, m_colour); 
}

bool circle::checkCollision(PhysicsObject* a_pOther)
{
	return false; // return collision_manager::circle_vs_circle(*this, (circle&)*a_pOther);
}


