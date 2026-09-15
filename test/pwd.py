from pathlib import Path
import subprocess
import platform

executable_postfix = ".exe" if platform.system() == "Windows" else ""

def main() -> None:
    result = subprocess.run(["out/pwd" + executable_postfix], capture_output=True, text=True)
    assert result.stdout == str(Path.cwd()) + "\n"
    print("Regular Usage: PASSED")

if __name__ == "__main__":
    main()
