
///////////////////////////////////////////////////////////////////////////////
// algorithm_test.cpp
//
// Unit tests for the functionality declared in algorithms.hpp .
///////////////////////////////////////////////////////////////////////////////

#include "gtest/gtest.h"

#include "algorithms.hpp"


TEST(run_length_encode_trivial_cases, trivial_cases) {
  // empty string
  EXPECT_EQ("", algorithms::run_length_encode(""));

  // single character
  EXPECT_EQ("a", algorithms::run_length_encode("a"));
  EXPECT_EQ("b", algorithms::run_length_encode("b"));
  EXPECT_EQ("c", algorithms::run_length_encode("c"));

  // spaces
  EXPECT_EQ(" ", algorithms::run_length_encode(" "));
  EXPECT_EQ(" a b c ", algorithms::run_length_encode(" a b c "));
  
  // no runs
  EXPECT_EQ("abcdefghijklmnop", algorithms::run_length_encode("abcdefghijklmnop"));
  EXPECT_EQ("the quick brown fox", algorithms::run_length_encode("the quick brown fox"));
}


TEST(run_length_encode_error_handling, error_handling) {
  // invalid character
  EXPECT_THROW(algorithms::run_length_encode("A    "), std::invalid_argument);
  EXPECT_THROW(algorithms::run_length_encode("  A  "), std::invalid_argument);
  EXPECT_THROW(algorithms::run_length_encode("    A"), std::invalid_argument);
  EXPECT_THROW(algorithms::run_length_encode("  9  "), std::invalid_argument);
  EXPECT_THROW(algorithms::run_length_encode("  ?  "), std::invalid_argument);
}

TEST(run_length_encode_just_one_run, just_one_run) {
  // example in comment
  EXPECT_EQ("3a", algorithms::run_length_encode("aaa"));
  
  EXPECT_EQ("z", algorithms::run_length_encode("z"));
  EXPECT_EQ("2z", algorithms::run_length_encode("zz"));
  EXPECT_EQ("3z", algorithms::run_length_encode("zzz"));
  EXPECT_EQ("4z", algorithms::run_length_encode("zzzz"));
  EXPECT_EQ("5z", algorithms::run_length_encode("zzzzz"));
  EXPECT_EQ("6z", algorithms::run_length_encode("zzzzzz"));
  EXPECT_EQ("7z", algorithms::run_length_encode("zzzzzzz"));
  EXPECT_EQ("8z", algorithms::run_length_encode("zzzzzzzz"));
  EXPECT_EQ("9z", algorithms::run_length_encode("zzzzzzzzz"));
  EXPECT_EQ("10z", algorithms::run_length_encode("zzzzzzzzzz"));

  // spaces
  EXPECT_EQ("z", algorithms::run_length_encode("z"));
  EXPECT_EQ("2z", algorithms::run_length_encode("zz"));
  EXPECT_EQ("3z", algorithms::run_length_encode("zzz"));
}

