#pragma once
#include <vector>
#include "PhysicsObject.h"


#include <functional>
using collisionFunction = std::function<glm::vec2(const PhysicsObject*, const PhysicsObject*)>;

#ifndef _PHYSICS_SCENE_H_


class PhysicsScene
{
public:
	PhysicsScene();
	~PhysicsScene();

	void addActor(PhysicsObject* a_actor);
	void removeActor(PhysicsObject* a_actor);
	void update(float a_deltaTime);
	void updateGizmos();

	void setGravity(const glm::vec2 a_gravity) { m_gravity = a_gravity; }
	glm::vec2 getGravity() const { return m_gravity; }

	void setTimeStep(const float a_timeStep) { m_timeStep = a_timeStep; }
	float getTimeStep() const { return m_timeStep; }

	//using collisionFunction = std::function<glm::vec2(const PhysicsObject*, const PhysicsObject*)>; 

	static const collisionFunction collisionFunctions[];

protected:
	glm::vec2 m_gravity;
	float m_timeStep;
	std::vector<PhysicsObject*> m_actors;

};

#endif // !_PHYSICS_SCENE_H_
