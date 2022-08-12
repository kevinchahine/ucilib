#pragma once

#include "../go.h"
#include "../info.h"
#include "../options/option.h"
#include "../options/setoption.h"

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

		std::string to_quoted_string() const;

		friend std::ostream& operator<<(std::ostream& os, const Command& cmd);

		void parse(const std::string & line);
		
		bool is_cmd(const std::string& cmd);
		bool is_uci() const;
		bool is_debug() const;
		bool is_isready() const;
		bool is_setoption() const;
		bool is_register() const;
		bool is_ucinewgame() const;
		bool is_position() const;
		bool is_go() const;
		bool is_stop() const;
		bool is_ponderhit() const;
		bool is_quit() const;
		bool is_id() const;
		bool is_uciok() const;
		bool is_readyok() const;
		bool is_bestmove() const;
		bool is_copyprotection() const;
		bool is_registration() const;
		bool is_info() const;
		bool is_option() const;

		bool to_debug() const;
		setoption to_setoption() const;
		//option to_option() const;
		void to_position() const;
		//go to_go() const;
		void to_id() const;
		std::string to_bestmove() const;
		info to_info() const;

	private:
		// --- GUI commands (sent by GUI) ---
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

		// --- Engine commands (sent by Engine) ---
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