cmake_minimum_required(VERSION 3.10)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(homework VERSION ${PROJECT_VESRION})


#set(CMAKE_CXX_CLANG_TIDY clang-tidy -warnings-as-errors=*)

find_package(GTest REQUIRED)

configure_file(version.h.in version.h)

add_executable(homework homework.cpp)

add_library(lib lib.cpp)

add_executable(test_version test_version.cpp)

add_executable(1264_working_days 1264_working_days.cpp)

add_executable(1409_two_bandits 1409_two_bandits.cpp)

add_executable(1787_turn_on_Mega 1787_turn_on_Mega.cpp)

add_executable(1877_bycicle_codes 1877_bycicle_codes.cpp)

add_executable(2001_mathNberry 2001_mathNberry.cpp)


list(APPEND TARGETS homework lib 1264_working_days 1409_two_bandits 1787_turn_on_Mega 1877_bycicle_codes 2001_mathNberry test_version)

foreach(target ${TARGETS})
    target_compile_features(${target} PUBLIC cxx_std_17)
    set_target_properties(${target} PROPERTIES 
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON)

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



target_include_directories(lib
    PRIVATE "${CMAKE_BINARY_DIR}"
)

target_link_libraries(homework PRIVATE
    lib
)

set_target_properties(test_version PROPERTIES
    COMPILE_DEFINITIONS 
    INCLUDE_DIRECTORIES 
)

target_link_libraries(test_version PRIVATE GTest::GTest
    lib
)






install(TARGETS homework RUNTIME DESTINATION bin)

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
