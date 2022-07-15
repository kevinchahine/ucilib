#include "command.h"

#include <algorithm>
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
			os << token << ' ';
		}

		return os;
	}

	std::string Command::to_quoted_string() const
	{
		stringstream ss;

		for (const string& token : *this) {
			ss << '\'' << token << "\' ";
		}

		return ss.str();
	}

	void Command::parse(const string& line)
	{
		// --- 0.) Clear existing tokesn and puse currline into a stream ---
		this->clear();
		istringstream is(line);

		// --- 1.) parse command ---
		string cmd;
		is >> cmd;

		boost::algorithm::to_lower(cmd);

		// --- Set Option ---
		if (cmd == "uci")					parse_uci(line);
		else if (cmd == "debug")			parse_debug(line);
		else if (cmd == "isready")			parse_isready(line);
		else if (cmd == "setoption")		parse_setoption(line);
		else if (cmd == "register")			parse_register(line);
		else if (cmd == "ucinewgame")		parse_ucinewgame(line);
		else if (cmd == "position")			parse_position(line);
		else if (cmd == "go")				parse_go(line);
		else if (cmd == "stop")				parse_stop(line);
		else if (cmd == "ponderhit")		parse_ponderhit(line);
		else if (cmd == "quit")				parse_quit(line);
		else if (cmd == "id")				parse_id(line);
		else if (cmd == "uciok")			parse_uciok(line);
		else if (cmd == "readyok")			parse_readyok(line);
		else if (cmd == "bestmove")			parse_bestmove(line);
		else if (cmd == "copyprotection")	parse_copyprotection(line);
		else if (cmd == "registration")		parse_registration(line);
		else if (cmd == "info")				parse_info(line);
		else if (cmd == "option")			parse_option(line);
		else {
			//	cout << "Error: " << __FILE__ << " currline " << __LINE__ << " Invalid command: \'" << currline << "\'" << endl;
			setAsInvalid();
		}
	}

	// -------------------------------- IS COMMAND ----------------------------

	bool Command::is_cmd(const std::string& cmd)
	{
		return this->cmd() == cmd;
	}

	bool Command::is_uci() const
	{
		return this->cmd() == "uci";
	}

	bool Command::is_debug() const
	{
		return this->cmd() == "debug";
	}

	bool Command::is_isready() const
	{
		return this->cmd() == "isready";
	}

	bool Command::is_setoption() const
	{
		return this->cmd() == "setoption";
	}

	bool Command::is_register() const
	{
		return this->cmd() == "register";
	}

	bool Command::is_ucinewgame() const
	{
		return this->cmd() == "ucinewgame";
	}

	bool Command::is_position() const
	{
		return this->cmd() == "position";
	}

	bool Command::is_go() const
	{
		return this->cmd() == "go";
	}

	bool Command::is_stop() const
	{
		return this->cmd() == "stop";
	}

	bool Command::is_ponderhit() const
	{
		return this->cmd() == "ponderhit";
	}

	bool Command::is_quit() const
	{
		return this->cmd() == "quit";
	}

	bool Command::is_id() const
	{
		return this->cmd() == "id";
	}

	bool Command::is_uciok() const
	{
		return this->cmd() == "uciok";
	}

	bool Command::is_readyok() const
	{
		return this->cmd() == "readyok";
	}

	bool Command::is_bestmove() const
	{
		return this->cmd() == "bestmove";
	}

	bool Command::is_copyprotection() const
	{
		return this->cmd() == "copyprotection";
	}

	bool Command::is_registration() const
	{
		return this->cmd() == "registration";
	}

	bool Command::is_info() const
	{
		return this->cmd() == "info";
	}

	bool Command::is_option() const
	{
		return this->cmd() == "option";
	}

	bool Command::to_debug() const
	{
		const string& d = (*this)[1];

		if (d == "on") {
			return true;
		}
		else if (d == "off") {
			return false;
		}
		else {
			// Throw exception or just ignore
			return false;
		}
	}

	//option Command::to_option() const
	//{
	//	option op;
	//
	//	
	//
	//	return op;
	//}

	// -------------------------------- PARSE ---------------------------------

	void Command::parse_uci(const std::string& line)
	{
		this->resize(1);

		this->front() = "uci";
	}

	void Command::parse_debug(const std::string& line)
	{
		boost::regex regex(R"dil((debug)\s+(on|off))dil");

		boost::sregex_token_iterator regex_it(line.begin(), line.end(), regex, { 1, 2 });

		parse_helper(*this, line, regex_it);
	}

	void Command::parse_isready(const std::string& line)
	{
		this->resize(1);

		this->front() = "isready";
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

	void Command::parse_ucinewgame(const std::string& line)
	{
		this->resize(1);

		this->front() = "ucinewgame";
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
		// Example: After "position startpos" and "go infinite searchmoves e2e4 d2d4"

		// * go
		//	* searchmoves <move1> .... <movei>
		//	* ponder
		//	* wtime <x>			<x> is a positive number (int or float? I dont know)
		//	* btime <x>			...
		//	* winc <x>			positive integer number
		//	* binc <x>			...
		//	* movestogo <x>		integer 
		//	* depth <x>
		//	* nodes <x>
		//	* mate <x>
		//	* movetime <x>
		//	* infinite

		vector<string> vec;

		//boost::algorithm::split(vec, line, boost::algorithm::is_space);

		// TODO: Finish this
	}

	void Command::parse_stop(const std::string& line)
	{
		this->resize(1);

		this->front() = "stop";
	}

	void Command::parse_ponderhit(const std::string& line)
	{
		this->resize(1);

		this->front() = "ponderhit";
	}

	void Command::parse_quit(const std::string& line)
	{
		this->resize(1);

		this->front() = "quit";
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

	void Command::parse_uciok(const std::string& line)
	{
		this->resize(1);

		this->front() = "uciok";
	}

	void Command::parse_readyok(const std::string& line)
	{
		this->resize(1);

		this->front() = "readyok";
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

		if (this->size() >= 6) {
			string last = std::move(this->back());
			this->pop_back();

			vector<string> temp;

			if (this->at(4) == "string") {
				regex = boost::regex(R"dil((default)\s+(.*))dil");

				regex_it = boost::sregex_token_iterator(last.begin(), last.end(), regex, { 1, 2 });

				parse_helper(temp, last, regex_it);
			}
			else {
				boost::split(temp, last, boost::is_space());
			}

			for (string& str : temp) {
				this->emplace_back(move(str));
			}
		}
	}
} // namespace uci