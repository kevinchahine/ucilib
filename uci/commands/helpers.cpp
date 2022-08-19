#include "uci/commands/helpers.h"

#include <boost/algorithm/string/trim.hpp>

using namespace std;

namespace uci
{
	namespace commands
	{
		void find_all_tokens(const string& line, const string& token, back_insert_iterator<vector<size_type_pair>>& destination)
		{
			string::size_type pos = 0;

			const string spaced_line = " " + line + " ";
			const string spaced_token = " " + token + " ";

			while (pos != string::npos) {
				// Look for beginning of next token
				pos = spaced_line.find(spaced_token, pos);

				// Did we find token?
				if (pos == string::npos) {
					// No a token was not found. We're done here.
					break;
				}

				pos++;

				// Look for end of token
				string::size_type end = spaced_line.find_first_of(' ', pos);	// find end of token

				// If end is npos, then the token is at the end of 'line' 
				if (end == string::npos) {
					end = spaced_line.size() - 1;
				}

				// Make sure match is a full token
				if (boost::is_space()(spaced_line.at(pos - 1)) &&
					boost::is_space()(spaced_line.at(end))) {
					destination = size_type_pair{ pos - 1, end };
				}
				else {
				}

				pos = end;	// Begin next token search starting from end (optional but a little faster)
			}
		}

		void extract_key_value_pairs(
			const string& line,
			const vector<string>& separators,
			back_insert_iterator<vector<key_value_pair>>& destination)
		{
			// Separators are the tokens "default", "min", "max" and "var"
			// The index of the first character of the separators will be stored in separators_pos
			vector<size_type_pair> separators_pos;

			// --- Find Separators ---
			// Look for all occurences of each token one by one and store their indicies in separators_pos
			for (const string& sep : separators) {
				find_all_tokens(line, sep, back_inserter(separators_pos));
			}

			// --- Sort positions ---
			// separators_pos may be unsorted. 
			sort(separators_pos.begin(), separators_pos.end());

			// --- Extract all tokens ---
			// Go from one token to the next and extract the separators and their cooresponding values
			for (size_t i = 0; i < separators_pos.size(); i++) {
				// Get index range of each token
				const size_type_pair& key_pos = separators_pos.at(i);
				string::size_type val_begin = std::min(line.find_first_not_of(' ', key_pos.end), line.size());
				string::size_type next_key_begin = (i + 1 < separators_pos.size() ? separators_pos.at(i + 1).begin : line.size());

				// Extract substring of each token
				// TODO: Try to do this with string_view to save on copy ops
				string key = line.substr(key_pos.begin, key_pos.end - key_pos.begin);
				string val = line.substr(val_begin, next_key_begin - val_begin);

				// Remove any trailing whitespace
				boost::trim_right(key);
				boost::trim_right(val);

				// Append to container as a key value pair
				destination = key_value_pair{ std::move(key), std::move(val) };
			}
		}
	} // namespace commands
} // namespace uci