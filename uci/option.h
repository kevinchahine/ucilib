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
		std::optional<std::string> var;
	};

	// ---------------------- OPTIONS --------------------------------------------

	class hash_option : public spin_option
	{
	public:
		friend std::ostream& operator<<(std::ostream& os, const hash_option& op)
		{
			os << "option name Hash value "
				<< static_cast<const spin_option&>(op);

			return os;
		}

		std::optional<std::string> var;	// TODO: not sure if this should exist
	};

	class nalimov_path_option : public spin_option
	{
	public:
		friend std::ostream& operator<<(std::ostream& os, const nalimov_path_option& op)
		{
			os << "option name NalimovPath "
				<< static_cast<const spin_option&>(op);

			return os;
		}
	};

	class nalimov_cache_option : public spin_option
	{
	public:
		friend std::ostream& operator<<(std::ostream& os, const nalimov_cache_option& op)
		{
			os << "option name NalimovCache "
				<< static_cast<const spin_option&>(op);

			return os;
		}
	};

	class ponder_option : public check_option
	{
	public:
		friend std::ostream& operator<<(std::ostream& os, const ponder_option& op)
		{
			os << "option name Ponder "
				<< static_cast<const check_option&>(op);

			return os;
		}
	};

	class own_book_option : public check_option
	{
	public:
		friend std::ostream& operator<<(std::ostream& os, const own_book_option& op)
		{
			os << "option name OwnBook "
				<< static_cast<const check_option&>(op);

			return os;
		}
	};

	class multi_pv_option : public spin_option
	{
	public:
		friend std::ostream& operator<<(std::ostream& os, const multi_pv_option& op)
		{
			os << "option name MultiPV "
				<< static_cast<const spin_option&>(op);

			return os;
		}
	};

	class uci_show_curr_line_option : public check_option
	{
	public:
		friend std::ostream& operator<<(std::ostream& os, const uci_show_curr_line_option& op)
		{
			os << "option name UCI_ShowCurrLine "
				<< static_cast<const check_option&>(op);

			return os;
		}
	};

	// should be false by default,
	class uci_show_refutations_option : public check_option
	{
	public:
		friend std::ostream& operator<<(std::ostream& os, const uci_show_refutations_option& op)
		{
			os << "option name UCI_ShowRefutations "
				<< static_cast<const check_option&>(op);

			return os;
		}
	};

	// should be false by default,
	class uci_limit_strength_option : public check_option
	{
	public:
		friend std::ostream& operator<<(std::ostream& os, const uci_limit_strength_option& op)
		{
			os << "option name UCI_LimitStrength "
				<< static_cast<const check_option&>(op);

			return os;
		}
	};

	// should be false by default,
	class uci_elo_option : public spin_option
	{
	public:
		friend std::ostream& operator<<(std::ostream& os, const uci_elo_option& op)
		{
			os << "option name UCI_Elo "
				<< static_cast<const spin_option&>(op);

			return os;
		}
	};

	class uci_analyse_mode_option : public check_option
	{
	public:
		friend std::ostream& operator<<(std::ostream& os, const uci_analyse_mode_option& op)
		{
			os << "option name UCI_AnalyseMode "
				<< static_cast<const check_option&>(op);

			return os;
		}
	};

	class uci_opponent_option : public string_option
	{
	public:
		friend std::ostream& operator<<(std::ostream& os, const uci_opponent_option& op)
		{
			os << "option name UCI_Opponent "
				<< static_cast<const string_option&>(op);

			return os;
		}
	};

	class uci_engine_about_option : public string_option
	{
	public:
		friend std::ostream& operator<<(std::ostream& os, const uci_engine_about_option& op)
		{
			os << "option name UCI_EngineAbout "
				<< static_cast<const string_option&>(op);

			return os;
		}
	};

	class uci_shredder_bases_path_option : public string_option
	{
	public:
		friend std::ostream& operator<<(std::ostream& os, const uci_shredder_bases_path_option& op)
		{
			os << "option name UCI_ShredderbasesPath "
				<< static_cast<const string_option&>(op);

			return os;
		}
	};

	class uci_set_position_value_option : public string_option
	{
	public:
		friend std::ostream& operator<<(std::ostream& os, const uci_set_position_value_option& op)
		{
			os << "option name UCI_SetPositionValue "
				<< static_cast<const string_option&>(op);

			return os;
		}
	};
} // namespace uci
