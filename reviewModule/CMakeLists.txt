file(GLOB_RECURSE SOURCES "*.cpp" "*.hpp")

add_library(review-module SHARED ${SOURCES})
target_link_libraries(review-module LINK_PRIVATE sc-memory)

target_include_directories(review-module PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})