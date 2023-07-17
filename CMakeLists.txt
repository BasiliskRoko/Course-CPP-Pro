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

add_executable(1000_AplusB_Problem 1000_AplusB_Problem.cpp)

add_executable(1001_reverse_root 1001_reverse_root.cpp)

add_executable(1293_Aniya 1293_Aniya.cpp)

add_executable(1785_Localization_difficulties 1785_Localization_difficulties.cpp)

add_executable(1880_Eigenvalues_Psych_Up 1880_Eigenvalues_Psych_Up.cpp)

add_executable(2012_About_Grisha_N 2012_About_Grisha_N.cpp)

add_executable(1820_Ural_steaks 1820_Ural_steaks.cpp)

add_executable(2066_Simple_expression 2066_Simple_expression.cpp)

add_executable(1197_One_in_the_field_warrior 1197_One_in_the_field_warrior.cpp)

add_executable(2100_Wedding_dinner 2100_Wedding_dinner.cpp)

list(APPEND TARGETS homework lib   
1000_AplusB_Problem 1001_reverse_root 
1293_Aniya 1785_Localization_difficulties 1880_Eigenvalues_Psych_Up 2012_About_Grisha_N
1820_Ural_steaks 2066_Simple_expression 1197_One_in_the_field_warrior 2100_Wedding_dinner
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
