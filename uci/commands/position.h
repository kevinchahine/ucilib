#pragma once

#include "uci/commands/command.h"

namespace uci
{
	namespace commands
	{
		class position : public Command
		{
		public:
			void* to_position() const;
		};
	} // namespace commands
} // namespace uci