#include <iostream>
#include <assert.h>
#include "ds.h"
#include "diff.h"
#include "transform.h"

int main(int argc, char** argv)
{
    CHyperString s0("zbc");
//    cout << s0.getString() <<endl;

    CHyperString s1("abc");
    CHyperString s2("abdddd");
    cout << s1.getRawString() << " vs. " << s2.getRawString() << endl;


    vector<SHyperChar> &d0 = s0.getData();
    const vector<SHyperChar> &d1 = s1.getDataCst();
    const vector<SHyperChar> &d2 = s2.getDataCst();



    assert(d1.size() == d2.size());
    for (unsigned int i = 0; i < d1.size(); i++)
    {
        CAnyPlaceTransformRule t1("dummy", true);
        if (t1.deduce(d1[i], d2[i])) {
            cout << t1.why() << endl;
            t1.apply(d0[i], d0[i]);
        } else {
            cout << "No Change" << endl;
        }
    }

//    for (unsigned int i = 0; i < d0.size(); i++)
//    {
//        cout << diffs[0].apply(d0[i].c, d0[i].c) << endl;
//    }
    s0.reconstruct();

    cout << "Final: " << s0.getString() << " ~ " << s0.getRawString() << endl;
    return 0;
}

