set(DirectorSOURCES
        sgl_director.hpp
        sgl_director.cpp)

add_library(Director ${DirectorSOURCES})

target_link_libraries()

install(TARGETS Director DESTINATION "${CMAKE_INSTALL_PREFIX}/lib")