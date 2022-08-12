#pragma once

#include "uci/commands/command.h"
#include <forge/core/Position.h>

#include <exception>

namespace uci
{
	namespace commands
	{
		class position : public Command
		{
		public:
			position() = default;
			position(const Command& cmd);
			position(Command&& cmd);
			position(const position&) = default;
			position(position&&) noexcept = default;
			~position() noexcept = default;
			position& operator=(const position&) = default;
			position& operator=(position&&) noexcept = default;

			// should return "position"
			const std::string& cmd() const { return this->at(0); }

			// Returns the format of the position
			// Either "fen" or "startpos"
			const std::string& format() const { return this->at(1); }

			bool is_fen() const { return format() == "fen"; }
			bool is_startpos() const { return format() == "startpos"; }

			// If format() is "fen" then this returns the position represented as a fen string
			// Otherwise it returns a fen string equivalent to "startpos"
			const std::string& fen() const;

			// Returns the move sequence as a vector of strings
			std::vector<std::string> get_moves() const;

			forge::Position to_position();

		protected:
			// fen string representing the starting position of a chess game.
			inline static const std::string startpos_fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
		};
	} // namespace commands
} // namespace uci