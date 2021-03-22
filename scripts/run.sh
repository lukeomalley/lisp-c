cc -std=c99 -Wall lispc.c ./lib/mpc.c -ledit -lm -o ./bin/lispc && echo "Compiled Lispc Successfully!\n"

./bin/lispc
