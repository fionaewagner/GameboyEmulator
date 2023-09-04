#include "../include/cart.hpp"
#include "../include/common.hpp"
#include <cstdint>
#include <array>
#include <unordered_map>
#include <string>
#include <cstdlib> // For malloc and free
#include <cstring>
#include <iostream> // For C++ I/O stream
#include <fstream>  // For C++ file stream
#include <memory>



uint8_t CartridgeHeader::getRomType() const {
    return type;
}

const std::string& Cartridge::getFilename() const {
    return filename;
}

std::vector<u8>* Cartridge::getRamBank() {
    return ramBank;
}

bool Cartridge::getNeedSave() const {
    return needSave;
}

bool CartridgeHeader::isMbc1() const {
    return BETWEEN(type, 1, 3);
}

bool CartridgeHeader::findBattery() const {
    //mbc1 only for now...
    return type == 3;
}

// ROM Types using std::array
static const std::array<const char*, 39> ROM_TYPES = {
    "ROM ONLY",
    "MBC1",
    "MBC1+RAM",
    "MBC1+RAM+BATTERY",
    "0x04 ???",
    "MBC2",
    "MBC2+BATTERY",
    "0x07 ???",
    "ROM+RAM 1",
    "ROM+RAM+BATTERY 1",
    "0x0A ???",
    "MMM01",
    "MMM01+RAM",
    "MMM01+RAM+BATTERY",
    "0x0E ???",
    "MBC3+TIMER+BATTERY",
    "MBC3+TIMER+RAM+BATTERY 2",
    "MBC3",
    "MBC3+RAM 2",
    "MBC3+RAM+BATTERY 2",
    "0x14 ???",
    "0x15 ???",
    "0x16 ???",
    "0x17 ???",
    "0x18 ???",
    "MBC5",
    "MBC5+RAM",
    "MBC5+RAM+BATTERY",
    "MBC5+RUMBLE",
    "MBC5+RUMBLE+RAM",
    "MBC5+RUMBLE+RAM+BATTERY",
    "0x1F ???",
    "MBC6",
    "0x21 ???",
    "MBC7+SENSOR+RUMBLE+RAM+BATTERY",
};

// LIC Code using std::unordered_map
static const std::unordered_map<uint8_t, std::string> LIC_CODE = {
    {0x00, "None"},
    {0x01, "Nintendo R&D1"},
    {0x08, "Capcom"},
    {0x13, "Electronic Arts"},
    {0x18, "Hudson Soft"},
    {0x19, "b-ai"},
    {0x20, "kss"},
    {0x22, "pow"},
    {0x24, "PCM Complete"},
    {0x25, "san-x"},
    {0x28, "Kemco Japan"},
    {0x29, "seta"},
    {0x30, "Viacom"},
    {0x31, "Nintendo"},
    {0x32, "Bandai"},
    {0x33, "Ocean/Acclaim"},
    {0x34, "Konami"},
    {0x35, "Hector"},
    {0x37, "Taito"},
    {0x38, "Hudson"},
    {0x39, "Banpresto"},
    {0x41, "Ubi Soft"},
    {0x42, "Atlus"},
    {0x44, "Malibu"},
    {0x46, "angel"},
    {0x47, "Bullet-Proof"},
    {0x49, "irem"},
    {0x50, "Absolute"},
    {0x51, "Acclaim"},
    {0x52, "Activision"},
    {0x53, "American sammy"},
    {0x54, "Konami"},
    {0x55, "Hi tech entertainment"},
    {0x56, "LJN"},
    {0x57, "Matchbox"},
    {0x58, "Mattel"},
    {0x59, "Milton Bradley"},
    {0x60, "Titus"},
    {0x61, "Virgin"},
    {0x64, "LucasArts"},
    {0x67, "Ocean"},
    {0x69, "Electronic Arts"},
    {0x70, "Infogrames"},
    {0x71, "Interplay"},
    {0x72, "Broderbund"},
    {0x73, "sculptured"},
    {0x75, "sci"},
    {0x78, "THQ"},
    {0x79, "Accolade"},
    {0x80, "misawa"},
    {0x83, "lozc"},
    {0x86, "Tokuma Shoten Intermedia"},
    {0x87, "Tsukuda Original"},
    {0x91, "Chunsoft"},
    {0x92, "Video system"},
    {0x93, "Ocean/Acclaim"},
    {0x95, "Varie"},
    {0x96, "Yonezawa/s’pal"},
    {0x97, "Kaneko"},
    {0x99, "Pack in soft"},
    {0xA4, "Konami (Yu-Gi-Oh!)"}
};

// Getter for ROM type
const std::string& CartridgeHeader::cartTypeName() const {
    if (type < ROM_TYPES.size()) {
        return ROM_TYPES[type];
    } else {
        static const std::string emptyStr;
        return emptyStr;
    }
}

// Getter for LIC Code
const std::string& CartridgeHeader::getLicCode() const {
    auto it = LIC_CODE.find(licCode);
    if (it != LIC_CODE.end()) {
        return it->second;
    } else {
        static const std::string unknownStr = "UNKNOWN";
        return unknownStr;
    }
}

