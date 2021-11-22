#include <iostream>
#include "bmp.h"
#include "steganography.h"
#include "file_converter.h"

using namespace std;

int main(int argc, char** argv)
{
    if (argc < 4)
    {
        cout << "Not enought arguments!\n";
        return 1;
    }
    const string mod = argv[1];
    const string pathCont = argv[2];
    const string pathOutput = argv[3];

    if (isFileExists(pathCont) == false)
    {
        cout << "File \"" << pathCont << "\" not correct!\n";
        return 2;
    }

    if (mod == "-h" or mod == "--hide")
    {
        const string dataMod = argv[4];

    } else if (mod == "-e" or mod == "--extract")
    {

    } else
    {
        cout << "Select mode\n'-h' to hide data\n'-e' to extract data\n";
        return 4;
    }
//    BMP pic("sample_640×426.bmp");
//    cout << hideMessage(pic.data, "Hello world!") << endl;
//    pic.write("test.bmp");

//    BMP pic2("test.bmp");
//    cout << extractHideMessage(pic2.data) << endl;
    auto data = fileToStr("pp.pptx");
    strToFile("str.pptx", data);
    return 0;
}
