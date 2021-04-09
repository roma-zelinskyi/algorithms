# Project  Algorithms
#
# @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>

add_executable(dp-tab-tests fib_unittest.cpp grid_traveler_unittest.cpp)

target_include_directories(dp-tab-tests PRIVATE ${GTEST_INCLUDE_DIRS}
                                            ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(dp-tab-tests PRIVATE dp-tab GTest::GTest GTest::Main pthread)

add_test(NAME dp-tab-tests COMMAND dp-tab-tests)
