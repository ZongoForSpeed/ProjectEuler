set (PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_library (maths SHARED
        ${PROJECT_SOURCE_DIR}/arithmetiques.h
        ${PROJECT_SOURCE_DIR}/arithmetiques_modulaire.h
        ${PROJECT_SOURCE_DIR}/chiffres.h
        ${PROJECT_SOURCE_DIR}/combinatoire.h
        ${PROJECT_SOURCE_DIR}/diophantienne.cpp
        ${PROJECT_SOURCE_DIR}/diophantienne.h
        ${PROJECT_SOURCE_DIR}/fenwick.h
        ${PROJECT_SOURCE_DIR}/graphe.cpp
        ${PROJECT_SOURCE_DIR}/graphe.h
        ${PROJECT_SOURCE_DIR}/matrice.h
        ${PROJECT_SOURCE_DIR}/multidimension.h
        ${PROJECT_SOURCE_DIR}/permutation.h
        ${PROJECT_SOURCE_DIR}/polygonal.h
        ${PROJECT_SOURCE_DIR}/polynome.h
        ${PROJECT_SOURCE_DIR}/premiers.cpp
        ${PROJECT_SOURCE_DIR}/premiers.h
        ${PROJECT_SOURCE_DIR}/puissance.h
        ${PROJECT_SOURCE_DIR}/pythagoricien.cpp
        ${PROJECT_SOURCE_DIR}/pythagoricien.h
        ${PROJECT_SOURCE_DIR}/timer.cpp
        ${PROJECT_SOURCE_DIR}/timer.h
        ${PROJECT_SOURCE_DIR}/utilitaires.cpp
        ${PROJECT_SOURCE_DIR}/utilitaires.h)

include_directories(${PROJECT_SOURCE_DIR})

target_include_directories (maths PUBLIC ${PROJECT_SOURCE_DIR})
