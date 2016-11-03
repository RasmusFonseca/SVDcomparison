# SVDcomparison

This repo outlines a quick-and-dirty running time comparison between singular value decomposition (SVD) computations using three popular libraries -- GSL, MKL, and CUDA. The CPU-time of the core computation was recorded with the `clock` function. The output of this corresponded reasonably well with the output out the `time` command. More specialized timing should probably be performed for the CUDA call -- feel free to add a pull-request. 

# Running code

The code depends on CMake, Gnu Scientific Library (GSL), Intels Math Kernel Libraries (MKL) and Nvidias CUDA libraries. Ideally, CMake will find and configure everything but you might need to play around with the CMakeLists.txt to get it working. After installing dependencies type
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
Examples on how each method was run are outlined in the sections below. The following table summarizes runtimes in milliseconds for each method on each matrix. The 'sparsity' is the number of zero-values divided by total entries in the matrix. The [3LMK](http://www.rcsb.org/pdb/explore/explore.do?structureId=3LMK) matrix is a typical (large) use-case for [KGS](https://simtk.org/projects/kgs/) molecular sampling.

| Matrix  | Dimension | Sparsity | Method | Time (ms) |
|---------|-----------|----------|--------|-----------|
| 3LMK    | 3735x2969 | 0.979    | GSL    | 470090    |
| 3LMK    | 3735x2969 | 0.979    | MKL    | 29590     |
| 3LMK    | 3735x2969 | 0.979    | CUDA   | 78800     |
| dense1k | 1000x1000 | 0.000    | GSL    | 9750      |
| dense1k | 1000x1000 | 0.000    | MKL    | 1640      |
| dense1k | 1000x1000 | 0.000    | CUDA   | 5340      |

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
