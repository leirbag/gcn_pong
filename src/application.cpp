/***************************************************************************
 *   Copyright (C) 2009 by Gabriel Huau                                    *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "application.h"
#include "inputmanager.h"
#include "messagemanager.h"
#include "intro.h"
#include <SFML/Window.hpp>
#include <iostream>

void Application::handle(const std::string& message)
{
	if(message == "WINDOW_CLOSED") quit();
}

void Application::createWindow()
{
	window.Create(sf::VideoMode(500, 300, 32), "Pong");
}

void Application::initializeStates()
{
	states["INTRO"]    = new Intro();

	setActiveState("INTRO");
}

void Application::initialize()
{
	std::cout << "Initialisation de l'application\n";
	font.LoadFromFile("./resources/cheeseburger.ttf");
	activeState = NULL;
	sound = false;
	createWindow();
	initializeStates();
	MessageManager::getInstancePtr()->addListener(this);
	window.EnableKeyRepeat(false);
}

void Application::run()
{
	running = true;
	while(running)
	{
		window.Clear();

		InputManager::getInstancePtr()->process();
		MessageManager::getInstancePtr()->process();

		if(activeState != NULL)
		{
			activeState->process();
		}

		window.Display();
	}
}

void Application::destroy()
{
	std::cout << "Destruction de l'application\n";
	MessageManager::getInstancePtr()->removeListener(this);
	window.Close();
}

const sf::Font& Application::getFont()
{
	return font;
}

void Application::setSound(bool value)
{
	sound = value;
}

bool Application::hasSound()
{
	return sound;
}

State* Application::getActiveState()
{
	return activeState;
}

void Application::setActiveState(const std::string& name)
{
	State* state = states[name];
	if(state == NULL)
		return;

	if(activeState != NULL)
		activeState->exit();

	activeState = state;
	activeState->enter();
}

sf::RenderWindow& Application::getWindow()
{
	return window;
}

void Application::quit()
{
	running = false;
}
