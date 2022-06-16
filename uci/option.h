#pragma once

#include <iostream>
#include <string>
#include <list>
#include <optional>

namespace uci
{
	// Stores data for the 'option' and 'setoption' commands
	class option
	{
	public:

		void setHash(int default_val, int min, int max, int var);

		friend std::ostream& operator<<(std::ostream& os, const option& op)
		{
			os << "name " << op.name << " value " << op.value;

			return os;
		}

		std::string to_string_command() const;

	private:
		std::string name;
		std::string value;
	};

	// ------------------------- OPTION TYPES ------------------------------------

	class check_option : public option
	{
	public:
		friend std::ostream& operator<<(std::ostream& os, const check_option& op)
		{
			os << "type check";

			if (op.default_val)
				os << " default " << op.default_val.value();

			if (op.var)
				os << " var " << op.var.value();

			return os;
		}

		std::optional<bool> default_val;
		std::optional<bool> var;
	};

	class spin_option : public option
	{
	public:
		friend std::ostream& operator<<(std::ostream& os, const spin_option& op)
		{
			os << "type spin";

			if (op.default_val) {
				os << " default " << op.default_val.value();
			}

			if (op.min) {
				os << " min " << op.min.value();
			}

			if (op.max) {
				os << " max " << op.max.value();
			}

			if (op.var) {
				os << " var " << op.var.value();
			}

			return os;
		}

		std::optional<int> default_val;
		std::optional<int> min;
		std::optional<int> max;
		std::optional<int> var;
	};

	class combo_option : public option
	{
	public:
		friend std::ostream& operator<<(std::ostream& os, const combo_option& op)
		{
			os << "type combo";

			if (op.default_val)
				os << " default " << op.default_val.value();

			if (op.vals) {
				for (const std::string& val : op.vals.value()) {
					os << " var " << val;
				}
			}

			return os;
		}

		std::optional<std::string> default_val;
		std::optional<std::list<std::string>> vals;
	};

	class button_option : public option
	{
	public:
		friend std::ostream& operator<<(std::ostream& os, const button_option& op)
		{
			os << "type button";

			return os;
		}
	};

	class string_option : public option
	{
	public:
		friend std::ostream& operator<<(std::ostream& os, const string_option& op)
		{
			os << "type string";

			if (op.default_val)
				os << " default " << op.default_val.value();

			// TODO: Not sure if this should exist
			if (op.var)
				os << " var " << op.var.value();

			return os;
		}

		std::optional<std::string> default_val;
		std::optional<std::string> var;	// TODO: not sure if this should exist
	};

	// ---------------------- OPTIONS --------------------------------------------

	class hash_option : public spin_option
	{
	public:
		friend std::ostream& operator<<(std::ostream& os, const hash_option& op)
		{
			os << "option name Hash "
				<< static_cast<const spin_option&>(op);

			return os;
		}
	};

	class nalimov_path_option : public spin_option
	{
	public:
		friend std::ostream& operator<<(std::ostream& os, const nalimov_path_option& op)
		{
			os << "option name NalimovPath "
				<< static_cast<const nalimov_path_option&>(op);

			return os;
		}
	};

	// TODO: fix case
	class NalimovCache_option : public spin_option
	{
	public:
		friend std::ostream& operator<<(std::ostream& os, const NalimovCache_option& op)
		{
			os << "option name NalimovCache "
				<< static_cast<const spin_option&>(op);

			return os;
		}
	};

	class Ponder_option : public check_option
	{
	public:
		friend std::ostream& operator<<(std::ostream& os, const Ponder_option& op)
		{
			os << "option name Ponder "
				<< static_cast<const check_option&>(op);

			return os;
		}
	};

	class OwnBook_option : public check_option
	{
	public:
		friend std::ostream& operator<<(std::ostream& os, const OwnBook_option& op)
		{
			os << "option name OwnBook "
				<< static_cast<const check_option&>(op);

			return os;
		}
	};

