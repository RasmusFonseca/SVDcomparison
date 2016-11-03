cmake_minimum_required (VERSION 2.8.8)

project(SVDcompare)


# Enable C++11 support
#include(CheckCXXCompilerFlag)
#CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
#CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
#if(COMPILER_SUPPORTS_CXX11)
#	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
#elseif(COMPILER_SUPPORTS_CXX0X)
#	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
#else()
#	message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
#endif()
#	message (STATUS "${CMAKE_CXX_COMPILER} ${CMAKE_CXX_FLAGS}")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}")

find_package(GSL REQUIRED)
link_directories(   ${GSL_LIBRARY_DIR} )
include_directories(${GSL_INCLUDE_DIR} )

find_package(MKL REQUIRED)
include_directories(${MKL_INCLUDE_DIR})
link_libraries( mkl_intel_lp64 mkl_intel_thread mkl_core iomp5 pthread )

find_package(CUDA REQUIRED)
link_libraries(${CUDA_LIBRARIES} ${CUDA_cusolver_LIBRARY} ${CUDA_CUBLAS_LIBRARIES})
include_directories(${CUDA_INCLUDE_DIRS})

add_executable( SVDcompare main.cpp SVD.cpp SVDGSL.cpp SVDMKL.cpp CudaSVD.cpp)

set( EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR} )



