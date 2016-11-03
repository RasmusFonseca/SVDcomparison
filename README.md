# SVDcomparison

This repo outlines a quick-and-dirty running time comparison between singular value decomposition (SVD) computations using three popular libraries -- GSL, MKL, and CUDA. 

# Running code

The library depends on CMake, Gnu Scientific Library (GSL), Intels Math Kernel Libraries (MKL) and Nvidias CUDA libraries. Ideally, CMake will find and configure everything but you might need to play around with the CMakeLists.txt to get it working. After installing dependencies type
```bash
$ mkdir build
$ cd build
$ cmake -DCMAKE_BUILD_TYPE=Release ..
$ make
```
to compile. If everything works, the `SVDcompare` executable should now be in the `build` directory. The program takes two argument, an SVD method selector (either "GSL", "MKL", or "CUDA") and a clear-text matrix-file:
```bash
$ ./SVDcompare GSL ../matrices/tiny.txt
$ ./SVDcompare MKL ../matrices/tiny.txt
$ ./SVDcompare CUDA ../matrices/tiny.txt
```

# Results
Details of how each method was run are outlined in the sections below. The following table summarizes runtimes in milliseconds for each method on each matrix:
| Matrix | Method | Time (ms) |
|--------|--------|-----------|
| 3LMK   | GSL    | 470090    |
| 3LMK   | MKL    | 29590     |
| 3LMK   | CUDA   | 78800     |


## GSL
```bash
$ ./SVDcompare GSL ../matrices/3LMK_jacobian.txt
readMatrix(../matrices/3LMK_jacobian.txt)
.. done reading
Computing SVD with GSL
.. done. Took: 470090 ms
```

## MKL

```bash
$ export MKL_NUM_THREADS=1
$ ./SVDcompare MKL ../matrices/3LMK_jacobian.txt
readMatrix(../matrices/3LMK_jacobian.txt)
.. done reading
Computing SVD with MKL
.. done. Took: 29590 ms
```

## CUDA
```bash
$ nvidia-smi 
Wed Nov  2 22:07:55 2016       
+------------------------------------------------------+                       
| NVIDIA-SMI 352.39     Driver Version: 352.39         |                       
|-------------------------------+----------------------+----------------------+
| GPU  Name        Persistence-M| Bus-Id        Disp.A | Volatile Uncorr. ECC |
| Fan  Temp  Perf  Pwr:Usage/Cap|         Memory-Usage | GPU-Util  Compute M. |
|===============================+======================+======================|
|   0  Tesla K20Xm         On   | 0000:04:00.0     Off |                    0 |
| N/A   25C    P8    17W / 235W |     14MiB /  5759MiB |      0%      Default |
+-------------------------------+----------------------+----------------------+
                                                                               
+-----------------------------------------------------------------------------+
| Processes:                                                       GPU Memory |
|  GPU       PID  Type  Process name                               Usage      |
|=============================================================================|
|  No running processes found                                                 |
+-----------------------------------------------------------------------------+
$ ./SVDcompare CUDA ../matrices/3LMK_jacobian.txt
readMatrix(../matrices/3LMK_jacobian.txt)
.. done reading
Computing SVD with CUDA
.. done. Took: 78800 ms
```
