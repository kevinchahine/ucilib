#include "setoption.h"

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string_regex.hpp>
#include <boost/regex.hpp>

using namespace std;

namespace uci
{
	namespace commands
	{
		void setoption::parse(const std::string& line)
		{
			// expression: setoption name <id> [value <x>]

			// TODO: try to combine these

			if (boost::algorithm::contains(line, "value")) {
				// TODO: Optimize: Consider making regex const static to prevent
				// reconstruction on reach function call
				boost::regex regex(R"dil((setoption)\s+(name)\s+(.+)\s+(value)\s+(.+))dil");

				boost::sregex_token_iterator regex_it(line.begin(), line.end(), regex, { 1, 2, 3, 4, 5 });

				const string& cmd = *regex_it++;
				if (cmd != "setoption")	throw_exception("setoption", cmd, line);

				const string& name = *regex_it++;
				if (name != "name") throw_exception("name", name, line);
				this->id = *regex_it++;

				const string& value = *regex_it++;
				if (value != "value") throw_exception("value", value, line);
				this->x = *regex_it++;
			}
			else {
				boost::regex regex(R"dil((setoption)\s+(name)\s+(.+))dil");

				boost::sregex_token_iterator regex_it(line.begin(), line.end(), regex, { 1, 2, 3 });

				const string& cmd = *regex_it++;
				if (cmd != "setoption")	throw_exception("setoption", cmd, line);

				const string& name = *regex_it++;
				if (name != "name") throw_exception("name", name, line);
				this->id = *regex_it++;
			}
		}
	} // namespace commands
} // namespace uci