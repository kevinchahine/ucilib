#include "go.h"

#include <boost/property_tree/ptree.hpp>

using namespace std;

namespace uci
{
	boost::property_tree::ptree uci::go::serialize() const
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
		boost::optional<const boost::property_tree::ptree &> op = tree.get_child_optional(name);

		if (op.has_value()) {
			field = list<string>{};

			const boost::property_tree::ptree & child = op.value();

			for (const boost::property_tree::ptree::value_type& c : child) {
				const string & data = c.second.data();

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
} // namespace uci
