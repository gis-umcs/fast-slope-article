Source code for the article "Fast slope algorithm as an example of a methodology for parallelization and vectorization of neighbourhood operation for multi-core architectures".
====

The `cpp` directory contains five versions of the source code used to perform the numerical experiment (section 4). Each directory contains a different implementation (base, parallelized base, transformed, transformed with SIMD, parallelized transformed with SIMD).
To compile the program run `make` command. To set the level of optimization (compiler options: `-O0`, `-O1`, `-O2`, `-O3`):

`make OPT=<optimization level>`

e.g:

`make OPT=0`

or

`make OPT=1`


To run the program:

`slope DEM_FILE SLOPE_FILE`


The `compare.py` program (used in section 4.5 for the comparison of the results accuracy) prints the maximum-norm of element-wise differences between two rasters (GeoTIFF files).

Usage:

`python compare.py RASTER1 RASTER2`
