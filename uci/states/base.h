#pragma once

#include <iostream>

namespace uci
{
	namespace states
	{
		class Base
		{
		public:
			enum class States
			{
				// Name			// From Server								From Client
				Init,			// Spawn child process						Reads pipe from serverand determines uci mode
				StartUp,		// Listen for "id name" and "id author"		Send "id name" and "id author"
								// for which options are supported			Send which options are supported
				Options,		// Set engine options						Listen for options
				Wait,			// Wait for engine to finish initializing	Initialize parameters
				NewGame,		// Create a new game						Reset game data and start a new game
				NewPosition,	// Set the new position						Reset old positionand set to new one
				Search,			// Wait for engine to search a position		Search a position
				Info,			// for info messages						Send info messages periodically
								// Tell engine to stop search if necessary	Listen for stop command
				Commit,			// Get best move from engine				Send best move to engine
			};

			virtual void init(const std::string& engine_exe) = 0;
			
			virtual Base::States update() = 0;
			
			virtual void terminate() = 0;

		protected:

		};
	} // namespace states
} // namespace uci