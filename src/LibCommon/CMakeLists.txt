
add_library(LibCommon SHARED)

add_subdirectory(BackOfficeInterface)
add_subdirectory(InterprocessCommunication)
add_subdirectory(MqttClient)
add_subdirectory(Types)

target_link_libraries(LibCommon
    PRIVATE
    BackOfficeInterface
    InterprocessCommunication
    MqttClient
    Types
)
