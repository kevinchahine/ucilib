#include "uci_base.h"
#include "uci_server.h"

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

#include <vector>

using namespace std;

namespace uci
{
	// -------------------------------- 

	// -------------------------------- SEND ----------------------------------

    void UciServer::send_id(const string & name, const string & author)
    {
		send_id_name(name);
		send_id_author(author);
    }

    void UciServer::send_id_name(const string & name)
    {
        os << "name " << name << endl;
    }
    
    void UciServer::send_id_author(const string & author)
    {
        os << "author " << author << endl;
    }
    
    void UciServer::send_uciok()
    {
		os << "uciok" << endl;
    }
    
    void UciServer::send_readyok()
    {
		os << "readyok" << endl;
    }

	void UciServer::send_bestmove(const std::string& bestMove, const std::string & ponderMove)
	{
		os << "bestmove " << bestMove;

		if (ponderMove.size()) {
			os << "ponder " << ponderMove;
		}

		os << endl;
	}

	void UciServer::send_info(info info)
	{
		os << info << endl;
	}

	// -------------------------------- RECEIVE -------------------------------

	const Command& UciServer::recv(const std::string& cmd_to_wait_for)
	{
		while (true) {
			// Reads next currline from input stream. 
			// Blocking call. Blocks until entire currline is read.
			// If currline is a valid command, it will be appended to back of `commands_in`
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

	const Command& UciServer::recv_uci()
	{
		return recv("uci");
	}

	const Command& UciServer::recv_debug()
	{
		return recv("debug");
	}

	const Command& UciServer::recv_isready()
	{
		return recv("isready");
	}

	const Command& UciServer::recv_setoption()
	{
		return recv("setoption");
	}

	const Command& UciServer::recv_register()
	{
		return recv("register");
	}

	const Command& UciServer::recv_ucinewgame()
	{
		return recv("ucinewgame");
	}

	const Command& UciServer::recv_position()
	{
		return recv("position");
	}

	const Command& UciServer::recv_go()
	{
		return recv("go");
	}

	const Command& UciServer::recv_stop()
	{
		return recv("stop");
	}

	const Command& UciServer::recv_ponderhit()
	{
		return recv("ponderhit");
	}

	const Command& UciServer::recv_quit()
	{
		return recv("quit");
	}

	// -------------------------------- CALLBACKS -----------------------------

    void UciServer::on_setoption(const Command& cmd)
    {
		// --- 1.) Generate an option object from command ---
		//option op;

		// --- 2.) Push option object to list ---
		//option_settings.push_back(op);
    }

} // namespace uci
