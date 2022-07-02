#pragma once

#include "uci/commands/command.h"
#include "uci/options/option.h"

namespace uci
{
	namespace options
	{
		// TODO: remove factory class. All we need is uci::options::option::fill_from(cmd);
		// Takes a uci 'command' and creates a cooresponding option object.
		class factory
		{
		public:
			option generate(const Command& cmd);

		private:
		};
	} // namespace options
} // namespace uci