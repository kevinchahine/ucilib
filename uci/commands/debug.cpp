#include "debug.h"

#include "helpers.h"

using namespace std;

namespace uci
{
	namespace commands
	{
		void debug::parse(const std::string& line)
		{
			// --- 0.) Clear existing tokesn and puse currline into a stream ---
			istringstream is(line);

			// --- 1.) parse command ---
			string cmd;
			string value;

			is >> cmd >> value;

			// --- 2.) assign value ---
			this->is_on = to_bool(value);
		}
	} // namespace commands
} // namespace uci
