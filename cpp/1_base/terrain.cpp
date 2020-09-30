#include <cmath>

#include "terrain.hpp"

#define RADTODEG 57.29577951f

void slopeCPU(int ncols, int nrows, float xcellsize, float ycellsize,
              float *input, float *outputS, int ldx)
{
    for (int i = 1; i < nrows - 1; i++)
    {
        for (int j = 1; j < ncols - 1; j++)
        {
            float dzdx = ((input[(i - 1) * ncols + j + 1] + 2.0 * input[i * ncols + j + 1] + input[(i + 1) * ncols + j + 1]) -
                          (input[(i - 1) * ncols + j - 1] + 2.0 * input[i * ncols + j - 1] + input[(i + 1) * ncols + j - 1])) /
                         8.0;
            float dzdy = ((input[(i + 1) * ncols + j - 1] + 2.0 * input[(i + 1) * ncols + j] +
                           input[(i + 1) * ncols + j + 1]) -
                          (input[(i - 1) * ncols + j - 1] + 2.0 * input[(i - 1) * ncols + j] +
                           input[(i - 1) * ncols + j + 1])) /
                         8.0;

            dzdx /= xcellsize;
            dzdy /= ycellsize;

            float rise_run = std::sqrt(dzdx * dzdx + dzdy * dzdy);
            outputS[i * ncols + j] = std::atan(rise_run) * RADTODEG;
        }
    }
}
