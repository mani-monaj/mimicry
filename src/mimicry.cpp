#include <iostream>
#include <assert.h>
#include "ds.h"

int main(int argc, char** argv)
{
    CHyperString s1("abc");
    CHyperString s2("abd");
    CSingleDigitTransform t1;

    const vector<SHyperChar> &d1 = s1.getData();
    const vector<SHyperChar> &d2 = s2.getData();

    assert(d1.size() == d2.size());
    for (unsigned int i = 0; i < d1.size(); i++)
    {
        if (t1.deduce(d1[i], d2[i])) {
            cout << t1.why() << endl;
        } else {
            cout << "No Change" << endl;
        }

    }
    return 0;
}

