#!/bin/bash
#
# Builds cub3D and launches it on maps/level1.cub, maps/level2.cub, ...
# Every time a map is completed (all doors opened) it loads the next
# one automatically, until level 9 is reached or the player closes
# the window / presses ESC.

set -e

NAME=cub3D
MAPS_DIR=maps
MAX_LEVEL=9
WIN_PATTERN="You opened all"

make "$NAME"

map_info() {
	awk '
		/^[01 NSEWD]+$/ {
			if (length($0) > w)
				w = length($0)
			h++
			d += gsub(/D/, "D")
		}
		END { printf "%d %d %d", w, h, d }
	' "$1"
}

level=1
while [ "$level" -le "$MAX_LEVEL" ]; do
	map="${MAPS_DIR}/level${level}.cub"
	if [ ! -f "$map" ]; then
		echo "$map does not exist, stopping."
		break
	fi

	read -r w h doors <<< "$(map_info "$map")"
	echo "=== Map: $map | Size: ${w}x${h} | Doors to open: ${doors} ==="

	out=$(mktemp)
	./"$NAME" "$map" | tee "$out"

	if grep -q "$WIN_PATTERN" "$out"; then
		rm -f "$out"
		level=$((level + 1))
	else
		rm -f "$out"
		echo "Game ended on $map without completing it."
		exit 0
	fi
done

if [ "$level" -gt "$MAX_LEVEL" ]; then
	echo "You completed all $MAX_LEVEL levels."
fi
