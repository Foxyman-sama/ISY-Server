cmake_minimum_required (VERSION 3.8)
project (ISY)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 23)

set(HEADERS
	include/network/acceptor.hpp	
	include/system/handler.hpp	
	include/network/data.hpp	
	include/network/reader.hpp	
	include/system/system.hpp	
	include/libs.hpp
	include/network/writer.hpp)	
set(SOURCES
	src/network/acceptor.cpp
	src/system/handler.cpp	
	src/network/reader.cpp	
	src/system/system.cpp
	src/network/writer.cpp)		

find_package(Boost REQUIRED)

add_executable(ISY 
	main.cpp 
	${HEADERS}
	${SOURCES})
target_include_directories(ISY PUBLIC
	include
	${Boost_INCLUDE_DIRS})
target_link_libraries(ISY PUBLIC
	${Boost_LIBRARIES})
target_compile_definitions(ISY PUBLIC
	_WIN32_WINNT=0x0601)