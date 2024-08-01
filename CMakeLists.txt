cmake_minimum_required(VERSION 3.0)
project(ROOT_MT)

find_package(nlohmann_json 3.11.3 REQUIRED)
find_package(ROOT REQUIRED)

add_executable(ROOT_MT mt_hello.cpp)

# Link against ROOT libraries
target_link_libraries(ROOT_MT PUBLIC ${ROOT_LIBRARIES})
# Add ROOT include directories
target_include_directories(ROOT_MT PUBLIC ${ROOT_INCLUDE_DIRS})
# Add ROOT flags
target_compile_options(ROOT_MT PUBLIC
    -std=c++17
    -m64
    # -pipe
    # -fsigned-char
    # -fno-common
    # -Qunused-arguments
    -pthread
    -stdlib=libc++
)

add_executable(ROOT_MT2 mt_hello_array.cpp)
target_link_libraries(ROOT_MT2 PUBLIC ${ROOT_LIBRARIES})
target_include_directories(ROOT_MT2 PUBLIC ${ROOT_INCLUDE_DIRS})
target_compile_options(ROOT_MT2 PUBLIC
    -std=c++17
    -m64
    # -pipe
    # -fsigned-char
    # -fno-common
    # -Qunused-arguments
    -pthread
    -stdlib=libc++
)

add_executable(MTTH1 mt_TH1.cpp)
target_link_libraries(MTTH1 PUBLIC ${ROOT_LIBRARIES})
target_include_directories(MTTH1 PUBLIC ${ROOT_INCLUDE_DIRS})
target_compile_options(MTTH1 PUBLIC
    -std=c++17
    -m64
    # -pipe
    # -fsigned-char
    # -fno-common
    # -Qunused-arguments
    -pthread
    -stdlib=libc++
)

# root-config --libs
# root-config --cflags