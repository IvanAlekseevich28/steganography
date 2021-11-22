#pragma once
#include <string>
#include <vector>

u_int32_t getMaxByteLen(const std::vector<uint8_t>& container, const uint8_t bitsDeep = 1);
std::string extractHideMessage(const std::vector<uint8_t>& container, const uint8_t bitsDeep = 1);
bool hideMessage(std::vector<uint8_t>& container, const std::string &message , const uint8_t bitsDeep = 1);
