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

		//std::string line;
		//
		//while (is && std::getline(is, line) && !line.empty()) {
		//	std::cerr << "\'" << line << "\'" << std::endl;
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

	void UciClient::send_position(const string fen)
	{
		os << "position " << fen << endl;
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

	void UciClient::wait_for(const std::string& cmd_to_wait_for)
	{
		while (true) {
			// Reads next line from input stream. 
			// Blocking call. Blocks until entire line is read.
			// If line is a valid command, it will be appended to back of `commands_in`
			// Invalid commands will be deleted and method will return
			this->getline();

			if (commands_in.size()) {
				const Command& cmd = commands_in.back();

				if (cmd.cmd() == cmd_to_wait_for) {
					break;
				}
			}
		}
	}

	void UciClient::wait_for_id() { wait_for("id"); }

	void UciClient::wait_for_uciok() { wait_for("uciok"); }

	void UciClient::wait_for_readyok() { wait_for("readyok"); }

	void UciClient::wait_for_bestmove() { wait_for("bestmove"); }

	void UciClient::wait_for_copyprotection() { wait_for("copyprotection"); }

	void UciClient::wait_for_registration() { wait_for("registration"); }

	void UciClient::wait_for_info() { wait_for("info"); }

	void UciClient::wait_for_option() { wait_for("option"); }

	// ----------------------------------- CALLBACKS -----------------------------

	void UciClient::handle(string& message)
	{
		// --- 1.) Parse Command ---
		string::iterator start = find_if(message.begin(), message.end(), isalpha);
		string::iterator stop = find(start, message.end(), ' ');
		string command(start, stop);

		// --- 2.) Call appropriate command ---
		/**/ if (command == "id") {
			start = find_if(message.begin(), message.end(), isalpha);
			stop = find(start, message.end(), ' ');

			string key(start, stop);

			string::iterator start = find_if(stop, message.end(), isalnum);
			string value(start, message.end());

			on_id(key, value);
		}
		else if (command == "uciok") {
			on_uciok();
		}
		else if (command == "readyok") {

		}
		else if (command == "bestmove") {

		}
		else if (command == "copyprotection") {

		}
		else if (command == "register") {

		}
		else if (command == "info") {

		}
		else if (command == "option") {

		}
	}

	void UciClient::on_id(const std::string& key, const std::string& value)
	{
		if (key == "name") {
			this->name = value;
		}
		else if (key == "author") {
			this->author = value;
		}

		on_id_callback();
	}

	void UciClient::on_uciok()
	{
		on_uciok_callback();
	}

	void UciClient::on_readyok()
	{
	}

	void UciClient::on_bestmove()
	{
	}

	void UciClient::on_copyprotection()
	{
	}

	void UciClient::on_register()
	{
	}

	void UciClient::on_info()
	{
	}

	void UciClient::on_option()
	{
	}
} // namespace uci
