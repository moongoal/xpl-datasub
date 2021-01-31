cmake_minimum_required(VERSION 3.19)

project(
    datasub
    VERSION 0.0.1
)

set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)

file(
    GLOB_RECURSE SOURCES
    LIST_DIRECTORIES false
    ${SOURCE_DIR}/*.c
)

add_library(datasub SHARED ${SOURCES})

set(CONTRIB_DIR ${CMAKE_BINARY_DIR}/contrib)
set(CACHE_DIR ${CMAKE_BINARY_DIR}/cache)
set(XPL_SDK_ZIP ${CACHE_DIR}/XPSDK303.zip)
set(XPL_SDK_DIR ${CONTRIB_DIR}/SDK)

if(NOT EXISTS ${XPL_SDK_ZIP})
    file(
        DOWNLOAD
        https://developer.x-plane.com/wp-content/plugins/code-sample-generation/sample_templates/XPSDK303.zip
        ${XPL_SDK_ZIP}
        EXPECTED_HASH SHA256=11a550dc553876d8c0b7187ae2e1c7e9fee5909dce6d8469720cad51e5bcb7ff
    )
endif()

if(NOT EXISTS ${XPL_SDK_DIR})
    file(
        ARCHIVE_EXTRACT
        INPUT ${XPL_SDK_ZIP}
        DESTINATION ${CONTRIB_DIR}
    )
endif()

find_library(
    XPL_SDK_LIB
    XPLM_64
    PATHS ${XPL_SDK_DIR}/Libraries/Win
    REQUIRED
)

find_file(
    XPL_SDK_HDR_DIR
    CHeaders
    PATHS ${XPL_SDK_DIR}
    REQUIRED
)

target_include_directories(datasub PRIVATE ${XPL_SDK_HDR_DIR})
target_compile_definitions(datasub PRIVATE IBM XPLM210 _CRT_SECURE_NO_WARNINGS)

find_package(xxHash CONFIG REQUIRED)
target_link_libraries(datasub PRIVATE xxHash::xxhash)
target_link_libraries(datasub PRIVATE ${XPL_SDK_LIB})
target_link_libraries(datasub PRIVATE Ws2_32 wsock32)
