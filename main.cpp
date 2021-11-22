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
    return 0;
}
