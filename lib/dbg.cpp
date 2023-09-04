#include "../include/dbg.hpp"
#include "../include/bus.hpp"

#include <iostream>
#include <vector> 

static char dbg_msg[1024] = {0};
static int msg_size = 0;

void Debug::dbgUpdate() {
        // Assuming bus_read and bus_write are functions that interact with some bus
        if (bus_read(0xFF02) == 0x81) {
            char c = bus_read(0xFF01);

            dbg_msg[msg_size++] = c;

            bus_write(0xFF02, 0);
        }
    }

void Debug::dbgPrint() const {
    if (!dbgMsg.empty()) {
        std::string message(dbgMsg.begin(), dbgMsg.begin() + msgSize);
        std::cout << "DBG: " << message << std::endl;
    }
}
