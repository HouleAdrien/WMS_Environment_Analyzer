@echo off
setlocal enabledelayedexpansion

REM Chemin vers votre dossier satellite
set "folder=Esa_tile1_Sat"


REM Parcourir les fichiers .tif dans le dossier
for %%f in ("%folder%\*_Map*.tif") do (
    set "filename=%%~nxf"
    
    REM Extraire la partie du nom avant "_Map" inclus
    set "newname=!filename:_Map=&!"
    set "newname=!newname:&=!_Map.tif"

    REM Renommer le fichier
    echo Renommer: "%%f" en "!newname!"
    ren "%%f" "!newname!"
)

echo Renommage termine.
pause
