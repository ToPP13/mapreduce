cmake_minimum_required(VERSION 3.2)


if (DEFINED ENV{TRAVIS_BUILD_NUMBER})
    project(mapreduce VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else ()
    project(mapreduce VERSION 0.0.1)
endif ()

# Load settings for an external project.
find_package (Threads REQUIRED)
find_package (Boost COMPONENTS system regex REQUIRED)
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)


# Copy a file to another location and modify its contents.
configure_file(version.h.in version.h)


add_executable(mapreduce mapreduce.cpp mapreducer.cpp filereader.cpp minunique.cpp)
# Add an executable to the project using the specified source files.


# Set propertiess to a target.
set_target_properties(mapreduce PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

# Add include directories to a target.
# CMAKE_BINARY_DIR - The path to the top level of the build tree.
target_include_directories(mapreduce PRIVATE "${CMAKE_BINARY_DIR}" ${Boost_INCLUDE_DIRS})

# Add include directories to the build.

target_link_libraries(mapreduce PRIVATE dl pthread ${Boost_LIBRARIES})

# Add compile options to a target.
if (MSVC)
    target_compile_options(mapreduce PRIVATE
        /W4
    )
else ()    
    target_compile_options(mapreduce PRIVATE
        -Wall -Wextra  -pedantic -Werror
    )
endif()



# Load and run CMake code from a file or module.
install(TARGETS mapreduce RUNTIME DESTINATION bin)

# Set a CMake, cache or environment variable to a given value.
set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT martynovich@protei.ru)

include(CPack)


