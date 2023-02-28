CMAKE_MINIMUM_REQUIRED (VERSION 3.2)
project (DataStructures)
add_executable(main main.c
                src/hashtable.c
                src/heap.c
                src/stack.c
                src/tree.c
                src/vector.c
                )
target_include_directories(main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)