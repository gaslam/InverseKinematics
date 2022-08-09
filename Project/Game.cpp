#include "pch.h"
#include "Game.h"
#include "Point.h"
#include "utils.h"
#include <iostream>

Game::Game(const Window& window)
	:m_Window{ window }
{
	Initialize();
}

Game::~Game()
{
	Cleanup();
}

void Game::Initialize()
{
	ShowInstructions();
	Point2f newPoint{ m_Window.width / 4, m_Window.height / 8 };
	Point2f newPoint2{ m_Window.width / 4, (m_Window.height / 8) * 3 };
	Point2f newPoint3{ (m_Window.width / 4) + (newPoint2.y - newPoint.y), (m_Window.height / 8) * 3 };
	Point2f newPoint4{ newPoint3.x + 100, newPoint3.y + 200 };
	m_Points.push_back(newPoint);
	m_Points.push_back(newPoint2);
	m_Points.push_back(newPoint3);

	const Point2f target { 130,170 };
	utils::CalculateCCD(m_Points, target);
}

void Game::Cleanup()
{
}

void Game::Update(float elapsedSec)
{
	// Check keyboard state
	//const Uint8 *pStates = SDL_GetKeyboardState( nullptr );
	//if ( pStates[SDL_SCANCODE_RIGHT] )
	//{
	//	std::cout << "Right arrow key is down\n";
	//}
	//if ( pStates[SDL_SCANCODE_LEFT] && pStates[SDL_SCANCODE_UP])
	//{
	//	std::cout << "Left and up arrow keys are down\n";
	//}
}

void Game::Draw() const
{
	ClearBackground();
	Point2f previousPos;
	for (size_t i{}; i < m_Points.size(); ++i)
	{
		Point2f newPos{ m_Points[i] };
		utils::FillEllipse(newPos, m_Radius, m_Radius);
		if (i > 0)utils::DrawLine(newPos, previousPos);
		previousPos = newPos;
	}
}

void Game::ProcessKeyDownEvent(const SDL_KeyboardEvent& e)
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;

	switch (e.keysym.sym)
	{
	case SDLK_f:
		m_CanFollowMouse = !m_CanFollowMouse;
		break;
	}
}

void Game::ProcessKeyUpEvent(const SDL_KeyboardEvent& e)
{
	//std::cout << "KEYUP event: " << e.keysym.sym << std::endl;
	//switch ( e.keysym.sym )
	//{
	//case SDLK_LEFT:
	//	//std::cout << "Left arrow key released\n";
	//	break;
	//case SDLK_RIGHT:
	//	//std::cout << "`Right arrow key released\n";
	//	break;
	//case SDLK_1:
	//case SDLK_KP_1:
	//	//std::cout << "Key 1 released\n";
	//	break;
	//}
}

void Game::ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
	if (!m_CanFollowMouse) return;

	Point2f mousePos{ float(e.x),float(e.y) };
	utils::CalculateCCD(m_Points, mousePos);
}

void Game::ProcessMouseDownEvent(const SDL_MouseButtonEvent& e)
{
	//std::cout << "MOUSEBUTTONDOWN event: ";
	const Point2f mousePos{ float(e.x),float(e.y) };
	switch (e.button)
	{
	case SDL_BUTTON_LEFT:
		HandleLeftMouseButton(mousePos);
		break;
	}
}

void Game::ProcessMouseUpEvent(const SDL_MouseButtonEvent& e)
{
	//std::cout << "MOUSEBUTTONUP event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}

void Game::ClearBackground() const
{
	glClearColor(0.0f, 0.0f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Game::HandleLeftMouseButton(const Point2f& mousePos)
{
	const Uint8* pStates{ SDL_GetKeyboardState(nullptr) };

	if (pStates[SDL_SCANCODE_LSHIFT])
	{
		m_Points.push_back(mousePos);
	}
	utils::CalculateCCD(m_Points, mousePos);
}

void Game::ShowInstructions() const
{
	std::cout << "--- Inverse Kinematics ---\n\n";
	std::cout << "-- Instructions --\n\n";
	std::cout << "F = Toggle whether the end point should follow the mouse cursor or not.\n";
	std::cout << "Left Mouse Button = Set new target.\n";
	std::cout << "LSHIFT + Left Mouse Button = Add point to the joints.\n";
}
