#include <emu.h>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

int main(int argc, char **argv) {
    printf("starting\n");
    return emu_run(argc, argv);
}