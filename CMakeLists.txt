cmake_minimum_required(VERSION 3.22)
project(aquarium-seahorse VERSION 4.0.0
        LANGUAGES C
        DESCRIPTION "Collections in C")

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
# Dependencies
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)
find_package(Doxygen OPTIONAL_COMPONENTS dot mscgen dia)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    include(cmake/FetchAquariumCMocka.cmake)
endif()
include(cmake/FetchAquariumSeaTurtle.cmake)
include(cmake/FetchAquariumTriggerfish.cmake)

# Sources
set(EXPORTED_HEADER_FILES
        include/seahorse/array_list_i.h
        include/seahorse/array_list_ni.h
        include/seahorse/array_list_p.h
        include/seahorse/error.h
        include/seahorse/collection_i.h
        include/seahorse/linked_queue_ni.h
        include/seahorse/linked_queue_sr.h
        include/seahorse/linked_red_black_tree_set_ni.h
        include/seahorse/linked_stack_ni.h
        include/seahorse/ordered_set_i.h
        include/seahorse/red_black_tree_map_i_i.h
        include/seahorse/red_black_tree_map_ni_i.h
        include/seahorse/red_black_tree_map_ni_ni.h
        include/seahorse/red_black_tree_map_ni_p.h
        include/seahorse/red_black_tree_map_p_p.h
        include/seahorse/red_black_tree_map_s_p.h
        include/seahorse/red_black_tree_map_s_s.h
        include/seahorse/red_black_tree_map_s_wr.h
        include/seahorse/red_black_tree_map_sr_sr.h
        include/seahorse/red_black_tree_set_i.h
        include/seahorse/red_black_tree_set_ni.h
        include/seahorse/red_black_tree_set_s.h
        include/seahorse/set_i.h
        include/seahorse/sorted_set_i.h
        include/seahorse/stream_i.h
        include/seahorse.h)
set(SOURCES
        ${EXPORTED_HEADER_FILES}
        src/private/collection_i.h
        src/private/ordered_set_i.h
        src/private/set_i.h
        src/private/sorted_set_i.h
        src/private/stream_i.h
        src/array_list_i.c
        src/array_list_ni.c
        src/array_list_p.c
        src/collection_i.c
        src/error.c
        src/linked_queue_ni.c
        src/linked_queue_sr.c
        src/linked_red_black_tree_set_ni.c
        src/linked_stack_ni.c
        src/ordered_set_i.c
        src/red_black_tree_map_i_i.c
        src/red_black_tree_map_ni_i.c
        src/red_black_tree_map_ni_ni.c
        src/red_black_tree_map_ni_p.c
        src/red_black_tree_map_p_p.c
        src/red_black_tree_map_s_p.c
        src/red_black_tree_map_s_s.c
        src/red_black_tree_map_s_wr.c
        src/red_black_tree_map_sr_sr.c
        src/red_black_tree_set_i.c
        src/red_black_tree_set_ni.c
        src/red_black_tree_set_s.c
        src/seahorse.c
        src/sorted_set_i.c
        src/set_i.c
        src/stream_i.c)

if (DOXYGEN_FOUND)
    set(DOXYGEN_EXTRACT_ALL YES)
    doxygen_add_docs(${PROJECT_NAME}-documentation
            ${EXPORTED_HEADER_FILES})
