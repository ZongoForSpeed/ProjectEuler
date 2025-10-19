set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_library(utils SHARED
        ${PROJECT_SOURCE_DIR}/executor.h
        ${PROJECT_SOURCE_DIR}/format.h
        ${PROJECT_SOURCE_DIR}/iterator.h
        ${PROJECT_SOURCE_DIR}/mpf_nombre.cpp
        ${PROJECT_SOURCE_DIR}/mpf_nombre.h
        ${PROJECT_SOURCE_DIR}/mpq_fraction.cpp
        ${PROJECT_SOURCE_DIR}/mpq_fraction.h
        ${PROJECT_SOURCE_DIR}/mpz_nombre.cpp
        ${PROJECT_SOURCE_DIR}/mpz_nombre.h
        ${PROJECT_SOURCE_DIR}/multidimension.h
        ${PROJECT_SOURCE_DIR}/numerique.h
        ${PROJECT_SOURCE_DIR}/timer.cpp
        ${PROJECT_SOURCE_DIR}/timer.h
        ${PROJECT_SOURCE_DIR}/utilitaires.h
)

include_directories(${PROJECT_SOURCE_DIR})

target_include_directories(utils PUBLIC ${PROJECT_SOURCE_DIR})
