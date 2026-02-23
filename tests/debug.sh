VALGRIND="valgrind \
	--track-fds=yes \
	--suppressions=./tests/mlx.supp \
	--gen-suppressions=all \
	--leak-check=full \
	--show-leak-kinds=all \
	--track-origins=yes \
	--trace-children=no \
"

${VALGRIND} \
	./cub3D \
	maps/level1.cub