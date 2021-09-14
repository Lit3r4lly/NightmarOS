# set up this file ONLY for the clion IDE (linter, syntax highlighting etc..)
# NOT for any other usage!!!

cmake_minimum_required(VERSION 3.20)
project(NightmareOS)

set(CMAKE_CXX_STANDARD 20)
file(GLOB_RECURSE source_list "*.c" "*.cpp" "*.h" "*.hpp" "*.s")

add_executable(NightmareOS ${source_list})
include_directories(kernel/include libc/include)
add_compile_options(-ffreestanding -Wall -Wextra -fno-rtti -fno-exceptions)
add_compile_definitions(__is_libk __is_libc __is_kernel _K_LOG)