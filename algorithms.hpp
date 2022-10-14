///////////////////////////////////////////////////////////////////////////////
// algorithms.hpp
//
// Definitions for four algorithms:
//
// run_length_encode
// longest_frequent_substring
// reformat_date
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include <string>
#include <map>

namespace algorithms {

  // Run-length-encode the given string.
  //
  // uncompressed must be a string containing only lower-case letters or spaces.
  //
  // A run is defined as a sequence of K>2 contiguous copies of the same
  // character c.
  // For example, "aaa" is a run with K=3 and c='a'.
  // This function returns a string based on uncompressed, where every run is
  // replaced with the string
  //   COUNTc
  // where COUNT is the base-10 representation of K. Non-run characters are
  // left as-is.
  //
  // Example inputs and outputs:
  //   "aaa" -> "3a"
  //   "heloooooooo there" -> "hel8o there"
  //   "footloose and fancy free" -> "f2otl2ose and fancy fr2e"
  //
  // Throws std::invalid_argument if the string contains invalid characters.

  void append_run(std::string& C, char& run_char, int& run_length) {
    if (run_length > 1) {
      C += std::to_string(run_length);
    }

    C += (run_char);
  }

  std::string run_length_encode(const std::string& uncompressed) {
    for (char c : uncompressed) {
      if ((c < 97 && c != 32) || c > 122) {
        throw std::invalid_argument("Invalid Input!");
      }
    }

    std::string C = "";

    if (uncompressed.empty()) {
      return C;
    }

    char run_char = uncompressed[0];

    int run_length = 1;

    for (int i = 1; i < uncompressed.size(); i++) {
      char c = uncompressed[i];
      if (c == run_char) {
        run_length++;
      } else {
          append_run(C, run_char, run_length);
          run_char = c;
          run_length = 1;
      }
    }

    append_run(C, run_char, run_length);
    return C;
  }

  // Returns the longest substring of text, such that every character in the
  // substring appears at least k times in text.
  // If there are ties, the substring that appears first is returned.
  std::string longest_frequent_substring(const std::string& text, unsigned k) {
    if (k <= 1) {
      return text;
    }

    std::map<char, int> freq;

    for (char c : text) {
      if (freq[c] == 0) {
        freq[c] = 1;
      } else {
        freq[c]++;
      }
    }

    std::string best = "";

    for (int b = 0; b < text.size()-1; ++b) {
      for (int e = b; e < text.size(); ++e) {
        std::string cand = text.substr(b, (e-b+1));
        bool freq_check = true;
        for (char c : cand) {
          if (freq[c] < k) {
            freq_check = false;
            break;
          }
        }
        if (freq_check && cand.size() > best.size()) {
          best = cand;
        }
      }
    }
    return best;
  }

  // Reformats a string containing a date into YYYY-MM-DD format.
  //
  // input may be formatted in one of four patterns:
  // 1. Y-M-D
  //    where Y, M, and D are positive integers
  // 2. M/D/Y
  //    where Y, M, and D are positive integers
  // 3. MONTH DAY, YEAR
  //    where
  //    - MONTH is a case-insensitive name of a month, ex.
  //      "january", "FEBRUARY", "March", etc.
  //    - DAY is a positive integer representing a day, e.x. "15"
  //    - YEAR is a positive integer representing a year, e.x. "2022"
  // 4. MON DAY, YEAR
  //    where
  //    - MON is a case-insensitive three-letter abbreviation of a month, ex.
  //      "jan", "FEB", "Mar", etc.
  //    - DAY is the same as above
  //    - YEAR is the same as above
  //
  // Any leading spaces or trailing spaces are ignored.
  //
  // Returns a string in strict YYYY-MM-DD format.
  //
  // Throws std::invalid argument if:
  // - input does not fit any of the four patterns
  // - MONTH is not a valid month name
  // - MON is not a valid month abbreviation
  // - DAY is not in the range [1, 31]
  // - YEAR is not in the range [1900, 2099]

  // Helper function for reformat_date()
  std::string verify_format(std::string& year, std::string& month, std::string& day) {
    std::map<std::string, std::string> months = {
      {"january", "01"}, {"february", "02"}, {"march", "03"},
      {"april", "04"}, {"may", "05"}, {"june", "06"},
      {"july", "07"}, {"august", "08"}, {"september", "09"},
      {"october", "10"}, {"november", "11"}, {"december", "12"} };

    std::map<std::string, std::string> month_abbr = {
      {"jan", "01"}, {"feb", "02"}, {"mar", "03"}, {"apr", "04"},
      {"may", "05"}, {"jun", "06"}, {"jul", "07"}, {"aug", "08"},
      {"sep", "09"}, {"oct", "10"}, {"nov", "11"}, {"dec", "12"} };

    std::string D = "";

    int y = 0;

    if (year.size() == 4) {
      y = std::stoi(year);
    }

    if (y < 1900 || y > 2099) {
      throw std::invalid_argument("Year is not in the range [1900, 2099].");
    } else {
      D = year + "-";
    }

    for (int i = 0; i < month.size(); i++) {
      month[i] = std::tolower(month[i]);
    }

    if (month.size() == 2 || month.size() == 1) {

      if (month.size() == 1) {
        month = month.insert(0, "0");
      }

      int m = std::stoi(month);

      if (m < 1 || m > 12) {
        throw std::invalid_argument("M is not in the range [1, 12]");
      } else {
        D = D + month + "-";
      }
    } else if (month.size() == 3) {
      std::map<std::string, std::string>::iterator iter = month_abbr.find(month);

      if (iter != month_abbr.end()) {
        D = D + month_abbr[month] + "-";
      } else {
        throw std::invalid_argument("MON is not a valid month abbreviation.");
      }
    } else if (month.size() > 3) {
        std::map<std::string, std::string>::iterator iter = months.find(month);
        if (iter != months.end()) {
          D = D + months[month] + "-";
        } else {
          throw std::invalid_argument("MONTH is not a valid month name");
        }
    }

    if (day.size() == 1) {
      day = day.insert(0, "0");
    }

    int d = 0;

    if (day.size() == 2) {
      d = std::stoi(day);
    }

    if (d < 1 || d > 31) {
      throw std::invalid_argument("DAY is not in the range [1, 31]");
    } else {
      D = D + day;
    }

    return D;
  }

  std::string reformat_date(const std::string& input) {
    std::string D, substring = "";

    std::vector<std::string> parts;

    int delimiter_count = 0;

    for (int i = 0; i < input.size(); i++) {
      char c = input[i];

      if ((i == input.size() - 1) && (c != ' ')) {
        substring += c;
        parts.push_back(substring);
      }

      if (c == '-' || c == '/' || c == ',' || c == ' ') {
        if (substring != "") {
          parts.push_back(substring);
        }

        if (c != ' ') {
          delimiter_count++;
          parts.push_back(std::string(1, c));
        }

        substring = "";
      } else {
        substring += c;
      }
    }

    if (delimiter_count < 1 || parts.size() < 4) {
      throw std::invalid_argument("Input does not fit pattern 1, 2, 3, or 4.");
    }

    if (parts[2] == "," && delimiter_count == 1) {
      D = verify_format(parts[3], parts[0], parts[1]);
    } else if ((parts[1] == "-" && parts[3] == "-") && delimiter_count == 2) {
      D = verify_format(parts[0], parts[2], parts[4]);
    } else if ((parts[1] == "/" && parts[3] == "/") && delimiter_count == 2) {
      D = verify_format(parts[4], parts[0], parts[2]);
    } else {
      throw std::invalid_argument("Input does not fit pattern 1, 2, 3, or 4.");
    }

    return D;
  }
}
