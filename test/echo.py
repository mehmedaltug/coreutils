import subprocess
import platform

executable_postfix = ".exe" if platform.system() == "Windows" else ""

def main() -> None:
    result = subprocess.run(["out/echo" + executable_postfix, "321"], capture_output=True, text=True)
    assert result.stdout == "321\n"
    print("Single Arg Usage: PASSED")

    result = subprocess.run(["out/echo" + executable_postfix, "321", "321"], capture_output=True, text=True)
    assert result.stdout == "321 321\n"
    print("Multi Arg Usage: PASSED")

if __name__ == "__main__":
    main()
