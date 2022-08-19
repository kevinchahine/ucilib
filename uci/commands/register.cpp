#include "register.h"

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string_regex.hpp>
#include <boost/regex.hpp>

using namespace std;

namespace uci
{
	namespace commands
	{
		void register_cmd::parse(const std::string& line)
		{
			// expressions:
			//	register later
			//	register name <x>
			//	register code <y>

			boost::regex regex(R"dil((register)\s+(later|name\s+|code\s+)([\w\s]+)?)dil");
			
			boost::regex_token_iterator regex_it(line.begin(), line.end(), regex, { 1, 2, 3 });
			
			const string& cmd = *regex_it++;
			assert_token("register", cmd, line);
			
			string type = *regex_it++;
			boost::trim_right(type);
			assert_token({ "later", "name", "code" }, type, line);
			
			if (type == "later") {
				this->type = TYPE::LATER;
				this->value = "";
			}
			else if (type == "name") {
				this->type = TYPE::NAME;
				this->value = *regex_it;
			}
			else if (type == "code") {
				this->type = TYPE::CODE;
				this->value = *regex_it;
			}
		}
	} // namespace commands
} // namespace uci