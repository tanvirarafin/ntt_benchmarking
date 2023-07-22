This is a benchmarking suite for number theoratic transform. This should act as a starting point for testing your own NTT implementation. The scripts in this repo is heavily derived from https://github.com/IBM/optimized-number-theoretic-transform-implementations/tree/main. The licenses of the original repo is maintained.

# Useage
Create a build and build/results directory, and then make and execute the package from the build directory. The test values are written in the results directory. 

```
mkdir -p build/results
cd build
cmake ..
make
./ntt_experiments
```


