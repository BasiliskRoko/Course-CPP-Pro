cmake_minimum_required(VERSION 3.10)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(homework VERSION ${PROJECT_VERSION})


#set(CMAKE_CXX_CLANG_TIDY clang-tidy -warnings-as-errors=*)

find_package(GTest REQUIRED)

set(boost_program_options_DIR /usr/local/Cellar/boost/1.76.0/lib/cmake/boost_program_options-1.76.0/)

find_package(Boost REQUIRED COMPONENTS program_options regex filesystem)
if(NOT Boost_FOUND)
    message(SEND_ERROR "Failed to find Boost")
    return()
else()
    include_directories(${Boost_INCLUDE_DIR})
endif()

configure_file(version.h.in version.h)

add_executable(bayan homework.cpp)

add_library(lib lib.cpp)

add_executable(test_version test_version.cpp)



list(APPEND TARGETS bayan lib   
test_version)

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


include_directories(${Boost_INCLUDE_DIR})

target_include_directories(lib
    PRIVATE "${CMAKE_BINARY_DIR}"
)

target_link_libraries(bayan PRIVATE
    ${Boost_LIBRARIES}
    lib
)

set_target_properties(test_version PROPERTIES
    COMPILE_DEFINITIONS 
    INCLUDE_DIRECTORIES 
)

target_link_libraries(test_version PRIVATE GTest::GTest
    lib
)






install(TARGETS bayan RUNTIME DESTINATION bin)

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
