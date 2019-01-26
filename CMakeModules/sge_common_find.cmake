## GLEW:
find_package(GLEW REQUIRED)
if (NOT GLEW_FOUND)
    message(Error "GLEW not found!!! ${GLEW_ROOT_DIR}")
endif()

## GLM:
find_package(GLM REQUIRED)
if (NOT GLM_INCLUDE_DIRS)
    message(WARNING "GLM not found! GLM includes may not be found")
else()
    include_directories(${GLM_INCLUDE_DIRS})
endif()