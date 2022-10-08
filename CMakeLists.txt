cmake_minimum_required(VERSION 3.22)
project(aquarium-seahorse VERSION 1.1.0
        LANGUAGES C
        DESCRIPTION "Container compositions")

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
# Dependencies
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)
find_package(Doxygen OPTIONAL_COMPONENTS dot mscgen dia)
include(cmake/FetchAquariumRock.cmake)
include(cmake/FetchAquariumSeaTurtle.cmake)

# Sources
set(EXPORTED_HEADER_FILES
        include/seahorse/array_i.h
        include/seahorse/array_ni.h
        include/seahorse/error.h
        include/seahorse/linked_red_black_tree_set_ni.h
        include/seahorse/red_black_tree_map_i_i.h
        include/seahorse/red_black_tree_map_ni_ni.h
        include/seahorse/red_black_tree_map_ni_p.h
        include/seahorse/red_black_tree_map_s_s.h
        include/seahorse/red_black_tree_set_ni.h
        include/seahorse.h)
set(SOURCES
        ${EXPORTED_HEADER_FILES}
        src/array_i.c
        src/array_ni.c
        src/error.c
        src/linked_red_black_tree_set_ni.c
        src/red_black_tree_map_i_i.c
        src/red_black_tree_map_ni_ni.c
        src/red_black_tree_map_ni_p.c
        src/red_black_tree_map_s_s.c
        src/red_black_tree_set_ni.c
        src/seahorse.c)

if (DOXYGEN_FOUND)
    set(DOXYGEN_EXTRACT_ALL YES)
    doxygen_add_docs(${PROJECT_NAME}-documentation
            ${EXPORTED_HEADER_FILES})
