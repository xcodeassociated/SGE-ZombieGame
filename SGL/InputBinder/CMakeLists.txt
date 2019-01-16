set(InputBinderSOURCES
        sgl_input_binder.hpp
        sgl_input_binder.cpp)
        
add_library(InputBinder ${InputBinderSOURCES})
install(TARGETS InputBinder DESTINATION "${CMAKE_INSTALL_PREFIX}/lib")
