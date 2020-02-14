//Course: GAME 3001 Assignment 1
//Name: Wanhao (Jerry) Sun and Zijie (Louis) Zhang
#include "Game.h"
#include "Util.h"

Game* Game::s_pInstance = 0;

glm::vec2 Game::getTargetPosition()
{
	return m_pTarget->getPosition();
}

SDL_Renderer * Game::getRenderer()
{
	return m_pRenderer;
}

glm::vec2 Game::getMousePosition()
{
	return m_mousePosition;
}

Game::Game():m_debug(false)
{
	m_doAvoid = false;
	m_pause = true;
}

Game::~Game()
{
}

void Game::createGameObjects()
{
	m_pShip = new ship();
	m_pTarget = new Target();
	m_pObstacle = new Obstacle();
	m_pBackground = new Background();
}

bool Game::init(const char* title, int xpos, int ypos, int height, int width, bool fullscreen)
{
	

	int flags = 0;

	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	// initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
	{
		std::cout << "SDL Init success" << std::endl;

		// if succeeded create our window
		m_pWindow = SDL_CreateWindow(title, xpos, ypos, height, width, flags);

		// if window creation successful create our renderer
		if (m_pWindow != 0)
		{
			std::cout << "window creation success" << std::endl;
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);

			if (m_pRenderer != 0) // render init success
			{
				std::cout << "renderer creation success" << std::endl;
				SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);
			}
			else
			{
				std::cout << "renderer init failure" << std::endl;
				return false; // render int fail
			}
			//TheTextureManager::Instance()->load("../../Assets/textures/animate-alpha.png", "animate", m_pRenderer);
			createGameObjects();
		}
		else 
		{
			std::cout << "window init failure" << std::endl;
			return false; // window init fail
		}
	}
	else
	{
		std::cout << "SDL init failure" << std::endl;
		return false; //SDL could not intialize
	}
	SoundManager::Instance()->playMusic("bgm" , -1);
	std::cout << "init success" << std::endl;
	m_bRunning = true; // everything initialized successfully - start the main loop

	return true;
}

void Game::render()
{
	if (m_pause) {
		SDL_RenderClear(m_pRenderer); // clear the renderer to the draw colour
		m_pBackground->draw();

		SDL_RenderPresent(m_pRenderer); // draw to the screen
	}
	else {
		SDL_RenderClear(m_pRenderer); // clear the renderer to the draw colour
		m_pTarget->draw();
		m_pShip->draw();
		m_pObstacle->draw();

		if (m_debug)
		{
			Util::DrawRect(m_pObstacle->getPosition() - glm::vec2(m_pObstacle->getWidth() * 0.5, m_pObstacle->getHeight() * 0.5), m_pObstacle->getWidth(), m_pObstacle->getHeight());
			Util::DrawCircle(m_pShip->getPosition(), m_pShip->getHeight() * 0.5);
			Util::DrawCircle(m_pTarget->getPosition(), m_pTarget->getHeight() * 0.5);

			Util::DrawLine(m_pShip->getPosition(), m_pShip->getPosition() + m_pShip->getCurrentDirection() * 50.0f);

			Util::DrawLine(m_pShip->getPosition() + 20.0f, m_pShip->getPosition() + m_pShip->getCurrentDirection() * 50.0f + 5.0f);
			Util::DrawLine(m_pShip->getPosition() - 20.0f, m_pShip->getPosition() + m_pShip->getCurrentDirection() * 50.0f - 5.0f);
		}

		SDL_RenderPresent(m_pRenderer); // draw to the screen
	}
}

void Game::update()
{
	m_pShip->update();
	m_pTarget->update();
	m_pObstacle->update();

	CollisionManager::circleAABBCheck(m_pShip, m_pObstacle);
	CollisionManager::squaredRadiusCheck(m_pShip, m_pTarget);

	bool checkMid, checkLeft, checkRight, checkCircle;
	if (m_doAvoid) {
		checkMid = CollisionManager::lineAABBCheck(m_pShip, m_pObstacle);
		checkLeft = CollisionManager::lineAABBCheckLeft(m_pShip, m_pObstacle);
		checkRight = CollisionManager::lineAABBCheckRight(m_pShip, m_pObstacle);
		if (checkMid || checkLeft || checkRight)
		{
			m_pShip->setSteeringState(AVOID);
		}
		else {
			m_pShip->setSteeringState(SEEK);
		}
	}
}

