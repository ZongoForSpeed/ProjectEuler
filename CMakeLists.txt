project(ProjectEuler)

message("Boost_DIR = " ${Boost_DIR})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/install/")
set(Boost_USE_STATIC_LIBS        ON) # only find static libs
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    ON)

cmake_minimum_required(VERSION 3.9)
find_package(Boost 1.58 REQUIRED unit_test_framework date_time)
# find_package(GMP 2.6 REQUIRED)
# find_package(Gperftools)

# Check for standard to use
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

IF (WIN32)
    # set stuff for windows
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "/O2 /Zi")
    set(CMAKE_CXX_FLAGS_RELEASE "/O2 /Ox")
    set(CMAKE_CXX_FLAGS_DEBUG "/Od /Zi")
	add_compile_options(/std:c++17)
ELSE ()
    # set stuff for other systems
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O3 -g")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
    set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")
	add_compile_options(-std=c++17)


    add_compile_options(-Werror -Wall -Wextra -Wpedantic -Weverything
    					-Wno-c++98-compat
    					-Wno-c++98-compat-pedantic
    					-Wno-padded
    					-Wno-global-constructors
    					-Wno-disabled-macro-expansion
    					-Wno-exit-time-destructors
    					-Wno-unused-macros)
ENDIF ()

add_definitions(${Boost_LIB_DIAGNOSTIC_DEFINITIONS})

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
# include_directories(${GMP_INCLUDE_DIR})
include_directories(${Boost_INCLUDE_DIR})
# include_directories(${GPERFTOOLS_INCLUDE_DIR})

include(CheckCXXCompilerFlag)

file(COPY data DESTINATION .)

message("Boost_LIBRARIES = " ${Boost_LIBRARIES})
message("Boost_UNIT_TEST_FRAMEWORK_LIBRARY = " ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
message("Boost_DATE_TIME_LIBRARY = " ${Boost_DATE_TIME_LIBRARY})
# message("GMP_LIBRARIES = " ${GMP_LIBRARIES})
# message("GMP_INCLUDE_DIR = " ${GMP_INCLUDE_DIR})

add_subdirectory(maths)
add_subdirectory(tests)
add_subdirectory(problemes)

add_executable(ProjectEuler euler.cpp)
target_link_libraries(ProjectEuler maths)
target_link_libraries(ProjectEuler problemes)
# target_link_libraries(ProjectEuler ${GMP_LIBRARIES})
target_link_libraries(ProjectEuler ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
target_link_libraries(ProjectEuler ${Boost_DATE_TIME_LIBRARY})
# target_link_libraries(ProjectEuler ${GPERFTOOLS_LIBRARIES})

add_executable(ProjectEulerTest test.cpp)
target_link_libraries(ProjectEulerTest maths)
target_link_libraries(ProjectEulerTest tests)
# target_link_libraries(ProjectEulerTest ${GMP_LIBRARIES})
target_link_libraries(ProjectEulerTest ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
# target_link_libraries(ProjectEulerTest ${GPERFTOOLS_LIBRARIES})
