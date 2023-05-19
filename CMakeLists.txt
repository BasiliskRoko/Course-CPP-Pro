cmake_minimum_required(VERSION 3.10)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(ip_filter VERSION ${PROJECT_VESRION})

set(CMAKE_CXX_CLANG_TIDY clang-tidy -warnings-as-errors=*)

find_package(GTest REQUIRED)

configure_file(version.h.in version.h)

add_executable(ip_filter ip_filter.cpp)
add_library(lib lib.cpp)
add_executable(test_version test_version.cpp)

set_target_properties(ip_filter lib test_version PROPERTIES
    CMAKE_CXX_STANDARD 14
    CMAKE_CXX_STANDARD_REQUIRED ON
)
target_include_directories(lib
    PRIVATE "${CMAKE_BINARY_DIR}"
)
set_target_properties(test_version PROPERTIES
    COMPILE_DEFINITIONS 
    INCLUDE_DIRECTORIES 
)

target_link_libraries(ip_filter PRIVATE
    lib
)

target_link_libraries(test_version PRIVATE GTest::GTest
    lib
)

foreach(target ${TARGETS})
    target_compile_features(${target} PUBLIC cxx_std_14)
    set_target_properties(${target} PROPERTIES CXX_STANDARD_REQUIRED ON)

    if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR
        CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang" OR
        CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        target_compile_options(${target}
            PRIVATE -g -Wall -Wextra -Werror -pedantic)
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        target_compile_options(${target}
            PRIVATE /W4 /WX)
    endif()
endforeach()



install(TARGETS ip_filter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT Alexey.Seredov@bercut.com)

include(CPack)

enable_testing()
include(Dart)

add_test(test_version test_version)

include(GoogleTest)
gtest_discover_tests(test_version)
