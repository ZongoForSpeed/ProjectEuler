project(ProjectEuler)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/install/")

cmake_minimum_required(VERSION 3.5)
find_package(GMP 2.6 REQUIRED)
find_package(Boost 1.58 REQUIRED system thread timer chrono)

# Check for standard to use
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O3 -g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")

add_subdirectory(gtest)

add_compile_options(-Werror -Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-padded -Wno-global-constructors -Wno-exit-time-destructors -Wno-double-promotion -Wno-missing-prototypes -Wno-unused-macros -Wno-weak-vtables)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${GMP_INCLUDE_DIR})
include_directories(${Boost_INCLUDE_DIR})
include_directories(${MPFR_INCLUDES})
include_directories(SYSTEM ${GTEST_INCLUDE_DIRS})

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

add_executable(ProjectEuler ${SOURCE_FILES})
target_link_libraries(ProjectEuler ${GMP_LIBRARIES})
target_link_libraries(ProjectEuler ${Boost_LIBRARIES})
target_link_libraries(ProjectEuler ${MPFR_LIBRARIES})

add_executable(ProjectEulerTest ${TEST_FILES})
add_dependencies(ProjectEulerTest googletest)
target_link_libraries(ProjectEulerTest ${GTEST_LIBS_DIR}/libgtest.a ${GTEST_LIBS_DIR}/libgtest_main.a)
target_link_libraries(ProjectEulerTest -lpthread -lm)
target_link_libraries(ProjectEulerTest ${GMP_LIBRARIES})
target_link_libraries(ProjectEulerTest ${Boost_LIBRARIES})