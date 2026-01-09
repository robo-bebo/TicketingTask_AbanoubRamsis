# populate the ${SOURCES} variable with all the cpp files in the dir
file(GLOB SOURCES CONFIGURE_DEPENDS "*.cpp")

# create a target for the object files generated from this dir
add_executable(BackOffice ${SOURCES})


target_include_directories(BackOffice INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/../../include/BackOffice
)

target_link_libraries(BackOffice PRIVATE common CommonTypes InterprocessCommunication)
