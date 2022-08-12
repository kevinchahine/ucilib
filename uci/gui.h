#pragma once

#include "base.h"

#include "info.h"
#include "options/option.h"
#include "options/list.h"

#include <thread>

namespace uci
{
	// See class base
	// 
	// Represents the gui which is running this process. 
	// A UCI Server is a UCI compatible Chess GUI.
	// An object of this class can be used to communicate with 
	// a UCI Server using the UCI protocol.
	// 
	// A chess engine which is spawned from a UCI Server (Chess GUI) 
	// should instantiate a gui object and connect 
	// std_in and std_out to the gui object using its constructor.
	// 
	// Because the UCI Client (Chess Engine) needs to always be responsive
	// to commands received from the UCI Server (Chess GUI), the 
	// gui object internally spawns a separate thread.
	// This thread will need access to parts of the engine like
	// search parameters and engine information.
	// 
	// Streams:
	//	use std::cin and std::cout when communicating with UCI Server (UCI GUI)
	class gui : public base
	{
	public:
		gui() :
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
		template<class OPTION_T> void send_option(const OPTION_T& op) { os << op << std::endl; }

		// ---------------------------- RECEIVE -------------------------------
		
		// Waits until the next command is received from server (gui) before returning.
		// Returns command. Command may be valid or invalid. Check using a call to Command::isValid()
		// Method will block until the next command is received.
		const Command & recv();

		// Waits until a specific command is received from server (gui) before returning.
		// Received command must be valid. Method will continue to block until a valid command is received
		// and matches `cmd_to_wait_for`.
		// Blocking call. 
		const Command & recv_until(const std::string& cmd_to_wait_for);
		const Command & recv_until_uci();
		const Command & recv_until_debug();
		const Command & recv_until_isready();
		const Command & recv_until_setoption();
		const Command & recv_until_register();
		const Command & recv_until_ucinewgame();
		const Command & recv_until_position();
		const Command & recv_until_go();
		const Command & recv_until_stop();
		const Command & recv_until_ponderhit();
		const Command & recv_until_quit();

	protected:

		// Callbacks
		void handle_uci(const Command & cmd);
		void handle_debug(const Command & cmd);
		void handle_isready(const Command & cmd);
		void handle_setoption(const Command & cmd);
		void handle_register(const Command & cmd);
		void handle_ucinewgame(const Command & cmd);
		void handle_position(const Command & cmd);
		void handle_go(const Command & cmd);
		void handle_stop(const Command & cmd);
		void handle_ponderhit(const Command & cmd);
		void handle_quit(const Command & cmd);

	protected:
		std::ostream & os;
		std::istream & is;

	public:
		// List of all options which the server (GUI) has set
		// through 'setoption' commands
		options::list option_settings;

		// --- User defined Callbacks ---
		std::function<void(const Command& cmd)> on_uci;
		std::function<void(const Command& cmd)> on_debug;
		std::function<void(const Command& cmd)> on_isready;
		std::function<void(const Command& cmd)> on_setoption;
		std::function<void(const Command& cmd)> on_register;
		std::function<void(const Command& cmd)> on_ucinewgame;
		std::function<void(const Command& cmd)> on_position;
		std::function<void(const Command& cmd)> on_go;
		std::function<void(const Command& cmd)> on_stop;
		std::function<void(const Command& cmd)> on_ponderhit;
		std::function<void(const Command& cmd)> on_quit;

	};
} // namespace uci