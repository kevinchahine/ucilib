#pragma once

#include "uci/go.h"
#include "uci/options/option.h"
#include "uci/options/list.h"
#include "uci/uci_base.h"
#include "uci/debug.h"

#include <boost/process/child.hpp>
#include <boost/process/pipe.hpp>

namespace uci
{
	// TODO: Why not simply call this 'Client' (no Uci)
	class UciClient : public UciBase
	{
	public:
		UciClient(const std::string& engineFilePath);

		UciClient() = default;
		UciClient(const UciClient&) = default;
		UciClient(UciClient&&) noexcept = default;
		virtual ~UciClient() noexcept = default;
		UciClient& operator=(const UciClient&) = default;
		UciClient& operator=(UciClient&&) noexcept = default;

		void launch(const std::string & engine_file_path);

		void close();

		// Messages which the client (engine) can send to the server (gui)
		void send_uci();
		void send_debug(const Debug& debug);
		void send_isready();
		void send_setoption() {}	// TODO: remove this overload
		//void send_setoption(const std::string opName, int id, const std::string& value);
		//void send_setoption(const Option& op);
		//void send_register(...);
		void send_ucinewgame();
		//template<typename CONTAINER_T>
		//void send_position(const std::string fen, const CONTAINER_T& moves_begin, const CONTAINER_T& moves_end);
		void send_position();
		// fen - fen representation of position (can be 'startpos')
		void send_position(const std::string fen);
		void send_position(const std::string fen, const std::vector<std::string>& moveSequence);
		void send_go(const go & go_params);
		void send_stop();
		void send_ponderhit();
		void send_quit();

		// Waits until a specific command is received from client (engine) before returning.
		// Received command must be valid. Method will continue to block until a valid command is received
		// and matches `cmd_to_wait_for`.
		// Blocking call. 
		const Command & recv(const std::string& cmd_to_wait_for);
		const Command & recv_id();
		const Command & recv_uciok();
		const Command & recv_readyok();
		const Command & recv_bestmove();
		const Command & recv_copyprotection();
		const Command & recv_registration();
		const Command & recv_info();
		const Command & recv_option();

		//void handle(std::string & message);
		//void on_id();
		//void on_uciok();
		//void on_readyok();
		//void on_bestmove();
		//void on_copyprotection();
		//void on_register();
		//void on_info();
		//void on_option(); 

	protected:
		boost::process::child engine;
	
		boost::process::ipstream is;
		boost::process::opstream os;
		
		//std::function<void()> on_id_callback;
		//std::function<void()> on_uciok_callback;
		//std::function<void()> on_readyok_callback;
		//std::function<void()> on_bestmove_callback;
		//std::function<void()> on_copyprotection_callback;
		//std::function<void()> on_register_callback;
		//std::function<void()> on_info_callback;
		//std::function<void()> on_option_callback;

		std::string name;
		std::string author;
		std::string bestmove;

		// list of options that the engine supports.
		// This list comes from the option commands that the engine sends after 
		// receiving 'uci'
		//option_list options;
	};
} // namespace uci