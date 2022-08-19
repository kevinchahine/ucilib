#include "option.h"

#include <assert.h>
#include <functional>	
#include <iterator>		// for back_insert_iterator

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string_regex.hpp>
#include <boost/regex.hpp>

using namespace std;

namespace uci
{
	namespace commands
	{
		
		// 'line' should be the last part of the option command after the
		// string: option name <name> type <type>
		// 'line' should contain tokens for "default", "min", "max" or "var"
		void parse_helper(
			const std::string& line,
			std::function<void(const std::string& attribute, const std::string& value)>& assign_attribute)
		{
			// Separators are the tokens "default", "min", "max" and "var"
			// The index of the first character of the separators will be stored in separators_pos
			vector<size_type_pair> separators_pos;

			// --- Find Separators ---
			// Look for all occurences of each token one by one and store their indicies in separators_pos
			find_all_tokens(line, "default", back_inserter(separators_pos));
			find_all_tokens(line, "min", back_inserter(separators_pos));
			find_all_tokens(line, "max", back_inserter(separators_pos));
			find_all_tokens(line, "var", back_inserter(separators_pos));

			// --- Sort positions ---
			// separators_pos may be unsorted. 
			sort(separators_pos.begin(), separators_pos.end());
			
			// --- Extract all tokens ---
			// Go from one token to the next and extract the separators and their cooresponding values
			for (size_t i = 0; i < separators_pos.size(); i++) {
				// Get index range of each token
				const size_type_pair & key_pos = separators_pos.at(i);
				std::string::size_type val_begin = line.find_first_not_of(' ', key_pos.end);
				std::string::size_type next_key_begin = (i + 1 < separators_pos.size() ? separators_pos.at(i + 1).begin : line.size());

				// Extract substring of each token
				// TODO: Try to do this with string_view to save on copy ops
				std::string key = line.substr(key_pos.begin, key_pos.end - key_pos.begin);
				std::string val = line.substr(val_begin, next_key_begin - val_begin);

				boost::trim_right(key);
				boost::trim_right(val);

				// Remove any trailing whitespace
				boost::trim_right(val);
			
				// Assign tokens to proper fields
				assign_attribute(key, val);
			}
		}

		// --- Methods ---

		string option::check::to_string() const
		{
			stringstream ss;

			ss << " type check";

			if (this->default_val)
				ss << " default " << (this->default_val.value() ? "true" : "false");

			if (this->var)
				ss << " var " << (this->var.value() ? "true" : "false");

			return ss.str();
		}

		void option::check::parse(const std::string& line)
		{
			// "option name Nullmove type check default true\n"

			this->default_val.reset();

			std::function<void(const std::string&, const std::string&)> assignment =
				[&](const std::string& attribute, const std::string& value) {
				if (attribute == "default") {
					this->default_val = to_bool(value);
				}
				else if (attribute == "var") {
					this->var = to_bool(value);
				}
				else {
					// Unknown attribute
				}
			};

			parse_helper(line, assignment);

			return;
		}

		std::string option::spin::to_string() const
		{
			stringstream ss;

			ss << " type spin";

			if (this->default_val) {
				ss << " default " << this->default_val.value();
			}

			if (this->min) {
				ss << " min " << this->min.value();
			}

			if (this->max) {
				ss << " max " << this->max.value();
			}

			if (this->var) {
				ss << " var " << this->var.value();
			}

			return ss.str();
		}

		void option::spin::parse(const std::string& line)
		{
			// "option name Selectivity type spin default 2 min 0 max 4\n"

			this->default_val.reset();
			this->min.reset();
			this->max.reset();
			this->var.reset();

			std::function<void(const std::string&, const std::string&)> assignment =
				[&](const std::string& attribute, const std::string& value) {
				const std::string& a = attribute;

				int ivalue = stoi(value);

				if (a == "default")		this->default_val = ivalue;
				else if (a == "min")	this->min = ivalue;
				else if (a == "max")	this->max = ivalue;
				else if (a == "var")	this->var = ivalue;
				else {
					// Unknown attribute
				}
			};

			parse_helper(line, assignment);
		}