	class MultiPV_option : public spin_option
	{
	public:
		friend std::ostream& operator<<(std::ostream& os, const MultiPV_option& op)
		{
			os << "option name MultiPV "
				<< static_cast<const spin_option&>(op);

			return os;
		}
	};

	class UCI_ShowCurrLine_option : public check_option
	{
	public:
		friend std::ostream& operator<<(std::ostream& os, const UCI_ShowCurrLine_option& op)
		{
			os << "option name UCI_ShowCurrLine "
				<< static_cast<const check_option&>(op);

			return os;
		}
	};

	// should be false by default,
	class UCI_ShowRefutations_option : public check_option
	{
	public:
		friend std::ostream& operator<<(std::ostream& os, const UCI_ShowRefutations_option& op)
		{
			os << "option name UCI_ShowRefutations "
				<< static_cast<const check_option&>(op);

			return os;
		}
	};

	// should be false by default,
	class UCI_LimitStrength_option : public check_option
	{
	public:
		friend std::ostream& operator<<(std::ostream& os, const UCI_LimitStrength_option& op)
		{
			os << "option name UCI_LimitStrength "
				<< static_cast<const check_option&>(op);

			return os;
		}
	};

	// should be false by default,
	class UCI_Elo_option : public spin_option
	{
	public:
		friend std::ostream& operator<<(std::ostream& os, const UCI_Elo_option& op)
		{
			os << "option name UCI_Elo "
				<< static_cast<const spin_option&>(op);

			return os;
		}
	};

	class UCI_AnalyseMode_option : public check_option
	{
	public:
		friend std::ostream& operator<<(std::ostream& os, const UCI_AnalyseMode_option& op)
		{
			os << "option name UCI_AnalyseMode "
				<< static_cast<const check_option&>(op);

			return os;
		}
	};

	class UCI_Opponent_option : public string_option
	{
	public:
		friend std::ostream& operator<<(std::ostream& os, const UCI_Opponent_option& op)
		{
			os << "option name UCI_Opponent "
				<< static_cast<const string_option&>(op);

			return os;
		}
	};

	class UCI_EngineAbout_option : public string_option
	{
	public:
		friend std::ostream& operator<<(std::ostream& os, const UCI_EngineAbout_option& op)
		{
			os << "option name UCI_EngineAbout "
				<< static_cast<const string_option&>(op);

			return os;
		}
	};

	class UCI_ShredderbasesPath_option : public string_option
	{
	public:
		friend std::ostream& operator<<(std::ostream& os, const UCI_ShredderbasesPath_option& op)
		{
			os << "option name UCI_ShredderbasesPath "
				<< static_cast<const string_option&>(op);

			return os;
		}
	};

	class UCI_SetPositionValue_option : public string_option
	{
	public:
		friend std::ostream& operator<<(std::ostream& os, const UCI_SetPositionValue_option& op)
		{
			os << "option name UCI_SetPositionValue "
				<< static_cast<const string_option&>(op);

			return os;
		}
	};


} // namespace uci

/*
option
	* name <id>

	* type <t>
		* check		a checkbox that can either be true or false
		* spin		a spin wheel that can be an integer in a certain range
		* combo		a combo box that can have different predefined strings as a value
		* button	a button that can be pressed to send a command to the engine
		* string	a text field that has a string as a value,	an empty string has the value "<empty>"
	* default <x>	used for: all (check, spin, combo, button, string)
	* min <x>		used for: spin
	* max <x>		used for: spin
	* var <x>		used for: combo,
	Examples:
	Here are 5 strings for each of the 5 possible types of options
		"option name Nullmove type check default true\n"
		"option name Selectivity type spin default 2 min 0 max 4\n"
		"option name Style type combo default Normal var Solid var Normal var Risky\n"
		"option name NalimovPath type string default c:\\n"
		"option name Clear Hash type button\n"
*/