// Version 3/2011
#include <iostream>
#include "stamp.h"
#include "stampstream.h"
#include <stdexcept>

using namespace stamping_press;

int main()
{

stampstream s(30,10);
s << "hi th#re planetoid humans" << endrow
<< "  how's all the fish" << row(5) << "one more";
s << row(4) << "   two more" << 3.1415;
s << row(8) << "The quick brown fox jumped over the lazy dog’s back.";
s << row(3) << "the end";
return 0;
}
