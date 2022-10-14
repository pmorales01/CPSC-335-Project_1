
from gggg import *

a = Assignment(39, 20)
s = State(a)

horizontal_rule()

s.reject_if_missing_contributors()
s.reject_if_starter_contributors()

s.reject_unless_files_exist(['algorithms.hpp',
                             'algorithms_test.cpp'])

s.reject_if_file_unchanged('algorithms.hpp',
                           '0549959b9fd44bcab2b50842b6d4e648a177e6b351ee3453739fbac9ba69a9e1')

s.reject_if_file_changed('algorithms_test.cpp',
                         '783f0b12ed43a73b8850da42a6f4a182910b9f0b93ff3bf927ac6c869a52acd5')

s.reject_unless_command_succeeds(['make', 'clean', 'algorithms_test'])

s.string_removed_test('TODO comments removed', 3, 'TODO', ['algorithms.hpp'])

s.gtest_run('algorithms_test')
s.gtest_suite_test('run_length_encode_trivial_cases', 3)
s.gtest_suite_test('run_length_encode_error_handling', 3)
s.gtest_suite_test('run_length_encode_just_one_run', 3)
s.gtest_suite_test('run_length_encode_mixture', 3)
s.gtest_suite_test('longest_frequent_substring_trivial_cases', 6)
s.gtest_suite_test('longest_frequent_substring_nontrivial_cases', 6)
s.gtest_suite_test('reformat_date_pattern_1', 2)
s.gtest_suite_test('reformat_date_pattern_2', 2)
s.gtest_suite_test('reformat_date_pattern_3', 2)
s.gtest_suite_test('reformat_date_pattern_4', 2)
s.gtest_suite_test('reformat_invalid_format', 2)
s.gtest_suite_test('reformat_invalid_field', 2)

s.summarize()