endif ()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    include(CTest)
    include(cmake/FetchCMocka.cmake)
    add_library(${PROJECT_NAME} STATIC "")
    add_compile_definitions(TEST)
    target_sources(${PROJECT_NAME}
            PRIVATE
                ${SOURCES}
                src/test/cmocka.h)
    target_link_libraries(${PROJECT_NAME}
            PUBLIC
                ${CMAKE_THREAD_LIBS_INIT}
                ${CMOCKA_SHARED_LIBRARY}
                aquarium-rock
                aquarium-sea-turtle)
    target_include_directories(${PROJECT_NAME}
            PUBLIC
                "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
                "$<INSTALL_INTERFACE:$<INSTALL_PREFIX>/${CMAKE_INSTALL_INCLUDEDIR}>")
    # Unit Tests
    enable_testing()
    # aquarium-seahorse-unit-test
    add_executable(${PROJECT_NAME}-unit-test test/test_seahorse.c)
    target_include_directories(${PROJECT_NAME}-unit-test
            PRIVATE
                "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>")
    target_link_libraries(${PROJECT_NAME}-unit-test
            PRIVATE
                ${PROJECT_NAME})
    add_test(${PROJECT_NAME}-unit-test ${PROJECT_NAME}-unit-test)
    # aquarium-seahorse-red-black-tree-map-ni-ni-unit-test
    add_executable(${PROJECT_NAME}-red-black-tree-map-ni-ni-unit-test
            test/test_red_black_tree_map_ni_ni.c)
    target_include_directories(${PROJECT_NAME}-red-black-tree-map-ni-ni-unit-test
            PRIVATE
                "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>")
    target_link_libraries(${PROJECT_NAME}-red-black-tree-map-ni-ni-unit-test
            PRIVATE
                ${PROJECT_NAME})
    add_test(${PROJECT_NAME}-red-black-tree-map-ni-ni-unit-test
            ${PROJECT_NAME}-red-black-tree-map-ni-ni-unit-test)
    # aquarium-seahorse-red-black-tree-map-ni-p-unit-test
    add_executable(${PROJECT_NAME}-red-black-tree-map-ni-p-unit-test
            test/test_red_black_tree_map_ni_p.c)
    target_include_directories(${PROJECT_NAME}-red-black-tree-map-ni-p-unit-test
            PRIVATE
                "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>")
    target_link_libraries(${PROJECT_NAME}-red-black-tree-map-ni-p-unit-test
            PRIVATE
                ${PROJECT_NAME})
    add_test(${PROJECT_NAME}-red-black-tree-map-ni-p-unit-test
            ${PROJECT_NAME}-red-black-tree-map-ni-p-unit-test)
    # aquarium-seahorse-red-black-tree-map-i-i-unit-test
    add_executable(${PROJECT_NAME}-red-black-tree-map-i-i-unit-test
            test/test_red_black_tree_map_i_i.c)
    target_include_directories(${PROJECT_NAME}-red-black-tree-map-i-i-unit-test
            PRIVATE
                "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>")
    target_link_libraries(${PROJECT_NAME}-red-black-tree-map-i-i-unit-test
            PRIVATE
                ${PROJECT_NAME})
    add_test(${PROJECT_NAME}-red-black-tree-map-i-i-unit-test
            ${PROJECT_NAME}-red-black-tree-map-i-i-unit-test)
    # aquarium-seahorse-red-black-tree-map-s-s-unit-test
    add_executable(${PROJECT_NAME}-red-black-tree-map-s-s-unit-test
            test/test_red_black_tree_map_s_s.c)
    target_include_directories(${PROJECT_NAME}-red-black-tree-map-s-s-unit-test
            PRIVATE
                "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>")
    target_link_libraries(${PROJECT_NAME}-red-black-tree-map-s-s-unit-test
            PRIVATE
                ${PROJECT_NAME})
    add_test(${PROJECT_NAME}-red-black-tree-map-s-s-unit-test
            ${PROJECT_NAME}-red-black-tree-map-s-s-unit-test)
    # aquarium-seahorse-red-black-set-ni-unit-test
    add_executable(${PROJECT_NAME}-red-black-set-ni-unit-test
            test/test_red_black_tree_set_ni.c)
    target_include_directories(${PROJECT_NAME}-red-black-set-ni-unit-test
            PRIVATE
                "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>")
    target_link_libraries(${PROJECT_NAME}-red-black-set-ni-unit-test
            PRIVATE
                ${PROJECT_NAME})
    add_test(${PROJECT_NAME}-red-black-set-ni-unit-test
                ${PROJECT_NAME}-red-black-set-ni-unit-test)
    # aquarium-seahorse-linked-red-black-set-ni-unit-test
    add_executable(${PROJECT_NAME}-linked-red-black-set-ni-unit-test
            test/test_linked_red_black_tree_set_ni.c)
    target_include_directories(${PROJECT_NAME}-linked-red-black-set-ni-unit-test
            PRIVATE
                "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>")
    target_link_libraries(${PROJECT_NAME}-linked-red-black-set-ni-unit-test
            PRIVATE
                ${PROJECT_NAME})
    add_test(${PROJECT_NAME}-linked-red-black-set-ni-unit-test
            ${PROJECT_NAME}-linked-red-black-set-ni-unit-test)
    # aquarium-seahorse-array-ni-unit-test
    add_executable(${PROJECT_NAME}-array-ni-unit-test test/test_array_ni.c)
    target_include_directories(${PROJECT_NAME}-array-ni-unit-test
            PRIVATE
                "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>")
    target_link_libraries(${PROJECT_NAME}-array-ni-unit-test
            PRIVATE
                ${PROJECT_NAME})
    add_test(${PROJECT_NAME}-array-ni-unit-test
            ${PROJECT_NAME}-array-ni-unit-test)
    # aquarium-seahorse-array-i-unit-test
    add_executable(${PROJECT_NAME}-array-i-unit-test test/test_array_i.c)
    target_include_directories(${PROJECT_NAME}-array-i-unit-test
            PRIVATE
                "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>")
    target_link_libraries(${PROJECT_NAME}-array-i-unit-test
            PRIVATE
                ${PROJECT_NAME})
    add_test(${PROJECT_NAME}-array-i-unit-test
            ${PROJECT_NAME}-array-i-unit-test)
else ()
    add_library(${PROJECT_NAME} "")
    target_sources(${PROJECT_NAME}
            PRIVATE
                ${SOURCES})
    target_include_directories(${PROJECT_NAME}
            PUBLIC
                "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
                "$<INSTALL_INTERFACE:$<INSTALL_PREFIX>/${CMAKE_INSTALL_INCLUDEDIR}>")
    target_link_libraries(${PROJECT_NAME}
            PUBLIC
                ${CMAKE_THREAD_LIBS_INIT}
                aquarium-rock
                aquarium-sea-turtle)
    set_target_properties(${PROJECT_NAME}
            PROPERTIES
                VERSION ${PROJECT_VERSION}
                SOVERSION ${PROJECT_VERSION_MAJOR})
    include(GNUInstallDirs)
    install(DIRECTORY include/
            DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
    install(TARGETS ${PROJECT_NAME}
            LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
    configure_file(${PROJECT_NAME}.pc.in ${PROJECT_NAME}.pc @ONLY)
    install(FILES ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.pc
            DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)
endif ()
