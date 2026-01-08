# populate the ${SOURCES} variable with all the cpp files in the dir
file(GLOB SOURCES CONFIGURE_DEPENDS "*.cpp")

# create a target for the object files generated from this dir
add_executable(CommonTypes ${SOURCES})


target_include_directories(CommonTypes INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include/CommonTypes
)

target_link_libraries(CommonTypes PRIVATE common)
