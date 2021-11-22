#pragma once

#include <string>

std::string fileToStr(const std::string& filePath);
bool strToFile(const std::string& filePath, const std::string &data);
size_t filesize(const char* filename);
bool isFileExists (const std::string& name);
