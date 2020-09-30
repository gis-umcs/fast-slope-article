#include <cmath>

#include "mem.hpp"
#include "terrain.hpp"

#define RADTODEG 57.29577951f

void slopeCPU(int ncols, int nrows, float xcellsize, float ycellsize,
              float *input, float *output, int ldx)
{

    __assume_aligned(input, ALIGNSIZE);
    __assume_aligned(output, ALIGNSIZE);
    int j;
    float *temp = (float *)_mm_malloc(sizeof(float) * ncols, ALIGNSIZE);

    for (int i = 1; i < nrows - 1; i++)
    {

        float *pRowInp = &input[i * ldx];
        float *pUppInp = pRowInp - ldx;
        float *pLowInp = pRowInp + ldx;
        float *pRowOut = &output[i * ldx];

        __assume_aligned(pRowInp, ALIGNSIZE);
        __assume_aligned(pUppInp, ALIGNSIZE);
        __assume_aligned(pLowInp, ALIGNSIZE);
        __assume_aligned(pRowOut, ALIGNSIZE);
#pragma omp simd
        for (j = 1; j < ncols - 1; j++)
        {
            pRowOut[j] = (pLowInp[j - 1] + 2 * pLowInp[j] + pLowInp[j + 1]) / (8.0f * ycellsize);
        }
#pragma omp simd
        for (j = 1; j < ncols - 1; j++)
        {
            pRowOut[j] -= (pUppInp[j - 1] + 2 * pUppInp[j] + pUppInp[j + 1]) / (8.0f * ycellsize);
        }
#pragma omp simd
        for (j = 1; j < ncols - 1; j++)
        {
            temp[j] = 2 * (pRowInp[j + 1] - pRowInp[j - 1]) / (8.0f * xcellsize);
        }
#pragma omp simd
        for (j = 1; j < ncols - 1; j++)
        {
            temp[j] += (pLowInp[j + 1] - pLowInp[j - 1] + pUppInp[j + 1] - pUppInp[j - 1]) / (8.0f * xcellsize);
        }
#pragma omp simd
        for (j = 1; j < ncols - 1; j++)
        {
            pRowOut[j] = std::atan(std::sqrt(pRowOut[j] * pRowOut[j] + temp[j] * temp[j])) * RADTODEG;
        }
    }
    _mm_free(temp);
}
