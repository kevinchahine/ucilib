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
			command() = default;
			
			command(const command&) = default;
			
			command(command&&) noexcept = default;
			
			template <class COMMAND_T> 
			command(const COMMAND_T& cmd) : 
				cmd_ptr(cmd.clone()) {}
			
			~command() noexcept = default;
			
			command& operator=(const command& right) {
				cmd_ptr = right.cmd_ptr->clone();

				return *this;
			};
			
			command& operator=(command&&) noexcept = default;

			template<class T>
			bool is() const {
				static_assert(std::is_base_of<commands::command_base, T>(), "T must derive from command_base");

				return dynamic_cast<const T*>(cmd_ptr.get()) != nullptr;
			}

			bool is_same_as(const command& right_cmd) const {
				return cmd_ptr->is_same_as(*right_cmd.cmd_ptr);
			}

			template<class T>
			const T& as() const 
			{
				static_assert(std::is_base_of<commands::command_base, T>(), "T must derive from command_base");
				
				return static_cast<const T&>(*cmd_ptr);
			}

			std::string to_string() const { return cmd_ptr->to_string(); }

			void parse(const std::string& line);

			std::string name() const { return cmd_ptr->command_name(); }

			bool is_valid() const { return cmd_ptr != nullptr; }
			bool is_invalid() const { return !is_valid(); }

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

