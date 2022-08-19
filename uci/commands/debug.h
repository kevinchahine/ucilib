#pragma once

#include "uci/commands/command_base.h"

namespace uci
{
	namespace commands
	{
		class debug : public command_base_template<debug>
		{
		public:
			virtual void parse(const std::string& line) override;

			friend std::ostream& operator<<(std::ostream& os, const debug& obj)
			{
				os << "debug " << (obj.is_on ? "on" : "off");

				return os;
			}

		public:
			bool is_on = false;
		};
	} // namespace commands
} // namespace uci