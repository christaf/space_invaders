#include "Engine.cpp"

int main(int argc, char **argv) {
    Engine engine(600, 600, "Space Invaders");
    engine.run(&argc, argv);
    return 0;
}