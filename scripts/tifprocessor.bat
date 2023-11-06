@echo off
setlocal enabledelayedexpansion

rem Spécifiez le chemin vers le dossier contenant les images TIFF
set "inputFolder=.\TM250m\"

rem Spécifiez la largeur et la hauteur de l'image d'origine
set "imageSize=21600"

rem Spécifiez la taille des tuiles voulues
set "tileSize=216"

rem Calculez le nombre de tuiles en largeur et en hauteur
set /a "numTilesX=!imageSize! / !tileSize!"
set /a "numTilesY=!imageSize! / !tileSize!"

rem Parcourez tous les fichiers TIFF dans le dossier
for %%f in ("%inputFolder%\*.tif") do (
    set "inputFile=%%~nf"
    set "outputFolder=%inputFolder%\!inputFile!"

    rem Créez un dossier pour chaque image
    mkdir "!outputFolder!"

    rem Divisez l'image en tuiles et stockez-les dans le dossier
    for /l %%x in (0,%tileSize%,!imageSize!) do (
        for /l %%y in (0,%tileSize%,!imageSize!) do (
            set /a x_end=%%x+%tileSize%
            set /a y_end=%%y+%tileSize%
            gdal_translate -of PNM -srcwin %%x %%y %tileSize% %tileSize% "%%f" "!outputFolder!\!inputFile!_%%x_%%y.ppm"
        )
    )
)

rem Supprimez tous les fichiers XML à la fin si vous ne voulez pas garder les infos de géoréférence
for %%f in ("%inputFolder%\*.xml") do (
    del "%%f"
)

echo Le processus est terminé.
pause
