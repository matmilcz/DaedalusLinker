cmake_minimum_required(VERSION 3.15.2)

project(dLinker)

link_libraries("-static")

set(CMAKE_CXX_STANDARD 17)

find_package(Boost 1.69 COMPONENTS program_options REQUIRED)

set(project_main "dLinker.cpp")
set(src_dir "src")
set(inc_dir "inc")

add_executable(${PROJECT_NAME} "${src_dir}/${project_main}")
target_link_libraries(${PROJECT_NAME} PRIVATE Boost::program_options 
                                              -lboost_filesystem 
                                              DaedalusLinker 
                                              FilePathExtractor 
                                              Utils)

include_directories(PUBLIC ${inc_dir})

add_library(DaedalusLinker STATIC "${src_dir}/DaedalusLinker.cpp" 
                                  "${src_dir}/DaedalusLinkerBase.cpp"
                                  "${src_dir}/DaedalusLinkerWithComments.cpp"
                                  "${src_dir}/DaedalusLinkerWithoutComments.cpp")
target_link_libraries(DaedalusLinker PRIVATE Boost::program_options -lboost_filesystem)

add_library(FilePathExtractor STATIC "${src_dir}/FilePathExtractor.cpp")
target_link_libraries(FilePathExtractor PRIVATE Boost::program_options -lboost_filesystem)

add_library(Utils STATIC "${src_dir}/GlobalFlagsContainer.cpp")


# ==== GTEST ====

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
  include_directories("${gtest_SOURCE_DIR}/include")
endif()


set(GTestName "ut")
set(ut_dir "ut")
set(unit_test_main "${ut_dir}/ut.cpp")

add_executable(${GTestName} ${unit_test_main} 
                            "${ut_dir}/TestGlobalFlagsContainer/TestGlobalFlagsContainer.cpp"
                            "${ut_dir}/TestFilePathExtractor/TestFilePathExtractor.cpp")
target_link_libraries(${GTestName} PRIVATE gtest_main
                                           gmock_main
                                           Boost::program_options 
                                           -lboost_filesystem
                                           Utils
                                           FilePathExtractor)