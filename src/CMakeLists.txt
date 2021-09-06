cmake_minimum_required(VERSION 2.8)
project(spr)


#set(CMAKE_C_COMPILER "gcc")
#set(CMAKE_CXX_COMPILER "g++")

#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
#set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -fgnu89-inline -g -O3 -W -Wall -DDEBUG")
#set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -fgnu89-inline -g -O3 -W -Wall")
set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -fgnu89-inline -g -W -Wall")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fgnu89-inline -g -O3 -W -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fgnu89-inline -g -W -Wall")

message(STATUS "CMAKE_C_COMPILER = ${CMAKE_C_COMPILER}")
message(STATUS "CMAKE_CXX_COMPILER = ${CMAKE_CXX_COMPILER}")
message(STATUS "CMAKE_AR = ${CMAKE_AR}")
message(STATUS "CMAKE_RANLIB = ${CMAKE_RANLIB}")
message(STATUS "CMAKE_ASM_COMPILER = ${CMAKE_ASM_COMPILER}")
message(STATUS "CMAKE_LINKER = ${CMAKE_LINKER}")
message(STATUS "CMAKE_NM = ${CMAKE_NM}")
message(STATUS "CMAKE_OBJCOPY = ${CMAKE_OBJCOPY}")
message(STATUS "CMAKE_OBJDUMP = ${CMAKE_OBJDUMP}")
message(STATUS "CMAKE_STRIP = ${CMAKE_STRIP}")
message(STATUS "CMAKE_CXX_FLAGS = ${CMAKE_CXX_FLAGS}")
message(STATUS "CMAKE_C_FLAGS = ${CMAKE_C_FLAGS}")

enable_testing()

#测试暂时放下
#file(COPY ./test/testing_files DESTINATION test)
#add_subdirectory(./test)

# add_subdirectory(./cli)
# add_subdirectory(./compiler)
# add_subdirectory(./gc)
# add_subdirectory(./include)
# add_subdirectory(./object)
# add_subdirectory(./parser)
# add_subdirectory(./vm)

# SET(CMAKE_INCLUDE_PATH "include_path") # find_path，查找头文件

include_directories(./cli)
include_directories(./compiler)
include_directories(./gc)
include_directories(./include)
include_directories(./object)
include_directories(./parser)
include_directories(./vm)


aux_source_directory(./cli "CLI")
add_library(cli STATIC ${CLI})

aux_source_directory(./compiler "COMPLIER")
add_library(compiler STATIC ${COMPLIER})

aux_source_directory(./gc "GC")
add_library(gc STATIC ${GC})

aux_source_directory(./include "INCLUDE")
add_library(include STATIC ${INCLUDE})

aux_source_directory(./object "OBJECT")
add_library(object STATIC ${OBJECT})

aux_source_directory(./parser "PARSER")
add_library(parser STATIC ${PARSER})

aux_source_directory(./vm "VM")
add_library(vm STATIC ${VM})

# aux_source_directory(./cli "SPR")
add_executable(${PROJECT_NAME} ${VM} ${PARSER} ${OBJECT} ${INCLUDE} ${GC} ${COMPLIER} ${CLI})
# target_link_libraries(object include cli compiler parser vm gc)

target_link_libraries(${PROJECT_NAME} m)
