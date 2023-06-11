mkdir -p build;

clang++ position.cpp main.cpp -o ./build/main;

./build/main;

# debug
# clang++ -g position.cpp main.cpp -o ./build/main;

# lldb ./build/main;

# compile
# clang++ -c position.cpp main.cpp;

# ar -crv main.a position.o main.o;

# clang++ main.a -o main.out;

# rm *.o *.a *.out;