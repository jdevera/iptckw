PROJECT(iptckw)

ADD_EXECUTABLE(iptckw src/optionparser.cpp src/kwimage.cpp src/keywordbag.cpp main.cpp)

target_link_libraries(iptckw exiv2)
