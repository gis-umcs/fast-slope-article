#include "terrain.hpp"
#include "time.hpp"
#include "mem.hpp"

#include "gdal_priv.h"

#include <cstdlib>
#include <iostream>
#include <string>



int main(int argc, char *argv[])
{
    if (argc < 3) {
        std::cerr << "Usage:\n\tslope dem_file slope_file\n";
        std::exit(1);
    }
    std::string in_file(argv[1]);
    std::string out_file(argv[2]);

    GDALAllRegister();

    double t1 = now();

    /////////////
    /* Reading */
    /////////////

    GDALDataset *ds;
    ds = (GDALDataset *) GDALOpen(in_file.c_str(), GA_ReadOnly);
    if (ds == nullptr) {
        std::cerr << "Can't open file '" << in_file << "'.\n";
        std::exit(1);
    }

    double gt[6];
    ds->GetGeoTransform(gt);
    double x_cell_size = gt[1];
    double y_cell_size = gt[5];
    std::string proj = std::string(ds->GetProjectionRef());
    int x_size = ds->GetRasterXSize();
    int y_size = ds->GetRasterYSize();

    float *dem_raster = alloc<float>(x_size, y_size);
    int ldx = compute_ldx<float>(x_size) * sizeof(float);

    GDALRasterBand *band = ds->GetRasterBand(1);
    if (band->RasterIO(GF_Read, 0, 0, x_size, y_size, dem_raster, x_size, y_size, GDT_Float32, 0, ldx) != CE_None) {
        std::cerr << "Cannot read data.\n";
        std::exit(1);
    }

    double t2 = now();
    std::cout << "Reading time: " << t2 - t1 << std::endl;

    ///////////////
    /* Computing */
    ///////////////

    float nodata = -9999.0;
    float *slope_raster = alloc(x_size, y_size, nodata);
    slopeCPU(x_size, y_size, x_cell_size, y_cell_size, dem_raster, slope_raster, ldx);


    double t3 = now();
    std::cout << "Computing time: " << t3 - t2 << std::endl;

    ///////////////
    /* Writing */
    ///////////////

    GDALDriver *driver = ds->GetDriver();

    GDALDataset *ds_out = driver->Create(out_file.c_str(), x_size, y_size, 1, GDT_Float32, nullptr);
    if (ds_out == nullptr) {
        std::cerr << "Can't create slope file.\n";
        std::exit(1);
    }

    GDALRasterBand *band_out = ds_out->GetRasterBand(1);
    band_out->SetNoDataValue(nodata);
    if (band_out->RasterIO(GF_Write, 0, 0, x_size, y_size, slope_raster, x_size, y_size, GDT_Float32, 0, ldx) != CE_None) {
        std::cerr << "Cannot write data.\n";
        std::exit(1);
    }

    double t4 = now();
    std::cout << "Writing time: " << t4 - t3 << std::endl;


    std::cout << "Total time: " << t4 - t1 << std::endl;


}
