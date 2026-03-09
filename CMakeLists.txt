cmake_minimum_required(VERSION 3.28.3)

project(lists)

set(LIST_SRCS
    src/list/list.c
)

set(LIST_HDRS_PATH
    inc/
)

add_library(lists ${LIST_SRCS})

target_include_directories(lists PUBLIC ${LIST_HDRS_PATH})

set(SOURCES
    src/main.c
)

add_executable(app ${SOURCES})
target_link_libraries(app lists)