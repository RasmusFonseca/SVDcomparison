cmake_minimum_required (VERSION 2.8.8)

project(SVDcompare)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}")

find_package(GSL REQUIRED)
link_directories(   ${GSL_LIBRARY_DIR} )
include_directories(${GSL_INCLUDE_DIR} )
link_libraries(gsl)

find_package(MKL REQUIRED)
include_directories(${MKL_INCLUDE_DIR})
link_libraries( mkl_intel_lp64 mkl_intel_thread mkl_core iomp5 pthread )

find_package(CUDA REQUIRED)
link_libraries(${CUDA_LIBRARIES} ${CUDA_TOOLKIT_ROOT_DIR}/lib64/libcusolver.so ${CUDA_cusolver_LIBRARY} ${CUDA_CUBLAS_LIBRARIES})
include_directories(${CUDA_INCLUDE_DIRS})
message("CUDA_TOOLKIT_ROOT_DIR ${CUDA_TOOLKIT_ROOT_DIR}")
message("CUDA_CUBLAS_LIBRARIES ${CUDA_CUBLAS_LIBRARIES}")

add_executable( SVDcompare main.cpp SVD.cpp SVDGSL.cpp SVDMKL.cpp CudaSVD.cpp)

set( EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR} )



