import os
import json

def get_directory_structure(source_path):
    if not os.path.exists(source_path):
        raise ValueError(f"Error: The 'Source' folder does not exist at {source_path}")

    folder_structure = {}
    for root, dirs, files in os.walk(source_path):
        dirs[:] = [d for d in dirs if not d.startswith(".")]
        relative_root = os.path.relpath(root, source_path)
        folder_structure[relative_root] = dirs

    return folder_structure

def update_json_file(file_path, base_directory, folder_structure):
    if not os.path.exists(file_path):
        print(f"Warning: File {file_path} does not exist. Skipping.")
        return

    with open(file_path, "r") as file:
        data = json.load(file)

    if "configurations" in data:
        for config in data["configurations"]:
            if "includePath" in config:
                config["includePath"] = []
                include_paths = [
                    os.path.join("${workspaceFolder}", "Source") + "\\**"
                ]
                for folder, subfolders in folder_structure.items():
                    folder_path = os.path.join("${workspaceFolder}", "Source", folder)
                    if "." not in folder_path and folder_path != "${workspaceFolder}\\Source":
                        include_paths.append(folder_path + "\\**")
                
                print(f"Adding includePaths: {include_paths}")
                config["includePath"] = include_paths

    with open(file_path, "w") as file:
        json.dump(data, file, indent=4)

def main():
    current_directory = os.getcwd()
    base_directory = current_directory
    source_path = os.path.join(base_directory, "Source")
    folder_structure = get_directory_structure(source_path)
    print(f"Folder structure: {folder_structure}")
    vscode_path = os.path.join(base_directory, ".vscode")
    cpp_properties_json_path = os.path.join(vscode_path, "c_cpp_properties.json")
    update_json_file(cpp_properties_json_path, base_directory, folder_structure)

if __name__ == "__main__":
    main()