void Cartridge::cartSetupBanking() {
    //std::vector<u8>* ramBank; // Current selected RAM bank
    //std::vector<void*> ramBanks;
    //std::vector<u8> romData;
   ramBanks.resize(16, nullptr);

    for (int i = 0; i < 16; i++) {
        ramBanks[i] = nullptr;

        if ((header.getRamSize() == 2 && i == 0) ||
            (header.getRamSize() == 3 && i < 4) ||
            (header.getRamSize() == 4 && i < 16) ||
            (header.getRamSize() == 5 && i < 8)) {
            ramBanks[i] = new std::vector<u8>(0x2000, 0);
        }
    }

    ramBank = static_cast<std::vector<u8>*>(ramBanks[0]);

    // Create the ROM banks
    int numBanks = romData.size() / 0x4000; // Assuming each bank is 16KB (0x4000 bytes)
    romBankX.resize(numBanks);
    for (int i = 0; i < numBanks; i++) {
        romBankX[i] = std::make_unique<u8[]>(0x4000);
        std::copy(romData.begin() + (i * 0x4000), romData.begin() + ((i + 1) * 0x4000), romBankX[i].get());
    }
    
}


bool Cartridge::cartLoad(char* cart) {
    std::ifstream file(cart, std::ios::binary | std::ios::ate);
    
    if (!file.is_open()) {
        std::cout << "Error: Could not open cartridge file: " << cart << std::endl;
        return false;
    }

    std::streampos size = file.tellg();
    if (size == 0) {
        std::cout << "Error: Cartridge file is empty." << std::endl;
        file.close();
        return false;
    }

    romData.resize(size);

    file.seekg(0, std::ios::beg);
    file.read(reinterpret_cast<char*>(romData.data()), size);
    file.close();

    // Verify the cartridge size and load the header
    if (size < 0x150) {
        std::cout << "Error: Invalid cartridge size." << std::endl;
        return false;
    }

    setHeader(romData.data());

    // Perform additional setup here, e.g., cartridge banking, battery loading, etc.
    cartSetupBanking();
    cartBatteryLoad();

    return true;
}

void Cartridge::setHeader(uint8_t* romData) {
    // Copy the cartridge header data to the CartridgeHeader class members
    header.setTitle(reinterpret_cast<const char*>(romData + 0x134));
    header.setNewLicCode(*reinterpret_cast<uint16_t*>(romData + 0x144));
    header.setSgbFlag(*(romData + 0x146));
    header.setType(*(romData + 0x147));
    header.setRomSize(*(romData + 0x148));
    header.setRamSize(*(romData + 0x149));
    header.setDestCode(*(romData + 0x14A));
    header.setLicCode(*(romData + 0x14B));
    header.setVersion(*(romData + 0x14C));
    header.setChecksum(*(romData + 0x14D));
    header.setGlobalChecksum(*reinterpret_cast<uint16_t*>(romData + 0x14E));
}

void Cartridge::cartBatteryLoad() {
    if (!getRamBank()) {
        return;
    }

    std::string filename = std::string(filename) + ".battery";
    std::ifstream file(filename, std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "FAILED TO OPEN: " << filename << std::endl;
        return;
    }

    file.read(reinterpret_cast<char*>(ramBank), 0x2000);
}

void Cartridge::cartBatterySave() {
    if (!getRamBank()) {
        return;
    }

    std::string filename = std::string(filename) + ".battery";
    std::ofstream file(filename, std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "FAILED TO OPEN: " << filename << std::endl;
        return;
    }

    file.write(reinterpret_cast<char*>(ramBank), 0x2000);
}

const u8 Cartridge::cartRead(u16 address) {
        const u16 romBankOffset = 0x4000;
        const u16 ramBankOffset = 0xA000;

        if (!header.isMbc1() || address < romBankOffset) {
            return romData[address];
        } else if ((address & 0xE000) == ramBankOffset) {
            u8 ramBankNumber = address / 0x2000;

            if (ramEnabled && ramBankNumber < ramBanks.size() && ramBanks[ramBankNumber] != nullptr) {
                u8* ramBankPtr = static_cast<u8*>(ramBanks[ramBankNumber]);
                return ramBankPtr[address - ramBankOffset];
            } else {
                return 0xFF; // Return default value if RAM is not enabled or no valid RAM bank.
            }
        } else {
            u8 romBankNumber = address / 0x4000;

            return romBankX[romBankNumber][address - romBankOffset];
        }
}

void Cartridge::cartWrite(u16 address, u8 value) {
        if (!header.isMbc1()) {
            return;
        }

        if (address < 0x2000) {
            ramEnabled = ((value & 0xF) == 0xA);
        }

        if ((address & 0xE000) == 0x2000) {
            if (value == 0) {
                value = 1;
            }

            value &= 0b11111;

            romBankValue = value;
            ramBank = (ramBankValue < ramBanks.size())
                ? static_cast<std::vector<u8>*>(ramBanks[ramBankValue])
                : nullptr;
        }

        if ((address & 0xE000) == 0x4000) {
            ramBankValue = value & 0b11;

            if (ramBanking) {
                if (needSave) {
                    cartBatterySave();
                }

                ramBank = (ramBankValue < ramBanks.size())
                    ? static_cast<std::vector<u8>*>(ramBanks[ramBankValue])
                    : nullptr;
            }
        }

        if ((address & 0xE000) == 0x6000) {
            bankingMode = value & 1;

            ramBanking = bankingMode;

            if (ramBanking) {
                if (needSave) {
                    cartBatterySave();
                }

                ramBank = (ramBankValue < ramBanks.size())
                    ? static_cast<std::vector<u8>*>(ramBanks[ramBankValue])
                    : nullptr;
            }
        }

        if ((address & 0xE000) == 0xA000) {
            if (!ramEnabled) {
                return;
            }

            if (!ramBank) {
                return;
            }

            std::size_t ramOffset = address - 0xA000;
            if (ramOffset < ramBank->size()) {
                (*ramBank)[ramOffset] = value;

                if (battery) {
                    needSave = true;
                }
            }
        }
    }

