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

namespace uci
{
	// --- forward declarations ---
	class Command;

	namespace options
	{
		class base
		{
		public:
			virtual std::string to_string() const = 0;
			
			virtual void fill_from(const Command & cmd) = 0;
		public:
		};

		// ------------------------- OPTION TYPES ------------------------------------

		class check : public base
		{
		public:
			virtual void fill_from(const Command & cmd) override;

			friend std::ostream& operator<<(std::ostream& os, const check& op)
			{
				os << "type check";

				if (op.default_val)
					os << " default " << (op.default_val.value() ? "true" : "false");

				if (op.var)
					os << " var " << (op.var.value() ? "true" : "false");

				return os;
			}

			std::optional<bool> default_val;
			std::optional<bool> var;
		};

		class spin : public base
		{
		public:
			virtual void fill_from(const Command & cmd) override;
			
			friend std::ostream& operator<<(std::ostream& os, const spin& op)
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

		class combo : public base
		{
		public:
			virtual void fill_from(const Command& cmd) override;
		
			friend std::ostream& operator<<(std::ostream& os, const combo& op)
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

		class button : public base
		{
		public:
			virtual void fill_from(const Command& cmd) override;
			
			friend std::ostream& operator<<(std::ostream& os, const button& op)
			{
				os << "type button";

				return os;
			}
		};

		class string : public base
		{
		public:
			virtual void fill_from(const Command& cmd) override;
			
			friend std::ostream& operator<<(std::ostream& os, const string& op)
			{
				os << "type string default";

				if (op.default_val)
					os << " " << op.default_val.value();

				//// TODO: Not sure if this should exist
				//if (op.var)
				//	os << " var " << op.var.value();

				return os;
			}

			std::optional<std::string> default_val;
			//std::optional<std::string> var;
		};

		// ---------------------- OPTIONS (DERIVED TYPES) -------------------------

		class hash : public spin
		{
		public:
			virtual std::string to_string() const override
			{
				std::stringstream str;

				str << *this;

				return str.str();
			}

			friend std::ostream& operator<<(std::ostream& os, const hash& op)
			{
				os << "option name Hash "
					<< static_cast<const spin&>(op);

				return os;
			}

			std::optional<std::string> var;	// TODO: not sure if this should exist
		};

		class nalimov_path : public string
		{
		public:
			virtual std::string to_string() const override
			{
				std::stringstream str;

				str << *this;

				return str.str();
			}

			friend std::ostream& operator<<(std::ostream& os, const nalimov_path& op)
			{
				os << "option name NalimovPath "
					<< static_cast<const string&>(op);

				return os;
			}
		};

		class nalimov_cache : public spin
		{
		public:
			virtual std::string to_string() const override
			{
				std::stringstream str;

				str << *this;

				return str.str();
			}

			friend std::ostream& operator<<(std::ostream& os, const nalimov_cache& op)
			{
				os << "option name NalimovCache "
					<< static_cast<const spin&>(op);

				return os;
			}
		};

		class ponder : public check
		{
		public:
			virtual std::string to_string() const override
			{
				std::stringstream str;

				str << *this;

				return str.str();
			}

			friend std::ostream& operator<<(std::ostream& os, const ponder& op)
			{
				os << "option name Ponder "
					<< static_cast<const check&>(op);

				return os;
			}
		};

		class own_book : public check
		{
		public:
			virtual std::string to_string() const override
			{
				std::stringstream str;

				str << *this;

				return str.str();
			}

			friend std::ostream& operator<<(std::ostream& os, const own_book& op)
			{
				os << "option name OwnBook "
					<< static_cast<const check&>(op);

				return os;
			}
		};

		class multi_pv : public spin
		{
		public:
			virtual std::string to_string() const override
			{
				std::stringstream str;

				str << *this;

				return str.str();
			}

			friend std::ostream& operator<<(std::ostream& os, const multi_pv& op)
			{
				os << "option name MultiPV "
					<< static_cast<const spin&>(op);

				return os;
			}
		};

		class uci_show_curr_line : public check
		{
		public:
			virtual std::string to_string() const override
			{
				std::stringstream str;

				str << *this;

				return str.str();
			}

			friend std::ostream& operator<<(std::ostream& os, const uci_show_curr_line& op)
			{
				os << "option name UCI_ShowCurrLine "
					<< static_cast<const check&>(op);

				return os;
			}
		};

		// should be false by default,
		class uci_show_refutations : public check
		{
		public:
			virtual std::string to_string() const override
			{
				std::stringstream str;

				str << *this;

				return str.str();
			}

