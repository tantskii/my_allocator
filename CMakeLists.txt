cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

if(NOT DEFINED ENV{TRAVIS_BUILD_NUMBER})
    message(STATUS "TRAVIS_BUILD_NUMBER environment variable is not defined. Run 'export TRAVIS_BUILD_NUMBER=1'.")
endif()

project(my_allocator VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

set(CMAKE_CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED ON)

include_directories(source)
add_subdirectory(source)
add_subdirectory(test)
add_subdirectory(lib/googletest)

if (MSVC)
    target_compile_options(my_allocator PRIVATE
        /W4
    )
else ()
    target_compile_options(my_allocator PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

install(TARGETS my_allocator RUNTIME DESTINATION bin)
set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT tihon1997@gmail.com)
include(CPack)

enable_testing()
add_test(my_allocator_test my_allocator_test)
