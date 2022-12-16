cmake_minimum_required(VERSION 3.18)

project(AdventOfCode)

find_program(CLANG_TIDY_EXE "clang-tidy")
set(CLANG_TIDY_COMMAND "${CLANG_TIDY_EXE}" "-checks=-*,clang-analyzer-*,cppcoreguidelines-*,clang-analyzer-cplusplus-*")
set(HAS_CLANG_TIDY 1)

if ("${CLANG_TIDY_COMMAND}" MATCHES ".NOTFOUND")
	set(HAS_CLANG_TIDY 0)
endif()

set(CMAKE_CXX_STANDARD 20)
if (WIN32)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /WX /W3")
else()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wall -pedantic")# -fsanitize=address") does not work on alpine docker
endif()

function(addLib name)
	file(GLOB sources ${name}/src/*.cpp)
	file(GLOB headers ${name}/include/${name}/*.h)

	add_library(${name} ${sources} ${headers})
	target_include_directories(${name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/${name}/include/)
	
	if (${HAS_CLANG_TIDY} EQUAL 1)
		set_target_properties(${name} PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_COMMAND}")
	endif()
endfunction()

addLib(Days)
addLib(frwk)

add_executable(App main.cpp)
target_link_libraries(App Days frwk)
if (${HAS_CLANG_TIDY} EQUAL 1)
	set_target_properties(App PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_COMMAND}")
endif()
