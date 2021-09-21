

cmake_minimum_required(VERSION 3.10)

project(practice)

file(GLOB_RECURSE source ./src/*.c)

foreach(filepath_name ${source})
    # message(${c_file})
    get_filename_component(file_name ${filepath_name} NAME_WE)
    message(${file_name})
    add_executable(${file_name} ${filepath_name})
endforeach()
