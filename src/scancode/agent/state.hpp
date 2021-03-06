/*
 * Copyright (C) 2014-2015, Siemens AG
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifndef SCANCODE_AGENT_STATE_HPP
#define SCANCODE_AGENT_STATE_HPP

#include "databasehandler.hpp"
#include "libfossdbmanagerclass.hpp"

using namespace std;

class State
{
public:
  State(int agentId);

  int getAgentId() const;

private:
  int agentId;
};

#endif // SCANCODE_AGENT_STATE_HPP
