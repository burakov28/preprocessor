cmake_minimum_required(VERSION 3.16)
project(preprocessor)

set(CMAKE_CXX_STANDARD 14)

add_definitions(-DCMD="cmd")

set(SOURCES
		main.cpp
		simple-definitions.cpp
		argumented-definitions.cpp
		)

set(HEADERS
		simple-definitions.h
		argumented-definitions.h
		abacaba.h
		)
add_executable(preprocessor ${SOURCES} ${HEADERS})
