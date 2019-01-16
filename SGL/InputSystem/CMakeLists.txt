set(InputSystemSOURCES
        InputSystem.hpp
        InputSystem.cpp)
        
add_library(InputSystem ${InputSystemSOURCES})

target_link_libraries(InputSystem 
        InputBinder
        IO)

install(TARGETS InputSystem DESTINATION "${CMAKE_INSTALL_PREFIX}/lib")
