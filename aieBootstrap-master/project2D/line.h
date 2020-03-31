#pragma once
#include "PhysicsObject.h"
class line : public PhysicsObject
{
public:
	line(const glm::vec2& a_normal, const float a_distance = 0.0f);

	const glm::vec2 get_normal() const;
	void set_normal(const glm::vec2& a_normal);

	const float get_distance() const;
	void set_distance(const float a_distance);

	//Implementation of virual members
	void debug() override {}
	void fixedUpdate(glm::vec2 gravity, float timeStep) override {}
	void makeGizmo() override; 



private:
	glm::vec2 m_normal = glm::vec2(0,1);
	float m_distanceFromOrigin = 0.0f;
};

