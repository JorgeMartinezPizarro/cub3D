#!/bin/sh

BASE="$(cd "$(dirname "$0")/.." && pwd)"

# Cuenta lineas de codigo reales: elimina comentarios /* */ (incluidos
# multilinea) y //, y descarta lineas en blanco.
count_code() {
    files=$(find "$@" 2>/dev/null)
    [ -z "$files" ] && { echo 0; return; }
    cat $files | awk '
        {
            line = $0
            out = ""
            if (inblock) {
                p = index(line, "*/")
                if (p == 0) next
                line = substr(line, p + 2)
                inblock = 0
            }
            while ((s = index(line, "/*")) > 0) {
                out = out substr(line, 1, s - 1)
                rest = substr(line, s + 2)
                e = index(rest, "*/")
                if (e == 0) { inblock = 1; line = ""; break }
                line = substr(rest, e + 2)
            }
            if (!inblock) out = out line
            sub(/\/\/.*/, "", out)
            if (out ~ /[^ \t]/) n++
        }
        END { print n + 0 }
    '
}

nc=$(count_code "$BASE/srcs" "$BASE/includes" -type f -name "*.c")
nh=$(count_code "$BASE/srcs" "$BASE/includes" -type f -name "*.h")
ns=$(count_code "$BASE/scripts" -type f -name "*.sh")
mk=$(count_code "$BASE" -maxdepth 1 -type f \
    \( -name "Makefile" -o -name "makefile" -o -name "*.mk" \))
total=$((nc + nh + ns + mk))

# --- Colores (se desactivan si la salida no es una terminal) ---
if [ -t 1 ]; then
    B="$(printf '\033[1m')"; DIM="$(printf '\033[2m')"; R="$(printf '\033[0m')"
    RED="$(printf '\033[31m')"; GREEN="$(printf '\033[32m')"
    YELLOW="$(printf '\033[93m')"; BLUE="$(printf '\033[34m')"
    BOLDW="$(printf '\033[1;37m')"
else
    B=""; DIM=""; R=""; RED=""; GREEN=""; YELLOW=""; BLUE=""; BOLDW=""
fi

LW=14   # ancho columna etiqueta
NW=10   # ancho columna numero
TITLE="Lines of Code"

rep() {
    i=0
    s=""
    while [ $i -lt "$1" ]; do
        s="$s$2"
        i=$((i+1))
    done
    printf '%s' "$s"
}

row() { # $1 color  $2 label  $3 value
    printf "%s│%s %s%-*s%s %s│%s %s%*d%s %s│%s\n" \
        "$DIM" "$R" "$1" "$LW" "$2" "$R" \
        "$DIM" "$R" "$1" "$NW" "$3" "$R" "$DIM" "$R"
}

line_mid() {
    printf "%s├%s┼%s┤%s\n" \
        "$DIM" "$(rep $((LW+2)) ─)" "$(rep $((NW+2)) ─)" "$R"
}

line_bot() {
    printf "%s└%s┴%s┘%s\n" \
        "$DIM" "$(rep $((LW+2)) ─)" "$(rep $((NW+2)) ─)" "$R"
}

WIDTH=$((LW + NW + 5))
title_pad=$(( (WIDTH - ${#TITLE}) / 2 ))

echo

# Header
printf "%s┌%s┐%s\n" "$DIM" "$(rep $WIDTH ─)" "$R"
printf "%s│%s%*s%s%s%s%*s%s│%s\n" \
    "$DIM" "$R" "$title_pad" "" "$B$RED" "$TITLE" "$R" \
    "$((WIDTH - title_pad - ${#TITLE}))" "" "$DIM" "$R"
line_mid

row "$GREEN"  ".c"       "$nc"
row "$BLUE"   ".h"       "$nh"
row "$YELLOW" ".sh"      "$ns"
row "$RED"    "Makefile" "$mk"
line_mid
row "$BOLDW"  "TOTAL"    "$total"
line_bot

echo
