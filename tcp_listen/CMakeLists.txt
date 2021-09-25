

cmake_minimum_required(VERSION 3.10)

project(tcp_listen)

file(GLOB_RECURSE source ./src/*.c)

# set(objs "./tcp_listen ./tcp_listen_test")

# foreach(filepath_name ${source})
    # 只保留文件名称到file_name 根据NAME_WE来判断是否需要保留后缀
    # get_filename_component(file_name ${filepath_name} NAME_WE)
    # get_filename_component(file_name ${file_name} NAME_WLE)
    # 输出文件
    # message(${file_name})
    # 添加到编译
    # add_executable(${PROJECT_NAME} ${source})
# endforeach()

# foreach(obj ${objs})
#     set(file__ ${obj}.c)
#     add_executable(${PROJECT_NAME} ${file__})
# endforeach()


# message(${file__})
message(${source})
add_executable(${PROJECT_NAME} ${source})

