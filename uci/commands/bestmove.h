#pragma once

#include "uci/commands/command_base.h"

namespace uci
{
	namespace commands
	{
		class bestmove : public command_base_template<bestmove>
		{
		public:

			virtual void parse(const std::string& line) override;

			friend std::ostream& operator<<(std::ostream& os, const bestmove& obj)
			{
				os << "bestmove " << obj.move;

				if (obj.ponder.has_value()) {
					os << " ponder " << obj.ponder.value();
				}

				return os;
			}

		public:
			forge::Move move;
			std::optional<forge::Move> ponder;
		};
	} // namespace commands
} // namespace uci