TEST(run_length_encode_mixture, mixture) {
  // examples in comments
  EXPECT_EQ("hel8o there", algorithms::run_length_encode("heloooooooo there"));
  EXPECT_EQ("f2otl2ose and fancy fr2e", algorithms::run_length_encode("footloose and fancy free"));

  // single run at index 0, 1, 2, 3
  EXPECT_EQ("3abcd", algorithms::run_length_encode("aaabcd"));
  EXPECT_EQ("a3bcd", algorithms::run_length_encode("abbbcd"));
  EXPECT_EQ("ab3cd", algorithms::run_length_encode("abcccd"));
  EXPECT_EQ("abc3d", algorithms::run_length_encode("abcddd"));

  // two adjacent runs
  EXPECT_EQ("4g2h", algorithms::run_length_encode("gggghh"));
  
  // two runs at varying positions
  EXPECT_EQ("2a 2b c d", algorithms::run_length_encode("aa bb c d"));
  EXPECT_EQ("2a b 2c d", algorithms::run_length_encode("aa b cc d"));
  EXPECT_EQ("2a b c 2d", algorithms::run_length_encode("aa b c dd"));
  EXPECT_EQ("a 2b 2c d", algorithms::run_length_encode("a bb cc d"));
  EXPECT_EQ("a 2b c 2d", algorithms::run_length_encode("a bb c dd"));
  EXPECT_EQ("a b 2c 2d", algorithms::run_length_encode("a b cc dd"));

  // multiple adjacent runs
  EXPECT_EQ("2i2j2k2l2m2n2o", algorithms::run_length_encode("iijjkkllmmnnoo"));
  EXPECT_EQ(" 2i 2j 2k 2l 2m 2n 2o ", algorithms::run_length_encode(" ii jj kk ll mm nn oo "));

  // prose
  {
    static const std::string
      declaration{"we hold these truths to be self evident that all men are created equal that they are endowed by their creator with certain unalienable rights that among these are life liberty and the pursuit of happiness"},
      compressed{"we hold these truths to be self evident that a2l men are created equal that they are endowed by their creator with certain unalienable rights that among these are life liberty and the pursuit of ha2pine2s"};
    EXPECT_EQ(compressed, algorithms::run_length_encode(declaration)); 
  }
  
  // long runs
  {
    std::string thousands = " " + std::string(1000, 'x') + " " + std::string(2000, 'y') + " ";
    EXPECT_EQ(" 1000x 2000y ", algorithms::run_length_encode(thousands));

    std::string millions = "a" + std::string(9123456, 'b') + "c";
    EXPECT_EQ("a9123456bc", algorithms::run_length_encode(millions));
  }
}

TEST(longest_frequent_substring_trivial_cases, trivial_cases) {

  // empty string
  EXPECT_EQ("", algorithms::longest_frequent_substring("", 1));

  // k=1, so keep entire string
  EXPECT_EQ("a", algorithms::longest_frequent_substring("a", 1));
  EXPECT_EQ("ab", algorithms::longest_frequent_substring("ab", 1));
  EXPECT_EQ("abc", algorithms::longest_frequent_substring("abc", 1));
  EXPECT_EQ("the quick brown fox", algorithms::longest_frequent_substring("the quick brown fox", 1));

  // k > n, so keep nothing
  EXPECT_EQ("", algorithms::longest_frequent_substring("a", 30));
  EXPECT_EQ("", algorithms::longest_frequent_substring("ab", 30));
  EXPECT_EQ("", algorithms::longest_frequent_substring("abc", 30));
  EXPECT_EQ("", algorithms::longest_frequent_substring("the quick brown fox", 30));  
}

