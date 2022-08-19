#pragma once

#include "uci/commands/command_base.h"
namespace uci
{
	namespace commands
	{
		class registration : public command_base_template<registration>
		{
		public:

			virtual void parse(const std::string& line) override;

			friend std::ostream& operator<<(std::ostream& os, const registration& obj)
			{
				os << "registration ";

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

