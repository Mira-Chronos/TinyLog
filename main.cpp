/*
 *
 * Copyright 2021 Mira
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 *
 */

#include <stdio.h>
#include <iostream>
#include "TLog.hpp"

int main(int argc, char* argv[])
{
	//oepn file 
	TLog::get()->open("log.txt");

	// parameters specification
	TLog::get()->debugOnConsole(true);
	TLog::get()->debugWithTimer(false);
	
	TLog::get()->write("hello world");	
	*TLog::get() << LOG_TYPE::L_ERROR << "starter wrong" << LOG_TYPE::L_INFO << "help on";
	
	TLog::ss() << LOG_TYPE::L_WARNING << "missing chipset";
	TLog::ss() << LOG_TYPE::L_DEBUG << "var undefine";
	TLog::ss() << LOG_TYPE::L_CRITICAL << "engine fail";
	
	TLog::get()->write("fin", LOG_TYPE::L_OTHER );

	TLog::get()->close();
	return 0;
}
