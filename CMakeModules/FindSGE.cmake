## FindSGE version 0.1 -- this is not the final bersion of this module. Temporary solution.

if (NOT SGE_ROOT)
    message(ERROR "SGE_ROOT not specified!")
endif()

set(SGE_INCLUDE_DIR "${SGE_ROOT}/include")
set(SGE_LIBRARY_DIR "${SGE_ROOT}/lib")
set(SGE_FOUND ON)

find_library(SGE_CAMERA2D_LIB NAMES IO PATHS ${SGE_LIBRARY_DIR})
if (NOT SGE_IO_LIB)
    message(WARNING "Cannot find SGE lib!")
    set(SGE_FOUND OFF)
endif()

find_library(SGE_IO_LIB NAMES IO PATHS ${SGE_LIBRARY_DIR})
if (NOT SGE_IO_LIB)
    message(WARNING "Cannot find SGE lib!")
    set(SGE_FOUND OFF)
endif()

find_library(SGE_SPRITE_LIB NAMES IO PATHS ${SGE_LIBRARY_DIR})
if (NOT SGE_IO_LIB)
    message(WARNING "Cannot find SGE lib!")
    set(SGE_FOUND OFF)
endif()

find_library(SGE_PicoPNG_LIB NAMES PicoPNG PATHS ${SGE_LIBRARY_DIR})
if (NOT SGE_PicoPNG_LIB)
    message(WARNING "Cannot find SGE lib!")
    set(SGE_FOUND OFF)
endif()

find_library(SGE_RENDERSYSTEM_LIB NAMES Renderer PATHS ${SGE_LIBRARY_DIR})
if (NOT SGE_RENDERER_LIB)
    message(WARNING "Cannot find SGE lib!")
    set(SGE_FOUND OFF)
endif()

find_library(SGE_UTILS_LIB NAMES Utils PATHS ${SGE_LIBRARY_DIR})
if (NOT SGE_UTILS_LIB)
    message(WARNING "Cannot find SGE lib!")
    set(SGE_FOUND OFF)
endif()

if (SGE_FOUND)
    set(SGE_LIBRARIES "${SGE_CAMERA2D_LIB};${SGE_IO_LIB};${SGE_SPRITE_LIB};${SGE_UTILS_LIB};${SGE_PicoPNG_LIB};${SGE_RENDERSYSTEM_LIB}")
endif()