		string option::combo::to_string() const
		{
			stringstream ss;

			ss << " type combo";

			if (this->default_val)
				ss << " default " << this->default_val.value();

			if (this->vals) {
				for (const std::string& val : this->vals.value()) {
					ss << " var " << val;
				}
			}

			return ss.str();
		}

		void option::combo::parse(const std::string& line)
		{
			// "option name Style type combo default Normal var Solid var Normal var Risky\n"

			this->default_val.reset();
			this->vals.reset();

			std::function<void(const std::string&, const std::string&)> assignment =
				[&](const std::string& attribute, const std::string& value) {
				const std::string& a = attribute;

				if (a == "default")		this->default_val = value;
				else if (a == "var") {
					// Has vals been initialized yet
					if (this->vals.has_value() == false) {
						// Make sure vals is initialized
						this->vals = list<std::string>{};
					}

					this->vals.value().push_back(value);
				}
				else {
					// Unknown attribute
				}
			};

			parse_helper(line, assignment);
		}

		string option::button::to_string() const
		{
			stringstream ss;

			ss << " type button";

			return ss.str();
		}

		void option::button::parse(const std::string& line)
		{
			// "option name Clear Hash type button\n"
			// 
			// nothing to do here
		}

		string option::string::to_string() const
		{
			stringstream ss;

			ss << " type string default";

			if (this->default_val)
				ss << " " << this->default_val.value();

			return ss.str();
		}

		void option::string::parse(const std::string& line)
		{
			// "option name NalimovPath type string default c:\\n"

			this->default_val.reset();

			std::function<void(const std::string&, const std::string&)> assignment =
				[&](const std::string& attribute, const std::string& value) {
				const std::string& a = attribute;

				if (a == "default")		this->default_val = value;
				else { /* Unknown attribute */ }
			};

			parse_helper(line, assignment);
		}

		void option::parse(const std::string& line)
		{
			// Here are 5 strings for each of the 5 possible types of options:
			// "option name Nullmove type check default true\n"
			// "option name Selectivity type spin default 2 min 0 max 4\n"
			// "option name Style type combo default Normal var Solid var Normal var Risky\n"
			// "option name NalimovPath type string default c:\\n"
			// "option name Clear Hash type button\n"

			boost::regex regex(R"dil((option)\s+(name)\s+([\w_\s]+)\s+(type)\s+(check|spin|combo|string|button)\s*(.*))dil");
			boost::sregex_token_iterator regex_it(line.begin(), line.end(), regex, { 1, 2, 3, 4, 5, 6 });
			boost::sregex_token_iterator end;

			// Keep the std::string to avoid ambiguity with option::string
			const std::string& cmd_name = *regex_it++;	// should equal "option"
			assert_token("option", cmd_name, line);

			const std::string& name = *regex_it++;		// should equal "name"
			assert_token("name", name, line);

			const std::string& op_name = *regex_it++;	// name of option
			option_name = op_name;

			const std::string& type = *regex_it++;		// should be "type"
			assert_token("type", type, line);

			const std::string& op_type = *regex_it++;	// type of option: (check|spin|combo|string|button)
			assert_token({ "check", "spin", "combo", "string", "button" }, op_type, line);

			const std::string& last = *regex_it++;		// rest of command

			if (op_type == "check") 		this->ptr = make_unique<option::check>();
			else if (op_type == "spin")		this->ptr = make_unique<option::spin>();
			else if (op_type == "combo")	this->ptr = make_unique<option::combo>();
			else if (op_type == "string")	this->ptr = make_unique<option::string>();
			else if (op_type == "button")	this->ptr = make_unique<option::button>();
			else throw_exception("check|spin|combo|string|button", op_type, line);

			this->ptr->parse(last);
		}

	} // namespace commands
} // namespace uci