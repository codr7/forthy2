cmake_minimum_required(VERSION 3.5)

project(forthy2)
set(CMAKE_CXX_COMPILER clang++)
add_compile_options(-std=c++17 -Wall -Werror -O2 -g)
add_link_options(-rdynamic)

file(GLOB_RECURSE src src/forthy2/*.cpp)

add_library(lib_static STATIC ${src})
set_target_properties(lib_static PROPERTIES OUTPUT_NAME forthy2)
target_include_directories(lib_static PUBLIC src/)
target_link_libraries(lib_static dl stdc++fs)

add_executable(forthy2 ${src} src/main.cpp)
target_include_directories(forthy2 PUBLIC src/)
target_link_libraries(forthy2 dl stdc++fs)

file(GLOB root_inc src/forthy2/*.hpp)
install(FILES ${root_inc} DESTINATION include/forthy2)

file(GLOB type_inc src/forthy2/types/*.hpp)
install(FILES ${type_inc} DESTINATION include/forthy2/types)

install(FILES build/forthy2 DESTINATION bin PERMISSIONS WORLD_EXECUTE)
install(FILES build/libforthy2.a DESTINATION lib)

