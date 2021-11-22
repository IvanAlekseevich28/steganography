#include <iostream>
#include "bmp.h"
#include "steganography.h"
#include "file_converter.h"

using namespace std;

int main()
{
//    BMP pic("sample_640×426.bmp");
//    cout << hideMessage(pic.data, "Hello world!") << endl;
//    pic.write("test.bmp");

//    BMP pic2("test.bmp");
//    cout << extractHideMessage(pic2.data) << endl;
    auto data = fileToStr("pp.pptx");
    strToFile("str.pptx", data);
    return 0;
}
