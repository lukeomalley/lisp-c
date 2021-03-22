cc -std=c99 -Wall lib/*.c src/**/*.c src/lispc.c  -ledit -lm -o ./bin/lispc && echo "Successfully Compiled Lispc!\n" && ./bin/lispc
