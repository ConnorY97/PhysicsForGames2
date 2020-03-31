#pragma once
#include "RigidBody.h"

class circle : public RigidBody
{
public:
	circle(glm::vec2 a_position, glm::vec2 a_veloctiy,
			float a_mass, float a_radious,
			glm::vec4 a_colour); 

	//~circle(); 

	const float GetRadious() const;
	
	/*	@brief Sets the radius to the absolute value of the argument
		@param The new radius as float
	*/
	void SetRadious(const float a_radius);

	virtual void makeGizmo();
	virtual bool checkCollision(PhysicsObject* a_pOther);


	glm::vec4 getColour() { return m_colour; }
	const glm::vec2 getPosition() const;
	void setPosition(const glm::vec2& a_position);

	virtual void debug() override {}

private:
	float m_radius = 0.0f;
	glm::vec4 m_colour; 
};


