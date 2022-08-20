#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <list>
#include <optional>
#include <memory>
#include <vector>
#include <cassert>
#include <typeinfo>

///namespace uci
///{
///	namespace options
///	{
///		class base
///		{
///		public:
///			virtual std::string to_string() const = 0;
///			
///			virtual void fill_from(const Command & cmd) = 0;
///		public:
///		};
///
///		// ------------------------- OPTION TYPES ------------------------------------
///
///		class check : public base
///		{
///		public:
///			virtual void fill_from(const Command & cmd) override;
///
///			friend std::ostream& operator<<(std::ostream& os, const check& op)
///			{
///				os << "type check";
///
///				if (op.default_val)
///					os << " default " << (op.default_val.value() ? "true" : "false");
///
///				if (op.var)
///					os << " var " << (op.var.value() ? "true" : "false");
///
///				return os;
///			}
///
///			std::optional<bool> default_val;
///			std::optional<bool> var;
///		};
///
///		class spin : public base
///		{
///		public:
///			virtual void fill_from(const Command & cmd) override;
///			
///			friend std::ostream& operator<<(std::ostream& os, const spin& op)
///			{
///				os << "type spin";
///
///				if (op.default_val) {
///					os << " default " << op.default_val.value();
///				}
///
///				if (op.min) {
///					os << " min " << op.min.value();
///				}
///
///				if (op.max) {
///					os << " max " << op.max.value();
///				}
///
///				if (op.var) {
///					os << " var " << op.var.value();
///				}
///
///				return os;
///			}
///
///			std::optional<int> default_val;
///			std::optional<int> min;
///			std::optional<int> max;
///			std::optional<int> var;
///		};
///
///		class combo : public base
///		{
///		public:
///			virtual void fill_from(const Command& cmd) override;
///		
///			friend std::ostream& operator<<(std::ostream& os, const combo& op)
///			{
///				os << "type combo";
///
///				if (op.default_val)
///					os << " default " << op.default_val.value();
///
///				if (op.vals) {
///					for (const std::string& val : op.vals.value()) {
///						os << " var " << val;
///					}
///				}
///
///				return os;
///			}
///
///			std::optional<std::string> default_val;
///			std::optional<std::list<std::string>> vals;
///		};
///
///		class button : public base
///		{
///		public:
///			virtual void fill_from(const Command& cmd) override;
///			
///			friend std::ostream& operator<<(std::ostream& os, const button& op)
///			{
///				os << "type button";
///
///				return os;
///			}
///		};
///
///		class string : public base
///		{
///		public:
///			virtual void fill_from(const Command& cmd) override;
///			
///			friend std::ostream& operator<<(std::ostream& os, const string& op)
///			{
///				os << "type string default";
///
///				if (op.default_val)
///					os << " " << op.default_val.value();
///
///				//// TODO: Not sure if this should exist
///				//if (op.var)
///				//	os << " var " << op.var.value();
///
///				return os;
///			}
///
///			std::optional<std::string> default_val;
///			//std::optional<std::string> var;
///		};
///
///		// ---------------------- OPTIONS (DERIVED TYPES) -------------------------
///
///		class hash : public spin
///		{
///		public:
///			virtual std::string to_string() const override
///			{
///				std::stringstream str;
///
///				str << *this;
///
///				return str.str();
///			}
///
///			friend std::ostream& operator<<(std::ostream& os, const hash& op)
///			{
///				os << "option name Hash "
///					<< static_cast<const spin&>(op);
///
///				return os;
///			}
///
///			std::optional<std::string> var;	// TODO: not sure if this should exist
///		};
///
///		class nalimov_path : public string
///		{
///		public:
///			virtual std::string to_string() const override
///			{
///				std::stringstream str;
///
///				str << *this;
///
///				return str.str();
///			}
///
///			friend std::ostream& operator<<(std::ostream& os, const nalimov_path& op)
///			{
///				os << "option name NalimovPath "
///					<< static_cast<const string&>(op);
///
///				return os;
///			}
///		};
///
///		class nalimov_cache : public spin
///		{
///		public:
///			virtual std::string to_string() const override
///			{
///				std::stringstream str;
///
///				str << *this;
///
///				return str.str();
///			}
///
///			friend std::ostream& operator<<(std::ostream& os, const nalimov_cache& op)
///			{
///				os << "option name NalimovCache "
///					<< static_cast<const spin&>(op);
///
///				return os;
///			}
///		};
///
///		class ponder : public check
///		{
///		public:
///			virtual std::string to_string() const override
///			{
///				std::stringstream str;
///
///				str << *this;
///
///				return str.str();
///			}
///
///			friend std::ostream& operator<<(std::ostream& os, const ponder& op)
///			{
///				os << "option name Ponder "
///					<< static_cast<const check&>(op);
///
///				return os;
///			}
///		};
///
///		class own_book : public check
///		{
///		public:
///			virtual std::string to_string() const override
///			{
///				std::stringstream str;
///
///				str << *this;
///
///				return str.str();
///			}
///
///			friend std::ostream& operator<<(std::ostream& os, const own_book& op)
///			{
///				os << "option name OwnBook "
///					<< static_cast<const check&>(op);
///
///				return os;
///			}
///		};
///
///		class multi_pv : public spin
///		{
///		public:
///			virtual std::string to_string() const override
///			{
///				std::stringstream str;
///
///				str << *this;
///
///				return str.str();
///			}
///
///			friend std::ostream& operator<<(std::ostream& os, const multi_pv& op)
///			{
///				os << "option name MultiPV "
///					<< static_cast<const spin&>(op);
///
///				return os;
///			}
///		};
///
///		class uci_show_curr_line : public check
///		{
///		public:
///			virtual std::string to_string() const override
///			{
///				std::stringstream str;
///
///				str << *this;
///
///				return str.str();
///			}
///
///			friend std::ostream& operator<<(std::ostream& os, const uci_show_curr_line& op)
///			{
///				os << "option name UCI_ShowCurrLine "
///					<< static_cast<const check&>(op);
///
///				return os;
///			}
///		};
///
///		// should be false by default,
///		class uci_show_refutations : public check
///		{
///		public:
///			virtual std::string to_string() const override
///			{
///				std::stringstream str;
///
///				str << *this;
///
///				return str.str();
///			}
///
///			friend std::ostream& operator<<(std::ostream& os, const uci_show_refutations& op)
///			{
///				os << "option name UCI_ShowRefutations "
///					<< static_cast<const check&>(op);
///
///				return os;
///			}
///		};
///
///		// should be false by default,
///		class uci_limit_strength : public check
///		{
///		public:
///			virtual std::string to_string() const override
///			{
///				std::stringstream str;
///
///				str << *this;
///
///				return str.str();
///			}
///
///			friend std::ostream& operator<<(std::ostream& os, const uci_limit_strength& op)
///			{
///				os << "option name UCI_LimitStrength "
///					<< static_cast<const check&>(op);
///
///				return os;
///			}
///		};
///
///		// should be false by default,
///		class uci_elo : public spin
///		{
///		public:
///			virtual std::string to_string() const override
///			{
///				std::stringstream str;
///
///				str << *this;
///
///				return str.str();
///			}
///
///			friend std::ostream& operator<<(std::ostream& os, const uci_elo& op)
///			{
///				os << "option name UCI_Elo "
///					<< static_cast<const spin&>(op);
///
///				return os;
///			}
///		};
///
///		class uci_analyse_mode : public check
///		{
///		public:
///			virtual std::string to_string() const override
///			{
///				std::stringstream str;
///
///				str << *this;
///
///				return str.str();
///			}
///
///			friend std::ostream& operator<<(std::ostream& os, const uci_analyse_mode& op)
///			{
///				os << "option name UCI_AnalyseMode "
///					<< static_cast<const check&>(op);
///
///				return os;
///			}
///		};
///
///		class uci_opponent : public string
///		{
///		public:
///			virtual std::string to_string() const override
///			{
///				std::stringstream str;
///
///				str << *this;
///
///				return str.str();
///			}
///
///			friend std::ostream& operator<<(std::ostream& os, const uci_opponent& op)
///			{
///				os << "option name UCI_Opponent "
///					<< static_cast<const string&>(op);
///
///				return os;
///			}
///		};
///
///		class uci_engine_about : public string
///		{
///		public:
///			virtual std::string to_string() const override
///			{
///				std::stringstream str;
///
///				str << *this;
///
///				return str.str();
///			}
///
///			friend std::ostream& operator<<(std::ostream& os, const uci_engine_about& op)
///			{
///				os << "option name UCI_EngineAbout "
///					<< static_cast<const string&>(op);
///
///				return os;
///			}
///		};
///
///		class uci_shredder_bases_path : public string
///		{
///		public:
///			virtual std::string to_string() const override
///			{
///				std::stringstream str;
///
///				str << *this;
///
///				return str.str();
///			}
///
///			friend std::ostream& operator<<(std::ostream& os, const uci_shredder_bases_path& op)
///			{
///				os << "option name UCI_ShredderbasesPath "
///					<< static_cast<const string&>(op);
///
///				return os;
///			}
///		};
///
///		class uci_set_position_value : public string
///		{
///		public:
///			virtual std::string to_string() const override
///			{
///				std::stringstream str;
///
///				str << *this;
///
///				return str.str();
///			}
///
///			friend std::ostream& operator<<(std::ostream& os, const uci_set_position_value& op)
///			{
///				os << "option name UCI_SetPositionValue "
///					<< static_cast<const string&>(op);
///
///				return os;
///			}
///		};
///
///
///	} // namespace options
///} // namespace uci
