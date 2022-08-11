#include "base.h"
#include "gui.h"

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

#include <vector>

using namespace std;

namespace uci
{
	// -------------------------------- 

	// -------------------------------- SEND ----------------------------------

    void gui::send_id(const string & name, const string & author)
    {
		send_id_name(name);
		send_id_author(author);
    }

    void gui::send_id_name(const string & name)
    {
        os << "name " << name << endl;
    }
    
    void gui::send_id_author(const string & author)
    {
        os << "author " << author << endl;
    }
    
    void gui::send_uciok()
    {
		os << "uciok" << endl;
    }
    
    void gui::send_readyok()
    {
		os << "readyok" << endl;
    }

	void gui::send_bestmove(const std::string& bestMove, const std::string & ponderMove)
	{
		os << "bestmove " << bestMove;

		if (ponderMove.size()) {
			os << "ponder " << ponderMove;
		}

		os << endl;
	}

	void gui::send_info(info info)
	{
		os << info << endl;
	}

	// -------------------------------- RECEIVE -------------------------------

	const Command& gui::recv()
	{
		this->parse_line(is);

		return commands_in.back();
	}

	const Command& gui::recv_until(const std::string& cmd_to_wait_for)
	{
		while (true) {
			// Reads next currline from input stream. 
			// Blocking call. Blocks until entire line is read.
			// If line is a valid command, it will be appended to back of `commands_in`
			// Invalid commands will be deleted and method will return
			this->parse_line(is);

			if (commands_in.size()) {
				const Command& cmd = commands_in.back();

				if (cmd.cmd() == cmd_to_wait_for) {
					break;
				}
			}
		}

		return commands_in.back();
	}

	const Command& gui::recv_until_uci()
	{
		return recv_until("uci");
	}

	const Command& gui::recv_until_debug()
	{
		return recv_until("debug");
	}

	const Command& gui::recv_until_isready()
	{
		return recv_until("isready");
	}

	const Command& gui::recv_until_setoption()
	{
		return recv_until("setoption");
	}

	const Command& gui::recv_until_register()
	{
		return recv_until("register");
	}

	const Command& gui::recv_until_ucinewgame()
	{
		return recv_until("ucinewgame");
	}

	const Command& gui::recv_until_position()
	{
		return recv_until("position");
	}

	const Command& gui::recv_until_go()
	{
		return recv_until("go");
	}

	const Command& gui::recv_until_stop()
	{
		return recv_until("stop");
	}

	const Command& gui::recv_until_ponderhit()
	{
		return recv_until("ponderhit");
	}

	const Command& gui::recv_until_quit()
	{
		return recv_until("quit");
	}

	// -------------------------------- CALLBACKS -----------------------------

    void gui::on_setoption(const Command& cmd)
    {
		// --- 1.) Generate an option object from command ---
		options::option op;
		op.from(cmd);

		// --- 2.) Push option object to list ---
		option_settings.push_back(std::move(op));
    }

} // namespace uci
