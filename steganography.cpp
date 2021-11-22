#include "steganography.h"
#include <bitset>

static void writeBitToByte(u_int8_t& data, bool bit, u_int8_t pos = 0);
static bool readBitFromByte(const u_int8_t& data, u_int8_t pos = 0);
static bool getBitFromStr(const std::string& str, unsigned pos);

u_int32_t getMaxByteLen(const std::vector<uint8_t> &container, const uint8_t bitsDeep)
{
    return container.size() * bitsDeep / 8;
}

std::string extractHideMessage(const std::vector<uint8_t> &container, const uint8_t bitsDeep)
{
    std::string mes;
    std::bitset<8> buffer;
    int charIndex = 0;
    for (const auto& byte : container)
    {
        for (int i = 0; i < bitsDeep; i++)
        {
            buffer[charIndex] = readBitFromByte(byte, i);
            charIndex++;
            if (charIndex == 8)
            {
                mes.push_back(buffer.to_ulong());
                charIndex = 0;
                if (mes.back() == '\0')
                    break;
            }
        }
    }

    return mes;
}

bool readBitFromByte(const u_int8_t& data, u_int8_t pos)
{
    return (data >> pos) % 2;
}

void writeBitToByte(u_int8_t& data, bool bit, u_int8_t pos)
{
    u_int8_t mask = (bit << pos);
    if (bit)
        data |= mask;
    else
        data &= ~mask;
}

bool hideMessage(std::vector<uint8_t> &container, const std::string& message, const uint8_t bitsDeep)
{
    if (getMaxByteLen(container, bitsDeep) < message.size())
        return false;

    unsigned bitIndex = 0;
    for (unsigned i = 0; i < container.size(); i++)
    {
        auto& byte = container[i];
        for (unsigned i = 0; i < bitsDeep; i++)
        {
            writeBitToByte(byte, getBitFromStr(message, bitIndex++));
            if (bitIndex == message.size()*8)
                break;
        }
    }

    return true;
}

bool getBitFromStr(const std::string& str, unsigned pos)
{
   u_int8_t byte = str[pos / 8];
   return (byte >> (7 - (pos % 8))) % 2;
}
