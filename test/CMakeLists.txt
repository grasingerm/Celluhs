cmake_minimum_required(VERSION 2.8)

project(Celluhs)

set(CC clang)
set(CSTD c11)

# set flags for warnings, errors, and standards
if( NOT CMAKE_BUILD_TYPE )
  set( CMAKE_BUILD_TYPE release CACHE STRING
       "Choose the type of build, options are: None Debug Release RelWithDebInfo
        MinSizeRel."
       FORCE )
endif()

set(CMAKE_C_FLAGS_DEBUG "-Wall -Wextra -g -std=${CSTD} -pedantic -pedantic-errors")
set(CMAKE_C_FLAGS_RELEASE "-Wall -Wextra -std=${CSTD} -pedantic -pedantic-errors -O3")

# build directories
set(CMAKE_BINARY_DIR build)
set(EXECUTABLE_OUTPUT_PATH bin)

# include and link directories
include_directories(../include)

# dependencies
add_executable(test_m_elem_at test_m_elem_at.c ../src/grid.c)
add_executable(test_format_fs test_format_fs.c ../src/grid.c ../src/formats.c)
add_executable(test_fredkin test_fredkin.c ../src/grid.c ../src/formats.c ../src/rules.c)
# add_executable(test_rules test_rules.c ../src/grid.c)

target_link_libraries(test_m_elem_at profiler)
target_link_libraries(test_format_fs profiler)
target_link_libraries(test_fredkin profiler)
