cmake_minimum_required(VERSION 3.10)

# set the project name
project(TicketingSystem VERSION 1.0)

# set the two variables for cpp 17 required
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(PROJECT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(TEST_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tests/src)
set(TEST_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tests/include)

#this library is used to hold all thirdParty libraries.
add_library(thirdParty INTERFACE)

#append here any lib that needs to be linked to more than one target
target_link_libraries(thirdParty INTERFACE
    pthread
    ssl
    crypto
    mosquitto
    pugixml
)

#User options
option(BUILD_APP "Build the main application" OFF)
option(BUILD_TESTS "Build unit tests" OFF)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_subdirectory(src)

#add_subdirectory(tests)




