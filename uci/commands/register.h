#pragma once

#include "uci/commands/command_base.h"
namespace uci
{
	namespace commands
	{
		// this class is called "register_cmd" because "register" is a keyword in C/C++
		class register_cmd : public command_base_template<register_cmd>
		{
		public:

			virtual void parse(const std::string& line) override;

			friend std::ostream& operator<<(std::ostream& os, const register_cmd& obj)
			{
				os << "register ";

				switch (obj.type)
				{
				case TYPE::LATER:	os << "later";				break;
				case TYPE::NAME:	os << "name " << obj.value;	break;
				case TYPE::CODE:	os << "code " << obj.value;	break;
				}

				return os;
			}

		public:

			enum class TYPE { LATER, NAME, CODE } type;
			std::string value;
		};
	} // namespace commands
} // namespace uci

