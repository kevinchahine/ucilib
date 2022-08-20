#pragma once

#include "uci/base.h"
#include "uci/commands/commands.hpp"

#include <boost/process/child.hpp>
#include <boost/process/pipe.hpp>

namespace uci
{
	class engine : public base
	{
	public:
		engine() = default;
		engine(const engine&) = default;
		engine(engine&&) noexcept = default;
		engine(const boost::filesystem::path& engine_file_path);
		virtual ~engine() noexcept = default;
		engine& operator=(const engine&) = default;
		engine& operator=(engine&&) noexcept = default;
	
		void launch(const boost::filesystem::path& engine_file_path);
	
		void close();
	
		// Messages which the client (engine) can send to the server (gui)
		template<class COMMAND_T> void send(const COMMAND_T& obj) { os << obj << endl; }
		void send_uci();
		void send_debug(const commands::debug & obj);
		void send_isready();
		void send_setoption(const commands::setoption& obj);
		void send_register(const commands::register_cmd& obj);
		void send_ucinewgame();
		void send_position(const commands::position& obj = commands::position{});
		void send_go(const commands::go & obj);
		void send_stop();
		void send_ponderhit();
		void send_quit();
	
		// Waits until a specific command is received from client (engine) before returning.
		// Received command must be valid. Method will continue to block until a valid command is received
		// and matches `cmd_to_wait_for`.
		// Blocking call. 
		const commands::command & recv_until(const commands::command & cmd);
		const commands::id & recv_until_id();
		const commands::uciok & recv_until_uciok();
		const commands::readyok & recv_until_readyok();
		const commands::bestmove & recv_until_bestmove();
		const commands::copyprotection & recv_until_copyprotection();
		const commands::registration & recv_until_registration();
		const commands::info & recv_until_info();
		const commands::option & recv_until_option();
	
		// ------------------ ACCESSORS ---------------------------------------
	
		const std::string engine_name() const { return name; }
		const std::string engine_author() const { return author; }
		const std::string best_move() const { return bestmove; }
		
	protected:
		boost::process::child engine_process;
	
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
		////uci::options::list options;
	};
} // namespace uci