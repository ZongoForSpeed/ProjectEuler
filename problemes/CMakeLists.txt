set (PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

aux_source_directory(${PROJECT_SOURCE_DIR}/probleme0xx PROBLEME_0XX)
aux_source_directory(${PROJECT_SOURCE_DIR}/probleme1xx PROBLEME_1XX)
aux_source_directory(${PROJECT_SOURCE_DIR}/probleme2xx PROBLEME_2XX)
aux_source_directory(${PROJECT_SOURCE_DIR}/probleme3xx PROBLEME_3XX)
file(GLOB PROBLEME_YYY ${PROJECT_SOURCE_DIR}/probleme*.cpp)

add_library (problemes SHARED
        ${PROJECT_SOURCE_DIR}/problemes.h
        ${PROJECT_SOURCE_DIR}/problemes.cpp
        ${PROBLEME_0XX}
        ${PROBLEME_1XX}
        ${PROBLEME_2XX}
        ${PROBLEME_3XX}
        ${PROBLEME_YYY})

include_directories(${PROJECT_SOURCE_DIR})

target_link_libraries(problemes maths utils)
target_include_directories (problemes PUBLIC ${PROJECT_SOURCE_DIR})