TEST(longest_frequent_substring_nontrivial_cases, nontrivial_cases) {
  
  EXPECT_EQ("baba", algorithms::longest_frequent_substring("aa_bb_baba_aaa", 4));
  
  EXPECT_EQ("ababb", algorithms::longest_frequent_substring("ababbc", 2));
  
  EXPECT_EQ("aaa", algorithms::longest_frequent_substring("aaabb", 3));

  static const std::string fox{"the quick brown fox jumps over the lazy dog"};

  EXPECT_EQ("",
	    algorithms::longest_frequent_substring(fox, 10));
  
  EXPECT_EQ("",
	    algorithms::longest_frequent_substring(fox, 9));
  
  EXPECT_EQ(" ",
	    algorithms::longest_frequent_substring(fox, 8));
  
  EXPECT_EQ(" ",
	    algorithms::longest_frequent_substring(fox, 7));
  
  EXPECT_EQ(" ",
	    algorithms::longest_frequent_substring(fox, 6));
  
  EXPECT_EQ(" ",
	    algorithms::longest_frequent_substring(fox, 5));
  
  EXPECT_EQ(" o",
	    algorithms::longest_frequent_substring(fox, 4));
  
  EXPECT_EQ("e ",
	    algorithms::longest_frequent_substring(fox, 3));
  
  EXPECT_EQ("er the ",
	    algorithms::longest_frequent_substring(fox, 2));
  
  EXPECT_EQ(fox,
	    algorithms::longest_frequent_substring(fox, 1));
  
  EXPECT_EQ(fox,
	    algorithms::longest_frequent_substring(fox, 0));
  
  static const std::string declaration{"we hold these truths to be self evident that all men are created equal that they are endowed by their creator with certain unalienable rights that among these are life liberty and the pursuit of happiness"};

  EXPECT_EQ("",
	    algorithms::longest_frequent_substring(declaration, 36));

  EXPECT_EQ(" ",
	    algorithms::longest_frequent_substring(declaration, 35));

  EXPECT_EQ(" ",
	    algorithms::longest_frequent_substring(declaration, 29));

  EXPECT_EQ("e e",
	    algorithms::longest_frequent_substring(declaration, 28));

  EXPECT_EQ("e e",
	    algorithms::longest_frequent_substring(declaration, 27));

  EXPECT_EQ("e e",
	    algorithms::longest_frequent_substring(declaration, 26));

  EXPECT_EQ("e e",
	    algorithms::longest_frequent_substring(declaration, 25));

  EXPECT_EQ("e e",
	    algorithms::longest_frequent_substring(declaration, 24));

  EXPECT_EQ("e e",
	    algorithms::longest_frequent_substring(declaration, 23));

  EXPECT_EQ("e t",
	    algorithms::longest_frequent_substring(declaration, 22));

  EXPECT_EQ("e t",
	    algorithms::longest_frequent_substring(declaration, 21));

  EXPECT_EQ("e t",
	    algorithms::longest_frequent_substring(declaration, 20));

  EXPECT_EQ("e t",
	    algorithms::longest_frequent_substring(declaration, 19));

  EXPECT_EQ("e t",
	    algorithms::longest_frequent_substring(declaration, 18));

  EXPECT_EQ("e t",
	    algorithms::longest_frequent_substring(declaration, 17));

  EXPECT_EQ("at a",
	    algorithms::longest_frequent_substring(declaration, 16));

  EXPECT_EQ("at a",
	    algorithms::longest_frequent_substring(declaration, 15));

  EXPECT_EQ("at a",
	    algorithms::longest_frequent_substring(declaration, 14));

  EXPECT_EQ(" that the",
	    algorithms::longest_frequent_substring(declaration, 13));

  EXPECT_EQ(" that the",
	    algorithms::longest_frequent_substring(declaration, 12));

  EXPECT_EQ(" that the",
	    algorithms::longest_frequent_substring(declaration, 11));

  EXPECT_EQ(" that the",
	    algorithms::longest_frequent_substring(declaration, 10));

  EXPECT_EQ("ent that all ",
	    algorithms::longest_frequent_substring(declaration, 9));

  EXPECT_EQ("ent that all ",
	    algorithms::longest_frequent_substring(declaration, 8));

  EXPECT_EQ("ent that all ",
	    algorithms::longest_frequent_substring(declaration, 7));

  EXPECT_EQ("e hold these tr",
	    algorithms::longest_frequent_substring(declaration, 6));

  EXPECT_EQ("e hold these truths to ",
	    algorithms::longest_frequent_substring(declaration, 5));

  EXPECT_EQ("e hold these truths to be sel",
	    algorithms::longest_frequent_substring(declaration, 4));

  EXPECT_EQ("ual that they are endowed by their creator with certain unalienable ri",
	    algorithms::longest_frequent_substring(declaration, 3));

  EXPECT_EQ("ual that they are endowed by their creator with certain unalienable rights that among these are life liberty and the pursuit of happiness",
	    algorithms::longest_frequent_substring(declaration, 2));

  EXPECT_EQ(declaration,
	    algorithms::longest_frequent_substring(declaration, 1));

  EXPECT_EQ(declaration,
	    algorithms::longest_frequent_substring(declaration, 0));

  static const std::string long_str(400, 'a');
  EXPECT_EQ("",
	    algorithms::longest_frequent_substring(long_str, long_str.size() + 1));
}

