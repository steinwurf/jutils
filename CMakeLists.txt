cmake_minimum_required(VERSION 3.12)
project(jutils)

if(NOT DEFINED STEINWURF_TOP_NAME)
  set(STEINWURF_TOP_NAME jutils)
endif()

# Define library
file(GLOB_RECURSE jutils_sources ./src/*.cpp)

# Is this the top-level steinwurf project?
if(${PROJECT_NAME} STREQUAL ${STEINWURF_TOP_NAME})
  # Create static library
  add_library(jutils STATIC ${jutils_sources})
  # Install library
  install(FILES $<TARGET_FILE:jutils> DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
else()
  # Create object library
  add_library(jutils OBJECT ${jutils_sources})
  # Add this library to a global list of steinwurf object libraries
  set_property(GLOBAL APPEND PROPERTY steinwurf::object_libraries
                                      steinwurf::jutils)
endif()

target_include_directories(jutils INTERFACE src)

target_link_libraries(jutils INTERFACE log)

target_compile_features(jutils PUBLIC cxx_std_14)
add_library(steinwurf::jutils ALIAS jutils)

# Install headers excluding "detail" as these are internal to the library.
install(
  DIRECTORY ./src/jutils
  DESTINATION ${CMAKE_INSTALL_PREFIX}/include
  FILES_MATCHING
  PATTERN *.hpp
  PATTERN ./src/jutils/detail EXCLUDE)

# Is top level project?
if(${CMAKE_PROJECT_NAME} STREQUAL ${PROJECT_NAME})
  enable_testing()
  # Google Test dependency
  add_subdirectory("${STEINWURF_RESOLVE}/gtest-source" gtest EXCLUDE_FROM_ALL)
  
  # Build test executable
  file(GLOB_RECURSE jutils_test_sources ./test/*.cpp)
  add_executable(jutils_test  ${otacast_test_sources})
  target_link_libraries(jutils_test jutils)
  target_link_libraries(jutils_test gtest)

  add_test(jutils_test jutils_test)

endif()
