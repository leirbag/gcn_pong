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

#include "gameinfo.h"
#include "levelinfo.h"
#include "gamemanager.h"
#include "application.h"
#include "messagemanager.h"
#include <iostream>
#include <sstream>

GameInfo::GameInfo()
{
	font = Application::getInstancePtr()->getFont();
}

void GameInfo::handle(const std::string& message)
{
	if(message == "GAMEINFO_CONTINUE") Application::getInstancePtr()->setActiveState("GAME");
}

void GameInfo::enter()
{	
	MessageManager::getInstancePtr()->addListener(this);
}

void GameInfo::exit()
{
	MessageManager::getInstancePtr()->removeListener(this);
}

void GameInfo::draw()
{
	int width = Application::getInstancePtr()->getWindow().GetDefaultView().GetRect().GetWidth();
	LevelInfo levelInfo = GameManager::getInstancePtr()->getLevelInfo();

	std::ostringstream oss;
	oss << "Level : " << levelInfo.getLevel(); 
	sf::String text(oss.str(), font, 40);
	text.SetX(width * 0.5 - (text.GetRect().GetWidth() *0.5));
	text.SetY(150.0f);
	Application::getInstancePtr()->getWindow().Draw(text);

	sf::String text3(levelInfo.getInformations(), font, 30);
	text3.SetX(width * 0.5 - (text3.GetRect().GetWidth() *0.5));
	text3.SetY(200.0f);
	Application::getInstancePtr()->getWindow().Draw(text3);

	sf::String text2("press enter to play", font, 30);
	text2.SetX(width * 0.5 - (text2.GetRect().GetWidth() *0.5));
	text2.SetY(400.0f);
	Application::getInstancePtr()->getWindow().Draw(text2);
}

void GameInfo::update()
{
}


