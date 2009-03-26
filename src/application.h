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

#ifndef INCLUDE_APPLICATION
#define INCLUDE_APPLICATION

#include "singleton.h"
#include "listener.h"
#include <SFML/Graphics.hpp>
#include <map>
#include <string>

class State;

class Application : public Singleton<Application>, public Listener
{
	private:
		bool                                 running;

		sf::RenderWindow                     window;	

		sf::Font                             font;

		std::map<std::string, State*>        states;

		State*                               activeState;

		bool                                 sound;

		void createWindow();

		void initializeStates();

	public:
		void handle(const std::string& message);

		void initialize();

		void run();

		void destroy();

		bool hasSound();

		void setSound(bool value);

		const sf::Font& getFont();

		State* getActiveState();

		void setActiveState(const std::string& name);

		sf::RenderWindow& getWindow();
		
		void quit();
};

#endif
