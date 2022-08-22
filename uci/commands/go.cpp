#include "go.h"

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string_regex.hpp>
#include <boost/regex.hpp>
#include <boost/property_tree/ptree.hpp>

using namespace std;

namespace uci
{
	namespace commands
	{
		boost::property_tree::ptree go::serialize() const
		{
			boost::property_tree::ptree tree;

			tree.add_child("go", boost::property_tree::ptree{});

			if (searchmoves.has_value()) {
				boost::property_tree::ptree searchMovesTree;

				for (const string& move : searchmoves.value()) {
					boost::property_tree::ptree node;
					node.put("", move);
					searchMovesTree.push_back(make_pair("", node));
				}

				tree.add_child("go.searchmoves", searchMovesTree);
			}
			if (ponder.has_value()) {
				tree.put("go.ponder", ponder.value());
			}
			if (wtime.has_value()) {
				tree.put("go.wtime", wtime.value());
			}
			if (btime.has_value()) {
				tree.put("go.btime", btime.value());
			}
			if (winc.has_value()) {
				tree.put("go.winc", winc.value());
			}
			if (binc.has_value()) {
				tree.put("go.binc", binc.value());
			}
			if (movestogo.has_value()) {
				tree.put("go.movestogo", movestogo.value());
			}
			if (depth.has_value()) {
				tree.put("go.depth", depth.value());
			}
			if (nodes.has_value()) {
				tree.put("go.nodes", nodes.value());
			}
			if (mate.has_value()) {
				tree.put("go.mate", mate.value());
			}
			if (movetime.has_value()) {
				tree.put("go.movetime", movetime.value());
			}
			if (infinite.has_value()) {
				tree.put("go.infinite", true);
			}

			return tree;
		}

		template<typename T>
		inline void parseHelper(optional<T>& field, const string& name, const boost::property_tree::ptree& tree)
		{
			boost::optional<T> op = tree.get_optional<T>(name);

			if (op.has_value()) {
				field = op.get();
			}
		}

		// --- full specialization ---
		inline void parseHelper(optional<list<string>>& field, const string& name, const boost::property_tree::ptree& tree)
		{
			boost::optional<const boost::property_tree::ptree&> op = tree.get_child_optional(name);

			if (op.has_value()) {
				field = list<string>{};

				const boost::property_tree::ptree& child = op.value();

				for (const boost::property_tree::ptree::value_type& c : child) {
					const string& data = c.second.data();

					field->push_back(data);
				}
			}
		}

		void go::parse(const boost::property_tree::ptree& tree)
		{
			(*this) = go{};	// clear existing values

			parseHelper(searchmoves, "searchmoves", tree);
			parseHelper(ponder, "ponder", tree);
			parseHelper(wtime, "wtime", tree);
			parseHelper(btime, "btime", tree);
			parseHelper(winc, "winc", tree);
			parseHelper(binc, "binc", tree);
			parseHelper(movestogo, "movestogo", tree);
			parseHelper(depth, "depth", tree);
			parseHelper(nodes, "nodes", tree);
			parseHelper(mate, "mate", tree);
			parseHelper(movetime, "movetime", tree);
			parseHelper(infinite, "infinite", tree);
		}

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
				else if (key == "ponder") { this->ponder = true; }
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
