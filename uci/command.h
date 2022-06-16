#pragma once

#include <iostream>
#include <string>
#include <vector>

namespace uci
{
	class Command : public std::vector<std::string>
	{
	public:
		// A valid command is one which was successfully parsed.
		// An invalid command has an empty 1st token.
		// In that case, remaining tokens are meaningless 
		bool isValid() const { return this->size(); }
		bool isInValid() const { return !isValid(); }

		void setAsInvalid() { this->clear(); }

		std::string& cmd() { return this->front(); }
		const std::string& cmd() const { return this->front(); }

		friend std::ostream& operator<<(std::ostream& os, const Command& cmd);

		void parse(const std::string & line);

	private:
		// --- GUI commands (send by GUI) ---
		void parse_uci(const std::string& line);
		void parse_debug(const std::string& line);
		void parse_isready(const std::string& line);
		void parse_setoption(const std::string& line);
		void parse_register(const std::string & line);
		void parse_ucinewgame(const std::string& line);
		void parse_position(const std::string & line);
		void parse_go(const std::string & line);
		void parse_stop(const std::string& line);
		void parse_ponderhit(const std::string& line);
		void parse_quit(const std::string& line);

		// --- Engine commands (send by Engine) ---
		void parse_id(const std::string & line);
		void parse_uciok(const std::string& line);
		void parse_readyok(const std::string& line);
		void parse_bestmove(const std::string & line);
		void parse_copyprotection(const std::string & line);
		void parse_registration(const std::string & line);
		void parse_info(const std::string & line);
		void parse_option(const std::string & line);
	};
} // namespace uci