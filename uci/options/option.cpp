#include "../options/option.h"

#include "../commands/command.h"

using namespace std;

namespace uci
{
	namespace options
	{
		void check::fill_from(const Command& cmd)
		{
			this->default_val.reset();

			for (size_t token_index = 5; token_index + 1 < cmd.size(); token_index += 2) {
				const std::string& attrib_type = cmd.at(token_index);
				const std::string& attrib_value = cmd.at(token_index + 1);

				if (attrib_type == "default") {
					if (attrib_value == "true") {
						this->default_val = true;
					}
					else if (attrib_value == "false") {
						this->default_val = false;
					}
					else {
						cout << "Command is corrupt: " << cmd << endl
							<< "\tDefault must be either true or false: " << endl;
					}
				}
			}
		}

		void spin::fill_from(const Command& cmd)
		{
			this->default_val.reset();
			this->min.reset();
			this->max.reset();
			this->var.reset();

			for (size_t token_index = 5; token_index + 1 < cmd.size(); token_index += 2) {
				const std::string& attrib_type = cmd.at(token_index);
				const std::string& attrib_value = cmd.at(token_index + 1);

				if (attrib_type == "default") {
					this->default_val = stoi(attrib_value);
				}
				else if (attrib_type == "min") {
					this->min = stoi(attrib_value);
				}
				else if (attrib_type == "max") {
					this->max = stoi(attrib_value);
				}
				else if (attrib_type == "var") {
					this->var = stoi(attrib_value);
				}
			}
		}

		void combo::fill_from(const Command& cmd)
		{
			this->default_val.reset();
			this->vals.reset();

			for (size_t token_index = 5; token_index + 1 < cmd.size(); token_index += 2) {
				const std::string& attrib_type = cmd.at(token_index);
				const std::string& attrib_value = cmd.at(token_index + 1);

				if (attrib_type == "default") {
					this->default_val = attrib_value;
				}
				else if (attrib_type == "var") {
					if (this->vals.has_value() == false) {
						this->vals = std::list<std::string>();
					}

					this->vals->push_back(attrib_value);
				}
			}
		}

		void button::fill_from(const Command& cmd)
		{
			// Nothing to do here
		}

		void string::fill_from(const Command& cmd)
		{
			this->default_val.reset();

			const std::string& attrib_type = cmd.at(5);
			const std::string& attrib_value = cmd.at(6);

			if (attrib_type == "default") {
				this->default_val = attrib_value;
			}
		}

        option::option(const Command& cmd)
        {
			this->fill_from(cmd);
        }

        void option::fill_from(const Command& cmd)
		{
			if (cmd.is_option() == false) {
				cout << "error: " << cmd << " is not an option command" << endl;
				return;
			}

			if (cmd.size() < 5) {
				cout << "error: " << cmd << " must be atleast 5 tokens long to be an option" << endl;
				return;
			}

			if (cmd.at(1) != "name") {
				cout << "error: 2nd token must be \'name\'" << endl;
				return;
			}

			if (cmd.at(3) != "type") {
				cout << "error: 4th token must be \'type\'" << endl;
				return;
			}

			const std::string& op_name = cmd.at(2);
			const std::string& op_type = cmd.at(4);

			if (false) { /* placeholder */ }
			else if (op_name == "Hash") { (*this) = options::hash(); }
			else if (op_name == "NalimovPath") { (*this) = options::nalimov_path(); }
			else if (op_name == "NalimovCache") { (*this) = options::nalimov_cache(); }
			else if (op_name == "Ponder") { (*this) = options::ponder(); }
			else if (op_name == "OwnBook") { (*this) = options::own_book(); }
			else if (op_name == "MultiPV") { (*this) = options::multi_pv(); }
			else if (op_name == "UCI_ShowCurrLine") { (*this) = options::uci_show_curr_line(); }
			else if (op_name == "UCI_ShowRefutations") { (*this) = options::uci_show_refutations(); }
			else if (op_name == "UCI_LimitStrength") { (*this) = options::uci_limit_strength(); }
			else if (op_name == "UCI_Elo") { (*this) = options::uci_elo(); }
			else if (op_name == "UCI_AnalyseMode") { (*this) = options::uci_analyse_mode(); }
			else if (op_name == "UCI_Opponent") { (*this) = options::uci_opponent(); }
			else if (op_name == "UCI_EngineAbout") { (*this) = options::uci_engine_about(); }
			else if (op_name == "UCI_ShredderbasesPath") { (*this) = options::uci_shredder_bases_path(); }
			else if (op_name == "UCI_SetPositionValue") { (*this) = options::uci_set_position_value(); }
			else {
				cout << "Unknown option " << op_name << endl;
				return;
			}

			// *** The previous conditionals have set *this to a type of option cooresponding to the command ***
			// *** Now *this can parse the command and extract its data as it needs ***

			this->ptr->fill_from(cmd);
		}
	} // namespace options
} // namespace uci
