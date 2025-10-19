set (PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_library (tests SHARED
        ${PROJECT_SOURCE_DIR}/arithmetique.cpp
        ${PROJECT_SOURCE_DIR}/arithmetique_modulaire.cpp
        ${PROJECT_SOURCE_DIR}/chiffres.cpp
        ${PROJECT_SOURCE_DIR}/combinatoire.cpp
        ${PROJECT_SOURCE_DIR}/crible_quadratique.cpp
        ${PROJECT_SOURCE_DIR}/diophantienne.cpp
        ${PROJECT_SOURCE_DIR}/fenwick.cpp
        ${PROJECT_SOURCE_DIR}/fibonacci.cpp
        ${PROJECT_SOURCE_DIR}/graphe.cpp
        ${PROJECT_SOURCE_DIR}/matrice.cpp
        ${PROJECT_SOURCE_DIR}/multidimension.cpp
        ${PROJECT_SOURCE_DIR}/mpf_nombre.cpp
        ${PROJECT_SOURCE_DIR}/mpq_fraction.cpp
        ${PROJECT_SOURCE_DIR}/mpz_nombre.cpp
        ${PROJECT_SOURCE_DIR}/nombre_modulaire.cpp
        ${PROJECT_SOURCE_DIR}/permutation.cpp
        ${PROJECT_SOURCE_DIR}/polygonal.cpp
        ${PROJECT_SOURCE_DIR}/polynome.cpp
        ${PROJECT_SOURCE_DIR}/premiers.cpp
        ${PROJECT_SOURCE_DIR}/puissance.cpp
        ${PROJECT_SOURCE_DIR}/pythagoricien.cpp
        ${PROJECT_SOURCE_DIR}/racine.cpp
        ${PROJECT_SOURCE_DIR}/utilitaires.cpp
        )

include_directories(${PROJECT_SOURCE_DIR})

target_link_libraries(tests utils maths)
target_include_directories (tests PUBLIC ${PROJECT_SOURCE_DIR})
