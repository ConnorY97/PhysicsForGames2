#include "PhysicsScene.h"
#include <iostream>
#include "RigidBody.h"
#include <list>
#include "collision_manager.h"



const collisionFunction PhysicsScene::collisionFunctions[] =
{
	collision_manager::circle_vs_circle,	collision_manager::circle_vs_aabb,	collision_manager::circle_vs_line,
	collision_manager::aabb_vs_circle,		collision_manager::aabb_vs_aabb,	collision_manager::aabb_vs_line,
	collision_manager::line_vs_circle,		collision_manager::line_vs_aabb,	collision_manager::line_vs_line
};

PhysicsScene::PhysicsScene() : m_timeStep(0.01f), m_gravity(glm::vec2(0, 0))
{
}

PhysicsScene::~PhysicsScene()
{	
	for (size_t i = 0; i < m_actors.size(); i++)
	{
		delete m_actors[i];
		m_actors[i] = nullptr;
	}
}

void PhysicsScene::addActor(PhysicsObject* a_actor)
{
	m_actors.push_back(a_actor);
}

void PhysicsScene::removeActor(PhysicsObject* a_actor)
{
	auto location = std::find(m_actors.begin(), m_actors.end(), a_actor);
	m_actors.erase(location); 
	delete a_actor;
	a_actor = nullptr;
}

void PhysicsScene::update(float a_deltaTime)
{
	//Update physics at a fixed time step 

	static float accumulatedTime = 0.0f;
	accumulatedTime += a_deltaTime;

	while (accumulatedTime >= m_timeStep)
	{
		for (auto pActor : m_actors)
		{
			pActor->fixedUpdate(m_gravity, m_timeStep);
		}
		accumulatedTime -= m_timeStep; 
	}

	int actorCount = m_actors.size();

	for (int outer = 0; outer < actorCount - 1; outer++)
	{
		for (int inner = outer + 1; inner < actorCount; inner++)
		{
			PhysicsObject* object1 = m_actors[outer];
			PhysicsObject* object2 = m_actors[inner]; 
			ShapeType shapeID1 = object1->getShape();
			ShapeType shapeID2 = object2->getShape();
			//Using function pointers
			int funcIndex = (int(shapeID1) * int(ShapeType::shapeCount)) + int(shapeID2); 
			collisionFunction collisionFuncPtr = collisionFunctions[funcIndex]; 
			if (collisionFuncPtr != nullptr)
			{
				//Did a collision occur?
				auto result = collisionFuncPtr(object1, object2);
				if (glm::length(result) > 0.001)
				{
					int value = 1; 
					//Resolve collision
						//Seperate 
						//Apple reaction 
				}
			}
		}
	}
	//static std::list<PhysicsObject*> dirty; 
	////Check for collisions (ideally you'd want to have some sort 
	//	//of scene management in place 
	//for (auto pActor : m_actors)
	//{
	//	for (auto pOtherActor : m_actors)
	//	{
	//		if (pActor == pOtherActor)
	//			continue; 
	//		if (std::find(dirty.begin(), dirty.end(), pActor) != dirty.end() &&
	//			std::find(dirty.begin(), dirty.end(), pOtherActor) != dirty.end())
	//			continue; 

	//		RigidBody* pRigidBody = dynamic_cast<RigidBody*>(pOtherActor); 
	//		
	//		if (pRigidBody->checkCollision(pActor))
	//		{
	//			pRigidBody->applyForceToActor(dynamic_cast<RigidBody*>(pActor),
	//				pRigidBody->getVelocity() * pRigidBody->getMass()); 

	//			dirty.push_back(pRigidBody);
	//			dirty.push_back(pOtherActor); 
	//		}
	//	}
	//}
}

void PhysicsScene::updateGizmos()
{
	for (auto pActor : m_actors)
		pActor->makeGizmo(); 
}