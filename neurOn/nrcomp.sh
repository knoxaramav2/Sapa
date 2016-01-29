echo Starting Compilation
LIBS=-lncurses
SRCF="-c Launcher.cpp -c Collections.cpp -c Linker.cpp"
OBJS="Launcher.o Collections.o Linker.o"
OUTPUT="-oneurOn"
STANDARD=-std=c++14

g++ $SRCF $LIBS $STANDARD -m64
g++ $OBJS $OUTPUT $LIBS $STANDARD -m64
echo done
