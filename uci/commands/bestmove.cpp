#include "bestmove.h"

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string_regex.hpp>
#include <boost/regex.hpp>

using namespace std;

namespace uci
{
	namespace commands
	{
		void bestmove::parse(const std::string& line)
		{
			// expression: bestmove <move1> [ ponder <move2> ]

			boost::regex regex;
			boost::sregex_token_iterator regex_it;
			boost::sregex_token_iterator end;

			if (boost::algorithm::contains(line, "ponder")) {
				regex = boost::regex(R"dil((bestmove)\s+(\w+)\s+(ponder)\s+(\w+))dil");

				regex_it = boost::sregex_token_iterator(line.begin(), line.end(), regex, { 1, 2, 3, 4 });
			}
			else {
				regex = boost::regex(R"dil((bestmove)\s+(\w+))dil");

				regex_it = boost::sregex_token_iterator(line.begin(), line.end(), regex, { 1, 2 });
			}

			++regex_it;									// skip 'bestmove'

			this->best = forge::Move(*(regex_it++));	// extract 'move1'

			if (regex_it != end)	++regex_it;			// skip 'ponder'

			if (regex_it != end) {
				this->ponder = forge::Move(*regex_it);	// extract 'move2'
			}
		}
	} // namespace commands
} // namespace uci