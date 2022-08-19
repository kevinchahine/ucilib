#pragma once

#include "uci/commands/command_base.h"
namespace uci
{
	namespace commands
	{
		class ucinewgame : public command_base_template<ucinewgame>
		{
		public:

			virtual void parse(const std::string& line) override {}

			friend std::ostream& operator<<(std::ostream& os, const ucinewgame& obj)
			{
				os << "ucinewgame";

				return os;
			}
		};
	} // namespace commands
} // namespace uci