TEST(reformat_date_pattern_1, pattern_1) {
  // return input unchanged
  EXPECT_EQ("2000-01-01", algorithms::reformat_date("2000-01-01"));
  EXPECT_EQ("2022-02-03", algorithms::reformat_date("2022-02-03"));

  // min and max year, month, date
  EXPECT_EQ("1900-02-02", algorithms::reformat_date("1900-02-02"));
  EXPECT_EQ("2099-02-02", algorithms::reformat_date("2099-02-02"));
  EXPECT_EQ("2022-01-02", algorithms::reformat_date("2022-01-02"));
  EXPECT_EQ("2022-12-02", algorithms::reformat_date("2022-12-02"));
  EXPECT_EQ("2022-02-01", algorithms::reformat_date("2022-02-01"));
  EXPECT_EQ("2022-02-31", algorithms::reformat_date("2022-02-31"));

  // not zero-padded
  EXPECT_EQ("2022-02-03", algorithms::reformat_date("2022-2-3"));
  EXPECT_EQ("2022-02-03", algorithms::reformat_date("2022-02-3"));
  EXPECT_EQ("2022-02-03", algorithms::reformat_date("2022-2-03"));

  // leading spaces are ignored
  EXPECT_EQ("2022-02-03", algorithms::reformat_date(" 2022-02-03"));
  EXPECT_EQ("2022-02-03", algorithms::reformat_date("  2022-02-03"));
  EXPECT_EQ("2022-02-03", algorithms::reformat_date("   2022-02-03"));
  EXPECT_EQ("2022-02-03", algorithms::reformat_date("    2022-02-03"));
  EXPECT_EQ("2022-02-03", algorithms::reformat_date("     2022-02-03"));

  // trailing spaces are ignored
  EXPECT_EQ("2022-02-03", algorithms::reformat_date("2022-02-03 "));
  EXPECT_EQ("2022-02-03", algorithms::reformat_date("2022-02-03  "));
  EXPECT_EQ("2022-02-03", algorithms::reformat_date("2022-02-03   "));
  EXPECT_EQ("2022-02-03", algorithms::reformat_date("2022-02-03    "));
  EXPECT_EQ("2022-02-03", algorithms::reformat_date("2022-02-03     "));
}

TEST(reformat_date_pattern_2, pattern_2) {
  // same examples as for pattern 1
  EXPECT_EQ("2000-01-01", algorithms::reformat_date("01/01/2000"));
  EXPECT_EQ("2022-02-03", algorithms::reformat_date("02/03/2022"));

  // min and max year
  EXPECT_EQ("1900-02-02", algorithms::reformat_date("02/02/1900"));
  EXPECT_EQ("2099-02-02", algorithms::reformat_date("02/02/2099"));

  // min and max month
  EXPECT_EQ("2022-01-02", algorithms::reformat_date("01/02/2022"));
  EXPECT_EQ("2022-12-02", algorithms::reformat_date("12/02/2022"));

  // min and max day
  EXPECT_EQ("2022-02-01", algorithms::reformat_date("02/01/2022"));
  EXPECT_EQ("2022-02-31", algorithms::reformat_date("02/31/2022"));

  // not zero-padded
  EXPECT_EQ("2022-02-03", algorithms::reformat_date("2/3/2022"));
  EXPECT_EQ("2022-02-03", algorithms::reformat_date("02/3/2022"));
  EXPECT_EQ("2022-02-03", algorithms::reformat_date("2/03/2022"));
}

