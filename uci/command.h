#pragma once

#include <iostream>
#include <string>
#include <vector>

namespace uci
{
	class Command
	{
	public:
		// A valid command is one which was successfully parsed.
		// An invalid command has an empty 1st token.
		// In that case, remaining tokens are meaningless 
		bool isValid() const { return tokens.size(); }
		bool isInValid() const { return !isValid(); }

		void setAsInvalid() { tokens.clear(); }

		std::string& cmd() { return tokens.front(); }
		const std::string& cmd() const { return tokens.front(); }

		friend std::ostream& operator<<(std::ostream& os, const Command& cmd);

		void parse(const std::string & line);

		void parseRegex(const std::string& line);

	private:
		void parse_setoption(std::istream& is);
		void parse_register(std::istream& is);
		void parse_position(std::istream& is);
		void parse_go(std::istream& is);
		void parse_id(std::istream& is);
		void parse_bestmove(std::istream& is);
		void parse_copyprotection(std::istream& is);
		void parse_registration(std::istream& is);
		void parse_info(std::istream& is);
		void parse_option(std::istream& is);

	private:
		std::vector<std::string> tokens;
	};
} // namespace uci