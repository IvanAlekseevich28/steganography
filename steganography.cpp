#include "steganography.h"
#include <bitset>

static void writeBitToByte(uint8_t& data, bool bit, uint8_t pos = 0);
static bool readBitFromByte(const uint8_t& data, uint8_t pos = 0);
static bool getBitFromStr(const std::string& str, unsigned pos);
static std::vector<uint8_t> readLastBits(const std::vector<uint8_t> &data);
static bool writeLastBits(std::vector<uint8_t>& container, const std::vector<uint8_t> &data);
static std::string getStrFromVector(const std::vector<uint8_t>& vec, const unsigned start_index, const unsigned end_index);
static void pushStrToVector(std::vector<uint8_t>& vec, const std::string& str);

template<typename T>
static void pushToVector(std::vector<uint8_t>& vec, const T num)
{
    const auto len = sizeof (T);
    for (unsigned i = 1; i <= len; i++)
    {
        auto bitShift = (len - i) * 8;
        vec.push_back((num >> bitShift) % 0x100);
    }
}

template<typename T>
static T getFromVector(const std::vector<uint8_t>& vec, const unsigned current_index)
{
    T result;
    uint8_t *ptr = (uint8_t *) &result;
    unsigned idx = current_index + sizeof(T);
    while(idx > current_index)
        *ptr++ = vec[--idx];
    return result;
}

u_int32_t getMaxByteLen(const std::vector<uint8_t> &container, const uint8_t bitsDeep)
{
    return container.size() * bitsDeep / 8;
}

std::string extractHideMessage(const std::vector<uint8_t> &container, const uint8_t bitsDeep)
{
    auto vecHiddenData = readLastBits(container);

    size_t mesLen = getFromVector<size_t>(vecHiddenData, 0);
    unsigned mesHash = getFromVector<unsigned>(vecHiddenData, 8);
    std::string mes = getStrFromVector(vecHiddenData, 12, mesLen + 12);

    return mesHash == getStrHash(mes) ? mes : "";
}

bool hideMessage(std::vector<uint8_t> &container, const std::string& message, const uint8_t bitsDeep)
{
    if (getMaxByteLen(container, bitsDeep) < message.size() + 2 * sizeof (unsigned))
        return false;

    std::vector<uint8_t> vecHide;
    pushToVector(vecHide, message.size());
    pushToVector(vecHide, getStrHash(message));
    pushStrToVector(vecHide, message);

    return writeLastBits(container, vecHide);
}

bool readBitFromByte(const uint8_t& data, uint8_t pos)
{
    return (data >> pos) % 2;
}

void writeBitToByte(uint8_t& data, bool bit, uint8_t pos)
{
    uint8_t mask = (1 << pos);
    if (bit)
        data |= mask;
    else
        data &= ~mask;
    return;
}

bool getBitFromStr(const std::string& str, unsigned pos)
{
    uint8_t byte = str[pos / 8];
    return (byte >> (7 - (pos % 8))) % 2;
}

std::vector<uint8_t> readLastBits(const std::vector<uint8_t>& data)
{
    std::vector<uint8_t> hidden(data.size()/8, 0);
    auto dataIter = data.cbegin();
    for (auto& byte : hidden)
    {
        for (int i = 0; i < 8; i++)
            byte += (*(dataIter+i) % 2) << (7 - i);
        dataIter += 8;
    }

    return hidden;
}

std::string getStrFromVector(const std::vector<uint8_t>& vec, const unsigned start_index, const unsigned end_index)
{
    std::string str;
    for (unsigned i = start_index; i < end_index; i++)
        str.push_back((char)vec[i]);

    return str;
}

unsigned getStrHash(const std::string& str)
{
    std::hash<std::string> gen;
    return gen(str);
}

void pushStrToVector(std::vector<uint8_t>& vec, const std::string& str)
{
    for (const auto& c : str)
        vec.push_back((unsigned char)c);
}

static bool writeLastBits(std::vector<uint8_t>& container, const std::vector<uint8_t> &data)
{
    unsigned contIndex = 0;

    for (unsigned i = 0; i < data.size(); i++)
    {
        auto& byte = data[i];

        for (int i = 0; i < 8; i++)
        {
            bool bit = (byte >> (7 - i)) % 2;
            writeBitToByte(container[contIndex + i], bit, 0);
        }

        contIndex += 8;
    }

    return true;
}

void extrapolateLastBitsToBytes(std::vector<uint8_t> &container)
{
    for (auto& byte : container)
        byte = (byte % 2) * 0xff;
}
