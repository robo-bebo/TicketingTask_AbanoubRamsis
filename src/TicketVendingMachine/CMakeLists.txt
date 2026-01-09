# populate the ${SOURCES} variable with all the cpp files in the dir
file(GLOB SOURCES CONFIGURE_DEPENDS "*.cpp")

# create a target for the object files generated from this dir
add_executable(VendingMachine ${SOURCES})


target_include_directories(VendingMachine INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include/TicketVendingMachine
)

target_link_libraries(VendingMachine PRIVATE common mqttClient CommonTypes InterprocessCommunication)
