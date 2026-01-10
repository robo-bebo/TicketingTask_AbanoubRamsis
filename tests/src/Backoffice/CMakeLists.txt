# populate the ${SOURCES} variable with all the cpp files in the dir
file(GLOB SOURCES CONFIGURE_DEPENDS "*.cpp")

# create a target for the object files generated from this dir
add_executable(BackofficeTests ${SOURCES})


target_include_directories(BackofficeTests PRIVATE
    ${PROJECT_INCLUDE_DIR}/LibCommon
    ${PROJECT_INCLUDE_DIR}/BackOffice
    ${TEST_INCLUDE_DIR}
)

target_link_libraries(BackofficeTests PRIVATE LibCommon Database)

