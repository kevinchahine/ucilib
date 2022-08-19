#pragma once

#include "uci/commands/command_base.h"

namespace uci
{
	namespace commands
	{
		class id : public command_base_template<id>
		{
		public:

			virtual void parse(const std::string& line) override;

			friend std::ostream& operator<<(std::ostream& os, const id& id)
			{
				os << "id";

				if (id.name.size()) {
					os << " name " << id.name;
				}
				else if (id.author.size()) {
					os << " author " << id.author;
				}

				return os;
			}

		public:
			std::string name;
			std::string author;
		};
	} // namespace commands
} // namespace uci
