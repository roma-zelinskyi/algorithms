# Project  Algorithms
#
# @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>

find_package(GTest REQUIRED)

add_executable(
  tests
  main.cpp graph-theory/traversal_unittest.cpp
  graph-theory/top_sort_unittest.cpp graph-theory/sssp_dag_unittest.cpp
  graph-theory/dijkstra_unittest.cpp
  graph-theory/bellman_ford_unittest.cpp
  graph-theory/edge_iterator_unittest.cpp
  graph-theory/floyd_warshall_unittest.cpp
  graph-theory/find_bridges.cpp)

set_target_properties(tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                                       ${CMAKE_BINARY_DIR}/tests)

target_include_directories(tests PRIVATE ${GTEST_INCLUDE_DIRS}
                                         ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(tests PRIVATE ${GTEST_LIBRARIES} pthread)

gtest_add_tests(TARGET tests)
