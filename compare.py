#!/usr/bin/env python

import numpy as np
from osgeo import gdal
import sys


def load_raster(file_name):
    gdal.UseExceptions()
    try:
        ds = gdal.Open(file_name)
        band = ds.GetRasterBand(1)
        data = band.ReadAsArray()
        return data
    except:
        sys.exit("Can't load raster from {}.".format(file_name))


def max_diff(raster_1, raster_2):
    return np.max(abs(raster_1[1:-1, 1:-1] - raster_2[1:-1, 1:-1]))


def main():

    try:
        file_1 = sys.argv[1]
        file_2 = sys.argv[2]
    except IndexError:
        sys.exit("Usage:\n\tcompare RASTER1 RASTER2")

    raster_1 = load_raster(file_1)
    raster_2 = load_raster(file_2)

    if not raster_1.shape == raster_2.shape:
        sys.exit("Different shapes of rasters")

    print("Maximum difference: {}".format(max_diff(raster_1, raster_2)))


if __name__ == "__main__":
    main()
