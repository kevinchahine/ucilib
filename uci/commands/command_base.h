#pragma once

#include "uci/commands/command_base.h"
#include "uci/commands/helpers.h"

#include <forge/core/Move.h>

#include <string>
#include <sstream>
#include <optional>

namespace uci
{
	namespace commands
	{
		class command_base
		{
		public:

			virtual void parse(const std::string& line) = 0;

			virtual std::string to_string() const = 0;
		};

		// This class is used to generalize any functionallity common to all or most command classes.
		// It prevents having to reimplement methods which are the same except for its datatypes.
		// 
		// T should be a command class deriving from command_base_template
		// ex:
		//	class go : public command_base_template<go>
		//	{
		//	};
		template<class T>
		class command_base_template : public command_base
		{
		public:
			// Implements the to_string() methods for all deriving classes.
			// Each derived class must implement its own stream insertion operator
			virtual std::string to_string() const override
			{
				std::stringstream ss;

				ss << static_cast<const T&>(*this);

				return ss.str();
			}
		};
	} // namespace commands
} // namespace uci

