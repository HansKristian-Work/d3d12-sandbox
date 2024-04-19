cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_STANDARD 99)
project(d3d12-sandbox LANGUAGES CXX C)

if (CMAKE_COMPILER_IS_GNUCXX OR (${CMAKE_CXX_COMPILER_ID} MATCHES "Clang"))
    set(SANDBOX_CXX_FLAGS -Wshadow -Wall -Wextra -Wno-comment -Wno-missing-field-initializers -Wno-empty-body -fvisibility=hidden)
    if (${CMAKE_CXX_COMPILER_ID} MATCHES "Clang")
        set(SANDBOX_CXX_FLAGS ${SANDBOX_CXX_FLAGS} -Wno-backslash-newline-escape)
    endif()
    if (NOT (${CMAKE_BUILD_TYPE} MATCHES "Release"))
        message("Enabling frame pointer for profiling/debug.")
        set(SANDBOX_CXX_FLAGS ${SANDBOX_CXX_FLAGS} -fno-omit-frame-pointer)
    endif()
    if (CMAKE_SYSTEM_PROCESSOR MATCHES "(x86)|(X86)|(amd64)|(AMD64)")
        message("Enabling SSE3 support.")
        set(SANDBOX_CXX_FLAGS ${SANDBOX_CXX_FLAGS} -msse3)
    endif()
elseif (MSVC)
    set(SANDBOX_CXX_FLAGS /D_CRT_SECURE_NO_WARNINGS /wd4267 /wd4244 /wd4309 /wd4005 /MP)
endif()

include(GNUInstallDirs)

set(SDL_SHARED OFF CACHE BOOL "" FORCE)
set(SDL_STATIC ON CACHE BOOL "" FORCE)

add_subdirectory(SDL3 EXCLUDE_FROM_ALL)
add_executable(sandbox sandbox.cpp)

target_compile_options(sandbox PRIVATE ${SANDBOX_CXX_FLAGS})

target_link_libraries(sandbox PRIVATE SDL3-static)

if (WIN32)
    target_link_libraries(sandbox PRIVATE d3d12 dxgi)
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/pix/WinPixEventRuntime.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
    target_include_directories(sandbox PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/pix)
endif()

