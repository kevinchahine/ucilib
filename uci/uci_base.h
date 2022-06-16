#pragma once

#include "params.h"
#include "command.h"

#include <functional>
#include <iostream>
#include <string>
#include <vector>
#include <list>

#include <boost/process/pipe.hpp>

namespace uci
{
	// Base class of both UciServer and UciClient.
	// UciServer - represents a UCI compatible Chess GUI
	// UciClient - represents a UCI compatible Chess Engine
	// Data is transmitted through streams (istream and ostream)
	// 
	// send methods are always non-blocking and can be called at
	// anytime. They should be called in a way that conforms with 
	// the UCI protocol. 
	//
	// Handle methods should only be called internally by the UciBase,
	// UciClient and UciServer objects. Handle methods are called
	// asynchronously on a separate thread. These methods will 
	// 
	class UciBase
	{
	public:
		UciBase() = default;
		UciBase(const UciBase&) = default;
		UciBase(UciBase&&) noexcept = default;
		~UciBase() noexcept = default;
		UciBase& operator=(const UciBase&) = default;
		UciBase& operator=(UciBase&&) noexcept = default;

		// 
		static bool check_token_count(const std::vector<std::string> & tokens, size_t min_tokens);

	protected:
		// reads characters from `is` stream parses into a command and 
		// pushes to `commands_in` list
		// blocking call. function blocks until entire line is read from input stream
		// Only valid commands will be inserted into `commands_in`
		// Invalid commands will be ignored
		void getline();

	protected:
		//std::istream is;	// stream from remote process
		//std::ostream os;	// stream to   remote process
		boost::process::ipstream is;
		boost::process::opstream os;

		// commands are appended to back on list (push_back() emplace_back())
		// commands are removed and handled from front of list
		std::list<Command> commands_in;	// stores parsed commands from `is`
	};
} // namespace uci