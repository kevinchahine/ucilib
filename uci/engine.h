#pragma once

#include "uci/go.h"
#include "uci/options/option.h"
#include "uci/options/list.h"
#include "uci/base.h"
#include "uci/debug.h"

#include <boost/process/child.hpp>
#include <boost/process/pipe.hpp>

#include <boost/asio/streambuf.hpp>

namespace uci
{
	// TODO: Why not simply call this 'Client' (no Uci)
	class engine : public base
	{
	public:
		engine(const boost::filesystem::path& engine_file_path);

		engine() = default;
		engine(const engine&) = default;
		engine(engine&&) noexcept = default;
		virtual ~engine() noexcept = default;
		engine& operator=(const engine&) = default;
		engine& operator=(engine&&) noexcept = default;

		void launch(const boost::filesystem::path& engine_file_path);

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
		void send_position();
		// fen - fen representation of position (can be 'startpos')
		void send_position(const std::string fen);
		// fen - fen representation of position (can be 'startpos')
		void send_position(const std::string fen, const std::vector<std::string>& moveSequence);
		void send_go(const go & go_params);
		void send_stop();
		void send_ponderhit();
		void send_quit();

		// Waits until a specific command is received from client (engine) before returning.
		// Received command must be valid. Method will continue to block until a valid command is received
		// and matches `cmd_to_wait_for`.
		// Blocking call. 
		const Command & recv_until(const std::string& cmd_to_wait_for);
		const Command & recv_until_id();
		const Command & recv_until_uciok();
		const Command & recv_until_readyok();
		const Command & recv_until_bestmove();
		const Command & recv_until_copyprotection();
		const Command & recv_until_registration();
		const Command & recv_until_info();
		const Command & recv_until_option();

		//void handle(std::string & message);
		void on_any_command(const Command& cmd);
		void on_id(const Command & cmd);
		void on_uciok(const Command & cmd);
		void on_readyok(const Command & cmd);
		void on_bestmove(const Command & cmd);
		void on_copyprotection(const Command & cmd);
		void on_register(const Command & cmd);
		void on_info(const Command & cmd);
		void on_option(const Command & cmd); 

		// ------------------ ACCESSORS ---------------------------------------

		const std::string engine_name() const { return name; }
		const std::string engine_author() const { return author; }
		const std::string best_move() const { return bestmove; }
		
	protected:
		boost::process::child engine_process;
	
		boost::process::ipstream is;
		boost::process::opstream os;
		boost::asio::streambuf sbuf;	// for holding input data

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
		uci::options::list options;
	};
} // namespace uci