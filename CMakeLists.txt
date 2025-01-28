cmake_minimum_required(VERSION 3.20.0)
project("calc")

find_package(LLVM REQUIRED CONFIG)
message("Found LLVM ${LLVM_PACKAGE_VERSION}, build type ${LLVM_BUILD_TYPE}")
list(APPEND CMAKE_MODULE_PATH ${LLVM_DIR})

# Apply LLVM's compiler settings
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti -fno-exceptions")

include_directories(SYSTEM ${LLVM_INCLUDE_DIRS})

# Map LLVM components to libraries (Ensure all required components are linked)
llvm_map_components_to_libnames(llvm_libs
    Core
    Support
    Option
    IRReader
    BitstreamReader
    Remarks
    TargetParser
    Demangle
    MCParser
    Passes
    Analysis
    ExecutionEngine
    CodeGen
    BitWriter
    TransformUtils
)

add_subdirectory("src")
