#include "command.h"

#include "uci/commands/bestmove.h"
#include "uci/commands/copyprotection.h"
#include "uci/commands/debug.h"
#include "uci/commands/go.h"
#include "uci/commands/id.h"
#include "uci/commands/info.h"
#include "uci/commands/isready.h"
#include "uci/commands/option.h"
#include "uci/commands/ponderhit.h"
#include "uci/commands/position.h"
#include "uci/commands/quit.h"
#include "uci/commands/readyok.h"
#include "uci/commands/register.h"
#include "uci/commands/registration.h"
#include "uci/commands/setoption.h"
#include "uci/commands/stop.h"
#include "uci/commands/uci.h"
#include "uci/commands/ucinewgame.h"
#include "uci/commands/uciok.h"
#include "uci/commands/helpers.h"

#include <algorithm>
#include <sstream>

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string_regex.hpp>
#include <boost/regex.hpp>

using namespace std;

namespace uci
{
	namespace commands
	{
		void command::parse(const std::string& line)
		{
			// --- 0.) Clear existing tokesn and puse currline into a stream ---
			istringstream is(line);

			// --- 1.) parse command ---
			string cmd;
			is >> cmd;

			boost::algorithm::to_lower(cmd);

			// --- Determine which command we have ---
			if (cmd == "uci")					cmd_ptr = make_unique<uci>();
			else if (cmd == "debug")			cmd_ptr = make_unique<debug>();
			else if (cmd == "isready")			cmd_ptr = make_unique<isready>();
			else if (cmd == "setoption")		cmd_ptr = make_unique<setoption>();
			else if (cmd == "register")			cmd_ptr = make_unique<register_cmd>();
			else if (cmd == "ucinewgame")		cmd_ptr = make_unique<ucinewgame>();
			else if (cmd == "position")			cmd_ptr = make_unique<position>();
			else if (cmd == "go")				cmd_ptr = make_unique<go>();
			else if (cmd == "stop")				cmd_ptr = make_unique<stop>();
			else if (cmd == "ponderhit")		cmd_ptr = make_unique<ponderhit>();
			else if (cmd == "quit")				cmd_ptr = make_unique<quit>();
			else if (cmd == "id")				cmd_ptr = make_unique<id>();
			else if (cmd == "uciok")			cmd_ptr = make_unique<uciok>();
			else if (cmd == "readyok")			cmd_ptr = make_unique<readyok>();
			else if (cmd == "bestmove")			cmd_ptr = make_unique<bestmove>();
			else if (cmd == "copyprotection")	cmd_ptr = make_unique<copyprotection>();
			else if (cmd == "registration")		cmd_ptr = make_unique<registration>();
			else if (cmd == "info")				cmd_ptr = make_unique<info>();
			else if (cmd == "option")			cmd_ptr = make_unique<option>();
			else {
				//throw_exception("a command", cmd, line);
				return;	// command was invalid
			}
			
			// --- Parse command ---
			cmd_ptr->parse(line);
		}
	} // namespace commands
} // namespace uci

