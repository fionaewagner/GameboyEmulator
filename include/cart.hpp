#pragma once

#include <cstdint>
#include <vector>
#include <cstdint>
#include "common.hpp"

class CartridgeHeader {
private:
    u8 entry[4];
    u8 logo[0x30];
    char title[16];
    u16 newLicCode;
    u8 sgbFlag;
    u8 type;
    u8 romSize;
    u8 ramSize;
    u8 destCode;
    u8 licCode;
    u8 version;
    u8 checksum;
    u16 globalChecksum;

public:
    bool isMbc1() const;
    bool findBattery() const;

    // Getters for ROM header
    char* getTitle() const;
    u16 getNewLicCode() const;
    u8 getSgbFlag() const;
    u8 getRomType() const;
    u8 getHeaderRomSize() const;
    u8 getRamSize() const;
    u8 getDestCode() const;
    u8 getVersion() const;
    u8 getChecksum() const;
    u16 getGlobalChecksum() const;

    // Getter for ROM type
    const std::string& cartTypeName() const;
    // Getter for LIC Code
    const std::string& getLicCode() const;

    // Setters for the private members of RomHeader
    void setTitle(const char* title);
    void setNewLicCode(u16 newLicCode);
    void setSgbFlag(u8 sgbFlag);
    void setType(u8 type);
    void setRomSize(u8 romSize);
    void setRamSize(u8 ramSize);
    void setDestCode(u8 destCode);
    void setLicCode(u8 licCode);
    void setVersion(u8 version);
    void setChecksum(u8 checksum);
    void setGlobalChecksum(u16 globalChecksum);
};


class Cartridge {
public:
    bool cartLoad(char* cart);

    const u8 cartRead(u16 address);
    void cartWrite(u16 address, u8 value);

    void cartSetupBanking();

    void cartBatteryLoad();
    void cartBatterySave();

    // Getters
    const std::string& getFilename() const;
    u32 getRomSize() const;
    const std::vector<u8>& getRomData() const {
        return romData;
    }

    bool isRamEnabled() const;
    bool isRamBanking() const;

    u8* getRomBankX() const;
    u8 getBankingMode() const;

    u8 getRomBankValue() const;
    u8 getRamBankValue() const;

    std::vector<u8>* Cartridge::getRamBank();
    u8* getRamBanks(u8 index) const;

    bool hasBattery() const;
    bool shouldSaveBattery() const;

    bool getNeedSave() const;

    // Setters
    void setFilename(const char* filename);
    void setRomSize(u32 romSize);
    void setRomData(u8* romData);

    void setRamEnabled(bool ramEnabled);
    void setRamBanking(bool ramBanking);

    void setRomBankX(u8* romBankX);
    void setBankingMode(u8 bankingMode);

    void setRomBankValue(u8 romBankValue);
    void setRamBankValue(u8 ramBankValue);

    void setRamBank(u8* ramBank);
    void setRamBanks(u8 index, u8* ramBank);

    void setBattery(bool battery);
    void setNeedSave(bool needSave);

    CartridgeHeader header;
private:

    void setHeader(u8* romData);

    std::string filename;
    u32 romSize;
    std::vector<u8> romData;

    // MBC1 related data
    bool ramEnabled;
    bool ramBanking;

    std::vector<std::unique_ptr<u8[]>> romBankX;
    u8 bankingMode;

    u8 romBankValue;
    u8 ramBankValue;

    std::vector<u8>* ramBank; // Current selected RAM bank
    std::vector<void*> ramBanks;

    // For battery
    bool battery; // Has battery

    bool needSave;

};