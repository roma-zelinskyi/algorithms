#  Project  Algorithms
#
#  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>

find_package(GTest REQUIRED)

add_executable(tests main.cpp graph-theory/dfs.cpp)

set_target_properties(tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests)

target_include_directories(tests PRIVATE ${GTEST_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(tests PRIVATE ${GTEST_LIBRARIES} pthread)

gtest_add_tests(TARGET tests)
