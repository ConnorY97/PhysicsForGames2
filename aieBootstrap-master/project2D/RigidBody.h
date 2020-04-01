#pragma once
#include "PhysicsObject.h"
class RigidBody : public PhysicsObject
{
protected:
	RigidBody(ShapeType a_shapeID, glm::vec2 a_position, glm::vec2 a_velocity, float a_mass);
public:
	~RigidBody();

	
	virtual void fixedUpdate(glm::vec2 a_gravity, float a_timeStep);

	virtual void debug() {};

	//Applying a single force to the actor
		//E.g. gravity or thrust 
	void applyForce(glm::vec2 a_force);

	//Applying force and result of a colision 
	void applyForceToActor(RigidBody* a_actor2, glm::vec2 a_force);

	//Probably remove this later 
	virtual bool checkCollision(PhysicsObject* a_pOther) = 0;

	glm::vec2 getPosition() const { return m_position; }
	glm::vec2 getVelocity() const { return m_velocity; }
	float getMass() const { return m_mass; }

	void setVelocity(glm::vec2 a_velocity) { m_velocity = a_velocity; }
	void setPosition(glm::vec2 a_pos) { m_position = a_pos; }

protected:
	glm::vec2 m_position;
	glm::vec2 m_velocity;
	float m_mass;
};

