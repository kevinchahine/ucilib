#include "copyprotection.h"

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string_regex.hpp>
#include <boost/regex.hpp>

using namespace std;

namespace uci
{
	namespace commands
	{
		void copyprotection::parse(const std::string& line)
		{
			// expression: copyprotection ok|error

			boost::regex regex(R"dil((copyprotection)\s+(ok|error|checking))dil");
			boost::sregex_token_iterator regex_it;
			boost::sregex_token_iterator end;

			regex_it = boost::sregex_token_iterator(line.begin(), line.end(), regex, { 1, 2 });
			
			const string& cmd_name = *regex_it++;
			assert_token("copyprotection", cmd_name, line);

			const string& value = *regex_it;
			if (value == "ok")				this->value = VALUE::OK;
			else if (value == "error")		this->value = VALUE::ERROR_;
			else if (value == "checking")	this->value = VALUE::CHECKING;
			else throw_exception("ok or error", value, line);
		}
	} // namespace commands
} // namespace uci