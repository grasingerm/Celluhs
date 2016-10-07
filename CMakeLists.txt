cmake_minimum_required(VERSION 2.8)

project(Celluhs)

# set flags for warnings, errors, and standards
if( NOT CMAKE_BUILD_TYPE )
  set( CMAKE_BUILD_TYPE release CACHE STRING
       "Choose the type of build, options are: None Debug Release RelWithDebInfo
        MinSizeRel."
       FORCE )
endif()

set(CMAKE_C_FLAGS_DEBUG "-Wall -Wextra -g -pedantic -pedantic-errors")
set(CMAKE_C_FLAGS_RELEASE "-Wall -Wextra -pedantic -pedantic-errors -O3")

# use OpenMP if compiler supports it
#find_package(OpenMP)
#if (OPENMP_FOUND)
#  set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
#  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
#endif()

# build directories
set(CMAKE_BINARY_DIR build)
set(LIBRARY_OUTPUT_PATH lib)
set(EXECUTABLE_OUTPUT_PATH bin)

# include and link directories
include_directories(include)

file(GLOB libsources "src/*.c" "include/*.h")

add_library(celluhs SHARED ${libsources})
add_executable(test_m_elem_at test/test_m_elem_at.c)
add_executable(test_format_fs test/test_format_fs.c)
add_executable(test_fredkin test/test_fredkin.c)
add_executable(test_conway test/test_conway.c)

target_link_libraries(test_m_elem_at celluhs)
target_link_libraries(test_format_fs celluhs)
target_link_libraries(test_fredkin celluhs)
target_link_libraries(test_conway celluhs)
