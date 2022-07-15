#pragma once

#include <iostream>
#include <optional>
#include <string>
#include <vector>

/*
	e.g. "info currmove e2e4 currmovenumber 1" or
		 "info depth 12 nodes 123456 nps 100000".
		   "info refutation d1h5"

* info
	* depth <x>
	* seldepth <x>
	* time <x>
	* nodes <x>
	* pv <move1> ... <movei>
	* multipv <num>
	* score
		* cp <x>
		* mate <y>
		* lowerbound
		* upperbound
	* currmove <move>
	* currmovenumber <x>
	* hashfull <x>
	* nps <x>
	* tbhits <x>
	* sbhits <x>
	* cpuload <x>
	* string <str>
	* refutation <move1> <move2> ... <movei>
	* currline <cpunr> <move1> ... <movei>
	*/
	
namespace uci
{
	class score
	{
	public:
		friend std::ostream& operator<<(std::ostream& os, const score& sc)
		{
			os << "score";

			if (sc.cp) {
				os << " cp " << sc.cp.value();
			}
			if (sc.mate) {
				os << " mate " << sc.mate.value();
			}
			if (sc.is_lower_bound) {
				os << " lowerbound";
			}
			if (sc.is_upper_bound) {
				os << " upperbound";
			}

			return os;
		}

	public:
		std::optional<int> cp;
		std::optional<int> mate;
		std::optional<bool> is_lower_bound;
		std::optional<bool> is_upper_bound;
	};

	class currline
	{
	public:
		friend std::ostream& operator<<(std::ostream& os, const currline& cline) 
		{
			os << "line " << cline.cpu_num;

			for (const std::string& m : cline.moves) {
				os << ' ' << m;
			}

			return os;
		}

	public:
		int cpu_num;
		std::vector<std::string> moves;
	};

	class info
	{
	public:
		friend std::ostream& operator<<(std::ostream& os, const info& i)
		{
			os << "info";

			if (i.depth) {
				os << " depth " << i.depth.value();
			}
			if (i.seldepth) {
				os << " seldepth " << i.seldepth.value();
			}
			if (i.time) {
				os << " time " << i.time.value();
			}
			if (i.nodes) {
				os << " nodes " << i.nodes.value();
			}
			if (i.pv) {
				const std::vector<std::string>& pv = i.pv.value();

				if (pv.size()) {
					os << " pv";

					for (const std::string& str : pv) {
						os << ' ' << str;
					}
				}
			}
			if (i.multipv) {
				os << " multipv " << i.multipv.value();
			}
			if (i.score_val) {
				os << ' ' << i.score_val.value();
			}
			if (i.currmove) {
				os << " currmove " << i.currmove.value();
			}
			if (i.currmovenumber) {
				os << " currmovenumber " << i.currmovenumber.value();
			}
			if (i.hashfull) {
				os << " hashfull " << i.hashfull.value();
			}
			if (i.nps) {
				os << " nps " << i.nps.value();
			}
			if (i.tbhits) {
				os << " tbhits " << i.tbhits.value();
			}
			if (i.sbhits) {
				os << " sbhits " << i.sbhits.value();
			}
			if (i.cpuload) {
				os << " cpuload " << i.cpuload.value();
			}
			if (i.string_val) {
				os << " string " << i.string_val.value();
			}
			if (i.refutation) {
				const std::vector<std::string>& ref = i.refutation.value();

				if (ref.size()) {
					os << " refutation";
			
					for (const std::string & r : ref) {
						os << ' ' << r;
					}
				}
			}
			if (i.currline_val) {
				os << ' ' << i.currline_val.value();
			}

			return os;
		}

	public:
		std::optional<int> depth;
		std::optional<int> seldepth;
		std::optional<int> time;
		std::optional<int> nodes;
		std::optional<std::vector<std::string>> pv;
		std::optional<int> multipv;
		std::optional<score> score_val;
		std::optional<std::string> currmove;
		std::optional<int> currmovenumber;
		std::optional<int> hashfull;
		std::optional<int> nps;
		std::optional<int> tbhits;
		std::optional<int> sbhits;
		std::optional<int> cpuload;
		std::optional<std::string> string_val;
		std::optional<std::vector<std::string>> refutation;
		std::optional<currline> currline_val;
	};
} // namespace uci
