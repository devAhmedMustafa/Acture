//
// Created by Ahmed Mustafa on 4/25/2025.
//

#ifndef SMATH_H
#define SMATH_H
#include <cstdint>
#include <vector>
#include <bitset>

namespace SPI {
    class SMath {
        static std::bitset<sizeof(uint16_t) * 8 - 1> usedIds;
    public:
        static unsigned short GetFloatPart(float value);
        static int CantorFunction(int k1, int k2);

        static uint32_t EncodeBitPack(uint16_t k1, uint16_t k2);
        static std::vector<uint16_t> Decode2BitPack(uint32_t id);

        static uint32_t EncodeBitPack(uint16_t k1, uint16_t k2, uint16_t k3);
        static std::vector<uint16_t> Decode3BitPack(uint32_t id);

        static uint16_t GenerateId();
        static void ReserveId(uint16_t);
    };
}

#endif //SMATH_H
