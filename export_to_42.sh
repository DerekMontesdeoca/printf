#! /usr/bin/sh

SCRIPT_DIR=$(dirname $0)

mkdir -p $1
rsync -azv *.h *.c Makefile $1 
"$SCRIPT_DIR/libft/export_to_42.sh" $1/libft
