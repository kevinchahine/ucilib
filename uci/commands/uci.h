#pragma once

#include "uci/commands/command_base.h"


namespace uci
{
	namespace commands
	{
		class uci : public command_base_template<uci>
		{
		public:

			virtual void parse(const std::string& line) override {}

			friend std::ostream& operator<<(std::ostream& os, const uci& obj)
			{
				os << "uci";

				return os;
			}
		};
	} // namespace commands
} // namespace uci
