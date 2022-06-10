#pragma once

#include "uci_base.h"

namespace uci
{
	// TODO: Why not call this Client (no Uci)
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

		// TODO: Change return to some error type
		// TODO: Make data type boost::filesystem::path
		void launch(const std::string& engineFilePath);

		void close();

		// Messages which the client (engine) can send to the server (gui)
		void send_uci();
		void send_debug(const Debug& debug);
		void send_isready();
		//void send_setoption(const std::string opName, int id, const std::string& value);
		//void send_setoption(const Option& op);
		//void send_register(...);
		void send_ucinewgame();
		void send_position(const std::string fen);
		//template<typename CONTAINER_T>
		//void send_position(const std::string fen, const CONTAINER_T& moves_begin, const CONTAINER_T& moves_end);
		//void send_position(const std::string fen, const std::vector<forge::Move>& moveSequence);
		//void send_go(const GoParams& goParams);
		void send_stop();
		void send_ponderhit();
		void send_quit();

		void handle(std::string & message);
		void on_id(const std::string & key, const std::string & value);
		void on_uciok();
		void on_readyok();
		void on_bestmove();
		void on_copyprotection();
		void on_register();
		void on_info();
		void on_option(); 

	protected:
		std::function<void()> on_id_callback;
		std::function<void()> on_uciok_callback;
		std::function<void()> on_readyok_callback;
		std::function<void()> on_bestmove_callback;
		std::function<void()> on_copyprotection_callback;
		std::function<void()> on_register_callback;
		std::function<void()> on_info_callback;
		std::function<void()> on_option_callback;

		//boost::process::child engine;

		std::string name;
		std::string author;
	};
} // namespace uci