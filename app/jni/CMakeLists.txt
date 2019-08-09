cmake_minimum_required(VERSION 3.4.1)

set(CMAKE_CXX_STANDARD 11)

# 添加头文件路径
include_directories(./head)

# 添加C\C++文件路径
SET(DIR_SRC ./cpp)

FOREACH(next_ITEM ${DIR_SRC})
  aux_source_directory (${next_ITEM} SRC_INCLUDE)
  list(APPEND ALL_SRC ${SRC_INCLUDE})      #TODO
ENDFOREACH(next_ITEM ${DIR_SRC})


# 添加NDK的库文件
find_library(log-lib
              log )


# 生成库文件
add_library( corenote SHARED ${ALL_SRC} )


# 库文件的链接
target_link_libraries( corenote

                       ${log-lib})


#设置生成的so动态库最后输出的路径
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI})

# 生成静态库文件
#add_library(corenote_s
#             STATIC
#             ${ALL_SRC} )

#target_link_libraries(  corenote_s
#                        tools
#                        ${log-lib} )

# 生成可执行文件
 #add_executable(corenote_bin
 #               ${ALL_SRC})
 #target_link_libraries(corenote_bin
 #                       tools
 #                      ${log-lib} )