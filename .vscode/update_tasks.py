import os
import json

def get_directory_structure(source_path):
    if not os.path.exists(source_path):
        raise ValueError(f"Error: The 'Source' folder does not exist at {source_path}")

    folder_structure = []
    cpp_files = []
    for root, dirs, files in os.walk(source_path):
        dirs[:] = [d for d in dirs if not d.startswith(".") and "." not in d]
        relative_root = os.path.relpath(root, source_path)
        folder_structure.append(relative_root)

        for file in files:
            if file.endswith(".cpp"):
                cpp_files.append(os.path.join(relative_root, file))

    return folder_structure, cpp_files

def remove_dot_backslash(path):
    return path.replace("\\.\\", "\\")

def update_tasks_json(file_path, source_path, folder_structure, cpp_files):
    if not os.path.exists(file_path):
        print(f"Warning: File {file_path} does not exist. Skipping.")
        return

    try:
        with open(file_path, "r") as file:
            data = json.load(file)
    except json.decoder.JSONDecodeError as e:
        print(f"Warning: Failed to parse {file_path} due to JSONDecodeError: {e}")
        return

    if "tasks" in data:
        for task in data["tasks"]:
            if "label" in task and "c++" in task["label"].lower():
                if "args" in task:
                    task["args"] = [arg for arg in task["args"] if not arg.startswith("-I") and not arg.endswith(".cpp")]

                    task["args"] = [remove_dot_backslash(os.path.join("${workspaceFolder}", "Source", cpp_file)) for cpp_file in cpp_files] + task["args"]

                    for folder in folder_structure:
                        include_folder = os.path.join("${workspaceFolder}", "Source", folder)
                        if "." not in include_folder:
                            task["args"].append(f"-I{remove_dot_backslash(include_folder)}")

    with open(file_path, "w") as file:
        json.dump(data, file, indent=4)

def main():
    current_directory = os.getcwd()
    base_directory = current_directory
    source_path = os.path.join(base_directory, "Source")
    folder_structure, cpp_files = get_directory_structure(source_path)
    tasks_json_path = os.path.join(base_directory, ".vscode", "tasks.json")
    update_tasks_json(tasks_json_path, source_path, folder_structure, cpp_files)

if __name__ == "__main__":
    main()
