#include <iostream>
#include "bmp.h"
#include "steganography.h"

using namespace std;

int main()
{
    BMP pic("../pictures/sample_640×426.bmp");
    cout << extractHideMessage(pic.data, 1);
    pic.write("../pictures/test.bmp");
    return 0;
}
