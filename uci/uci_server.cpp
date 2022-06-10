#include "uci_base.h"
#include "uci_server.h"

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

#include <vector>

using namespace std;

namespace uci
{
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
	
	void UciServer::handle(const string& message)
	{
		// --- 1.) Parse message into tokens (1st token is the command) ---
		vector<string> tokens;
		boost::algorithm::split(tokens, message, boost::algorithm::is_space());
		
		if (tokens.size()) {
			const string& command = tokens.front();

			// --- 2.) Call appropriate onr for command ---
			/**/ if (command == "uci")			{ on_uci(tokens); }
			else if (command == "debug")		{ on_debug(tokens); }
			else if (command == "isready")		{ on_isready(tokens); }
			else if (command == "setoption")	{ on_setoption(tokens); }
			else if (command == "register")		{ on_register(tokens); }
			else if (command == "ucinewgame")	{ on_ucinewgame(tokens); }
			else if (command == "position")		{ on_position(tokens); }
			else if (command == "go")			{ on_go(tokens); }
			else if (command == "stop")			{ on_stop(tokens); }
			else if (command == "ponderhit")	{ on_ponderhit(tokens); }
			else if (command == "quit")			{ on_quit(tokens); }
			else { /* command is not recognized. ignore it and move on. */ }

			
		}
		else {
			// No tokens where found in message. Ignore it and move on.
		}
	}

	void UciServer::on_uci(const std::vector<std::string>& tokens)
	{
		// TODO: ???
	}
	
	void UciServer::on_debug(const std::vector<std::string>& tokens)
	{
		// TODO: ???
	}
	
	void UciServer::on_isready(const std::vector<std::string>& tokens)
	{
		// TODO: ???
	}
	
	void UciServer::on_setoption(const std::vector<std::string>& tokens)
	{
		// TODO: ???
	}
	
	void UciServer::on_register(const std::vector<std::string>& tokens)
	{
		// TODO: ???
	}
	
	void UciServer::on_ucinewgame(const std::vector<std::string>& tokens)
	{
		// TODO: ???
	}
	
	void UciServer::on_position(const std::vector<std::string>& tokens)
	{
		// TODO: ???
	}
	
	void UciServer::on_go(const std::vector<std::string>& tokens)
	{
		// TODO: ???
	}
	
	void UciServer::on_stop(const std::vector<std::string>& tokens)
	{
		// TODO: ???
	}
	
	void UciServer::on_ponderhit(const std::vector<std::string>& tokens)
	{
		// TODO: ???
	}
	
	void UciServer::on_quit(const std::vector<std::string>& tokens)
	{
		// TODO: ???
	}
} // namespace uci
