#include "command.h"

#include <sstream>

#include <boost/algorithm/string_regex.hpp>
#include <boost/regex.hpp>

using namespace std;

namespace uci
{
	ostream& operator<<(ostream& os, const Command& cmd)
	{
		for (const string& token : cmd.tokens) {
			os << "\'" << token << "\' ";
		}

		return os;
	}

	void Command::parse(const string& line)
	{
		// --- 0.) Clear existing tokesn and puse line into a stream ---
		tokens.clear();
		istringstream is(line);

		// --- 1.) parse command ---
		string cmd;
		is >> cmd;

		// --- Set Option ---
		if (cmd == "setoption")				parse_setoption(is);
		else if (cmd == "register")			parse_register(is);
		else if (cmd == "position")			parse_position(is);
		else if (cmd == "go")				parse_go(is);
		else if (cmd == "id")				parse_id(is);
		else if (cmd == "bestmove")			parse_bestmove(is);
		else if (cmd == "copyprotection")	parse_copyprotection(is);
		else if (cmd == "registration")		parse_registration(is);
		else if (cmd == "info")				parse_info(is);
		else if (cmd == "option")			parse_option(is);
		else {
			cout << __FILE__ << " line " << __LINE__ << " line = \'" << line << "\'" << endl;
			setAsInvalid();
		}
	}

	void Command::parseRegex(const std::string& line)
	{
		// setoption name <id> [value <x>]
		// setoption name asdf
		// setoption name asdf value sdf
		boost::regex regexSetoption(R"dil((setoption)\s+(name)\s+([\w\s ]+)\s+(value\s+)?(\w+)?)dil");
		//boost::regex regexSetoption(R"dil(setoption)dil");

		int subindx[] = { 1, 2, 3, 4, 5 };
		boost::sregex_token_iterator rit(line.begin(), line.end(), regexSetoption, subindx);
		boost::sregex_token_iterator rend;

		while (rit != rend) 
		{
			cout << '\t' << '\'' << *rit << '\'' << endl;

			rit++;
		}

		//boost::find_all_regex(words, line, regexSetoption);
		//boost::split_regex(words, line, regexSetoption);1
	}

	void Command::parse_setoption(std::istream& is)
	{
		// expression: setoption name <id> [value <x>]

		string temp;
		getline(is, temp);

		// --- Name ---
		// Next token should be "name"
		size_t namePos = temp.find("name");

		// Did we find "name"?
		if (namePos == string::npos) {
			// No. This line is invalid
			setAsInvalid();

			return;
		}

		// Find beginning of next token (skip spaces)
		size_t spacePos = temp.find_first_of(" ", namePos);
		size_t idPos = temp.find_first_not_of(" ", spacePos);
		// Did we find next token?
		if (idPos == string::npos) {
			// No. "name" is the last token
			setAsInvalid();

			return;
		}

		// Find end of <id> by looking for the start of "value"
		// Its okay if "value" is not found. That just means the rest of the line
		// is <id>.
		size_t valuePos = temp.find("value");

		// Parse <id> token
		tokens.push_back("name");
		tokens.push_back(temp.substr(idPos, valuePos));

		// --- Value (optional) ---
		// Did we find end of start of "value" token?
		if (valuePos == string::npos) {
			// No. value does not exist. Still a valid command.
			return;
		}

		// Find start of token <x>
		spacePos = temp.find_first_of(" ", valuePos);
		size_t xPos = temp.find_first_not_of(" ", spacePos);

		// Did we find the start of <x>?
		if (xPos == string::npos) {
			// No. <x> does not exist. Still a valid command.
		}

		// Parse <x> token
		tokens.push_back("value");
		tokens.push_back(temp.substr(xPos, string::npos));	// Rest of line is <x>
	}

	void Command::parse_register(std::istream& is)	
	{
		// expressions:
		//	register later
		//	register name <x>
		//	register code <y>
		string temp;
		is >> temp;

		if (temp.empty() || temp != "later" || temp != "name" || temp != "code") {
			setAsInvalid();

			return;
		}

		bool isNameOrCode = (temp == "name" || temp == "code");

		tokens.push_back(move(temp));

		if (isNameOrCode) {
			getline(is, temp);
			tokens.push_back(temp);
		}
	}

	void Command::parse_position(std::istream& is)
	{
		// expression: position [fen <fenstring> | startpos ]  moves <move1> .... <movei>
		
		size_t fenPos;
		size_t startPos;
		size_t movesPos;
		size_t spacePos;
		
		// --- fen | startpos ---
		string arg;
		is >> arg;

		string rest;
		getline(is, rest);
		
		if (arg == "fen") {
			// --- fen <fenstring> ---
			fenPos = rest.find_first_not_of(" ");
			movesPos = rest.find("moves", fenPos);	// Its okay to be npos. 
			// *** npos means <fenstring> was the rest of the line
			
			string fenstring = rest.substr(fenPos, movesPos);
			
			if (fenstring.size()) {
				tokens.push_back("position");
				tokens.push_back("fen");
				tokens.push_back(move(fenstring));
			}
			else {
				setAsInvalid();
				return;
			}
		}
		else if (arg == "startpos") {
			tokens.push_back("position");
			tokens.push_back("startpos");
		}
		else if (arg == "moves") {
			string move;
			is >> move;

			if (move.size()) {
				while (is.good()) {

				}
			}
		}
	}

	void Command::parse_go(std::istream& is)
	{
	}

	void Command::parse_id(std::istream& is)
	{
		// expressions:
		//	id name <x>
		//	id author <x>
		string second;
		is >> second;

		if (second == "name" || second == "author") {
			string x;
			getline(is, x);

			if (x.size()) {
				tokens.push_back(second);
				tokens.push_back(x);
			}
			else {
				setAsInvalid();
				return;
			}
		}
		else {
			setAsInvalid();
			return;
		}
	}

	void Command::parse_bestmove(std::istream& is)
	{
		// expression: bestmove <move1> [ ponder <move2> ]

		// --- <move1> ---
		string move1;
		is >> move1;

		if (move1.size()) {
			tokens.push_back(move1);
		}
		else {
			setAsInvalid();
			return;
		}

		// --- [ ponder <move2> ] ---
		string ponder;
		is >> ponder;

		if (ponder.size()) {
			string move2;
			is >> move2;

			if (move2.size()) {
				tokens.push_back("ponder");
				tokens.push_back(move2);
			}
		}
	}

	void Command::parse_copyprotection(std::istream& is)
	{		
		// expression: copyprotection [ <null> | checking | ok | error ]

		string value;
		is >> value;

		if (value == "checking" || value == "ok" || value == "error") {
			tokens.push_back("copyprotection");
			tokens.push_back(value);
		}
		else {
			setAsInvalid();
			return;
		}
	}

	void Command::parse_registration(std::istream& is)
	{	
		// expression: registration [ <null> | checking | ok | error ]

		string value;
		is >> value;

		if (value == "checking" || value == "ok" || value == "error") {
			tokens.push_back("registration");
			tokens.push_back(value);
		}
		else {
			setAsInvalid();
			return;
		}
	}

	void Command::parse_info(std::istream& is)
	{
	}

	void Command::parse_option(std::istream& is)
	{
	}

	// end of Command::parse()
} // namespace uci