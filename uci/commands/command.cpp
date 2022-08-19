#include "command.h"

#include "uci/commands/bestmove.h"
#include "uci/commands/copyprotection.h"
#include "uci/commands/debug.h"
#include "uci/commands/go.h"
#include "uci/commands/id.h"
#include "uci/commands/info.h"
#include "uci/commands/isready.h"
#include "uci/commands/option.h"
#include "uci/commands/ponderhit.h"
#include "uci/commands/position.h"
#include "uci/commands/quit.h"
#include "uci/commands/readyok.h"
#include "uci/commands/register.h"
#include "uci/commands/registration.h"
#include "uci/commands/setoption.h"
#include "uci/commands/stop.h"
#include "uci/commands/uci.h"
#include "uci/commands/ucinewgame.h"
#include "uci/commands/uciok.h"
#include "uci/commands/helpers.h"

#include <algorithm>
#include <sstream>

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string_regex.hpp>
#include <boost/regex.hpp>

using namespace std;

namespace uci
{
	namespace commands
	{
		void command::parse(const std::string& line)
		{
			// --- 0.) Clear existing tokesn and puse currline into a stream ---
			istringstream is(line);

			// --- 1.) parse command ---
			string cmd;
			is >> cmd;

			boost::algorithm::to_lower(cmd);

			// --- Determine which command we have ---
			if (cmd == "uci")					cmd_ptr = make_unique<uci>();
			else if (cmd == "debug")			cmd_ptr = make_unique<debug>();
			else if (cmd == "isready")			cmd_ptr = make_unique<isready>();
			else if (cmd == "setoption")		cmd_ptr = make_unique<setoption>();
			else if (cmd == "register")			cmd_ptr = make_unique<register_cmd>();
			else if (cmd == "ucinewgame")		cmd_ptr = make_unique<ucinewgame>();
			else if (cmd == "position")			cmd_ptr = make_unique<position>();
			else if (cmd == "go")				cmd_ptr = make_unique<go>();
			else if (cmd == "stop")				cmd_ptr = make_unique<stop>();
			else if (cmd == "ponderhit")		cmd_ptr = make_unique<ponderhit>();
			else if (cmd == "quit")				cmd_ptr = make_unique<quit>();
			else if (cmd == "id")				cmd_ptr = make_unique<id>();
			else if (cmd == "uciok")			cmd_ptr = make_unique<uciok>();
			else if (cmd == "readyok")			cmd_ptr = make_unique<readyok>();
			else if (cmd == "bestmove")			cmd_ptr = make_unique<bestmove>();
			else if (cmd == "copyprotection")	cmd_ptr = make_unique<copyprotection>();
			else if (cmd == "registration")		cmd_ptr = make_unique<registration>();
			else if (cmd == "info")				cmd_ptr = make_unique<info>();
			else if (cmd == "option")			cmd_ptr = make_unique<option>();
			else {
				throw_exception("a command", cmd, line);
			}
			
			// --- Parse command ---
			cmd_ptr->parse(line);
		}
	} // namespace commands

	//void parse_helper(
	//	vector<string>& tokens,
	//	const std::string& line,
	//	boost::sregex_token_iterator& regex_it)
	//{
	//	boost::sregex_token_iterator rend;
	//
	//	tokens.clear();
	//
	//	while (regex_it != rend)
	//	{
	//		tokens.emplace_back(*regex_it);
	//
	//		++regex_it;
	//	}
	//}

	// -------------------------------- PARSE ---------------------------------

	//void Command::parse_setoption(const std::string& line)
	//{
	//	// expression: setoption name <id> [value <x>]
	//
	//	if (boost::algorithm::contains(line, "value")) {
	//		// TODO: Optimize: Consider making regex const static to prevent
	//		// reconstruction on reach function call
	//		boost::regex regex(R"dil((setoption)\s+(name)\s+(.+)\s+(value)\s+(.+))dil");
	//
	//		boost::sregex_token_iterator regex_it(line.begin(), line.end(), regex, { 1, 2, 3, 4, 5 });
	//
	//		parse_helper(*this, line, regex_it);
	//	}
	//	else {
	//		boost::regex regex(R"dil((setoption)\s+(name)\s+(.+))dil");
	//
	//		boost::sregex_token_iterator regex_it(line.begin(), line.end(), regex, { 1, 2, 3 });
	//
	//		parse_helper(*this, line, regex_it);
	//	}
	//}

	/*
	void Command::parse_register(const std::string& line)
	{

	}

	void Command::parse_position(const std::string& line)
	{

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
	}*/

	//void Command::parse_option(const std::string& line)
	//{
		//// expressions:
		//// option name <id> type <type> default <default> min <min> max <max> var <var>
		//// 
		//// option name Nullmove type check default true
		//// option name Selectivity type spin default 2 min 0 max 4
		//// option name Style type combo default Normal var Solid var Normal var Risky
		//// option name NalimovPath type string default c:\
		//// option name Clear Hash type button
		//// option name UCI_EngineAbout type string default Shredder by Stefan Meyer-Kahlen, see www.shredderchess.com"
		//
		//boost::regex regex(R"dil((option)\s+(name)\s+(\w+)\s+(type)\s+(check|spin|combo|button|string)\s+(.*))dil");
		//
		//boost::sregex_token_iterator regex_it(line.begin(), line.end(), regex, { 1, 2, 3, 4, 5, 6 });
		//
		//parse_helper(*this, line, regex_it);
		//
		//if (this->size() >= 6) {
		//	string last = std::move(this->back());
		//	this->pop_back();
		//
		//	vector<string> temp;
		//
		//	if (this->at(4) == "string") {
		//		regex = boost::regex(R"dil((default)\s+(.*))dil");
		//
		//		regex_it = boost::sregex_token_iterator(last.begin(), last.end(), regex, { 1, 2 });
		//
		//		parse_helper(temp, last, regex_it);
		//	}
		//	else {
		//		boost::split(temp, last, boost::is_space());
		//	}
		//
		//	for (string& str : temp) {
		//		this->emplace_back(move(str));
		//	}
		//}
	//}
} // namespace uci

