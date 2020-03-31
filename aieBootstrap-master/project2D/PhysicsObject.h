#pragma once
#include "glm/glm.hpp"
#include "Gizmos.h"

//All enums should be of type class
	//This stops you being to type a variable and having equal the value 
	//So now to use a enum u must have class and declare with the name of enum
enum class ShapeType : char
{
	//none = 0,
	circle = 0,
	aabb,
	line,
	shapeCount
};

#ifndef  _PHYSICS_OBJECT_H_
#define _PHYSICS_OBJECT_H_

class PhysicsObject
{
protected:
	PhysicsObject(ShapeType a_shapeID) : m_shapeID(a_shapeID) {}
public:
	virtual void fixedUpdate(glm::vec2 gravity, float timeStep) = 0;
	virtual void debug() = 0;
	virtual void makeGizmo() = 0;
	virtual void resetPosition() {};

	ShapeType getShape() const { return m_shapeID; }

protected:
	ShapeType m_shapeID; 
};

#endif // ! _PHYSICS_OBJECT_H_
