#pragma once

#include "uci/commands/command_base.h"

namespace uci
{
	namespace commands
	{
		class quit : public command_base_template<quit>
		{
		public:

			virtual void parse(const std::string& line) override {}

			friend std::ostream& operator<<(std::ostream& os, const quit& obj)
			{
				os << "quit";

				return os;
			}
		};
	} // namespace commands
} // namespace uci