void Game::clean()
{
	std::cout << "cleaning game" << std::endl;

	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);
	SDL_Quit();
}

void Game::handleEvents()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			m_bRunning = false;
			break;
		case SDL_MOUSEMOTION:
			m_mousePosition.x = event.motion.x;
			m_mousePosition.y = event.motion.y;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
				case SDLK_ESCAPE:
					m_bRunning = false;
					break;
				case SDLK_w:
					m_pShip->setTargetPosition(m_pTarget->getPosition());
					m_pTarget->setVelocity(glm::vec2(m_pTarget->getVelocity().x, -1.0f));
					break;
				case SDLK_s:
					m_pShip->setTargetPosition(m_pTarget->getPosition());
					m_pTarget->setVelocity(glm::vec2(m_pTarget->getVelocity().x, 1.0f));
					break;
				
				case SDLK_a:
					m_pShip->setTargetPosition(m_pTarget->getPosition());
					m_pTarget->setVelocity(glm::vec2(-1.0f, m_pTarget->getVelocity().y));
					break;
				case SDLK_d:
					m_pShip->setTargetPosition(m_pTarget->getPosition());
					m_pTarget->setVelocity(glm::vec2(1.0f, m_pTarget->getVelocity().y));
					break;
				case SDLK_0:
					m_pause = !m_pause;
					m_pShip->setSteeringState(SteeringState::IDLE);
					break;
				case SDLK_1:
					m_pause = false;
					m_doAvoid = false;
					m_pShip->setTargetPosition(m_pTarget->getPosition());
					m_pShip->setSteeringState(SteeringState::SEEK);
					break;
				case SDLK_2:
					m_pause = false;
					m_doAvoid = false;
					m_pShip->setTargetPosition(m_pTarget->getPosition());
					m_pShip->setSteeringState(SteeringState::ARRIVE);
					break;
				case SDLK_3:
					m_pause = false;
					m_pShip->setTargetPosition(m_pTarget->getPosition());
					m_doAvoid = true;
					break;
				case SDLK_4:
					m_pause = false;
					m_doAvoid = false;
					m_pShip->setTargetPosition(m_pTarget->getPosition());
					m_pShip->setSteeringState(SteeringState::FLEE);
					break;
				case SDLK_RIGHT:
					m_pShip->turnRight();
					break;
				case SDLK_LEFT:
					m_pShip->turnLeft();
					break;
				case SDLK_UP:
					m_pShip->setVelocity(m_pShip->getCurrentDirection());
					m_pShip->move();
					break;
				case SDLK_b:
					m_debug = !m_debug;
					break;
			}
			break;
		case SDL_KEYUP:
			switch (event.key.keysym.sym) {
				case SDLK_w:
					if (m_pTarget->getVelocity().y < 0.0f) {
						m_pTarget->setVelocity(glm::vec2(m_pTarget->getVelocity().x, 0.0f));
					}
					break;
				
				case SDLK_s:
					if (m_pTarget->getVelocity().y > 0.0f) {
						m_pTarget->setVelocity(glm::vec2(m_pTarget->getVelocity().x, 0.0f));
					}
					break;
				
				case SDLK_a:
					if (m_pTarget->getVelocity().x < 0.0f) {
						m_pTarget->setVelocity(glm::vec2(0.0f, m_pTarget->getVelocity().y));
					}
					break;
				case SDLK_d:
					if (m_pTarget->getVelocity().x > 0.0f) {
						m_pTarget->setVelocity(glm::vec2(0.0f, m_pTarget->getVelocity().y));
					}
					break;
				case SDLK_RIGHT:
					
					break;
				case SDLK_LEFT:
					
					break;
				case SDLK_UP:
					
					break;
			}
			
		default:
			break;
		}
	}
}