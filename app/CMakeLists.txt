cmake_minimum_required(VERSION 3.4.1)

# 添加头文件路径
include_directories(./src/main/head)

# 添加C\C++文件路径
SET(DIR_SRC ./src/main/cpp)

FOREACH(next_ITEM ${DIR_SRC})
  aux_source_directory (${next_ITEM} SRC_INCLUDE)
  list(APPEND ALL_SRC ${SRC_INCLUDE})      #TODO
ENDFOREACH(next_ITEM ${DIR_SRC})

# 添加NDK的库文件
find_library(log-lib
              log )


# 生成库文件
add_library( datastructure
             SHARED
             ${ALL_SRC})


# 库文件的链接
target_link_libraries( datastructure

                       ${log-lib})


# 生成静态库文件
#add_library(datastructure_s
#             STATIC
#             ${ALL_SRC} )

#target_link_libraries(  datastructure_s
#                        tools
#                        ${log-lib} )

# 生成可执行文件
 #add_executable(datastructure_bin
 #               ${ALL_SRC})
 #target_link_libraries(datastructure_bin
 #                       tools
 #                      ${log-lib} )