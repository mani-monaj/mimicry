#include <iostream>
#include "ds.h"

int main(int argc, char** argv)
{
    CHyperString s("abbcccdddefg");
    cout << s.getString() << endl;
    cout << s.getRawString() << endl;
    return 0;
}

