#include "Application2D.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "Gizmos.h"
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "PhysicsScene.h"
#include "circle.h"
#include "aligned_bounding_box.h"

Application2D::~Application2D() 
{
	delete m_physicsScene;
	m_physicsScene = nullptr;
}

bool Application2D::startup() 
{	
	//Increase the 2D line count to maximize the number of objects we can draw
	aie::Gizmos::create(255U, 255U, 65535U, 65535U);

	m_2dRenderer = new aie::Renderer2D();

	m_texture = new aie::Texture("./textures/numbered_grid.tga");
	m_shipTexture = new aie::Texture("./textures/ship.png");

	m_font = new aie::Font("./font/consolas.ttf", 32);

	m_physicsScene = new PhysicsScene();
	m_physicsScene->setTimeStep(0.01f); 
	m_physicsScene->setGravity(glm::vec2(0.0f));
	
	m_timer = 0;

	line* base = new line(glm::vec2(0.0f, 1.0f), -50.0f); 
	line* lhs = new line(glm::vec2(1.0f, 0.0f), -85.0f); 
	line* rhs = new line(glm::vec2(-1.0f, 0.0f), -85.0f); 
	line* lhd = new line(glm::vec2(1.0f), -60.0f); 
	line* rhd = new line(glm::vec2(-1.0f, 1.0f), -60.0f);

	m_physicsScene->addActor(base);
	m_physicsScene->addActor(lhs);
	m_physicsScene->addActor(rhs);
	m_physicsScene->addActor(lhd);
	m_physicsScene->addActor(rhd);

	circle* c1 = new circle(glm::vec2(-70.0f, -30.0f), glm::vec2(0.0f), 1.0f, 5.0f, glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
	circle* c2 = new circle(glm::vec2(0.0f, -10.0f), glm::vec2(0.0f), 1.0f, 5.0f, glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));


	m_physicsScene->addActor(c1);
	m_physicsScene->addActor(c2);

	aligned_bounding_box* b1 = new aligned_bounding_box(glm::vec2(-70.0f, -10.0f), glm::vec2(10.0f));
	aligned_bounding_box* b2 = new aligned_bounding_box(glm::vec2(0.0f, -25.0f), glm::vec2(10.0f));
	m_physicsScene->addActor(b1); 
	m_physicsScene->addActor(b2); 
	return true;
}

void Application2D::shutdown() 
{
	aie::Gizmos::destroy(); 
	delete m_font;
	delete m_texture;
	delete m_shipTexture;
	delete m_2dRenderer;	
}

void Application2D::update(float deltaTime) {

	m_timer += deltaTime;

	// input example
	aie::Input* input = aie::Input::getInstance();

	aie::Gizmos::clear();

	m_physicsScene->update(deltaTime);
	m_physicsScene->updateGizmos();

	// Update the camera position using the arrow keys
	float camPosX;
	float camPosY;
	m_2dRenderer->getCameraPos(camPosX, camPosY);

	if (input->isKeyDown(aie::INPUT_KEY_UP))
		camPosY += 500.0f * deltaTime;

	if (input->isKeyDown(aie::INPUT_KEY_DOWN))
		camPosY -= 500.0f * deltaTime;

	if (input->isKeyDown(aie::INPUT_KEY_LEFT))
		camPosX -= 500.0f * deltaTime;

	if (input->isKeyDown(aie::INPUT_KEY_RIGHT))
		camPosX += 500.0f * deltaTime;

	m_2dRenderer->setCameraPos(camPosX, camPosY);

	if (input->isKeyDown(aie::INPUT_KEY_SPACE))
	{
		m_physicsScene->setGravity(glm::vec2(0.0f, -50.0f)); 
	}

#pragma region stuff

	/*
	static const glm::vec4 colours[] =
	{
		glm::vec4(1,0,0,1), glm::vec4(0,1,0,1),
		glm::vec4(0,0,1,1), glm::vec4(0.8f,0,0.5f,1),
		glm::vec4(0,1,1,1)
	};

	static const int rows = 5;
	static const int columns = 10;
	static const int hSpace = 1;
	static const int vSpace = 1;

	static const glm::vec2 scrExtents(100, 50);
	static const glm::vec2 boxExtents(7, 3);
	static const glm::vec2 startPos(-(columns >> 1)* ((boxExtents.x * 2) + vSpace)
									+ boxExtents.x + (vSpace / 2.0f),
									scrExtents.y - ((boxExtents.y * 2) + hSpace));

	//Draw the grid blocks
	glm::vec2 pos;
	for (int y = 0; y < rows; y++)
	{
		pos = glm::vec2(startPos.x, startPos.y - (y * ((boxExtents.y * 2) + hSpace)));
		for (int x = 0; x < columns; x++)
		{
			aie::Gizmos::add2DAABBFilled(pos, boxExtents, colours[y]);
			pos.x += (boxExtents.x * 2) + vSpace;
		}
	}

	//Draw the ball
	aie::Gizmos::add2DCircle(glm::vec2(0, -35), 3, 12, glm::vec4(1, 1, 0, 1));

	//Draw the player's paddle
	aie::Gizmos::add2DAABBFilled(	glm::vec2(0, -40), glm::vec2(12, 2),
									glm::vec4(1, 0, 1, 1));

	*/





#pragma endregion

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void Application2D::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();
	
	static float aspectRatio = 16.0f / 9.0f;
	aie::Gizmos::draw2D(glm::ortho<float>(-100, 100, -100 / aspectRatio, 100 / aspectRatio, -1.0f, 1.0f)); 
	
	// output some text, uses the last used colour
	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", getFPS());
	m_2dRenderer->drawText(m_font, fps, 0, 720 - 32);
	m_2dRenderer->drawText(m_font, "Press ESC to quit!", 0, 720 - 64);

	// done drawing sprites
	m_2dRenderer->end();
}