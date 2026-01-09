# populate the ${SOURCES} variable with all the cpp files in the dir
file(GLOB SOURCES CONFIGURE_DEPENDS "*.cpp")

# create a target for the object files generated from this dir
add_library(Types OBJECT ${SOURCES})


target_include_directories(Types PRIVATE
    ${PROJECT_INCLUDE_DIR}/LibCommon
    ${PROJECT_INCLUDE_DIR}/LibCommon/Types
)
