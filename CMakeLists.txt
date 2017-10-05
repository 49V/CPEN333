cmake_minimum_required(VERSION 3.2)
project(lab5)

set(CMAKE_CXX_STANDARD 11)
find_package( Threads REQUIRED )  # Multithreading package required

# add library directory
include_directories(../library/include)
# add json support
include_directories(include)

# copy data files
FILE(COPY data DESTINATION "${CMAKE_BINARY_DIR}")
FILE(COPY data DESTINATION "${CMAKE_BINARY_DIR}/Debug")

#===================================================
#  Music Library
#===================================================

set(MUSIC_LIBRARY_HEADERS
        src/music_library.h
        src/music_library_api.h
        src/music_library_json.h
        src/music_library_api_json.h
        src/music_library_messages.h
        src/music_library_song.h)

# server
add_executable(music_library_server src/music_library_server.cpp ${MUSIC_LIBRARY_HEADERS})
target_link_libraries(music_library_server Threads::Threads)

# client
add_executable(music_library_client src/music_library_client.cpp ${MUSIC_LIBRARY_HEADERS})
target_link_libraries(music_library_client Threads::Threads)

# link with unix realtime library
if(UNIX AND NOT APPLE)
    target_link_libraries(music_library_server rt)
    target_link_libraries(music_library_client rt)
endif()

if(WIN32)
    target_link_libraries(music_library_client wsock32 ws2_32)
    target_link_libraries(music_library_server wsock32 ws2_32)
endif()