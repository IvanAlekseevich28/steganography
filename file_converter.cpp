#include "file_converter.h"
#include <fstream>
#include <sstream>

using namespace std;

string fileToStr(const string &filePath)
{
    ifstream file(filePath, ios::in | ios::binary);
    if (file.is_open() == false)
        return "";
    stringstream dataStream;
    dataStream << file.rdbuf();
    file.close();

    return dataStream.str();
}

bool strToFile(const string &filePath, const string& data)
{
    ofstream file(filePath, ios::out | ios::binary);
    if (file.is_open() == false)
        return false;
    file.write(&data[0], data.size());
    file.close();

    return true;
}

size_t filesize(const char* filename)
{
    std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
    return in.tellg();
}


bool isFileExists (const std::string& name)
{
    ifstream f(name.c_str());
    return f.good();
}
