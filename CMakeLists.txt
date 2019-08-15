cmake_minimum_required(VERSION 3.15.2)

project(DaedalusLinker)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost 1.69 COMPONENTS program_options REQUIRED)

file(GLOB source
    "main.cpp"
    "src/*cpp"
    "inc/*.hpp")

add_executable(${PROJECT_NAME} ${source})

target_link_libraries(${PROJECT_NAME} Boost::program_options -lboost_filesystem)
