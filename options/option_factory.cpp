#include "option_factory.h"

using namespace std;

namespace uci
{
	//option option_factory::generate(const Command& cmd)
	//{
	//	option op;
	//
	//	// --- 1.) Determine type of command (1st token) ---
	//	const string & c = cmd.cmd();
	//
	//	if (c == "setoption") {
	//		if (cmd.at(1) == "name") {
	//			const string& id = cmd.at(2);
	//
	//			if (id == "Hash") {
	//			//	op = hash_option();
	//			}
	//			else if (id == "NalimovPath") {
	//
	//			}
	//			else if (id == "NalimovCache") {
	//
	//			}
	//			else if (id == "Ponder") {
	//
	//			}
	//			else if (id == "OwnBook") {
	//
	//			}
	//			else if (id == "MultiPV") {
	//
	//			}
	//			else if (id == "UCI_ShowCurrLine") {
	//
	//			}
	//			else if (id == "UCI_ShowRefutations") {
	//
	//			}
	//			else if (id == "UCI_LimitStrength") {
	//
	//			}
	//			else if (id == "UCI_Elo") {
	//
	//			}
	//			else if (id == "UCI_AnalyseMode") {
	//
	//			}
	//			else if (id == "UCI_Opponent") {
	//
	//			}
	//			else if (id == "UCI_EngineAbout") {
	//
	//			}
	//			else if (id == "UCI_ShredderbasesPath") {
	//
	//			}
	//			else if (id == "UCI_SetPositionValue") {
	//
	//			}
	//		} // if (cmd.at(1) == "name") 
	//	}
	//	else if (c == "option") {
	//
	//	}
	//	else {
	//		cout << "Command is not option or setoption: " << cmd << endl;
	//	}
	//
	//	return op;
	//}
} // namespace uci