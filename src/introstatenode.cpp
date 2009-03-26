/***************************************************************************
 *   Copyright (C) 2006 by Gabriel Huau                                    *
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

#include "introstatenode.h"
#include "messagemanager.h"
#include "application.h"

IntroStateNode::IntroStateNode()
{
	font = Application::getInstancePtr()->getFont();
	clock.Reset();
	message  = "     By Gabriel\n"; 
	message += "    For the GCN\n";
	message += "  Because Gnoll Rox\n";
	message += "http://www.gnoll.org";

	MessageManager::getInstancePtr()->addListener(this);
}

IntroStateNode::~IntroStateNode()
{
	MessageManager::getInstancePtr()->removeListener(this);	
}

void IntroStateNode::handle(const std::string& message)
{
	if(message == "INTRO_SKIP") Application::getInstancePtr()->setActiveState("MENU");
}

void IntroStateNode::draw()
{
	int width = Application::getInstancePtr()->getWindow().GetDefaultView().GetRect().GetWidth();

	//
	// Center the text
	//
	sf::String text(message, font, 20);
	text.SetX(width * 0.5 - (text.GetRect().GetWidth() *0.5));
	text.SetY(50.0f);
	Application::getInstancePtr()->getWindow().Draw(text);

	sf::String text2("Press any key to skip", font, 30);
	text2.SetX(width * 0.5 - (text2.GetRect().GetWidth() *0.5));
	text2.SetY(200.0f);
	Application::getInstancePtr()->getWindow().Draw(text2);
}

void IntroStateNode::update()
{
	if(clock.GetElapsedTime() > 7)
		Application::getInstancePtr()->setActiveState("MENU");
}
