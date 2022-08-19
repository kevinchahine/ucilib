#pragma once

#include "uci/commands/command_base.h"

namespace uci
{
	namespace commands
	{
		class ponderhit : public command_base_template<ponderhit>
		{
		public:

			virtual void parse(const std::string& line) override {}

			friend std::ostream& operator<<(std::ostream& os, const ponderhit& obj)
			{
				os << "ponderhit";

				return os;
			}
		};
	} // namespace commands
} // namespace uci
