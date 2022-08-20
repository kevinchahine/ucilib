#include "engine.h"

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>	

#include <boost/process.hpp>

#include <numeric>		// for accumulate

using namespace std;

namespace uci
{
	engine::engine(const boost::filesystem::path& engine_file_path)
	{
		launch(engine_file_path);
	}
	
	void engine::launch(const boost::filesystem::path& engine_file_path)
	{
		// --- 1.) Make sure engine application exists ---
		const boost::filesystem::path & path = engine_file_path;
	
		if (path.is_absolute()) {
		}
		else {
			// app can be in:
			//	- current currectory
			//	- under system path
			if (boost::filesystem::exists(path)) {
			}
			else {
				// Check under system path
				// boost::filesystem::path::find
				// TODO: Do this
			}
		}
	
		if (boost::filesystem::exists(path) == false) {
			cout << "Engine is not found or does not exist" << endl;
	
			return;
		}
	
		// --- 2.) Open engine ---
		engine_process = boost::process::child{
			engine_file_path,
			boost::process::std_out > is,
			boost::process::std_in < os
		};
	
		//std::string currline;
		//
		//while (is && std::getline(is, currline) && !currline.empty()) {
		//	std::cerr << "\'" << currline << "\'" << std::endl;
		//}
		//
		//cout << "done" << endl;
	
		boost::filesystem::path filename = path.filename();
		if (filename.has_extension()) {
			filename = filename.leaf();
		}
	
		name = filename.string();	// TODO: strip filename extension if it exists
	}
	
	void engine::close()
	{
		// TODO: This might hang
		//engine.wait();
	}

	// ----------------------------------- SEND METHODS --------------------------

	void engine::send_uci()
	{
		send(commands::uci{});
	}
	
	void engine::send_debug(const commands::debug& obj)
	{
		send(obj);
	}
	
	void engine::send_isready()
	{
		send(commands::isready{});
	}
	
	void engine::send_setoption(const commands::setoption& obj)
	{
		send(obj);
	}
	
	void engine::send_register(const commands::register_cmd& obj)
	{
		send(obj);
	}

	void engine::send_ucinewgame()
	{
		send(commands::ucinewgame{});
	}
	
	void engine::send_position(const commands::position& obj)
	{
		send(obj);
	}
	
	void engine::send_go(const commands::go& obj)
	{
		send(obj);
	}
	
	void engine::send_stop()
	{
		send(commands::stop{});
	}
	
	void engine::send_ponderhit()
	{
		send(commands::ponderhit{});
	}
	
	void engine::send_quit()
	{
		send(commands::quit{});
	}
	
	// ----------------------------------- RECV UNTILS ------------------------
	
	const commands::command & engine::recv_until(const commands::command& cmd)
	{
		while (true) {
			// Reads next currline from input stream. 
			// Blocking call. Blocks until entire currline is read.
			// If currline is a valid command, it will be appended to back of `commands_in`
			// Invalid commands will be deleted and method will return
			this->parse_line(is);
	
			if (commands_in.size()) {
				const commands::command& curr_command = commands_in.back();
				
				if (curr_command.is_valid()) {
					if (curr_command.is_same_as(cmd)) {
						break;
					}
				}
			}
		}
	
		return commands_in.back();
	}
	
	const commands::id & engine::recv_until_id() 
	{
		return recv_until(commands::id{}).as<commands::id>();
	}
	
	const commands::uciok & engine::recv_until_uciok() 
	{
		return recv_until(commands::uciok{}).as<commands::uciok>();
	}
	
	const commands::readyok & engine::recv_until_readyok()
	{
		return recv_until(commands::readyok{}).as<commands::readyok>();
	}
	
	const commands::bestmove & engine::recv_until_bestmove()
	{
		return recv_until(commands::bestmove{}).as<commands::bestmove>();
	}
	
	const commands::copyprotection & engine::recv_until_copyprotection() 
	{
		return recv_until(commands::copyprotection{}).as<commands::copyprotection>();
	}
	
	const commands::registration& engine::recv_until_registration()
	{
		return recv_until(commands::registration{}).as<commands::registration>();
	}
	
	const commands::info & engine::recv_until_info() 
	{
		return recv_until(commands::info{}).as<commands::info>();
	}
	
	const commands::option & engine::recv_until_option()
	{
		return recv_until(commands::option{}).as<commands::option>();
	}
} // namespace uci
