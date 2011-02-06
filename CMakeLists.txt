PROJECT(iptckw)

ADD_EXECUTABLE(iptckw src/optionparser.cpp src/kwimage.cpp src/keywordbag.cpp main.cpp)

target_link_libraries(iptckw exiv2 boost_program_options)
add_definitions(-pg -g)

SET(CMAKE_EXE_LINKER_FLAGS "-pg -g")
