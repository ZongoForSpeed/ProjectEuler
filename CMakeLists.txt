project(ProjectEuler)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/install/")
set(Boost_USE_STATIC_LIBS        ON) # only find static libs
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    ON)

cmake_minimum_required(VERSION 3.9)
find_package(Boost 1.58 REQUIRED unit_test_framework date_time)
find_package(GMP 2.6 REQUIRED)

# Check for standard to use
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O3 -g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")

IF (WIN32)
    # set stuff for windows
    # set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "/O2 -g")
    set(CMAKE_CXX_FLAGS_RELEASE "/O2 /Ox")
    set(CMAKE_CXX_FLAGS_DEBUG "/Od")
ELSE ()
    # set stuff for other systems
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O3 -g")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
    set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")

    add_compile_options(-Werror
            -Weverything
            -Wno-c++98-compat
            -Wno-c++98-compat-pedantic
            -Wno-padded
            -Wno-global-constructors
            -Wno-exit-time-destructors
            -Wno-weak-vtables)
ENDIF ()

add_definitions(${Boost_LIB_DIAGNOSTIC_DEFINITIONS})

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${GMP_INCLUDE_DIR})
include_directories(${Boost_INCLUDE_DIR})

include(CheckCXXCompilerFlag)

set(LIBRARY_FILES
        arithmetiques.h
        chiffres.h
        combinatoire.h
        diophantienne.cpp
        diophantienne.h
        fenwick.h
        graphe.cpp
        graphe.h
        matrice.h
        multidimension.h
        permutation.h
        polygonal.h
        polynome.h
        premiers.cpp
        premiers.h
        puissance.h
        pythagoricien.cpp
        pythagoricien.h
        timer.cpp
        timer.h
        mp_nombre.cpp
        mp_nombre.h
        utilitaires.h)

file(COPY data
        DESTINATION .)

FILE(GLOB TEST_WILDCARD test/*.cpp)
set(TEST_FILES
        test.cpp
        test/test.h
        ${TEST_WILDCARD}
        ${LIBRARY_HEADERS}
        ${LIBRARY_FILES})

aux_source_directory(probleme0xx PROBLEME_0XX)
aux_source_directory(probleme1xx PROBLEME_1XX)
aux_source_directory(probleme2xx PROBLEME_2XX)
FILE(GLOB PROBLEME_YYY probleme*.cpp)

set(PROBLEMES_FILES
        ${PROBLEME_0XX}
        ${PROBLEME_1XX}
        ${PROBLEME_2XX}
        ${PROBLEME_YYY})

set(SOURCE_FILES
        problemes.h
        problemes.cpp
        euler.cpp
        ${LIBRARY_FILES}
        ${PROBLEMES_FILES})

message("Boost_LIBRARIES = " ${Boost_LIBRARIES})

message("Boost_UNIT_TEST_FRAMEWORK_LIBRARY = " ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
message("Boost_DATE_TIME_LIBRARY = " ${Boost_DATE_TIME_LIBRARY})

message("GMP_LIBRARIES = " ${GMP_LIBRARIES})
message("GMP_INCLUDE_DIR = " ${GMP_INCLUDE_DIR})

add_executable(ProjectEuler ${SOURCE_FILES})
target_link_libraries(ProjectEuler ${GMP_LIBRARIES})
target_link_libraries(ProjectEuler ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
target_link_libraries(ProjectEuler ${Boost_DATE_TIME_LIBRARY})

add_executable(ProjectEulerTest ${TEST_FILES})
target_link_libraries(ProjectEulerTest ${GMP_LIBRARIES})
target_link_libraries(ProjectEulerTest ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})