#include <iostream>
#include <algorithm>
#include "bmp.h"
#include "steganography.h"
#include "file_converter.h"

using namespace std;

string getCmdOption(char ** begin, char ** end, const std::string & option)
{
    char ** itr = std::find(begin, end, option);
    if (itr != end && ++itr != end)
    {
        return string(*itr);
    }
    return "";
}

void printHelp()
{
    cout << "\t-s           source file\n"
         << "\t'-h'/'-e'    hide/extract mode\n"
         << "\t-f           file for hide\n"
         << "\t-o           file for output\n"
         << "\t-b           extrapolate bits to bytes\n"
         << "\t-t           text mod\n";
}

string getDir(const string& path)
{
    auto iter = path.find_last_of("/");
    if (iter == string::npos)
        return "";
    else
        return path.substr(0,iter+1);
}

int main(int argc, char** argv)
{
    if (getCmdOption(argv, argv+argc, "--help") != "")
    {
        printHelp();
        return 0;
    }
    if (argc < 4)
    {
        cout << "Not enought arguments!\n";
        printHelp();
        return 1;
    }
    const bool mod = getCmdOption(argv, argv+argc, "-h") != ""; // 1 - hide, 0 - extract
    const bool needExt = getCmdOption(argv, argv+argc, "-b") != "";
    const string text = getCmdOption(argv, argv+argc, "-t");
    const string pathHide = getCmdOption(argv, argv+argc, "-f");
    const string pathSrc = getCmdOption(argv, argv+argc, "-s");
    const string pathOutput = getCmdOption(argv, argv+argc, "-o");

    if (pathSrc.empty() or !isFileExists(pathSrc))
    {
        cout << "File \"" << pathSrc << "\" not correct!\n";
        return 2;
    }

    BMP pic(pathSrc.c_str());
    string data;
    if (mod)
    {
        if (text.size())
        {
            data = text;
        } else if (pathHide.size() and isFileExists(pathHide))
        {
            data = fileToStr(pathHide);
        } else
        {
            cout << "Nothing for doing!\n";
            return 4;
        }

        if (hideMessage(pic.data, data) == false)
        {
            cout << "Message too lenght!/nMax: "
                 << getMaxByteLen(pic.data)
                 << "\nCurrent: "
                 << data.size() << "\n";
            return 8;
        }

        if (pathOutput.empty())
        {
            cout << "Output path is empty!\n";
            return 16;
        }

        pic.write(pathOutput.c_str());
        if (isFileExists(pathOutput) == false)
        {
            cout << "Output path is not correct!\n";
            return 32;
        }

        if (needExt)
        {
            string pathExtOrig = getDir(pathOutput) + "ext_orig.bmp";
            string pathExtHide = getDir(pathOutput) + "ext_hide.bmp";

            extrapolateLastBitsToBytes(pic.data);
            pic.write(pathExtHide.c_str());

            pic.read(pathSrc.c_str());
            extrapolateLastBitsToBytes(pic.data);
            pic.write(pathExtOrig.c_str());

        }
    } else
    {
        string data = extractHideMessage(pic.data);
        if (data.empty())
        {
            cout << "No hidden data for " << pathSrc << "\n";
            return 128;
        }

        if (text.size())
        {
            cout << data << endl;
            return 0;
        } else if (pathOutput.size())
        {
            strToFile(pathOutput, data);
            if (isFileExists(pathOutput))
            {
                return 0;
            }
        } else
        {
            cout << "Output problem!\n";
            return 256;
        }
    }

    return 0;
}
