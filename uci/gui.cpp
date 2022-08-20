#include "base.h"
#include "gui.h"

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

#include <vector>

using namespace std;

namespace uci
{
	// -------------------------------- SEND ----------------------------------
	void gui::send(const commands::command& cmd) { os << cmd << endl; }
	
	void gui::send_id(const commands::id& id) { os << id << endl; }

	void gui::send_uciok() { os << commands::uciok{} << endl; }

	void gui::send_readyok() { os << commands::readyok{} << endl; }

	void gui::send_bestmove(const commands::bestmove& bestmove) { os << bestmove << endl; }

	void gui::send_copyprotection(const commands::copyprotection& copyprotection) { os << copyprotection << endl; }

	void gui::send_register(const commands::register_cmd& register_cmd) { os << register_cmd << endl; }

	void gui::send_info(const commands::info& info) { os << info << endl; }

	void gui::send_option(const commands::option& option) { os << option << endl; }

	// -------------------------------- RECEIVE -------------------------------

	const commands::command& gui::recv()
	{
		this->parse_line(is);

		return commands_in.back();
	}

	const commands::command& gui::recv_until(const commands::command& cmd_to_wait_for)
	{
		while (true) {
			// Reads next currline from input stream. 
			// Blocking call. Blocks until entire currline is read.
			// If currline is a valid command, it will be appended to back of `commands_in`
			// Invalid commands will be deleted and method will return
			this->parse_line(is);

			if (commands_in.size()) {
				const commands::command& curr_command = commands_in.back();

				if (curr_command.is_valid()) {
					if (curr_command.is_same_as(cmd_to_wait_for)) {
						break;
					}
				}
			}
		}

		return commands_in.back();
	}

	const commands::uci& gui::recv_until_uci() { return recv_until(commands::uci{}).as<commands::uci>(); }
	const commands::debug& gui::recv_until_debug() { return recv_until(commands::debug{}).as<commands::debug>(); }
	const commands::isready& gui::recv_until_isready() { return recv_until(commands::isready{}).as<commands::isready>(); }
	const commands::setoption& gui::recv_until_setoption() { return recv_until(commands::setoption{}).as<commands::setoption>(); }
	const commands::register_cmd& gui::recv_until_register() { return recv_until(commands::register_cmd{}).as<commands::register_cmd>(); }
	const commands::ucinewgame& gui::recv_until_ucinewgame() { return recv_until(commands::ucinewgame{}).as<commands::ucinewgame>(); }
	const commands::position& gui::recv_until_position() { return recv_until(commands::position{}).as<commands::position>(); }
	const commands::go& gui::recv_until_go() { return recv_until(commands::go{}).as<commands::go>(); }
	const commands::stop& gui::recv_until_stop() { return recv_until(commands::stop{}).as<commands::stop>(); }
	const commands::ponderhit& gui::recv_until_ponderhit() { return recv_until(commands::ponderhit{}).as<commands::ponderhit>(); }
	const commands::quit& gui::recv_until_quit() { return recv_until(commands::quit{}).as<commands::quit>(); }

	//// -------------------------------- CALLBACKS -----------------------------
	//
	//void gui::handle_setoption(const Command& cmd)
	//{
	//	// --- 1.) Generate an option object from command ---
	//	options::option op;
	//	op.from(cmd);
	//
	//	// --- 2.) Push option object to list ---
	//	option_settings.push_back(std::move(op));
	//
	//	// --- 3.) Call user defined callback ---
	//	on_setoption(cmd);
	//}
	//
} // namespace uci
