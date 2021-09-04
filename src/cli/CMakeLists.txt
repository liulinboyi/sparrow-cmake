aux_source_directory(./ "CLI")

add_library(cli STATIC ${CLI})


# include_directories(../cli)
# include_directories(../compiler)
# include_directories(../gc)
# include_directories(../include)
# include_directories(../object)
# include_directories(../parser)
# include_directories(../vm)

# add_executable(cli ${CLI})
# set(CMAKE_CXX_FLAGS "-g -lm -Wall -I src/vm/ -I src/object/ -I src/compiler/ -I src/parser/ -I src/include/ -I src/cli/ -I src/gc/ -W -Wstrict-prototypes -Wmissing-prototypes -Wsystem-headers -fgnu89-inline")
# target_link_libraries(cli object include compiler parser gc vm m)
