#! /usr/bin/sh

SCRIPT_DIR="$(dirname $0)"
DEST_DIR="$1"

mkdir -p "$DEST_DIR"
rsync -azv --delete "$SCRIPT_DIR"/*.h "$SCRIPT_DIR"/*.c "$SCRIPT_DIR/Makefile" "$DEST_DIR" 
"$SCRIPT_DIR/libft/export_to_42.sh" "$DEST_DIR/libft"