			friend std::ostream& operator<<(std::ostream& os, const uci_show_refutations& op)
			{
				os << "option name UCI_ShowRefutations "
					<< static_cast<const check&>(op);

				return os;
			}
		};

		// should be false by default,
		class uci_limit_strength : public check
		{
		public:
			virtual std::string to_string() const override
			{
				std::stringstream str;

				str << *this;

				return str.str();
			}

			friend std::ostream& operator<<(std::ostream& os, const uci_limit_strength& op)
			{
				os << "option name UCI_LimitStrength "
					<< static_cast<const check&>(op);

				return os;
			}
		};

		// should be false by default,
		class uci_elo : public spin
		{
		public:
			virtual std::string to_string() const override
			{
				std::stringstream str;

				str << *this;

				return str.str();
			}

			friend std::ostream& operator<<(std::ostream& os, const uci_elo& op)
			{
				os << "option name UCI_Elo "
					<< static_cast<const spin&>(op);

				return os;
			}
		};

		class uci_analyse_mode : public check
		{
		public:
			virtual std::string to_string() const override
			{
				std::stringstream str;

				str << *this;

				return str.str();
			}

			friend std::ostream& operator<<(std::ostream& os, const uci_analyse_mode& op)
			{
				os << "option name UCI_AnalyseMode "
					<< static_cast<const check&>(op);

				return os;
			}
		};

		class uci_opponent : public string
		{
		public:
			virtual std::string to_string() const override
			{
				std::stringstream str;

				str << *this;

				return str.str();
			}

			friend std::ostream& operator<<(std::ostream& os, const uci_opponent& op)
			{
				os << "option name UCI_Opponent "
					<< static_cast<const string&>(op);

				return os;
			}
		};

		class uci_engine_about : public string
		{
		public:
			virtual std::string to_string() const override
			{
				std::stringstream str;

				str << *this;

				return str.str();
			}

			friend std::ostream& operator<<(std::ostream& os, const uci_engine_about& op)
			{
				os << "option name UCI_EngineAbout "
					<< static_cast<const string&>(op);

				return os;
			}
		};

		class uci_shredder_bases_path : public string
		{
		public:
			virtual std::string to_string() const override
			{
				std::stringstream str;

				str << *this;

				return str.str();
			}

			friend std::ostream& operator<<(std::ostream& os, const uci_shredder_bases_path& op)
			{
				os << "option name UCI_ShredderbasesPath "
					<< static_cast<const string&>(op);

				return os;
			}
		};

		class uci_set_position_value : public string
		{
		public:
			virtual std::string to_string() const override
			{
				std::stringstream str;

				str << *this;

				return str.str();
			}

			friend std::ostream& operator<<(std::ostream& os, const uci_set_position_value& op)
			{
				os << "option name UCI_SetPositionValue "
					<< static_cast<const string&>(op);

				return os;
			}
		};

		// -------------------------------- All in one option object --------------

		// Stores data for the 'option' and 'setoption' commands
		class option
		{
		public:
			option() = default;
			
			//option(const option& op) :		// TODO: implement copy methods and clone()
			//	ptr(op.ptr->clone()) {}
			
			template<class OPTION_T>
			
			option(const OPTION_T& op) :
				ptr(std::make_unique<OPTION_T>(op)) 
			{
				static_assert(std::is_base_of<options::base, OPTION_T>(), "OPTION_T must be derive uci::options::base");
			}
			
			option(const Command& cmd);

			option(option&&) noexcept = default;
			virtual ~option() noexcept = default;
			
			//option& operator=(const option&) = default;
			
			option& operator=(option&&) noexcept = default;
		
			template<class OPTION_T>
			option& operator=(const OPTION_T& op)
			{
				static_assert(std::is_base_of<options::base, OPTION_T>(), "OPTION_T must be derive uci::options::base");
				
				this->ptr = std::make_unique<OPTION_T>(op);

				return *this;
			}
		
			template<class OPTION_T>
			OPTION_T& as()
			{
				return *static_cast<OPTION_T*>(ptr.get());
			}

			template<class OPTION_T>
			const OPTION_T& as() const
			{
				return *static_cast<const OPTION_T *>(ptr.get());
			}

			template<class OPTION_T>
			bool is() const
			{
				return dynamic_cast<const OPTION_T*>(ptr.get()) != nullptr;
			}

			void fill_from(const Command& cmd);

			std::string to_string() const
			{
				if (this->ptr != nullptr)
					return this->ptr->to_string();
				else
					return "option is nullptr";
			}

			friend std::ostream& operator<<(std::ostream& os, const option& op)
			{
				os << op.to_string();

				return os;
			}
		
		public:
			std::unique_ptr<base> ptr;
		};
	} // namespace options
} // namespace uci
