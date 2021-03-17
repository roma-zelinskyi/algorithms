# Project  Algorithms
#
# @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>

add_executable(dp-tests fib_unittest.cpp)

set_target_properties(dp-tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                                       ${CMAKE_BINARY_DIR}/tests)

target_include_directories(dp-tests PRIVATE ${GTEST_INCLUDE_DIRS}
                                         ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(dp-tests PRIVATE dp GTest::GTest GTest::Main pthread)

add_dependencies(tests dp-tests)
