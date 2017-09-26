cmake_minimum_required(VERSION 3.2)
project(lab4)

set(CMAKE_CXX_STANDARD 11)
find_package( Threads REQUIRED )  # Multithreading package required

# add library directory
include_directories(../library/include)

# copy data files
FILE(COPY data DESTINATION "${CMAKE_BINARY_DIR}")
FILE(COPY data DESTINATION "${CMAKE_BINARY_DIR}/${CONFIGURATION}")

#===================================================
#  Maze Runner
#===================================================

# child
add_executable(maze_runner_ui src/maze_runner_ui.cpp)
target_link_libraries(maze_runner_ui Threads::Threads)

# parent
add_executable(maze_runner_parent src/maze_runner_parent.cpp)
target_link_libraries(maze_runner_parent Threads::Threads)

# parent
add_executable(maze_runner_child src/maze_runner_child.cpp)
target_link_libraries(maze_runner_child Threads::Threads)

# link with unix realtime library
if(UNIX AND NOT APPLE)
    target_link_libraries(maze_runner_parent rt)
    target_link_libraries(maze_runner_child rt)
    target_link_libraries(maze_runner_ui rt)
endif()

#===================================================
# Malware
#===================================================

add_executable(malware src/malware.cpp)
target_link_libraries(malware Threads::Threads)

# link with unix realtime library
if(UNIX AND NOT APPLE)
    target_link_libraries(malware rt)
endif()

