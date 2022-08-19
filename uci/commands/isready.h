#pragma once

#include "uci/commands/command_base.h"

namespace uci
{
	namespace commands
	{
		class isready : public command_base_template<isready>
		{
		public:
			virtual void parse(const std::string& line) override { /* nothing to do here */ }

			friend std::ostream& operator<<(std::ostream& os, const isready& obj)
			{
				os << "isready";

				return os;
			}
		};
	} // namespace commands
} // namespace uci
