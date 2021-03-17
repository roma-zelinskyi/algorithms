# Project  Algorithms
#
# @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>

find_package(GTest REQUIRED)

add_custom_target(tests
    COMMAND ${CMAKE_COMMAND} -E env ./tests
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/tests
)

set_target_properties(tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                                       ${CMAKE_BINARY_DIR}/tests)

add_subdirectory(graph-theory)
add_subdirectory(dp)
