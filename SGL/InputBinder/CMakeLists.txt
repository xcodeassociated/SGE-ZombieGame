set(InputBinderSOURCES
        sgl_input_binder.hpp
        sgl_input_binder.cpp)
        
add_library(InputBinder ${InputBinderSOURCES})
install(TARGETS InputBinder DESTINATION "${CMAKE_INSTALL_PREFIX}/lib")

if(WIN32)
	include(GenerateExportHeader)
	generate_export_header(Control EXPORT_FILE_NAME ${CMAKE_BINARY_DIR}/exports/input_binder_export.h)
endif()