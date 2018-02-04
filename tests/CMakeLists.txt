set (PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_library (tests SHARED
        ${PROJECT_SOURCE_DIR}/arithmetiques.cpp
        ${PROJECT_SOURCE_DIR}/chiffres.cpp
        ${PROJECT_SOURCE_DIR}/combinatoire.cpp
        ${PROJECT_SOURCE_DIR}/diophantienne.cpp
        ${PROJECT_SOURCE_DIR}/fenwick.cpp
        ${PROJECT_SOURCE_DIR}/matrice.cpp
        ${PROJECT_SOURCE_DIR}/mp_nombre.cpp
        ${PROJECT_SOURCE_DIR}/multidimension.cpp
        ${PROJECT_SOURCE_DIR}/permutation.cpp
        ${PROJECT_SOURCE_DIR}/polygonal.cpp
        ${PROJECT_SOURCE_DIR}/polynome.cpp
        ${PROJECT_SOURCE_DIR}/premiers.cpp
        ${PROJECT_SOURCE_DIR}/puissance.cpp
        ${PROJECT_SOURCE_DIR}/pythagoricien.cpp
        ${PROJECT_SOURCE_DIR}/utilitaires.cpp)

include_directories(${PROJECT_SOURCE_DIR})

target_link_libraries(tests maths)
target_include_directories (tests PUBLIC ${PROJECT_SOURCE_DIR})
