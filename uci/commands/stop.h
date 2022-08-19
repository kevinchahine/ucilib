#pragma once

#include "uci/commands/command_base.h"
namespace uci
{
	namespace commands
	{
		class stop : public command_base_template<stop>
		{
		public:

			virtual void parse(const std::string& line) override {}

			friend std::ostream& operator<<(std::ostream& os, const stop& obj)
			{
				os << "stop";

				return os;
			}
		};
	} // namespace commands
} // namespace uci

