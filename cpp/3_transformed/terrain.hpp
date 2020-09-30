#ifndef TERRAIN__H
#define TERRAIN__H 1

void curvatureCPU(int ncols, int nrows, float xcellsize, float ycellsize,
          float* input, float * __restrict__ output, int ldx);

void slopeAspectCPU(int ncols, int nrows, float xcellsize, float ycellsize,
              float* input, float* outputS, float * __restrict__ outputA , int ldx);

void aspectCPU(int ncols, int nrows, float* input, float* output, int ldx);

void slopeCPU(int ncols, int nrows, float xcellsize, float ycellsize,
              float* input, float* output, int ldx);

#endif
