#include <iostream>
#include "bmp.h"
#include "steganography.h"

using namespace std;

int main()
{
    BMP pic("../pictures/sample_640×426.bmp");
    cout << hideMessage(pic.data, "Hello world!") << endl;
    pic.write("../pictures/test.bmp");
    cout << extractHideMessage(pic.data) << endl;

    extrapolateLastBitsToBytes(pic.data);
    pic.write("../pictures/ext_test.bmp");

    BMP pic2("../pictures/sample_640×426.bmp");
    extrapolateLastBitsToBytes(pic2.data);
    pic.write("../pictures/ext_sample_640×426.bmp");
    return 0;
}
