#pragma once

#include "uci/commands/command.h"
#include "uci/options/option.h"

namespace uci
{
	namespace options
	{
		// Takes a uci 'command' and creates a cooresponding option object.
		class factory
		{
		public:
			option generate(const Command& cmd);

		private:
		};
	} // namespace options
} // namespace uci