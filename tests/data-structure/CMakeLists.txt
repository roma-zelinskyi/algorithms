# Project  Algorithms
#
# @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>

add_executable(
  data-structure-tests
  trie_unittests.cpp
)

target_include_directories(data-structure-tests PRIVATE ${GTEST_INCLUDE_DIRS}
                                         ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(data-structure-tests PRIVATE GTest::GTest GTest::Main pthread)

add_test(
    NAME data-structure-tests
    COMMAND data-structure-tests
)
