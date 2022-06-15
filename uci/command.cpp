#include "command.h"

#include <sstream>

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string_regex.hpp>
#include <boost/regex.hpp>

using namespace std;

namespace uci
{
	void parse_helper(
		vector<string>& tokens,
		const std::string& line,
		boost::sregex_token_iterator& regex_it)
	{
		boost::sregex_token_iterator rend;

		tokens.clear();

		while (regex_it != rend)
		{
			tokens.emplace_back(*regex_it);

			++regex_it;
		}
	}

	ostream& operator<<(ostream& os, const Command& cmd)
	{
		for (const string& token : cmd) {
			os << "\'" << token << "\' ";
		}

		return os;
	}

	void Command::parse(const string& line)
	{
		// --- 0.) Clear existing tokesn and puse line into a stream ---
		this->clear();
		istringstream is(line);

		// --- 1.) parse command ---
		string cmd;
		is >> cmd;

		boost::algorithm::to_lower(cmd);

		// --- Set Option ---
		if (cmd == "setoption")				parse_setoption(line);
		else if (cmd == "register")			parse_register(line);
		else if (cmd == "position")			parse_position(line);
		else if (cmd == "go")				parse_go(line);
		else if (cmd == "id")				parse_id(line);
		else if (cmd == "bestmove")			parse_bestmove(line);
		else if (cmd == "copyprotection")	parse_copyprotection(line);
		else if (cmd == "registration")		parse_registration(line);
		else if (cmd == "info")				parse_info(line);
		else if (cmd == "option")			parse_option(line);
		else {
			cout << __FILE__ << " line " << __LINE__ << " line = \'" << line << "\'" << endl;
			setAsInvalid();
		}
	}

	void Command::parse_setoption(const std::string& line)
	{
		// expression: setoption name <id> [value <x>]

		if (boost::algorithm::contains(line, "value")) {
			// TODO: Optimize: Consider making regex const static to prevent
			// reconstruction on reach function call
			boost::regex regex(R"dil((setoption)\s+(name)\s+(.+)\s+(value)\s+(.+))dil");

			boost::sregex_token_iterator regex_it(line.begin(), line.end(), regex, { 1, 2, 3, 4, 5 });

			parse_helper(*this, line, regex_it);
		}
		else {
			boost::regex regex(R"dil((setoption)\s+(name)\s+(.+))dil");

			boost::sregex_token_iterator regex_it(line.begin(), line.end(), regex, { 1, 2, 3 });

			parse_helper(*this, line, regex_it);
		}
	}

	void Command::parse_register(const std::string& line)
	{
		// expressions:
		//	register later
		//	register name <x>
		//	register code <y>

		if (line.find("later") != string::npos) {
			boost::regex regex(R"dil((register)\s+(later)$)dil");

			boost::sregex_token_iterator regex_it(line.begin(), line.end(), regex, { 1, 2 });

			parse_helper(*this, line, regex_it);
		}
		else if (line.find("name") != string::npos || line.find("code") != string::npos) {
			boost::regex regex(R"dil((register)\s+(name|code)\s+([\w\s]+))dil");

			boost::sregex_token_iterator regex_it(line.begin(), line.end(), regex, { 1, 2, 3 });

			parse_helper(*this, line, regex_it);
		}
	}

	void Command::parse_position(const std::string& line)
	{
		// expression: position [fen <fenstring> | startpos ]  moves <move1> .... <movei>

		boost::regex regex;
		boost::sregex_token_iterator regex_it;

		string fenstring = R"dil([kqrbnp\d\/]+\s+[bw]\s+[kq]+\s+-\s+\d+\s+\d+)dil";

		if (boost::algorithm::contains(line, "fen")) {
			// position fen <fenstring> [ moves <move1> .... <movei> ]
			// position fen <fenstring>   moves <move1> .... <movei>
			// position fen <fenstring>
			regex = boost::regex(R"dil((position)\s+(fen)\s+([KkQqRrBbNnPp\d\/]+\s+[BbWw]\s+[KQkq]+\s+-\s+\d+\s+\d+)\s*(moves\s+.*)?)dil");

			regex_it = boost::sregex_token_iterator(line.begin(), line.end(), regex, { 1, 2, 3, 4 });
		}
		else if (boost::algorithm::contains(line, "startpos")) {
			// position startpos [ moves <move1> .... <movei> ]
			// position startpos   moves <move1> .... <movei> 
			// position startpos
			regex = boost::regex(R"dil((position)\s+(startpos)\s*(moves\s+.*)?)dil");

			regex_it = boost::sregex_token_iterator(line.begin(), line.end(), regex, { 1, 2, 3 });
		}
		
		parse_helper(*this, line, regex_it);

		// If parse moves 
		if (this->size() && boost::algorithm::starts_with(this->back(), "moves")) {
			string last = move(this->back());
			this->pop_back();

			vector<string> tokens;
			boost::split(tokens, last, boost::is_any_of(" "), boost::token_compress_on);

			move(tokens.begin(), tokens.end(), back_inserter(*this));
		}
	}

	void Command::parse_go(const std::string& line)
	{

	}

