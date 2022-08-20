#pragma once

#include "uci/commands/option.h"

#include <vector>

namespace uci
{
	namespace options
	{
		// TODO: Move this to uci::commands
		class list : public std::vector<commands::option>
		{
		public:

		};
	} // namespace options
} // namespace uci