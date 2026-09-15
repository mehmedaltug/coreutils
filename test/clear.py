import subprocess
import platform

executable_postfix = ".exe" if platform.system() == "Windows" else ""

def main() -> None:
    result = subprocess.run(["out/clear" + executable_postfix], capture_output=True, text=True)
    assert result.stdout == "\033[H\033[2J"
    print("Regular Usage: PASSED")

if __name__ == "__main__":
    main()
