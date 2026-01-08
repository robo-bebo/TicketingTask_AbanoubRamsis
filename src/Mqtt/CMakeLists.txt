# populate the ${SOURCES} variable with all the cpp files in the dir
file(GLOB SOURCES CONFIGURE_DEPENDS "*.cpp")


# create a target for the object files generated from this dir
add_library(mqttClient OBJECT ${SOURCES})

target_include_directories(mqttClient INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/../../include/Mqtt
)

target_link_libraries(mqttClient PRIVATE common)
