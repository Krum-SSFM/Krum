cmake_minimum_required(VERSION 3.20)
project(Krum)
set(CMAKE_CXX_STANDARD 17)

set(LIBS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/libs)

macro(add_sub_dir_if_exists dir)
	if(IS_DIRECTORY ${dir})
		add_subdirectory(${dir})
	endif()
endmacro()

macro(add_all_libs_as_sub_dir)
	file(GLOB LIBS_DIRECTORIES RELATIVE ${LIBS_DIRECTORY} ${LIBS_DIRECTORY}/*)

	foreach(subdir ${LIBS_DIRECTORIES})
		add_sub_dir_if_exists(${LIBS_DIRECTORY}/${subdir})
	endforeach()
endmacro(add_all_libs_as_sub_dir)

if(UNIX AND NOT WIN32 AND CMAKE_BUILD_TYPE MATCHES Debug)
	set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -fsanitize=address -fno-omit-frame-pointer")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address -fno-omit-frame-pointer")
endif()

file(GLOB_RECURSE SOURCE_FILES src/*.cpp)

add_executable(Krum ${SOURCE_FILES})

add_all_libs_as_sub_dir()

target_include_directories(Krum PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${LIBS_DIRECTORY}/CppBinaryStream/include
	${LIBS_DIRECTORY}/RakNet/include
	${LIBS_DIRECTORY}/stduuid/include
	${LIBS_DIRECTORY}/spdlog/include
)

target_link_libraries(Krum PRIVATE
	BinaryStream
	RakNetLibStatic
	stduuid
	spdlog
)
