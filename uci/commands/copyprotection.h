#pragma once

#include "uci/commands/command_base.h"

namespace uci
{
	namespace commands
	{
		class copyprotection : public command_base_template<copyprotection>
		{
		public:

			virtual void parse(const std::string& line) override;

			friend std::ostream& operator<<(std::ostream& os, const copyprotection& obj)
			{
				os << "copyprotection ";	

				switch (obj.value) {
				case VALUE::OK:			os << "ok";			break;
				case VALUE::ERROR_:		os << "error";		break;
				case VALUE::CHECKING:	os << "checking";	break;
				}

				return os;
			}

			enum class VALUE { OK, ERROR_, CHECKING } value;
		};
	} // namespace commands
} // namespace uci
