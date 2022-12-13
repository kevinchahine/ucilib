#pragma once

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <exception>

#include <boost/algorithm/string/join.hpp>

namespace uci
{
	namespace commands
	{
		// Throws an exception with a specified error message
		inline void throw_exception(const std::string & expected_token, const std::string & parsed_token, const std::string & line)
		{
			std::stringstream ss;

			ss << "expected token \'" << expected_token << "\' but got \'" << parsed_token << "\' instead: \'" << line << "\'";

			throw std::runtime_error(ss.str());
		}

		// Verifies that the parsed token matches the expected token in the given command. 
		// If it does not match an exception is thrown.
		inline void assert_token(const std::string& expected_token, const std::string& parsed_token, const std::string& line)
		{
			if (expected_token != parsed_token) {
				throw_exception(expected_token, parsed_token, line);
			}
		}

		// Verifies that the parsed token matches the expected token in the given command. 
		// If it does not match an exception is thrown.
		inline void assert_token(const std::vector<std::string>& expected_tokens, const std::string& parsed_token, const std::string& line)
		{
			const auto& e = expected_tokens;
			const auto& p = parsed_token;

			auto it = std::find(e.begin(), e.end(), p);

			if (it == e.end()) {
				//throw_exception(boost::join(e, ' '), p, line);
			}
		}

		inline bool to_bool(const std::string& value)
		{
			if (value == "true" || value == "1" || value == "on")			return true;
			else if (value == "false" || value == "0" || value == "off")	return false;
			else															return false;
		}

		class size_type_pair
		{
		public:
			size_type_pair() = default;
			size_type_pair(std::string::size_type begin, std::string::size_type end) :
				begin(begin),
				end(end) {}
			size_type_pair(const size_type_pair&) = default;
			size_type_pair(size_type_pair&&) noexcept = default;
			~size_type_pair() noexcept = default;
			size_type_pair& operator=(const size_type_pair&) = default;
			size_type_pair& operator=(size_type_pair&&) noexcept = default;

			bool operator<(const size_type_pair& left) const { return this->begin < left.begin; }
			bool operator==(const size_type_pair& left) const { return this->begin == left.begin; }

			friend std::ostream& operator<<(std::ostream& os, const size_type_pair& pair) {
				os << '(' << pair.begin << ", " << pair.end << ')';

				return os;
			}

		public:
			std::string::size_type begin;
			std::string::size_type end;
		};

		class key_value_pair
		{
		public:

			key_value_pair() = default;
			key_value_pair(const std::string& key, const std::string& value) :
				key(key),
				val(val) {}
			key_value_pair(std::string&& key, std::string&& val) :
				key(std::move(key)),
				val(std::move(val)) {}
			key_value_pair(const key_value_pair&) = default;
			key_value_pair(key_value_pair&&) noexcept = default;
			~key_value_pair() noexcept = default;
			key_value_pair& operator=(const key_value_pair&) = default;
			key_value_pair& operator=(key_value_pair&&) noexcept = default;

			friend std::ostream& operator<<(std::ostream& os, const key_value_pair& pair) {
				os << '(' << pair.key << ", " << pair.val << ')';

				return os;
			}

			std::string key;
			std::string val;
		};

		void find_all_tokens(const std::string& line, const std::string& token, std::back_insert_iterator<std::vector<size_type_pair>>& destination);

		void extract_key_value_pairs(
			const std::string& line, 
			const std::vector<std::string>& separators, 
			std::back_insert_iterator<std::vector<key_value_pair>>& destination);
		
	} // namespace commands
} // namespace uci
