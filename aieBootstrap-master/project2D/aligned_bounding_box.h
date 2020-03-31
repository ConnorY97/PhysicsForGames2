#pragma once
#include "RigidBody.h"

class aligned_bounding_box : public RigidBody
{
public:

	static const glm::vec2 DEFAULT_EXTENTS;

	aligned_bounding_box(const glm::vec2& a_position = glm::vec2(0.0f),
						 const glm::vec2& a_extents = DEFAULT_EXTENTS,
						 const glm::vec2& a_velocity = glm::vec2(0.0f),
						 const float a_mass = 1.0f);

	const glm::vec2 get_position() const;
	void set_position(const glm::vec2& a_position);

	const glm::vec2 get_extents() const;
	void set_extents(const glm::vec2& a_extents);

	const float get_width() const;
	const float get_height() const;

	const glm::vec2 get_min() const;
	const glm::vec2 get_max() const;

	//Implementation of virual members
	void debug() override {}

	bool checkCollision(PhysicsObject* a_pOther) override { return false; }

	void makeGizmo() override;

private:
	
	//Unions share the same memorey
		//Which allows you multiple ways to acces the varaibles 
		//And allows for the values to be assinged in multiple ways 
	union
	{
		//When adding and AABB multiply by .5 so that the bootsrap draws them properly 
		glm::vec2 m_extents;
		struct
		{
			float m_width;
			float m_height;
		};
	};
};

