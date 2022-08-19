#include "id.h"

#include <sstream>

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string_regex.hpp>
#include <boost/regex.hpp>

using namespace std;

namespace uci
{
	namespace commands
	{
		void id::parse(const std::string& line)
		{
			// expressions:
			//	id name <x>
			//	id author <x>

			boost::regex regex(R"dil((id)\s+(name|author)\s+(.*))dil");

			boost::sregex_token_iterator regex_it(line.begin(), line.end(), regex, { 1, 2, 3 });
			boost::sregex_token_iterator rend;

			const string& first = *(regex_it++);
			const string& second = *(regex_it++);
			const string& third = *(regex_it++);

			if (first != "id") {
				throw_exception("id", first, line);
			}

			if (second == "name") {
				this->name = third;
			}
			else if (second == "author") {
				this->author = third;
			}
			else {
				throw_exception("name or author", third, line);
			}
		}
	} // namespace commands
} // namespace uci