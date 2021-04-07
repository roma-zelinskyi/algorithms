# Project  Algorithms
#
# @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>

add_executable(
  graph-theory-tests
  traversal_unittest.cpp
  top_sort_unittest.cpp sssp_dag_unittest.cpp
  dijkstra_unittest.cpp
  bellman_ford_unittest.cpp
  edge_iterator_unittest.cpp
  floyd_warshall_unittest.cpp
  find_bridges.cpp
)

target_include_directories(graph-theory-tests PRIVATE ${GTEST_INCLUDE_DIRS}
                                         ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(graph-theory-tests PRIVATE GTest::GTest GTest::Main pthread)

add_test(
    NAME graph-theory-tests
    COMMAND graph-theory-tests
)