endif ()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    include(CTest)
    add_library(${PROJECT_NAME} STATIC "")
    add_compile_definitions(TEST)
    target_sources(${PROJECT_NAME}
            PRIVATE
                ${SOURCES})
    target_link_libraries(${PROJECT_NAME}
            PUBLIC
                ${CMAKE_THREAD_LIBS_INIT}
                aquarium-cmocka
                aquarium-triggerfish
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
    # aquarium-seahorse-red-black-set-tree-ni-unit-test
    add_executable(${PROJECT_NAME}-red-black-tree-set-ni-unit-test
            test/test_red_black_tree_set_ni.c)
    target_include_directories(${PROJECT_NAME}-red-black-tree-set-ni-unit-test
            PRIVATE
                "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>")
    target_link_libraries(${PROJECT_NAME}-red-black-tree-set-ni-unit-test
            PRIVATE
                ${PROJECT_NAME})
    add_test(${PROJECT_NAME}-red-black-tree-set-ni-unit-test
                ${PROJECT_NAME}-red-black-tree-set-ni-unit-test)
    # aquarium-seahorse-red-black-tree-set-s-unit-test
    add_executable(${PROJECT_NAME}-red-black-tree-set-s-unit-test
            test/test_red_black_tree_set_s.c)
    target_include_directories(${PROJECT_NAME}-red-black-tree-set-s-unit-test
            PRIVATE
                "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>")
    target_link_libraries(${PROJECT_NAME}-red-black-tree-set-s-unit-test
            PRIVATE
                ${PROJECT_NAME})
    add_test(${PROJECT_NAME}-red-black-tree-set-s-unit-test
            ${PROJECT_NAME}-red-black-tree-set-s-unit-test)
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
    # aquarium-seahorse-array-list-ni-unit-test
    add_executable(${PROJECT_NAME}-array-list-ni-unit-test
            test/test_array_list_ni.c)
    target_include_directories(${PROJECT_NAME}-array-list-ni-unit-test
            PRIVATE
                "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>")
    target_link_libraries(${PROJECT_NAME}-array-list-ni-unit-test
            PRIVATE
                ${PROJECT_NAME})
    add_test(${PROJECT_NAME}-array-list-ni-unit-test
            ${PROJECT_NAME}-array-list-ni-unit-test)
    # aquarium-seahorse-array-list-i-unit-test
    add_executable(${PROJECT_NAME}-array-list-i-unit-test
            test/test_array_list_i.c)
    target_include_directories(${PROJECT_NAME}-array-list-i-unit-test
            PRIVATE
                "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>")
    target_link_libraries(${PROJECT_NAME}-array-list-i-unit-test
            PRIVATE
                ${PROJECT_NAME})
    add_test(${PROJECT_NAME}-array-list-i-unit-test
            ${PROJECT_NAME}-array-list-i-unit-test)
    # aquarium-seahorse-array-list-p-unit-test
    add_executable(${PROJECT_NAME}-array-list-p-unit-test
            test/test_array_list_p.c)
    target_include_directories(${PROJECT_NAME}-array-list-p-unit-test
            PRIVATE
                "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>")
    target_link_libraries(${PROJECT_NAME}-array-list-p-unit-test
            PRIVATE
                ${PROJECT_NAME})
    add_test(${PROJECT_NAME}-array-list-p-unit-test
            ${PROJECT_NAME}-array-list-p-unit-test)
    # aquarium-seahorse-red-black-tree-map-ni-i-unit-test
    add_executable(${PROJECT_NAME}-red-black-tree-map-ni-i-unit-test
            test/test_red_black_tree_map_ni_i.c)
    target_include_directories(${PROJECT_NAME}-red-black-tree-map-ni-i-unit-test
            PRIVATE
                "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>")
    target_link_libraries(${PROJECT_NAME}-red-black-tree-map-ni-i-unit-test
            PRIVATE
                ${PROJECT_NAME})
    add_test(${PROJECT_NAME}-red-black-tree-map-ni-i-unit-test
            ${PROJECT_NAME}-red-black-tree-map-ni-i-unit-test)
    # aquarium-seahorse-linked-queue-ni-unit-test
    add_executable(${PROJECT_NAME}-linked-queue-ni-unit-test
            test/test_linked_queue_ni.c)
    target_include_directories(${PROJECT_NAME}-linked-queue-ni-unit-test
            PRIVATE
                "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>")
    target_link_libraries(${PROJECT_NAME}-linked-queue-ni-unit-test
            PRIVATE
                ${PROJECT_NAME})
    add_test(${PROJECT_NAME}-linked-queue-ni-unit-test
            ${PROJECT_NAME}-linked-queue-ni-unit-test)
    # aquarium-seahorse-linked-queue-sr-unit-test
    add_executable(${PROJECT_NAME}-linked-queue-sr-unit-test
            test/test_linked_queue_sr.c)
    target_include_directories(${PROJECT_NAME}-linked-queue-sr-unit-test
            PRIVATE
                "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>")
    target_link_libraries(${PROJECT_NAME}-linked-queue-sr-unit-test
            PRIVATE
                ${PROJECT_NAME})
    add_test(${PROJECT_NAME}-linked-queue-sr-unit-test
            ${PROJECT_NAME}-linked-queue-sr-unit-test)
    # aquarium-seahorse-linked-stack-ni-unit-test
    add_executable(${PROJECT_NAME}-linked-stack-ni-unit-test
            test/test_linked_stack_ni.c)
    target_include_directories(${PROJECT_NAME}-linked-stack-ni-unit-test
            PRIVATE
                "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>")
    target_link_libraries(${PROJECT_NAME}-linked-stack-ni-unit-test
            PRIVATE
                ${PROJECT_NAME})
    add_test(${PROJECT_NAME}-linked-stack-ni-unit-test
            ${PROJECT_NAME}-linked-stack-ni-unit-test)
    # aquarium-seahorse-red-black-tree-map-s-wr-unit-test
    add_executable(${PROJECT_NAME}-red-black-tree-map-s-wr-unit-test
            test/test_red_black_tree_map_s_wr.c)
    target_include_directories(${PROJECT_NAME}-red-black-tree-map-s-wr-unit-test
            PRIVATE
                "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>")
    target_link_libraries(${PROJECT_NAME}-red-black-tree-map-s-wr-unit-test
            PRIVATE
                ${PROJECT_NAME})
    add_test(${PROJECT_NAME}-red-black-tree-map-s-wr-unit-test
            ${PROJECT_NAME}-red-black-tree-map-s-wr-unit-test)
    # aquarium-seahorse-red-black-tree-map-sr-sr-unit-test
    add_executable(${PROJECT_NAME}-red-black-tree-map-sr-sr-unit-test
            test/test_red_black_tree_map_sr_sr.c)
    target_include_directories(
            ${PROJECT_NAME}-red-black-tree-map-sr-sr-unit-test
            PRIVATE
                "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>")
    target_link_libraries(${PROJECT_NAME}-red-black-tree-map-sr-sr-unit-test
            PRIVATE
                ${PROJECT_NAME})
    add_test(${PROJECT_NAME}-red-black-tree-map-sr-sr-unit-test
            ${PROJECT_NAME}-red-black-tree-map-sr-sr-unit-test)
    # aquarium-seahorse-red-black-tree-map-s-p-unit-test
    add_executable(${PROJECT_NAME}-red-black-tree-map-s-p-unit-test
            test/test_red_black_tree_map_s_p.c)
    target_include_directories(${PROJECT_NAME}-red-black-tree-map-s-p-unit-test
            PRIVATE
                "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>")
    target_link_libraries(${PROJECT_NAME}-red-black-tree-map-s-p-unit-test
            PRIVATE
                ${PROJECT_NAME})
    add_test(${PROJECT_NAME}-red-black-tree-map-s-p-unit-test
            ${PROJECT_NAME}-red-black-tree-map-s-p-unit-test)
    # aquarium-seahorse-red-black-tree-map-p-p-unit-test
    add_executable(${PROJECT_NAME}-red-black-tree-map-p-p-unit-test
            test/test_red_black_tree_map_p_p.c)
    target_include_directories(${PROJECT_NAME}-red-black-tree-map-p-p-unit-test
            PRIVATE
                "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>")
    target_link_libraries(${PROJECT_NAME}-red-black-tree-map-p-p-unit-test
            PRIVATE
                ${PROJECT_NAME})
    add_test(${PROJECT_NAME}-red-black-tree-map-p-p-unit-test
            ${PROJECT_NAME}-red-black-tree-map-p-p-unit-test)
    # aquarium-seahorse-red-black-tree-set-i-unit-test
    add_executable(${PROJECT_NAME}-red-black-tree-set-i-unit-test
            test/test_red_black_tree_set_i.c)
    target_include_directories(${PROJECT_NAME}-red-black-tree-set-i-unit-test
            PRIVATE
                "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>")
    target_link_libraries(${PROJECT_NAME}-red-black-tree-set-i-unit-test
            PRIVATE
                ${PROJECT_NAME})
    add_test(${PROJECT_NAME}-red-black-tree-set-i-unit-test
            ${PROJECT_NAME}-red-black-tree-set-i-unit-test)
    # aquarium-seahorse-stream-i-unit-test
    add_executable(${PROJECT_NAME}-stream-i-unit-test test/test_stream_i.c)
    target_include_directories(${PROJECT_NAME}-stream-i-unit-test
            PRIVATE
                "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>")
    target_link_libraries(${PROJECT_NAME}-stream-i-unit-test
            PRIVATE
                ${PROJECT_NAME})
    add_test(${PROJECT_NAME}-stream-i-unit-test
            ${PROJECT_NAME}-stream-i-unit-test)
    # aquarium-seahorse-collection-i-unit-test
    add_executable(${PROJECT_NAME}-collection-i-unit-test
            test/test_collection_i.c)
    target_include_directories(${PROJECT_NAME}-collection-i-unit-test
            PRIVATE
                "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>")
    target_link_libraries(${PROJECT_NAME}-collection-i-unit-test
            PRIVATE
                ${PROJECT_NAME})
    add_test(${PROJECT_NAME}-collection-i-unit-test
            ${PROJECT_NAME}-collection-i-unit-test)
    # aquarium-seahorse-set-i-unit-test
    add_executable(${PROJECT_NAME}-set-i-unit-test test/test_set_i.c)
    target_include_directories(${PROJECT_NAME}-set-i-unit-test
            PRIVATE
                "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>")
    target_link_libraries(${PROJECT_NAME}-set-i-unit-test
            PRIVATE
                ${PROJECT_NAME})
    add_test(${PROJECT_NAME}-set-i-unit-test ${PROJECT_NAME}-set-i-unit-test)
    # aquarium-seahorse-ordered-set-i-unit-test
    add_executable(${PROJECT_NAME}-ordered-set-i-unit-test
            test/test_ordered_set_i.c)
    target_include_directories(${PROJECT_NAME}-ordered-set-i-unit-test
            PRIVATE
                "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>")
    target_link_libraries(${PROJECT_NAME}-ordered-set-i-unit-test
            PRIVATE
                ${PROJECT_NAME})
    add_test(${PROJECT_NAME}-ordered-set-i-unit-test
            ${PROJECT_NAME}-ordered-set-i-unit-test)
    # aquarium-seahorse-sorted-set-i-unit-test
    add_executable(${PROJECT_NAME}-sorted-set-i-unit-test
            test/test_sorted_set_i.c)
    target_include_directories(${PROJECT_NAME}-sorted-set-i-unit-test
            PRIVATE
                "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>")
    target_link_libraries(${PROJECT_NAME}-sorted-set-i-unit-test
            PRIVATE
                ${PROJECT_NAME})
    add_test(${PROJECT_NAME}-sorted-set-i-unit-test
            ${PROJECT_NAME}-sorted-set-i-unit-test)
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
                aquarium-triggerfish
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
