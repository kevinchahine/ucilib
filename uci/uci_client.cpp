#include "uci_base.h"
#include "uci_client.h"

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>	

#include <boost/process.hpp>

#include <numeric>		// for accumulate

using namespace std;

namespace uci
{
	UciClient::UciClient(const std::string& engineFilePath)
	{
		launch(engineFilePath);
	}

	void UciClient::launch(const std::string& engine_file_path)
	{
		// --- 1.) Make sure engine application exists ---
		boost::filesystem::path path = engine_file_path;
		cout << "Engine path: " << path << endl;

		if (path.is_absolute()) {
			cout << "Path is absolute" << endl;
		}
		else {
			cout << "Path is relative" << endl;
			// app can be in:
			//	- current currectory
			//	- under system path
			if (boost::filesystem::exists(path)) {
				cout << "app exists" << endl;
			}
			else {
				// Check under system path
				// boost::filesystem::path::find
				// TODO: Do this
			}
		}

		//boost::filesystem::path fromPath = boost::process::search_path(path);

		//cout << "from path: " << fromPath << endl;

		if (boost::filesystem::exists(path) == false) {
			cout << "Engine is not found or does not exist" << endl;

			return;
		}

		// --- 2.) Open engine ---
		engine = boost::process::child{
			engine_file_path,
			boost::process::std_out > is,
			boost::process::std_in < os
		};

		//std::string currline;
		//
		//while (is && std::getline(is, currline) && !currline.empty()) {
		//	std::cerr << "\'" << currline << "\'" << std::endl;
		//}
		//
		//cout << "done" << endl;
	}

	void UciClient::close()
	{
		// TODO: This might hang
		//engine.wait();
	}

	void UciClient::send_uci()
	{
		os << "uci" << endl;
	}

	void UciClient::send_debug(const Debug& debug)
	{
		os << "debug ";

		switch (debug)
		{
		case Debug::on:		os << "on";		break;
		case Debug::off:	os << "off";	break;
		}

		os << endl;
	}

	void UciClient::send_isready()
	{
		os << "isready" << endl;
	}

	void UciClient::send_ucinewgame()
	{
		os << "ucinewgame" << endl;
	}

	void UciClient::send_position()
	{
		os << "position startpos" << endl;
	}

	void UciClient::send_position(const string fen)
	{
		os << "position " << fen << endl;
	}

	void UciClient::send_position(const std::string fen, const std::vector<std::string>& moveSequence)
	{
		os << "position " << fen;

		if (moveSequence.size()) {
			os << " moves";

			for (const std::string& move : moveSequence) {
				os << ' ' << move;
			}
		}

		os << endl;
	}

	void UciClient::send_go(const go& go_params)
	{
		os << go_params << endl;
	}

	void UciClient::send_stop()
	{
		os << "stop" << endl;
	}

	void UciClient::send_ponderhit()
	{
		os << "ponderhit" << endl;
	}

	void UciClient::send_quit()
	{
		os << "quit" << endl;
	}

	// ----------------------------------- WAITS ---------------------------------

	const Command & UciClient::recv(const std::string& cmd_to_wait_for)
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

	const Command & UciClient::recv_id() 
	{
		return recv("id");
	}

	const Command & UciClient::recv_uciok() 
	{
		return recv("uciok");
	}

	const Command & UciClient::recv_readyok()
	{
		return recv("readyok");
	}

	const Command & UciClient::recv_bestmove()
	{
		return recv("bestmove");
	}

	const Command & UciClient::recv_copyprotection() 
	{
		return recv("copyprotection");
	}

	const Command & UciClient::recv_registration() 
	{
		return recv("registration");
	}

	const Command & UciClient::recv_info() 
	{
		return recv("info");
	}

	const Command & UciClient::recv_option()
	{
		return recv("option");
	}

	// ----------------------------------- CALLBACKS -----------------------------

} // namespace uci
