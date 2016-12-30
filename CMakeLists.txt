project(ProjectEuler)

cmake_minimum_required(VERSION 3.6)
find_package(GMP REQUIRED)
find_package(Boost 1.58 REQUIRED system thread timer chrono)

set(CMAKE_CXX_STANDARD 14)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${GMP_INCLUDE_DIR})
include_directories(${Boost_INCLUDE_DIR})

set(LIBRARY_FILES
        arithmetiques.cpp
        arithmetiques.h
        chiffres.h
        combinatoire.h
        diophantienne.h
        graphe.cpp
        graphe.h
        nombre.h
        nombre.cpp
        matrice.h
        multidimension.h
        polygonal.h
        polynome.h
        premiers.cpp
        premiers.h
        problemes.cpp
        problemes.h
        puissance.h
        pythagoricien.cpp
        pythagoricien.h
        timer.cpp
        timer.h
        utilitaires.cpp
        utilitaires.h)

set(TEST_FILES
        test.cpp
        test/arithmetiques.cpp
        test/chiffres.cpp
        test/combinatoire.cpp
        test/diophantienne.cpp
        test/matrice.cpp
        test/multidimension.cpp
        test/polygonal.cpp
        test/polynome.cpp
        test/premiers.cpp
        test/puissance.cpp
        test/pythagoricien.cpp
        test/utilitaires.cpp
        ${LIBRARY_FILES})

aux_source_directory(probleme0xx PROBLEME_0XX)
aux_source_directory(probleme1xx PROBLEME_1XX)
aux_source_directory(probleme2xx PROBLEME_2XX)

set(PROBLEMES_FILES
        ${PROBLEME_0XX}
        ${PROBLEME_1XX}
        ${PROBLEME_2XX}
        probleme300.cpp
        probleme301.cpp
        probleme302.cpp
        probleme303.cpp
        probleme304.cpp
        probleme305.cpp
        probleme306.cpp
        probleme307.cpp
        probleme308.cpp
        probleme309.cpp
        probleme310.cpp
        probleme311.cpp
        probleme312.cpp
        probleme345.cpp
        probleme346.cpp
        probleme347.cpp
        probleme357.cpp
        probleme381.cpp
        probleme498.cpp
        probleme500.cpp
        probleme501.cpp)

set(SOURCE_FILES
        euler.cpp
        ${LIBRARY_FILES}
        ${PROBLEMES_FILES})

add_executable(ProjectEuler ${SOURCE_FILES})
add_executable(ProjectEulerTest ${TEST_FILES})

target_link_libraries(ProjectEuler ${GMP_LIBRARIES} ${Boost_LIBRARIES})
target_link_libraries(ProjectEulerTest ${GMP_LIBRARIES} ${Boost_LIBRARIES})
