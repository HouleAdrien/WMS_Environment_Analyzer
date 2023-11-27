import os
import subprocess

input_folder = "Esa_tile1"  # Remplacez par le nom de votre dossier source
output_folder = "Esa_tile1_resize"  # Dossier pour les images de sortie

if not os.path.exists(output_folder):
    os.makedirs(output_folder)

def resize_tiff(input_path, output_path):
    scale_factor = 0.04  # Facteur de réduction pour obtenir une taille environ 25 fois plus petite
    resize_command = f'gdal_translate -of GTiff -outsize {scale_factor * 100}% {scale_factor * 100}% "{input_path}" "{output_path}"'
    os.system(resize_command)

for file in os.listdir(input_folder):
    if file.endswith(".tif"):
        input_file_path = os.path.join(input_folder, file)
        output_file_path = os.path.join(output_folder, file)
        resize_tiff(input_file_path, output_file_path)

print("Traitement terminé.")
