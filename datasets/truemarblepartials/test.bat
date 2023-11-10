@echo off
SET OUTPUT_VRT=full_image.vrt
SET OUTPUT_TIF=full_image.tif
SET OUTPUT_PPM=full_image.ppm

:: Ensure we're in the directory with the PPM and .aux.xml files
cd /d "./TrueMarble.250m.21600x21600.C3"

:: Convert all PPMs to GeoTIFFs using their respective .aux.xml files for georeferencing
for %%f in (*.ppm) do (
    gdal_translate -of GTiff "%%f" "%%~nf.tif"
)

:: Create a list of GeoTIFF files
dir /b *.tif | sort > tif_list.txt

:: Create a virtual raster of all the GeoTIFF images
gdalbuildvrt -input_file_list tif_list.txt %OUTPUT_VRT%

:: Convert the VRT to a GeoTIFF
gdal_translate -of GTiff %OUTPUT_VRT% %OUTPUT_TIF%

:: Convert the GeoTIFF to a final PPM
gdal_translate -of PPM %OUTPUT_TIF% %OUTPUT_PPM%

:: Optionally, remove the intermediate files
del *.tif
del %OUTPUT_VRT%
del %OUTPUT_TIF%

echo Finished merging and converting to PPM.
pause
