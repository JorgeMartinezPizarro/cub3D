VALGRIND="valgrind \
	--track-fds=yes \
	--suppressions=./scripts/mlx.supp \
	--gen-suppressions=all \
	--leak-check=full \
	--show-leak-kinds=all \
	--track-origins=yes \
	--trace-children=no \
"
make build-san
./cub3D_san maps/level1.cub
make clean-san