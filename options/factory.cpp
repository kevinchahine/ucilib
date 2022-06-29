#include "uci/options/factory.h"

#include <functional>

using namespace std;

namespace uci
{
	namespace options
	{
		auto string_to_bool = [](const std::string& str)
		{
			if (str == "true") {
				return true;
			}
			else if (str == "false") {
				return false;
			}
			else {
				cout << "invalid attribute";
				return false;
			}
		};

		option factory::generate(const Command& cmd)
		{
			option op;

			// --- 1.) Determine type of command (1st token) ---
			if (cmd.is_option()) {
				op.fill_from(cmd);
			}
			else if (cmd.is_setoption()) {
				if (cmd.size() >= 5 && cmd.at(1) == "name" && cmd.at(3) == "value") {
					const std::string& id = cmd.at(2);
					const std::string& val = cmd.at(4);
					if (id == "Hash") {
						op = options::hash();

						options::hash& h = op.as<options::hash>();

						h.var = val;
					}
					else if (id == "NalimovPath") {

					}
					else if (id == "NalimovCache") {

					}
					else if (id == "Ponder") {

					}
					else if (id == "OwnBook") {

					}
					else if (id == "MultiPV") {

					}
					else if (id == "UCI_ShowCurrLine") {

					}
					else if (id == "UCI_ShowRefutations") {

					}
					else if (id == "UCI_LimitStrength") {

					}
					else if (id == "UCI_Elo") {

					}
					else if (id == "UCI_AnalyseMode") {

					}
					else if (id == "UCI_Opponent") {

					}
					else if (id == "UCI_EngineAbout") {

					}
					else if (id == "UCI_ShredderbasesPath") {

					}
					else if (id == "UCI_SetPositionValue") {

					}
				}
				else {
					cout << "something went wrong" << endl;
				}
			}
			else {
				cout << "Command is not option or setoption: " << cmd << endl;
			}

			return op;
		}
	} // namespace options
} // namespace uci