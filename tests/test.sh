NAME=cub3d
VALGRIND="valgrind \
  --leak-check=full \
  --show-leak-kinds=all \
  --track-origins=yes \
  --num-callers=30 \
  --track-fds=yes \
  --quiet \
"
${VALGRIND} ./${NAME} maps/invalid1.cub || true
${VALGRIND} ./${NAME} maps/invalid2.cub || true
${VALGRIND} ./${NAME} maps/invalid3.cub || true
${VALGRIND} ./${NAME} maps/invalid4.cub || true
${VALGRIND} ./${NAME} maps/invalid5.cub || true