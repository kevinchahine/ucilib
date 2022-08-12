#pragma once

#include <iostream>
#include <string>
#include <list>
#include <optional>

#include <boost/property_tree/ptree_fwd.hpp>

#include "commands/command.h"

namespace uci
{
	class go
	{
	public:

		go() = default;
		//go(const Command& cmd);
		go(const go&) = default;
		go(go&&) noexcept = default;
		~go() noexcept = default;
		go& operator=(const go&) = default;
		go& operator=(go&&) noexcept = default;

		boost::property_tree::ptree serialize() const;

		void parse(const boost::property_tree::ptree& tree);

		friend std::ostream& operator<<(std::ostream& os, const go& go)
		{
			os << "go";

			if (go.searchmoves && go.searchmoves.value().size()) {
				os << " searchmoves";
				
				const std::list<std::string> & moves = go.searchmoves.value();

				for (const std::string& m : moves) {
					os << ' ' << m;
				}
			}
			if (go.ponder)			os << " ponder " << go.ponder.value();
			if (go.wtime)			os << " wtime " << go.wtime.value();
			if (go.btime)			os << " btime " << go.btime.value();
			if (go.winc)			os << " winc " << go.winc.value();
			if (go.binc)			os << " binc " << go.binc.value();
			if (go.movestogo)		os << " movestogo " << go.movestogo.value();
			if (go.depth)			os << " depth " << go.depth.value();
			if (go.nodes)			os << " nodes " << go.nodes.value();
			if (go.mate)			os << " mate " << go.mate.value();
			if (go.movetime)		os << " movetime " << go.movetime.value();
			if (go.infinite)		os << " infinite";	// don't print value

			return os;
		}

	public:
		std::optional<std::list<std::string>> searchmoves;
		std::optional<void *> ponder;
		std::optional<int> wtime;
		std::optional<int> btime;
		std::optional<int> winc;
		std::optional<int> binc;
		std::optional<int> movestogo;
		std::optional<int> depth;
		std::optional<int> nodes;
		std::optional<int> mate;
		std::optional<int> movetime;
		std::optional<bool> infinite;	// Value is irrelevant. call infinite.has_value() to determine if infinite has been set.
	};
} // namespace uci
