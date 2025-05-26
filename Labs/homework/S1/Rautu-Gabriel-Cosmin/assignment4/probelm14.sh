#!/bin/bash
[ $# -ne 1 ] && { echo "Usage: $0 <source.c>"; exit 1; }
f=$1
[ -f "$f" ] || { echo "File not found: $f"; exit 1; }

vars=$(ctags -x --c-kinds=gv "$f" | awk '{print $1}' | sort -u)
for v in $vars; do
  occ=$(grep -n -w -- "$v" "$f")
  cnt=$(printf "%s\n" "$occ" | grep -c .)
  lines=$(printf "%s\n" "$occ" | cut -d: -f1 | paste -sd, -)
  [ -z "$lines" ] && lines="(none)"
  printf "%s: %d occurrence(s); lines: %s\n" "$v" "$cnt" "$lines"
done
