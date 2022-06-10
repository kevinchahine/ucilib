#pragma once

#include "uci_base.h"

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
		void send_id(const std::string& name, const std::string& author);
		void send_id_name(const std::string& name);
		void send_id_author(const std::string& author);
		void send_uciok();
		void send_readyok();
		//void send_bestmove(forge::Move bestMove, vector<forge::Move> ponderingMoves);	// TODO: Link to forgelib
		//void send_copyprotection(CopyProtection copyProtection);
		//void send_register(Registration registration);
		//void send_info(Info info);
		//void send_option(Option op);	// ??? 


	protected:

		// Handles all incomming messages
		void handle(const std::string& message);

		// Callbacks
		void on_uci(const std::vector<std::string>& tokens);
		void on_debug(const std::vector<std::string>& tokens);
		void on_isready(const std::vector<std::string>& tokens);
		void on_setoption(const std::vector<std::string>& tokens);
		void on_register(const std::vector<std::string>& tokens);
		void on_ucinewgame(const std::vector<std::string>& tokens);
		void on_position(const std::vector<std::string>& tokens);
		void on_go(const std::vector<std::string>& tokens);
		void on_stop(const std::vector<std::string>& tokens);
		void on_ponderhit(const std::vector<std::string>& tokens);
		void on_quit(const std::vector<std::string>& tokens);

	protected:

		std::function<void()> uci_callback;

	};
} // namespace uci