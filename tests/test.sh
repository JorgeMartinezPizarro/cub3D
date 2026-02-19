NAME=cub3D
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
${VALGRIND} ./${NAME} maps/invalid6.cub || true
${VALGRIND} ./${NAME} maps/invalid7.cub || true
${VALGRIND} ./${NAME} maps/invalid8.cub || true
${VALGRIND} ./${NAME} maps/invalid9.cub || true
${VALGRIND} ./${NAME} maps/invalid10.cub || true
${VALGRIND} ./${NAME} maps/invalid11.cub || true
${VALGRIND} ./${NAME} maps/invalid12.cube || true
${VALGRIND} ./${NAME} maps/invalid13_101x101.cub || true
${VALGRIND} ./${NAME} maps/invalid14.cub || true
