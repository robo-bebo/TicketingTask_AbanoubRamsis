# populate the ${SOURCES} variable with all the cpp files in the dir
file(GLOB SOURCES CONFIGURE_DEPENDS "*.cpp")

# create a target for the object files generated from this dir
add_library(InterprocessCommunication OBJECT ${SOURCES})


target_include_directories(InterprocessCommunication INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include/InterprocessCommunication
)

target_link_libraries(InterprocessCommunication PRIVATE common)