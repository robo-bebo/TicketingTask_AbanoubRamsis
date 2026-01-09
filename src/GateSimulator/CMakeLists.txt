# populate the ${SOURCES} variable with all the cpp files in the dir
file(GLOB SOURCES CONFIGURE_DEPENDS "*.cpp")

# create a target for the object files generated from this dir
add_executable(GateSimulator ${SOURCES})


target_include_directories(GateSimulator PRIVATE
    ${PROJECT_INCLUDE_DIR}/GateSimulator
    ${PROJECT_INCLUDE_DIR}/LibCommon
)

target_link_libraries(GateSimulator PRIVATE thirdParty LibCommon)
