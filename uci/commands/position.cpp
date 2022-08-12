#include "position.h"

#include <algorithm>

using namespace std;

namespace uci
{
	namespace commands
	{
		position::position(const Command& cmd) : 
			Command(cmd)
		{
		}
		
		position::position(Command&& cmd) :
			Command(std::move(cmd))
		{
		}
		
		const std::string& position::fen() const
		{
			if (is_fen())			return this->at(2);
			else if (is_startpos())	return position::startpos_fen;
			else					throw std::exception("position format is invalid");
		}

		vector<string> position::get_moves() const
		{
			vector<string> moves;

			// What is the index of the 1st move?
			size_t first_move_index = 0;
			if (is_fen())			first_move_index = 3;
			else if (is_startpos())	first_move_index = 2;
			else					throw exception("position format is invalid");

			// How many moves do we have?
			size_t n_moves = this->size() - first_move_index;
			moves.reserve(n_moves);

			// Copy moves into vector
			copy_n(this->begin() + first_move_index, n_moves, back_inserter(moves));

			return moves;
		}
		
		forge::Position position::to_position()
		{
			forge::Position pos;

			// --- Starting Position (before move squence) ---
			if (is_fen()) {
				pos.fromFEN(this->fen());
			}
			else if (is_startpos()) {
				pos.setupNewGame();
			}
			else {
				pos.setupNewGame();
			}

			// --- Apply move sequence if it exists ---
			vector<string> move_sequence = this->get_moves();

			for (const string& move : move_sequence) {
				forge::Move m(move);

				pos.move<forge::pieces::Piece>(m);
			}

			return pos;
		}
	} // namespace commands
} // namespace uci

