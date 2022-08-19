#pragma once

#include "uci/commands/command_base.h"
namespace uci
{
	namespace commands
	{
		class readyok : public command_base_template<readyok>
		{
		public:

			virtual void parse(const std::string& line) override {}

			friend std::ostream& operator<<(std::ostream& os, const readyok& obj)
			{
				os << "readyok";

				return os;
			}
		};
	} // namespace commands
} // namespace uci

