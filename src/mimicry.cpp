#include <iostream>
#include <assert.h>
#include "ds.h"
#include "transforms.h"

int main(int argc, char** argv)
{
    CHyperString s0("abbcccdddde");
    cout << s0.getString() <<endl;

    CHyperString s1("abc");
    CHyperString s2("efg");
    CSingleDigitTransform t1;

    const vector<SHyperChar> &d1 = s1.getDataCst();
    const vector<SHyperChar> &d2 = s2.getDataCst();

    assert(d1.size() == d2.size());
    for (unsigned int i = 0; i < d1.size(); i++)
    {
        if (t1.deduce(d1[i], d2[i])) {
            cout << t1.why();
            cout << " - Cost : " << t1.apply(s0, s0) << endl;
        } else {
            cout << "No Change" << endl;
        }
    }


    cout << "Final: " << s0.getRawString() << endl;
    return 0;
}

