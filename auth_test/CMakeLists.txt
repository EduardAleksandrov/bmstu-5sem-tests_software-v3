# Запуск
# conan install path/to/conan/file --output-folder=build --build=missing
# 
# conan install /home/eduard/Projects/iu7/TESTS_v1/lab1/conanfile.txt -of /home/eduard/Projects/iu7/TESTS_v1/lab1/build-conan --build=missing
# cd build
# 
# source conanbuild.sh  - необязательный элемент
# 
# cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release        - .. значит что файл cmakelists.txt лежит на директорию выше
# cmake --build .
# 
# source deactivate_conanbuild.sh
# 
# ./timer

# vscode .vscode/c_cpp_properties.json    - чтобы vscode не подчеркивал
# {
#     "configurations": [
#         {
#             "name": "Linux",
#             "includePath": [
#                 "${workspaceFolder}/**",
#                 "~/.conan2/**"
#             ],
#             "intelliSenseMode": "linux-gcc-x64",
#             "compilerPath": "/usr/bin/g++"
#         }
#     ],
#     "version": 4
# }


cmake_minimum_required(VERSION 3.16)
project(Tests_lab1)
add_definitions("-std=c++17")
message("cl: ${CONAN_LIBS}")
message("cl: ${PROJECT_SOURCE_DIR}")

#compiler flags
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release) # Release
endif()

include(${PROJECT_SOURCE_DIR}/build-conan/build/Release/generators/conan_toolchain.cmake)
find_package(Boost REQUIRED)

# Include directories
include_directories(include)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/include/5.auth1.txt
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/include/5.auth2.txt
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(1.test 1.test.cpp)

target_link_libraries(1.test boost::boost pthread)
