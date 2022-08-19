#include "info.h"

#include <sstream>

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string_regex.hpp>
#include <boost/regex.hpp>

using namespace std;

namespace uci
{
	namespace commands
	{
		// line should not start with 'score' as the first token
		// it should contain the rest of the score tokens
		void info::score::parse(const string& line)
		{
			this->cp.reset();
			this->mate.reset();
			this->bound = BOUND::NONE;

			vector<string> tokens;
			boost::split(tokens, line, boost::is_space());

			size_t i = 0;
			while (i < tokens.size()) {
				const string& key = tokens.at(i);

				if (key == "cp") {
					const string& value = tokens.at(i + 1);

					this->cp = stoi(value);

					i++;
				}
				else if (key == "mate") {
					const string& value = tokens.at(i + 1);

					this->mate = stoi(value);

					i++;
				}
				else if (key == "lowerbound") {
					this->bound = BOUND::LOWER;
				}
				else if (key == "upperbound") {
					this->bound = BOUND::UPPER;
				}

				i++;
			}
		}

		// line should not start with 'currline' as the first token
		// it should contain the rest of the currline tokens
		void info::currline::parse(const std::string& line)
		{
			moves.clear();

			vector<string> tokens;
			boost::split(tokens, line, boost::is_space());

			const string& next = tokens.at(0);
			bool isint = all_of(next.begin(), next.end(), isdigit);

			size_t i;
			if (isint) {
				this->cpu_num = stoi(next);

				i = 1;
			}
			else {
				i = 0;
			}

			std::copy(tokens.begin() + i, tokens.end(), back_inserter(this->moves));
		}

		void info::parse(const std::string& line)
		{
			this->depth.reset();
			this->seldepth.reset();
			this->time.reset();
			this->nodes.reset();
			this->pv.reset();
			this->multipv.reset();
			this->score_val.reset();
			this->currmove.reset();
			this->currmovenumber.reset();
			this->hashfull.reset();
			this->nps.reset();
			this->tbhits.reset();
			this->sbhits.reset();
			this->cpuload.reset();
			this->string_val.reset();
			this->refutation.reset();
			this->currline_val.reset();

			boost::regex regex;
			boost::sregex_token_iterator regex_it;
			boost::sregex_token_iterator end;

			regex = boost::regex(R"dil((info)\s*(.*))dil");

			regex_it = boost::sregex_token_iterator(line.begin(), line.end(), regex, { 1, 2 });

			const string& cmd = *regex_it++;
			assert_token("info", cmd, line);

			string last = *regex_it++;

			vector<key_value_pair> key_values;

			extract_key_value_pairs(
				last,
				{
					"depth", "seldepth", "time", "nodes", "pv", "multipv", "score", "currmove",
					"currmovenumber", "hashfull", "nps", "tbhits", "sbhits", "cpuload", "string",
					"refutation", "currline"
				},
				back_inserter(key_values)
			);

			for (const key_value_pair& pair : key_values)
			{
				const string& key = pair.key;
				const string& val = pair.val;

				if (key == "depth") { this->depth = stoi(val); }
				else if (key == "seldepth") { this->seldepth = stoi(val); }
				else if (key == "time") { this->time = stoi(val); }
				else if (key == "nodes") { this->nodes = stoi(val); }
				else if (key == "pv") {
					this->pv = vector<string>{};

					boost::split(this->pv.value(), val, boost::is_space());
				}
				else if (key == "multipv") { this->multipv = stoi(val); }
				else if (key == "score") {
					this->score_val = score{};

					this->score_val->parse(val);
				}
				else if (key == "currmove") { this->currmove = val; }
				else if (key == "currmovenumber") { this->currmovenumber = stoi(val); }
				else if (key == "hashfull") { this->hashfull = stoi(val); }
				else if (key == "nps") { this->nps = stoi(val); }
				else if (key == "tbhits") { this->tbhits = stoi(val); }
				else if (key == "sbhits") { this->sbhits = stoi(val); }
				else if (key == "cpuload") { this->cpuload = stoi(val); }
				else if (key == "string") { this->string_val = val; }
				else if (key == "refutation") {
					this->refutation = vector<string>{};

					boost::split(this->refutation.value(), val, boost::is_space());
				}
				else if (key == "currline") {
					this->currline_val = currline{};

					this->currline_val->parse(val);
				}
				else {
					const string expected =
						"depth|seldepth|time|nodes|pv|multipv|score|currmove|currmovenumber|"
						"hashfull|nps|tbhits|sbhits|cpuload|string|refutation|currline";

					throw_exception(expected, key, line);
				}
			}
		}
	} // namespace commands
} // namespace uci