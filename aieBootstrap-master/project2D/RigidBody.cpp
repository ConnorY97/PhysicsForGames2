#include "RigidBody.h"

//By assigining the varaibles in this way they are set before any code is run 
	//Allows for greater code control and run order 
RigidBody::RigidBody(ShapeType a_shapeID, glm::vec2 a_position, glm::vec2 a_velocity, float a_mass) :
	PhysicsObject(a_shapeID),
	m_position(a_position),
	m_velocity(a_velocity),
	m_mass(a_mass)
{
}

RigidBody::~RigidBody()
{

}

void RigidBody::fixedUpdate(glm::vec2 a_gravity, float a_timeStep)
{
	
	applyForce(a_gravity * m_mass * a_timeStep);
	
	m_position += m_velocity * a_timeStep;
}


void RigidBody::applyForce(glm::vec2 a_force)
{
	m_velocity += a_force / m_mass; //F = m * a; == ; a = F / m
}

void RigidBody::applyForceToActor(RigidBody* a_actor2, glm::vec2 a_force)
{
	this->applyForce(-a_force);
	a_actor2->applyForce(a_force);
}

void RigidBody::resolveCollision(RigidBody* a_actor, glm::vec2 a_collisionNormal)
{
	glm::vec2 normal = glm::normalize(a_collisionNormal);

	glm::vec2 relativeVelocity = a_actor->getVelocity() - m_velocity; 

	float elasticity = 1.0f; 

	float j =	glm::dot(-(1 + elasticity) * (relativeVelocity), normal)
											/
				glm::dot(normal, normal * ((1 / m_mass) + (1 / a_actor->getMass()))); 

	glm::vec2 force = normal * j; 

	applyForceToActor(a_actor, force); 
}



