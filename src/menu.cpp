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

#include "menu.h"
#include "application.h"
#include "messagemanager.h"
#include <iostream>

Menu::Menu()
{
	font = Application::getInstancePtr()->getFont();
	choix = new std::string[2];
	choix[0] = "New Game";
	choix[1] = "Quit";

	titre = "Menu";

	selectionned = 0;
}

void Menu::handle(const std::string& message)
{
	if(message == "MENU_SELECT")
	{
		if(selectionned == 1) Application::getInstancePtr()->quit();
		if(selectionned == 0) Application::getInstancePtr()->setActiveState("GAMEINFO");
	}

	if(message == "MENU_DOWN") selectionned++;	
	if(message == "MENU_UP") selectionned--;

	if(selectionned > 1) selectionned = 0;
	if(selectionned < 0) selectionned = 1;
}

void Menu::enter()
{	
	MessageManager::getInstancePtr()->addListener(this);
}

void Menu::exit()
{
	MessageManager::getInstancePtr()->removeListener(this);
}

void Menu::draw()
{
	int width = Application::getInstancePtr()->getWindow().GetDefaultView().GetRect().GetWidth();

	sf::String text2(titre, font, 50);
	text2.SetX(width * 0.5 - (text2.GetRect().GetWidth() *0.5));
	text2.SetY(50.0f);
	Application::getInstancePtr()->getWindow().Draw(text2);

	sf::String text(choix[0], font, 30);
	text.SetX(width * 0.5 - (text.GetRect().GetWidth() *0.5));
	text.SetY(50.0f);
	if(0 == selectionned) text.SetColor(sf::Color(128, 0, 0));
	else text.SetColor(sf::Color(255, 255, 255));
	Application::getInstancePtr()->getWindow().Draw(text);

	text.SetText(choix[1]);
	text.SetX(width * 0.5 - (text.GetRect().GetWidth() *0.5));
	text.SetY(100.0f);
	if(1 == selectionned) text.SetColor(sf::Color(128, 0, 0));
	else text.SetColor(sf::Color(255, 255, 255));
	Application::getInstancePtr()->getWindow().Draw(text);
}

void Menu::update()
{
}
