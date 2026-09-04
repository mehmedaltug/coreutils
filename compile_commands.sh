#!/bin/bash
# generate_compile_commands.sh

rm compile_commands.json

echo "[" > compile_commands.json
first=true

for cfile in src/*.c; do
    base=$(basename "$cfile" .c)

    if [ "$first" = true ]; then
        first=false
    else
        echo "," >> compile_commands.json
    fi

    cat >> compile_commands.json << EOF
  {
    "directory": "$(pwd)",
    "command": "gcc -Wall -Wextra -O2 -Ilib -c $cfile -o out/${base}.o",
    "file": "$cfile"
  }
EOF
done

echo "" >> compile_commands.json
echo "]" >> compile_commands.json
