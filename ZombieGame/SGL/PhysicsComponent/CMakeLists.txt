set(PhysicsComponentSOURCES
        sgl_physics_component.hpp
        sgl_physics_component.cpp)

add_library(PhysicsComponent ${PhysicsComponentSOURCES})

target_link_libraries()

install(TARGETS PhysicsComponent DESTINATION "${CMAKE_INSTALL_PREFIX}/lib")