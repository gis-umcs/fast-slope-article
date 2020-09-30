#ifndef MEM_H
#define MEM_H

#include <mm_malloc.h>
#include <algorithm>

#ifdef _XPHI
#define ALIGNSIZE 64
#else
#define ALIGNSIZE 32
#endif

// gcc
#define __assume_aligned(pointer, alignment) pointer = (decltype(pointer))__builtin_assume_aligned(pointer, alignment)

template <typename T>
constexpr int compute_ldx(int nXSize)
{
    int ald = ALIGNSIZE / sizeof(T);
    int ldx = ald * (nXSize / ald) + (nXSize % ald ? ald : 0);
    return ldx;
}

template <typename T>
T *alloc(int nXSize, int nYSize)
{
    int ldx = compute_ldx<T>(nXSize);
    T *w = (T *)_mm_malloc(sizeof(T) * ldx * nYSize, ALIGNSIZE);
    return w;
}

template <typename T>
T *alloc(int nXSize, int nYSize, T nodata)
{
    int ldx = compute_ldx<T>(nXSize);
    T *w = alloc<T>(nXSize, nYSize);
    std::fill(w, w + ldx * nYSize, nodata);
    return w;
}

template <typename T>
void release(T *mem)
{
    _mm_free(mem);
}

#endif
