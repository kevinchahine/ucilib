#include "uci_base.h"
#include "uci_client.h"

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>	

#include <numeric>		// for accumulate

using namespace std;

namespace uci
{
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
