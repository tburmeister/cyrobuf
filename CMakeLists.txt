cmake_minimum_required(VERSION 2.8.0)
project(cyrobuf C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(${PROJECT_SOURCE_DIR}/out)
include_directories(${PROJECT_SOURCE_DIR}/cyrobuf/src)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99")

file(GLOB CYROBUF_SRC
	${PROJECT_SOURCE_DIR}/out/*.c
	${PROJECT_SOURCE_DIR}/cyrobuf/src/*.c
)

add_executable(deserialize_perf
	${CYROBUF_SRC}
	${PROJECT_SOURCE_DIR}/tests/deserialize_perf.c
)

add_executable(serialize_perf
	${CYROBUF_SRC}
	${PROJECT_SOURCE_DIR}/tests/serialize_perf.c
)

