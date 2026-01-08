cmake_minimum_required(VERSION 3.10)

# set the project name
project(TicketingSystem VERSION 1.0)

# set the two variables for cpp 17 required
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#this library is used to hold all common includes and libraries.
add_library(common INTERFACE)
#append here any dir need to be included in more that one subdir
target_include_directories(common INTERFACE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    #${CMAKE_CURRENT_SOURCE_DIR}/thirdParty
)
#append here any lib that needs to be linked to more than one target
target_link_libraries(common INTERFACE
    pthread
    ssl
    crypto
    mosquitto
)

#User options
option(BUILD_APP "Build the main application" OFF)
option(BUILD_TESTS "Build unit tests" OFF)


add_subdirectory(src)




 