TEST(reformat_date_pattern_3, pattern_3) {

  EXPECT_EQ("2000-01-01", algorithms::reformat_date("january 1, 2000"));

  // min and max year
  EXPECT_EQ("1900-02-02", algorithms::reformat_date("february 2, 1900"));
  EXPECT_EQ("2099-02-02", algorithms::reformat_date("february 2, 2099"));

  // min and max day
  EXPECT_EQ("2022-02-01", algorithms::reformat_date("february 1, 2022"));
  EXPECT_EQ("2022-02-31", algorithms::reformat_date("february 31, 2022"));

  // all valid months
  EXPECT_EQ("2022-01-02", algorithms::reformat_date("january 2, 2022"));
  EXPECT_EQ("2022-02-02", algorithms::reformat_date("february 2, 2022"));
  EXPECT_EQ("2022-03-02", algorithms::reformat_date("march 2, 2022"));
  EXPECT_EQ("2022-04-02", algorithms::reformat_date("april 2, 2022"));
  EXPECT_EQ("2022-05-02", algorithms::reformat_date("may 2, 2022"));
  EXPECT_EQ("2022-06-02", algorithms::reformat_date("june 2, 2022"));
  EXPECT_EQ("2022-07-02", algorithms::reformat_date("july 2, 2022"));
  EXPECT_EQ("2022-08-02", algorithms::reformat_date("august 2, 2022"));
  EXPECT_EQ("2022-09-02", algorithms::reformat_date("september 2, 2022"));
  EXPECT_EQ("2022-10-02", algorithms::reformat_date("october 2, 2022"));
  EXPECT_EQ("2022-11-02", algorithms::reformat_date("november 2, 2022"));
  EXPECT_EQ("2022-12-02", algorithms::reformat_date("december 2, 2022"));

  // case-insensitive
  EXPECT_EQ("2007-09-12", algorithms::reformat_date("september 12, 2007"));
  EXPECT_EQ("2007-09-12", algorithms::reformat_date("September 12, 2007"));
  EXPECT_EQ("2007-09-12", algorithms::reformat_date("SEPTEMBER 12, 2007"));
  EXPECT_EQ("2007-09-12", algorithms::reformat_date("SePtEmBeR 12, 2007"));
}

TEST(reformat_date_pattern_4, pattern_4) {

  EXPECT_EQ("2000-01-01", algorithms::reformat_date("jan 1, 2000"));

  // min and max year
  EXPECT_EQ("1900-02-02", algorithms::reformat_date("feb 2, 1900"));
  EXPECT_EQ("2099-02-02", algorithms::reformat_date("feb 2, 2099"));

  // min and max day
  EXPECT_EQ("2022-02-01", algorithms::reformat_date("feb 1, 2022"));
  EXPECT_EQ("2022-02-31", algorithms::reformat_date("feb 31, 2022"));

  // all valid months
  EXPECT_EQ("2022-01-02", algorithms::reformat_date("jan 2, 2022"));
  EXPECT_EQ("2022-02-02", algorithms::reformat_date("feb 2, 2022"));
  EXPECT_EQ("2022-03-02", algorithms::reformat_date("mar 2, 2022"));
  EXPECT_EQ("2022-04-02", algorithms::reformat_date("apr 2, 2022"));
  EXPECT_EQ("2022-05-02", algorithms::reformat_date("may 2, 2022"));
  EXPECT_EQ("2022-06-02", algorithms::reformat_date("jun 2, 2022"));
  EXPECT_EQ("2022-07-02", algorithms::reformat_date("jul 2, 2022"));
  EXPECT_EQ("2022-08-02", algorithms::reformat_date("aug 2, 2022"));
  EXPECT_EQ("2022-09-02", algorithms::reformat_date("sep 2, 2022"));
  EXPECT_EQ("2022-10-02", algorithms::reformat_date("oct 2, 2022"));
  EXPECT_EQ("2022-11-02", algorithms::reformat_date("nov 2, 2022"));
  EXPECT_EQ("2022-12-02", algorithms::reformat_date("dec 2, 2022"));

  // case-insensitive
  EXPECT_EQ("2001-04-05", algorithms::reformat_date("Apr 5, 2001"));
  EXPECT_EQ("2001-04-05", algorithms::reformat_date("aPr 5, 2001"));
  EXPECT_EQ("2001-04-05", algorithms::reformat_date("apR 5, 2001"));
  EXPECT_EQ("2001-04-05", algorithms::reformat_date("APR 5, 2001"));
}

