set(DirectorSOURCES
        Director.hpp
        Director.cpp)

add_library(Director ${DirectorSOURCES})
install(TARGETS Director DESTINATION "${CMAKE_INSTALL_PREFIX}/lib")