	void Command::parse_id(const std::string& line)
	{
		// expressions:
		//	id name <x>
		//	id author <x>

		boost::regex regex(R"dil((id)\s+(name|author)\s+(.*))dil");

		boost::sregex_token_iterator regex_it(line.begin(), line.end(), regex, { 1, 2, 3 });

		parse_helper(*this, line, regex_it);
	}

	void Command::parse_bestmove(const std::string& line)
	{
		// expression: bestmove <move1> [ ponder <move2> ]

		boost::regex regex;
		boost::sregex_token_iterator regex_it;

		if (boost::algorithm::contains(line, "ponder")) {
			regex = boost::regex(R"dil((bestmove)\s+(\w+)\s+(ponder)\s+(\w+))dil");

			regex_it = boost::sregex_token_iterator(line.begin(), line.end(), regex, { 1, 2, 3, 4 });
		}
		else {
			regex = boost::regex(R"dil((bestmove)\s+(\w+))dil");

			regex_it = boost::sregex_token_iterator(line.begin(), line.end(), regex, { 1, 2 });
		}

		parse_helper(*this, line, regex_it);
	}

	void Command::parse_copyprotection(const std::string& line)
	{
		// expression: copyprotection [ <null> | checking | ok | error ]
		boost::regex regex(R"dil((copyprotection)\s*(checking|ok|error)?)dil");

		boost::sregex_token_iterator regex_it(line.begin(), line.end(), regex, { 1, 2 });

		parse_helper(*this, line, regex_it);
	}

	void Command::parse_registration(const std::string& line)
	{
		// expression: registration [ <null> | checking | ok | error ]
		boost::regex regex(R"dil((registration)\s*(checking|ok|error)?)dil");

		boost::sregex_token_iterator regex_it(line.begin(), line.end(), regex, { 1, 2 });

		parse_helper(*this, line, regex_it);
	}

	void Command::parse_info(const std::string& line)
	{
		boost::regex regex(R"dil((info)\s+)dil");

		// extract 1st 2 tokens
		istringstream iss(line);

		string first;
		string second;
		iss >> first >> second;
		
		if (second == "pv" ||
			second == "refutation" ||
			second == "currline") {
			// expressions:
			//	info pv <move1> ... <movei>
			//	info refutation <move1> <move2> ... <movei>
			//	info currline <cpunr> <move1> ... <movei>
			boost::regex regex(R"dil((info)\s+(\w+)\s+([\w\s]+))dil");

			boost::sregex_token_iterator regex_it(line.begin(), line.end(), regex, { 1, 2, 3 });

			parse_helper(*this, line, regex_it);

			if (this->isValid() && this->back().size()) {
				string last = move(this->back());
				this->pop_back();
			
				vector<string> tokens;
				boost::split(tokens, last, boost::is_any_of(" "), boost::token_compress_on);
			
				move(tokens.begin(), tokens.end(), back_inserter(*this));
			}
		}
		else if (second == "string") {
			// expressions:
			//	info string <str>
			boost::regex regex(R"dil((info)\s+(string)\s+(.*))dil");

			boost::sregex_token_iterator regex_it(line.begin(), line.end(), regex, { 1, 2, 3 });

			parse_helper(*this, line, regex_it);
		}
		else {
			// expressions:
			//	info score cp <x>
			//	info score mate <y>
			//	info score lowerbound
			//	info score upperbound
			//	info depth <x>
			//	info seldepth <x>
			//	info time <x>
			//	info nodes <x>
			//	info multipv <num>
			//	info currmove <move>
			//	info currmovenumber <x>
			//	info hashfull <x>
			//	info nps <x>
			//	info tbhits <x>
			//	info sbhits <x>
			//	info cpuload <x>
			boost::regex regex(R"dil((info)\s+(\w+)\s+(\w+)?)dil");

			boost::sregex_token_iterator regex_it(line.begin(), line.end(), regex, { 1, 2, 3 });

			parse_helper(*this, line, regex_it);
		}
	}

	void Command::parse_option(const std::string& line)
	{
		// expressions:
		// option name <id> type <type> default <default> min <min> max <max> var <var>
		// 
		// option name Nullmove type check default true
		// option name Selectivity type spin default 2 min 0 max 4
		// option name Style type combo default Normal var Solid var Normal var Risky
		// option name NalimovPath type string default c:\
		// option name Clear Hash type button
		// option name UCI_EngineAbout type string default Shredder by Stefan Meyer-Kahlen, see www.shredderchess.com"

		boost::regex regex(R"dil((option)\s+(name)\s+(\w+)\s+(type)\s+(check|spin|combo|button|string)\s+(.*))dil");

		boost::sregex_token_iterator regex_it(line.begin(), line.end(), regex, { 1, 2, 3, 4, 5, 6 });

		parse_helper(*this, line, regex_it);

		//if (this->size()) {
		//	string last = move(this->back());
		//	this->pop_back();
		//
		//	regex = boost::regex(R"dil((default|min|max|var)\s+(\w+)\s+(.*))dil");
		//
		//	regex_it = boost::sregex_token_iterator(last.begin(), last.end(), regex, { 1, 2, 3 });
		//	boost::sregex_token_iterator end;
		//
		//	while (regex_it != end) {
		//		this->emplace_back(*regex_it);
		//
		//		++regex_it;
		//	}
		//}
	}
} // namespace uci