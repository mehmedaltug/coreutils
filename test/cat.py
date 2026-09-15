import subprocess
import platform

executable_postfix = ".exe" if platform.system() == "Windows" else ""

def main() -> None:
    result = subprocess.run(["out/cat" + executable_postfix, "test/test.txt"], capture_output=True, text=True)
    assert result.stdout == "123\n"
    print("Single Arg Usage: PASSED")

    result = subprocess.run(["out/cat" + executable_postfix , "test/test.txt", "test/test.txt"], capture_output=True, text=True)
    assert result.stdout == "123\n123\n"
    print("Multi Arg Usage: PASSED")

if __name__ == "__main__":
    main()
