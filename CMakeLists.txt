cmake_minimum_required(VERSION 3.5.1)
project(JNISample)

set(CMAKE_CXX_STANDARD 11)

include_directories("/usr/lib/jvm/java-8-oracle/include")
include_directories("/usr/lib/jvm/java-8-oracle/include/linux")
add_library(jni_sample SHARED library.cpp library.h com_example_Main.h com_example_Main.cpp)

link_directories("/usr/lib/jvm/java-8-oracle/jre/lib/amd64/server")
add_executable(standalone_jvm standalone_jvm.cpp)
target_link_libraries(standalone_jvm "jvm")

add_executable(standalone_jvm_multiple_thread standalone_jvm_multiple_thread.cpp)
target_link_libraries(standalone_jvm_multiple_thread "jvm" "pthread")

# to build the java target
file(GLOB JAVA_SOURCES "${PROJECT_SOURCE_DIR}/java/com/example/*.java")
add_custom_command(TARGET standalone_jvm POST_BUILD
        COMMAND javac \""${JAVA_SOURCES}"\")

add_definitions(-DCLASS_PATH="${PROJECT_SOURCE_DIR}/java")
