#include "go.h"

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string_regex.hpp>
#include <boost/regex.hpp>

using namespace std;

namespace uci
{
	namespace commands
	{
		void go::parse(const std::string& line)
		{
			// Example: After "position startpos" and "go infinite searchmoves e2e4 d2d4"

			// go
			//		searchmoves <move1> .... <movei>
			//		ponder
			//		wtime <x>			<x> is a positive number (int only)
			//		btime <x>			...
			//		winc <x>			...
			//		binc <x>			...
			//		movestogo <x>		... 
			//		depth <x>			...
			//		nodes <x>			...
			//		mate <x>			...
			//		movetime <x>		...
			//		infinite

			this->searchmoves.reset();
			this->ponder.reset();
			this->wtime.reset();
			this->btime.reset();
			this->winc.reset();
			this->binc.reset();
			this->movestogo.reset();
			this->depth.reset();
			this->nodes.reset();
			this->mate.reset();
			this->movetime.reset();
			this->infinite.reset();

			boost::regex regex;
			boost::sregex_token_iterator regex_it;
			boost::sregex_token_iterator end;

			regex = boost::regex(R"dil((go)\s*(.*))dil");

			regex_it = boost::sregex_token_iterator(line.begin(), line.end(), regex, { 1, 2 });

			const string& cmd = *regex_it++;
			assert_token("go", cmd, line);

			string last = *regex_it++;

			vector<key_value_pair> key_values;

			extract_key_value_pairs(
				last,
				{ "searchmoves", "ponder", "wtime", "btime", "winc", "binc", "movestogo", "depth", "nodes", "mate", "movetime", "infinite" },
				back_inserter(key_values)
			);

			for (const key_value_pair& pair : key_values)
			{
				const string key = pair.key;
				const string val = pair.val;
				
				if (key == "searchmoves") {
					vector<string> moves;
					boost::split(moves, val, boost::is_space());

					this->searchmoves = list<string>{};

					for (const string& m : moves) {
						this->searchmoves->emplace_back(std::move(m));
					}
				}
				else if (key == "ponder") {	this->ponder = true;	}
				else if (key == "wtime") { this->wtime = stoi(val); }
				else if (key == "btime") { this->btime = stoi(val); }
				else if (key == "winc") { this->winc = stoi(val); }
				else if (key == "binc") { this->binc = stoi(val); }
				else if (key == "movestogo") { this->movestogo = stoi(val); }
				else if (key == "depth") { this->depth = stoi(val); }
				else if (key == "nodes") { this->nodes = stoi(val); }
				else if (key == "mate") { this->mate = stoi(val); }
				else if (key == "movetime") { this->movetime = stoi(val); }
				else if (key == "infinite") { this->infinite = true; }
				else
					throw_exception("searchmoves|ponder|wtime|btime|winc|binc|movestogo|depth|nodes|mate|movetime|infinite", key, line);
			}
		}
	} // namespace commands
} // namespace uci
