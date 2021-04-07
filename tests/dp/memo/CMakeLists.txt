# Project  Algorithms
#
# @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>

add_executable(
  dp-memo-tests
  fib_unittest.cpp
  grid_traveler_unittest.cpp
  can_sum_unittest.cpp
  how_sum_unittest.cpp
  can_construct_unittest.cpp
  count_construct_unittest.cpp
  all_construct_unittest.cpp)

target_include_directories(dp-memo-tests PRIVATE ${GTEST_INCLUDE_DIRS}
                                            ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(dp-memo-tests PRIVATE dp-memo GTest::GTest GTest::Main pthread)

add_test(NAME dp-memo-tests COMMAND dp-memo-tests)
