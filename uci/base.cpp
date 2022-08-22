#include "base.h"

using namespace std;

namespace uci
{
	void base::parse_line(istream & is)
	{
		// --- get currline from stream (blocking) ---
		std::string line;
	
		if (is && std::getline(is, line) && !line.empty()) {

			if (line.back() == '\r') {
				line.pop_back();
			}

			///cout << "Parsing line:  \'" << line << "\'" << endl;

			commands::command cmd;
			cmd.parse(line);

			if (cmd.is_valid()) {
				///cout << "Parsed command: " << cmd << endl;
				
				// --- append to command list ---
				commands_in.emplace_back(std::move(cmd));
			}
			else {
				///cout << "Invalid command" << endl;
			}
		}
	}

} // namespace uci
