#pragma once

#include "uci/commands/command_base.h"
#include "uci/commands/helpers.h"

#include <forge/core/Move.h>

#include <string>
#include <sstream>
#include <optional>

#include <boost/property_tree/ptree_fwd.hpp>

namespace uci
{
	namespace commands
	{
		class command_base
		{
		public:

			virtual void parse(const std::string& line) = 0;

			virtual std::string to_string() const = 0;

			virtual std::string command_name() const = 0;

			virtual std::unique_ptr<command_base> clone() const = 0;
			
			// Determines if polymorphic objects are of the same type.
			virtual bool is_same_as(const command_base& right) const = 0;
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

			virtual std::string command_name() const override { return typeid(T).name(); }

			virtual std::unique_ptr<command_base> clone() const override
			{
				std::unique_ptr<T> duplicate = std::make_unique<T>();

				return duplicate;
			}

			virtual bool is_same_as(const command_base& right) const override
			{
				return dynamic_cast<const T*>(&right);
			}
		};
	} // namespace commands
} // namespace uci

