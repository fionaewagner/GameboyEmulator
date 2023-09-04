#include <stdio.h>
#include "../include/bus.hpp"
#include "../include/emu.hpp"
#include "../include/cart.hpp"
#include "../include/cpu.hpp"
#include "../include/ui.hpp"
#include "../include/timer.hpp"
#include "../include/dma.hpp"
#include "../include/ppu.hpp"


/* 
  Emu components:

  |Cart|
  |CPU|
  |Address Bus|
  |PPU|
  |Timer|

*/

static emu_context ctx;

emu_context *emu_get_context() {
    return &ctx;
}

void *cpu_run(void *p) {
    printf("cpu runnings\n");
    timer_init();
    cpu_init();
    ppu_init();

    ctx.running = true;
    ctx.paused = false;
    ctx.ticks = 0;

    while(ctx.running) {
        if (ctx.paused) {
            delay(10);
            continue;
        }

        if (!cpu_step()) {
            printf("CPU Stopped\n");
            return 0;
        }
    }

    return 0;
}

int emu_run(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: emu <rom_file>\n");
        return -1;
    }

    if (!cart_load(argv[1])) {
        printf("Failed to load ROM file: %s\n", argv[1]);
        return -2;
    }

    printf("Cart loaded..\n");

    ui_init();
    
    pthread_t t1;

    printf("Before creating the CPU thread.\n");
    if (pthread_create(&t1, NULL, cpu_run, NULL) == 0) {
        printf("CPU thread created successfully.\n");
    } else {
        fprintf(stderr, "FAILED TO START MAIN CPU THREAD!\n");
        return -1;
    }

    u32 prev_frame = 0;

    while(!ctx.die) {
        usleep(1000);
        ui_handle_events();

        if (prev_frame != ppu_get_context()->current_frame) {
            ui_update();
        }

        prev_frame = ppu_get_context()->current_frame;
    }

    return 0;
}

void emu_cycles(int cpu_cycles) {
    
    for (int i=0; i<cpu_cycles; i++) {
        for (int n=0; n<4; n++) {
            ctx.ticks++;
            timer_tick();
            ppu_tick();
        }

        dma_tick();
    }
}