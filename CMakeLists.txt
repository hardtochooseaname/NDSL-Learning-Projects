cmake_minimum_required(VERSION 3.5)  

# Create a project
# and top level 'CMakeLists.txt' should be in the root dir of this project
project(kv) 

# Add source files and specify a target executable file
# that cmake will generate for this project
add_executable(kv chicken-twolegs.c functions.c)

# Add libraries needed linking
target_link_libraries(kv readline)

