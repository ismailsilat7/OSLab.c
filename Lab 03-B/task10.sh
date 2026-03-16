#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <directory_path>"
    exit 1
fi

DIR="$1"
DAYS=10

file_count=0
dir_count=0

cutoff=$(( $(date +%s) - DAYS*24*60*60 ))

cleanup() {
    local path="$1"

    for item in "$path"/*; do
        [ -e "$item" ] || continue

        if [ -f "$item" ]; then
            mtime=$(stat -c %Y "$item")
            if [ "$mtime" -lt "$cutoff" ]; then
                rm "$item"
                echo "Deleted file: $item"
                ((file_count++))
            fi

        elif [ -d "$item" ]; then
            cleanup "$item"  # recursive

            if [ -d "$item" ] && [ -z "$(ls -A "$item")" ]; then
                rmdir "$item"
                echo "Removed directory: $item"
                ((dir_count++))
            fi
        fi
    done
}

cleanup "$DIR"

echo "Cleanup completed."
echo "Files removed: $file_count"
echo "Directories removed: $dir_count"