TEST(reformat_invalid_format, invalid_format) {

  // not close to any pattern
  EXPECT_THROW(algorithms::reformat_date(""), std::invalid_argument);
  EXPECT_THROW(algorithms::reformat_date("    "), std::invalid_argument);
  EXPECT_THROW(algorithms::reformat_date("the quick brown fox"), std::invalid_argument);

  // extra invalid characters before
  EXPECT_THROW(algorithms::reformat_date("abc2001-05-10"), std::invalid_argument);
  EXPECT_THROW(algorithms::reformat_date("abc05/10/2001"), std::invalid_argument);
  EXPECT_THROW(algorithms::reformat_date("abcmay 10, 2001"), std::invalid_argument);
  
  // extra invalid characters after
  EXPECT_THROW(algorithms::reformat_date("2001-05-10abc"), std::invalid_argument);
  EXPECT_THROW(algorithms::reformat_date("05/10/2001abc"), std::invalid_argument);
  EXPECT_THROW(algorithms::reformat_date("may 10, 2001abc"), std::invalid_argument);
  
  // too many fields 
  EXPECT_THROW(algorithms::reformat_date("2000-01-01-01"), std::invalid_argument);
  EXPECT_THROW(algorithms::reformat_date("01/01/01/2000"), std::invalid_argument);
  EXPECT_THROW(algorithms::reformat_date("january 28, 2021, 2021"), std::invalid_argument);
  
  // not enough fields
  EXPECT_THROW(algorithms::reformat_date("2000-01"), std::invalid_argument);
  EXPECT_THROW(algorithms::reformat_date("2000"), std::invalid_argument);
  EXPECT_THROW(algorithms::reformat_date("01/2000"), std::invalid_argument);
  EXPECT_THROW(algorithms::reformat_date("2000"), std::invalid_argument);
  EXPECT_THROW(algorithms::reformat_date("28, 2021"), std::invalid_argument);
  EXPECT_THROW(algorithms::reformat_date("january, 2021"), std::invalid_argument);
  EXPECT_THROW(algorithms::reformat_date("january 28"), std::invalid_argument);

  // malformed fields
  EXPECT_THROW(algorithms::reformat_date("abcd-01-01"), std::invalid_argument);
  EXPECT_THROW(algorithms::reformat_date("2000-ab-01"), std::invalid_argument);
  EXPECT_THROW(algorithms::reformat_date("2000-01-ab"), std::invalid_argument);
  EXPECT_THROW(algorithms::reformat_date("ab/01/2000"), std::invalid_argument);
  EXPECT_THROW(algorithms::reformat_date("01/ab/2000"), std::invalid_argument);
  EXPECT_THROW(algorithms::reformat_date("01/01/abcd"), std::invalid_argument);
  EXPECT_THROW(algorithms::reformat_date("january ab, 2021"), std::invalid_argument);
  EXPECT_THROW(algorithms::reformat_date("january 28, ab"), std::invalid_argument);

  // blank fields
  EXPECT_THROW(algorithms::reformat_date("-01-01"), std::invalid_argument);
  EXPECT_THROW(algorithms::reformat_date("2000--01"), std::invalid_argument);
  EXPECT_THROW(algorithms::reformat_date("2000-01-"), std::invalid_argument);
  EXPECT_THROW(algorithms::reformat_date("/01/01"), std::invalid_argument);
  EXPECT_THROW(algorithms::reformat_date("2000//01"), std::invalid_argument);
  EXPECT_THROW(algorithms::reformat_date("2000/01/"), std::invalid_argument);
  EXPECT_THROW(algorithms::reformat_date(", 2021"), std::invalid_argument);
  EXPECT_THROW(algorithms::reformat_date("january 28,"), std::invalid_argument);

  // invalid months
  EXPECT_THROW(algorithms::reformat_date("juneuary 28, 2021"), std::invalid_argument);
  EXPECT_THROW(algorithms::reformat_date("abril 28, 2021"), std::invalid_argument);
  EXPECT_THROW(algorithms::reformat_date("augu 28, 2021"), std::invalid_argument);
  EXPECT_THROW(algorithms::reformat_date("augus 28, 2021"), std::invalid_argument);

  // invalid month abbreviations  
  EXPECT_THROW(algorithms::reformat_date("j 28, 2021"), std::invalid_argument);
  EXPECT_THROW(algorithms::reformat_date("ja 28, 2021"), std::invalid_argument);
  EXPECT_THROW(algorithms::reformat_date("aur 28, 2021"), std::invalid_argument);
  EXPECT_THROW(algorithms::reformat_date("deg 28, 2021"), std::invalid_argument);
}

