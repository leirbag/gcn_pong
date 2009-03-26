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

#include "messagemanager.h"
#include "listener.h"
#include "application.h"
#include <iostream>
#include <vector>

MessageManager::~MessageManager()
{
	removeAll();
}

void MessageManager::enqueueMessage(const std::string& message)
{
	messages.push(message);
}

void MessageManager::addListener(Listener* listener)
{
	if(listener == NULL)
		return;

	listeners.push_front(listener);
}

void MessageManager::removeListener(Listener* listener)
{
	if(listener == NULL)
		return;

	listeners.remove(listener);
}

void MessageManager::removeAll()
{
	listeners.clear();
}

void MessageManager::process()
{
	std::list<Listener*>::iterator iter; // Iterator on listeners
	
	// 
	// Get listeners into a vector
	// Solution for the problem if a handle add a listener during the process
	//
	std::vector<Listener*> tempListeners;
	for(iter = listeners.begin(); iter != listeners.end(); iter++)
		tempListeners.push_back(*iter);

	//
	// Process each event on each listener
	//
	while(!messages.empty())
	{
		// 
		// Stock message and pop it before to process it in
		// listener to avoid a "cyclic" loop if a handle 
		// enqueue a message
		//
		std::string message = messages.top();
		messages.pop();
		for(int i = 0; i < tempListeners.size(); i++)
		{
			tempListeners[i]->handle(message);
		}
	}
}
