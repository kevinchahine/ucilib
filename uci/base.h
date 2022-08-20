#pragma once

#include <boost/process/pipe.hpp>

#include "commands/command.h"

#include <functional>
#include <iostream>
#include <string>
#include <vector>
#include <list>

namespace uci
{
	// Base class of both gui and engine.
	// gui - represents a UCI compatible Chess GUI
	// engine - represents a UCI compatible Chess Engine
	// Data is transmitted through streams (istream and ostream)
	// 
	// send methods are always non-blocking and can be called at
	// anytime. They should be called in a way that conforms with 
	// the UCI protocol. 
	//
	// Handle methods should only be called internally by the base,
	// engine and gui objects. Handle methods are called
	// asynchronously on a separate thread. These methods will 
	// 
	class base
	{
	protected:
		// reads characters from `is` stream parses into a command and 
		// pushes to `commands_in` list
		// blocking call. function blocks until entire currline is read from input stream
		// Only valid commands will be inserted into `commands_in`
		// Invalid commands will be ignored
		void parse_line(std::istream& is);
		
		// TODO: Make this the only recv_until. Remove the derived classes implementations of it
		////const commands::command& recv_until(const commands::command& cmd_to_wait_for);

	public:
		// commands are appended to back on list (push_back() emplace_back())
		// commands are removed and handled from front of list
		std::list<commands::command> commands_in;	// stores parsed commands from `is`
	};
} // namespace uci