TEST(reformat_invalid_field, invalid_field) {

  // year too small
  EXPECT_THROW(algorithms::reformat_date("1899-07-22"), std::invalid_argument);
  EXPECT_THROW(algorithms::reformat_date("07/22/1899"), std::invalid_argument);
  EXPECT_THROW(algorithms::reformat_date("july 22, 1899"), std::invalid_argument);
  EXPECT_THROW(algorithms::reformat_date("999-07-22"), std::invalid_argument);
  EXPECT_THROW(algorithms::reformat_date("07/22/999"), std::invalid_argument);
  EXPECT_THROW(algorithms::reformat_date("july 22, 999"), std::invalid_argument);
  EXPECT_THROW(algorithms::reformat_date("0-07-22"), std::invalid_argument);
  EXPECT_THROW(algorithms::reformat_date("07/22/0"), std::invalid_argument);
  EXPECT_THROW(algorithms::reformat_date("july 22, 0"), std::invalid_argument);

  // year too large
  EXPECT_THROW(algorithms::reformat_date("2100-07-22"), std::invalid_argument);
  EXPECT_THROW(algorithms::reformat_date("07/22/2100"), std::invalid_argument);
  EXPECT_THROW(algorithms::reformat_date("july 22, 2100"), std::invalid_argument);
  EXPECT_THROW(algorithms::reformat_date("5000-07-22"), std::invalid_argument);
  EXPECT_THROW(algorithms::reformat_date("07/22/5000"), std::invalid_argument);
  EXPECT_THROW(algorithms::reformat_date("july 22, 5000"), std::invalid_argument);
  
  // month too small
  EXPECT_THROW(algorithms::reformat_date("2010-00-22"), std::invalid_argument);
  EXPECT_THROW(algorithms::reformat_date("00/22/2010"), std::invalid_argument);

  // month too large
  EXPECT_THROW(algorithms::reformat_date("2010-13-22"), std::invalid_argument);
  EXPECT_THROW(algorithms::reformat_date("13/22/2010"), std::invalid_argument);
  EXPECT_THROW(algorithms::reformat_date("2010-100-22"), std::invalid_argument);
  EXPECT_THROW(algorithms::reformat_date("100/22/2010"), std::invalid_argument);

  // day too small
  EXPECT_THROW(algorithms::reformat_date("2010-07-0"), std::invalid_argument);
  EXPECT_THROW(algorithms::reformat_date("07/00/2010"), std::invalid_argument);
  EXPECT_THROW(algorithms::reformat_date("july 0, 2010"), std::invalid_argument);
  
  // day too large
  EXPECT_THROW(algorithms::reformat_date("2010-07-32"), std::invalid_argument);
  EXPECT_THROW(algorithms::reformat_date("07/32/2010"), std::invalid_argument);
  EXPECT_THROW(algorithms::reformat_date("july 32, 2010"), std::invalid_argument);
  EXPECT_THROW(algorithms::reformat_date("2010-07-100"), std::invalid_argument);
  EXPECT_THROW(algorithms::reformat_date("07/100/2010"), std::invalid_argument);
  EXPECT_THROW(algorithms::reformat_date("july 100, 2010"), std::invalid_argument);
}
