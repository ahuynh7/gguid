cmake_minimum_required(VERSION 3.10)

project("gguid" VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add source to this project's executable.
add_executable(gguid "gguid.cpp" "gguid.h" )

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET gguid PROPERTY CXX_STANDARD 20)
endif()

#set preprocessor definition based on platform
if (WIN32)
  target_compile_definitions(gguid PRIVATE _WIN32)

elseif(APPLE)

else()
    target_compile_definitions(gguid PRIVATE _LIBUUID)

endif()

#add subdirectories
add_subdirectory(CLI11)
target_link_libraries(gguid CLI11::CLI11)
