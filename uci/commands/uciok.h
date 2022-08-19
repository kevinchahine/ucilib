#pragma once

#include "uci/commands/command_base.h"
namespace uci
{
	namespace commands
	{
		class uciok : public command_base_template<uciok>
		{
		public:

			virtual void parse(const std::string& line) override {}

			friend std::ostream& operator<<(std::ostream& os, const uciok& obj)
			{
				os << "uciok";

				return os;
			}
		};
	} // namespace commands
} // namespace uci

