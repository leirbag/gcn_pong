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

#ifndef INCLUDE_MESSAGEMANAGER
#define INCLUDE_MESSAGEMANAGER

#include "singleton.h"
#include <list>
#include <stack>
#include <string>

class Listener;

class MessageManager : public Singleton<MessageManager>
{
	private:
		std::list<Listener*> listeners;

		std::stack<std::string> messages;

	public:
		virtual ~MessageManager();

		void enqueueMessage(const std::string& message);

		void addListener(Listener* listener);

		void removeListener(Listener* listener);

		void removeAll();

		void process();
};

#endif
