#pragma once

#include "params.h"

#include <functional>
#include <iostream>
#include <string>
#include <vector>

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
		// 
		static bool check_token_count(const std::vector<std::string> & tokens, size_t min_tokens);

	protected:
		std::istream is;	// stream from remote process
		std::ostream os;	// stream to   remote process
	};
} // namespace uci