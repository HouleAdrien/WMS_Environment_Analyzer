@echo off
setlocal enabledelayedexpansion

rem Specify the path to the folder containing the TIFF images
set "inputFolder=.\ESA_WorldCover_10m_2021_v200_60deg_macrotile_N30W060\"

rem Iterate over all TIFF files in the folder
for %%f in ("%inputFolder%\*.tif") do (
    rem Extract the file name without the extension
    set "baseFileName=%%~nf"
    
    rem Use gdal_translate to convert only the first band to PPM format
    gdal_translate -expand rgb -of PNM "%%f" "%inputFolder%\!baseFileName!.ppm"
)

echo Process is complete.
pause
