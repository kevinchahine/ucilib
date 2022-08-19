#pragma once

#include "uci/commands/command_base.h"

namespace uci
{
	namespace commands
	{
		class setoption : public command_base_template<setoption>
		{
		public:

			virtual void parse(const std::string& line) override;

			friend std::ostream& operator<<(std::ostream& os, const setoption& obj)
			{
				os << "setoption name " << obj.id;

				if (obj.x.has_value()) {
					os << " value " << obj.x.value();
				}

				return os;
			}

			std::string id;
			std::optional<std::string> x;
		};
	} // namespace commands
} // namespace uci

