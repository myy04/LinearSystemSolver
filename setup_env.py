import os
import subprocess
import sys
import venv

def main():
    venv_dir = ".venv"
    req_file = "requirements.txt"

    # Create the virtual environment
    print(f"Creating virtual environment in '{venv_dir}'...")
    builder = venv.EnvBuilder(with_pip=True)
    builder.create(venv_dir)

    # Determine pip executable path based on OS
    if os.name == 'nt':
        pip_exe = os.path.join(venv_dir, "Scripts", "pip")
    else:
        pip_exe = os.path.join(venv_dir, "bin", "pip")

    # Install requirements if the file exists
    if os.path.exists(req_file):
        print(f"Installing packages from {req_file}...")
        subprocess.check_call([pip_exe, "install", "-r", req_file])
        print("Packages installed successfully!")
    else:
        print(f"Warning: {req_file} not found. Skipping package installation.")

    # Print activation instructions
    print("\nSetup complete!")
    print("To activate the virtual environment, run:")
    if os.name == 'nt':
        print(f"  {venv_dir}\\Scripts\\activate")
    else:
        print(f"  source {venv_dir}/bin/activate")

if __name__ == "__main__":
    main()
