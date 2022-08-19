#pragma once

#include "uci/commands/command_base.h"

#include <iostream>
#include <string>
#include <vector>
#include <memory>

namespace uci
{
	namespace commands
	{
		class command
		{
		public:
			template<class T>
			bool is() const {
				return dynamic_cast<const T*>(*cmd_ptr) != nullptr;
			}

			template<class T>
			const T& as() const 
			{
				return static_cast<const T&>(*cmd_ptr);
			}

			std::string to_string() const { return cmd_ptr->to_string(); }

			void parse(const std::string& line);

			friend std::ostream& operator<<(std::ostream& os, const command& obj)
			{
				os << obj.to_string();

				return os;
			}

		private:
			std::unique_ptr<command_base> cmd_ptr;
		};
	} // namespace commands
} // namespace uci

