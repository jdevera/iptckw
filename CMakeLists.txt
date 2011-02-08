PROJECT( iptckw )

SET( iptckw_SRCS src/optionparser.cpp src/kwimage.cpp src/keywordbag.cpp main.cpp )

ADD_EXECUTABLE( iptckw ${iptckw_SRCS} )

target_link_libraries( iptckw exiv2 boost_program_options )

