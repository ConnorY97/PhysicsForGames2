#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "line.h"

//Forward declaration 
	//Promise that there is a definition in the of these classes down the line 
class PhysicsScene;
class aligned_bounding_box; 

class Application2D : public aie::Application 
{
public:

	/*Application2D();*/
	virtual ~Application2D();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	aie::Renderer2D*		m_2dRenderer;
	aie::Texture*			m_texture;
	aie::Texture*			m_shipTexture;
	aie::Font*				m_font;


	PhysicsScene*			m_physicsScene; 

	float m_timer;
};