import os
import subprocess

esa_folder = "Esa"
truemarble_folder = "Truemarble"
output_folder = "sortie"

if not os.path.exists(output_folder):
    os.makedirs(output_folder)

def get_bounding_box(file_path):
    info = subprocess.check_output(f'gdalinfo "{file_path}"', text=True)
    ul_line = [line for line in info.splitlines() if "Upper Left" in line][0]
    lr_line = [line for line in info.splitlines() if "Lower Right" in line][0]

    ulx, uly = ul_line.split('(')[1].split(')')[0].split(',')
    lrx, lry = lr_line.split('(')[1].split(')')[0].split(',')

    return float(ulx.strip()), float(uly.strip()), float(lrx.strip()), float(lry.strip())

def bounding_boxes_match(box1, box2):
    # Implement logic to determine if two bounding boxes match
    # Example: Check if they overlap or are within a certain distance
    ulx1, uly1, lrx1, lry1 = box1
    ulx2, uly2, lrx2, lry2 = box2

    # Simple overlap check (can be refined)
    return not (lrx1 < ulx2 or lrx2 < ulx1 or uly1 < lry2 or uly2 < lry1)

for esa_file in os.listdir(esa_folder):
    if esa_file.endswith(".tif"):
        esa_path = os.path.join(esa_folder, esa_file)
        esa_box = get_bounding_box(esa_path)

        for tm_file in os.listdir(truemarble_folder):
            if tm_file.endswith(".tif"):
                tm_path = os.path.join(truemarble_folder, tm_file)
                tm_box = get_bounding_box(tm_path)

                if bounding_boxes_match(esa_box, tm_box):
                    output_file = os.path.join(output_folder, f"{os.path.splitext(esa_file)[0]}_{tm_file}")
                    cut_command = f'gdalwarp -overwrite -te {esa_box[0]} {esa_box[3]} {esa_box[2]} {esa_box[1]} "{tm_path}" "{output_file}"'
                    print(f"Processing ESA: {esa_file}, Truemarble: {tm_file}")
                    os.system(cut_command)

print("Processing complete.")
