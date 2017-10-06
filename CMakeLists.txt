project(ProjectEuler)

cmake_minimum_required(VERSION 3.5)
find_package(GMP 2.6 REQUIRED)
find_package(MPFR 3.1 REQUIRED)
find_package(Boost 1.58 REQUIRED system thread timer chrono)

include(CheckCXXCompilerFlag)

# Check for standard to use
check_cxx_compiler_flag(-std=c++17 HAVE_FLAG_STD_CXX17)
if(HAVE_FLAG_STD_CXX17)
	MESSAGE( STATUS "HAVE_FLAG_STD_CXX17"  )
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
else()
    check_cxx_compiler_flag(-std=c++1z HAVE_FLAG_STD_CXX1Z)
    if(HAVE_FLAG_STD_CXX1Z)
    	MESSAGE( STATUS "HAVE_FLAG_STD_CXX1Z"  )
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z")
        # Have -std=c++1z, use it
    else()
    	set(CMAKE_CXX_STANDARD 14)
        # And so on and on...
    endif()
endif()


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-padded -Wno-global-constructors -Wno-exit-time-destructors -Wno-double-promotion -Wno-missing-prototypes -Wno-unused-macros")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O3 -g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${GMP_INCLUDE_DIR})
include_directories(${Boost_INCLUDE_DIR})
include_directories(${MPFR_INCLUDES})

set(LIBRARY_FILES
        arithmetiques.h
        chiffres.h
        combinatoire.h
        diophantienne.cpp
        diophantienne.h
        graphe.cpp
        graphe.h
        matrice.h
        multidimension.h
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

set(TEST_FILES
        test.cpp
        test/arithmetiques.cpp
        test/chiffres.cpp
        test/combinatoire.cpp
        test/diophantienne.cpp
        test/matrice.cpp
        test/mp_nombre.cpp
        test/multidimension.cpp
        test/polygonal.cpp
        test/polynome.cpp
        test/premiers.cpp
        test/puissance.cpp
        test/pythagoricien.cpp
        test/utilitaires.cpp
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
add_executable(ProjectEulerTest ${TEST_FILES})

target_link_libraries(ProjectEuler ${GMP_LIBRARIES} ${Boost_LIBRARIES} ${MPFR_LIBRARIES})
target_link_libraries(ProjectEulerTest ${GMP_LIBRARIES} ${Boost_LIBRARIES} ${MPFR_LIBRARIES})
