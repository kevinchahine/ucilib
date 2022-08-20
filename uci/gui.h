#pragma once

#include "base.h"

#include "uci/commands/commands.hpp"

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
		
		void send(const commands::command& cmd);
		void send_id(const commands::id& id);
		void send_uciok();
		void send_readyok();
		void send_bestmove(const commands::bestmove& bestmove);
		void send_copyprotection(const commands::copyprotection& copyprotection);
		void send_register(const commands::register_cmd& register_cmd);
		void send_info(const commands::info & info);
		void send_option(const commands::option& option);

		// ---------------------------- RECEIVE -------------------------------
		
		// Waits until the next command is received from server (gui) before returning.
		// Method will block until the next command is received.
		const commands::command & recv();
		
		// Waits until a specific command is received from server (gui) before returning.
		// Received command must be valid. Method will continue to block until a valid command is received
		// and matches `cmd_to_wait_for`.
		// Blocking call. 
		const commands::command& recv_until(const commands::command& cmd_to_wait_for);
		const commands::uci & recv_until_uci();
		const commands::debug & recv_until_debug();
		const commands::isready & recv_until_isready();
		const commands::setoption & recv_until_setoption();
		const commands::register_cmd & recv_until_register();
		const commands::ucinewgame & recv_until_ucinewgame();
		const commands::position & recv_until_position();
		const commands::go & recv_until_go();
		const commands::stop & recv_until_stop();
		const commands::ponderhit & recv_until_ponderhit();
		const commands::quit & recv_until_quit();
	
	protected:
	
		// Callbacks
		////void handle_uci(const Command & cmd);
		////void handle_debug(const Command & cmd);
		////void handle_isready(const Command & cmd);
		////void handle_setoption(const Command & cmd);
		////void handle_register(const Command & cmd);
		////void handle_ucinewgame(const Command & cmd);
		////void handle_position(const Command & cmd);
		////void handle_go(const Command & cmd);
		////void handle_stop(const Command & cmd);
		////void handle_ponderhit(const Command & cmd);
		////void handle_quit(const Command & cmd);
	
	protected:
		std::ostream & os;
		std::istream & is;
	
	public:
		// List of all options which the server (GUI) has set
		// through 'setoption' commands
		////options::list option_settings;
	
		// --- User defined Callbacks ---
		//std::function<void(const Command& cmd)> on_uci;
		//std::function<void(const Command& cmd)> on_debug;
		//std::function<void(const Command& cmd)> on_isready;
		//std::function<void(const Command& cmd)> on_setoption;
		//std::function<void(const Command& cmd)> on_register;
		//std::function<void(const Command& cmd)> on_ucinewgame;
		//std::function<void(const Command& cmd)> on_position;
		//std::function<void(const Command& cmd)> on_go;
		//std::function<void(const Command& cmd)> on_stop;
		//std::function<void(const Command& cmd)> on_ponderhit;
		//std::function<void(const Command& cmd)> on_quit;
	
	};
} // namespace uci