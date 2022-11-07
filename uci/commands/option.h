#pragma once
#pragma once

#include "uci/commands/command_base.h"

#include <optional>
#include <list>

namespace uci
{
	namespace commands
	{
		class option : public command_base_template<option>
		{
		public: // --- Nested Classes ---
			class base
			{
			public:
				virtual std::string to_string() const = 0;

				// 'line' should be the last part of the command string that follows after:
				// option name <option_name> type <option_type>
				virtual void parse(const std::string& line) = 0;

				virtual std::unique_ptr<base> clone() const = 0;

				friend std::ostream& operator<<(std::ostream& os, const base& op)
				{
					os << op.to_string();

					return os;
				}
			};

			class check : public base
			{
			public:
				virtual std::string to_string() const override;

				// See comments for base::parse()
				virtual void parse(const std::string& line) override;

				virtual std::unique_ptr<base> clone() const override
				{
					return std::make_unique<check>(*this);
				}

				std::optional<bool> default_val;
				std::optional<bool> var;
			};

			class spin : public base
			{
			public:
				virtual std::string to_string() const override;
				
				// See comments for base::parse()
				virtual void parse(const std::string& line) override;

				virtual std::unique_ptr<base> clone() const override
				{
					return std::make_unique<spin>(*this);
				}

				std::optional<int> default_val;
				std::optional<int> min;
				std::optional<int> max;
				std::optional<int> var;
			};

			class combo : public base
			{
			public:
				virtual std::string to_string() const override;

				// See comments for base::parse()
				virtual void parse(const std::string& line) override;

				virtual std::unique_ptr<base> clone() const override
				{
					return std::make_unique<combo>(*this);
				}

				std::optional<std::string> default_val;
				std::optional<std::list<std::string>> vals;
			};

			class button : public base
			{
			public:
				virtual std::string to_string() const override;

				virtual std::unique_ptr<base> clone() const override
				{
					return std::make_unique<button>(*this);
				}

				// See comments for base::parse()
				virtual void parse(const std::string& line) override;
			};

			class string : public base
			{
			public:
				virtual std::string to_string() const override;

				// See comments for base::parse()
				virtual void parse(const std::string& line) override;

				virtual std::unique_ptr<base> clone() const override
				{
					return std::make_unique<string>(*this);
				}

				std::optional<std::string> default_val;
				//std::optional<std::string> var;
			};

		public: // --- Methods ---

			// Stores data for the 'option' and 'setoption' commands
			option() = default;
			template<class OPTION_T>
			option(const OPTION_T& op) : ptr(std::make_unique<OPTION_T>(op))
			{
				static_assert(std::is_base_of<commands::option::base, OPTION_T>(), "OPTION_T must be derive uci::options::base");
			}
			option(const option&) = default;
			option(option&&) noexcept = default;
			virtual ~option() noexcept = default;

			option& operator=(const option&) = default;
			option& operator=(option&&) noexcept = default;

			template<class OPTION_T>
			option& operator=(const OPTION_T& op)
			{
				static_assert(std::is_base_of<commands::option::base, OPTION_T>(), "OPTION_T must be derive uci::options::base");

				this->ptr = op.ptr->clone();// std::make_unique<OPTION_T>(op);

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
				return *static_cast<const OPTION_T*>(ptr.get());
			}

			template<class OPTION_T>
			bool is() const
			{
				return dynamic_cast<const OPTION_T*>(ptr.get()) != nullptr;
			}

			virtual void parse(const std::string& line) override;
			
			friend std::ostream& operator<<(std::ostream& os, const option& op)
			{
				os << "option name " << op.option_name;
				
				if (op.ptr != nullptr) os << op.ptr->to_string();
				else os << "!invalid option!";
			
				return os;
			}
		public:
			std::string option_name;
			std::unique_ptr<base> ptr;
		};
	} // namespace commands
} // namespace uci

