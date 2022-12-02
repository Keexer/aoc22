cmake_minimum_required(VERSION 3.18)

project(AdventOfCode)

set(CMAKE_CXX_STANDARD 17)

function(addLib name)
	file(GLOB sources ${name}/src/*.cpp)
	file(GLOB headers ${name}/include/${name}/*.h)

	add_library(${name} ${sources} ${headers})
	target_include_directories(${name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/${name}/include/)
endfunction()

addLib(Days)
addLib(frwk)

add_executable(App main.cpp)
target_link_libraries(App Days frwk)