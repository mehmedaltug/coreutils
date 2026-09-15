import subprocess
import platform

executable_postfix = ".exe" if platform.system() == "Windows" else ""

def main() -> None:
    result = subprocess.run(["out/cut" + executable_postfix, "-f2", "-d ", "123 321"], capture_output=True, text=True)
    assert result.stdout == "321\n"
    print("3 Arg Usage: PASSED")

    result = subprocess.run(["sh", "-c", "echo \"123 321\" | out/cut" + executable_postfix + " -f2 -d' ' \"123 321\""], capture_output=True, text=True)
    assert result.stdout == "321\n"
    print("2 Arg Usage: PASSED")

if __name__ == "__main__":
    main()
