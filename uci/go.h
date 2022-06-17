#pragma once

#include <iostream>
#include <string>
#include <list>
#include <optional>

namespace uci
{
	class go
	{
	public:

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
			if (go.infinite)		os << " infinite " << go.infinite.value();

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
		std::optional<void*> infinite;
	};
} // namespace uci
