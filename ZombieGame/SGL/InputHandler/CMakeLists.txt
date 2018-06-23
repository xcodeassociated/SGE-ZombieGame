set(InputHandlerSOURCES
        sgl_input_binder.hpp
        sgl_input_binder.cpp
        sgl_input_handler.hpp
        sgl_input_handler.cpp)

add_library(InputHandler ${InputHandlerSOURCES})

target_link_libraries()

install(TARGETS InputHandelr DESTINATION "${CMAKE_INSTALL_PREFIX}/lib")