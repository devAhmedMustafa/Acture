//
// Created by Ahmed Mustafa on 4/25/2025.
//

#include "SMath.h"

#include <bitset>
#include <random>

namespace SPI {

    std::bitset<sizeof(uint16_t) * 8 - 1> SMath::usedIds;

    unsigned short SMath::GetFloatPart(const float value) {
        float fractional = value - static_cast<int>(value);
        // Shift the fractional part to the right until it becomes an integer
        unsigned short result = 0;
        int multiplier = 1;

        while (fractional > 0.00001f && multiplier <= 10000) { // Prevent infinite loops on float errors
            fractional *= 10;
            int digit = static_cast<int>(fractional);
            result = result * 10 + digit;
            fractional -= digit;
        }

        return result;
    }

    int SMath::CantorFunction(const int k1, const int k2) {
        return (k1 + k2) * (k1 + k2 + 1) / 2 + k2;
    }

    uint32_t SMath::EncodeBitPack(const uint16_t k1, const uint16_t k2) {
        return (static_cast<uint32_t>(k1) << 16) | (static_cast<uint32_t>(k2));
    }

    std::vector<uint16_t> SMath::Decode2BitPack(const uint32_t id) {
        std::vector<uint16_t> result(2);
        result[0] = (id >> 16) & 0xFFFF;
        result[1] = id & 0xFFFF;
        return result;
    }

    uint32_t SMath::EncodeBitPack(const uint16_t k1, const uint16_t k2, const uint16_t k3) {
        return (static_cast<uint32_t>(k1) << 21) |
           (static_cast<uint32_t>(k2) << 10) |
           (static_cast<uint32_t>(k3));
    }

    std::vector<uint16_t> SMath::Decode3BitPack(const uint32_t id) {
        std::vector<uint16_t> result(3);
        result[0] = (id >> 21) & 0x7FF;
        result[1] = (id >> 10) & 0x7FF;
        result[2] = id & 0x3FF;
        return result;
    }

    uint16_t SMath::GenerateId() {

        static std::mt19937 rng{std::random_device{}()};
        static std::uniform_int_distribution<uint16_t> dist(0, sizeof(uint16_t) * 8 - 1);

        while (true) {
            if (const uint16_t id = dist(rng); !usedIds.test(id)) {
                usedIds.set(id);
                return id;
            }
        }
    }

    void SMath::ReserveId(uint16_t id){
        usedIds.set(id);
    }
}
