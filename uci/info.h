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

			if (i._depth) {
				os << " depth " << i._depth.value();
			}
			if (i._seldepth) {
				os << " seldepth " << i._seldepth.value();
			}
			if (i._time) {
				os << " time " << i._time.value();
			}
			if (i._nodes) {
				os << " nodes " << i._nodes.value();
			}
			if (i._pv) {
				const std::vector<std::string>& pv = i._pv.value();

				if (pv.size()) {
					os << " pv";

					for (const std::string& str : pv) {
						os << ' ' << str;
					}
				}
			}
			if (i._multipv) {
				os << " multipv " << i._multipv.value();
			}
			if (i._score) {
				os << ' ' << i._score.value();
			}
			if (i._currmove) {
				os << " currmove " << i._currmove.value();
			}
			if (i._currmovenumber) {
				os << " currmovenumber " << i._currmovenumber.value();
			}
			if (i._hashfull) {
				os << " hashfull " << i._hashfull.value();
			}
			if (i._nps) {
				os << " nps " << i._nps.value();
			}
			if (i._tbhits) {
				os << " tbhits " << i._tbhits.value();
			}
			if (i._sbhits) {
				os << " sbhits " << i._sbhits.value();
			}
			if (i._cpuload) {
				os << " cpuload " << i._cpuload.value();
			}
			if (i._string_val) {
				os << " string " << i._string_val.value();
			}
			if (i._refutation) {
				const std::vector<std::string>& ref = i._refutation.value();

				if (ref.size()) {
					os << " refutation";
			
					for (const std::string & r : ref) {
						os << ' ' << r;
					}
				}
			}
			if (i._currline) {
				os << ' ' << i._currline.value();
			}

			return os;
		}

	public:
		std::optional<int> _depth;
		std::optional<int> _seldepth;
		std::optional<int> _time;
		std::optional<int> _nodes;
		std::optional<std::vector<std::string>> _pv;
		std::optional<int> _multipv;
		std::optional<score> _score;
		std::optional<std::string> _currmove;
		std::optional<int> _currmovenumber;
		std::optional<int> _hashfull;
		std::optional<int> _nps;
		std::optional<int> _tbhits;
		std::optional<int> _sbhits;
		std::optional<int> _cpuload;
		std::optional<std::string> _string_val;
		std::optional<std::vector<std::string>> _refutation;
		std::optional<currline> _currline;
	};
} // namespace uci
