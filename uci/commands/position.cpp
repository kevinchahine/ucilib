#include "position.h"

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string_regex.hpp>
#include <boost/regex.hpp>

using namespace std;

namespace uci
{
	namespace commands
	{
		void position::parse(const std::string& line)
		{
			// expression: position [fen <fenstring> | startpos ]  moves <move1> .... <movei>

			boost::regex regex;
			boost::sregex_token_iterator regex_it;
			boost::sregex_token_iterator end;

			string fenstring = R"dil([kqrbnp\d\/]+\s+[bw]\s+[kq]+\s+-\s+\d+\s+\d+)dil";

			// --- Position ---
			
			// TODO: Try combining these into one

			if (boost::algorithm::contains(line, "fen")) {
				// position fen <fenstring> [ moves <move1> .... <movei> ]
				// position fen <fenstring>   moves <move1> .... <movei>
				// position fen <fenstring>
				regex = boost::regex(R"dil((position)\s+(fen)\s+([KkQqRrBbNnPp\d\/]+\s+[BbWw]\s+[KQkq]+\s+-\s+\d+\s+\d+)\s*(moves\s+.*)?)dil");

				regex_it = boost::sregex_token_iterator(line.begin(), line.end(), regex, { 1, 2, 3, 4 });

				const string& cmd = *regex_it++;
				if (cmd != "position")
					throw_exception("position", cmd, line);

				const string& format = *regex_it++;
				if (format != "fen")
					throw_exception("fen", format, line);

				const string& fen = *regex_it++;
				this->pos = fen;
			}
			else if (boost::algorithm::contains(line, "startpos")) {
				// position startpos [ moves <move1> .... <movei> ]
				// position startpos   moves <move1> .... <movei> 
				// position startpos
				regex = boost::regex(R"dil((position)\s+(startpos)\s*(moves\s+.*)?)dil");

				regex_it = boost::sregex_token_iterator(line.begin(), line.end(), regex, { 1, 2, 3 });

				const string& cmd = *regex_it++;
				if (cmd != "position")
					throw_exception("position", cmd, line);

				const string& format = *regex_it++;
				if (format != "startpos")
					throw_exception("startpos", format, line);

				this->pos = "startpos";
			}

			// --- Moves ---
			if (regex_it != end) {
				vector<string> tokens;
				boost::split(tokens, *regex_it, boost::is_any_of(" "), boost::token_compress_on);

				this->moves.clear();
				this->moves.reserve(tokens.size() == 0 ? 0 : tokens.size() - 1);

				// Skip the 1st token which is "moves"
				for (size_t i = 1; i < tokens.size(); i++) {
					const string& t = tokens.at(i);

					if (t.size()) {
						this->moves.emplace_back(t);
					}
				}
			}
		}
	} // namespace commands
} // namespace uci

//#include "position.h"
//
//#include <algorithm>
//
//using namespace std;
//
//namespace uci
//{
//	namespace commands
//	{
//		position::position(const Command& cmd) : 
//			Command(cmd)
//		{
//		}
//		
//		position::position(Command&& cmd) :
//			Command(std::move(cmd))
//		{
//		}
//		
//		const std::string& position::fen() const
//		{
//			if (is_fen())			return this->at(2);
//			else if (is_startpos())	return position::startpos_fen;
//			else					throw std::exception("position format is invalid");
//		}
//
//		vector<string> position::get_moves() const
//		{
//			vector<string> moves;
//
//			// What is the index of the 1st move?
//			size_t first_move_index = 0;
//			if (is_fen())			first_move_index = 3;
//			else if (is_startpos())	first_move_index = 2;
//			else					throw exception("position format is invalid");
//
//			// How many moves do we have?
//			size_t n_moves = this->size() - first_move_index;
//			moves.reserve(n_moves);
//
//			// Copy moves into vector
//			copy_n(this->begin() + first_move_index, n_moves, back_inserter(moves));
//
//			return moves;
//		}
//		
//		forge::Position position::to_position()
//		{
//			forge::Position pos;
//
//			// --- Starting Position (before move squence) ---
//			if (is_fen()) {
//				pos.fromFEN(this->fen());
//			}
//			else if (is_startpos()) {
//				pos.setupNewGame();
//			}
//			else {
//				pos.setupNewGame();
//			}
//
//			// --- Apply move sequence if it exists ---
//			vector<string> move_sequence = this->get_moves();
//
//			for (const string& move : move_sequence) {
//				forge::Move m(move);
//
//				pos.move<forge::pieces::Piece>(m);
//			}
//
//			return pos;
//		}
//	} // namespace commands
//} // namespace uci

