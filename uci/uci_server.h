#pragma once

#include "uci_base.h"

#include "uci/info.h"
#include "uci/options/option.h"
#include "uci/options/option_list.h"

namespace uci
{
	// See class UciBase
	// 
	// Represents the UciServer which is running this process. 
	// A UCI Server is a UCI compatible Chess GUI.
	// An object of this class can be used to communicate with 
	// a UCI Server using the UCI protocol.
	// 
	// A chess engine which is spawned from a UCI Server (Chess GUI) 
	// should instantiate a UciServer object and connect 
	// std_in and std_out to the UciServer object using its constructor.
	// 
	// Because the UCI Client (Chess Engine) needs to always be responsive
	// to commands received from the UCI Server (Chess GUI), the 
	// UciServer object internally spawns a separate thread.
	// This thread will need access to parts of the engine like
	// search parameters and engine information.
	// 
	// Streams:
	//	use std::cin and std::cout when communicating with UCI Server (UCI GUI)
	class UciServer : public UciBase
	{
	public:
		UciServer() :
			os(std::cout),
			is(std::cin) {}

		// ---------------------------- SEND ----------------------------------

		void send_id(const std::string& name, const std::string& author);
		void send_id_name(const std::string& name);
		void send_id_author(const std::string& author);
		void send_uciok();
		void send_readyok();
		void send_bestmove(const std::string & bestMove, const std::string & ponderMove);
		//void send_copyprotection(CopyProtection copyProtection);
		//void send_register(Registration registration);
		void send_info(info info);
		template<class OPTION_T> void send_option(const OPTION_T & op);

		// ---------------------------- RECEIVE -------------------------------
		
		// Waits until a specific command is received from client (engine) before returning.
		// Received command must be valid. Method will continue to block until a valid command is received
		// and matches `cmd_to_wait_for`.
		// Blocking call. 
		const Command & recv(const std::string& cmd_to_wait_for);
		const Command & recv_uci();
		const Command & recv_debug();
		const Command & recv_isready();
		const Command & recv_setoption();
		const Command & recv_register();
		const Command & recv_ucinewgame();
		const Command & recv_position();
		const Command & recv_go();
		const Command & recv_stop();
		const Command & recv_ponderhit();
		const Command & recv_quit();

	protected:

		// Handles all incomming messages
		//void handle(const std::string& message);

		// Callbacks
		void on_uci(const Command & cmd);
		void on_debug(const Command & cmd);
		void on_isready(const Command & cmd);
		void on_setoption(const Command & cmd);
		void on_register(const Command & cmd);
		void on_ucinewgame(const Command & cmd);
		void on_position(const Command & cmd);
		void on_go(const Command & cmd);
		void on_stop(const Command & cmd);
		void on_ponderhit(const Command & cmd);
		void on_quit(const Command & cmd);

	protected:

		std::function<void()> uci_callback;

		std::ostream & os;
		std::istream & is;

		bool is_quit_received = false;

		// List of all options which the server (GUI) has set
		// through 'setoption' commands
		//option_list option_settings;
	};
	
	template<class OPTION_T>
	void UciServer::send_option(const OPTION_T& op)
	{
		os << op << endl;
	}
} // namespace uci