#include <map>
#include <iostream>
#include <assert.h>
#include "ds.h"
#include "diff.h"
#include "transform.h"
#include "algorithm"

using namespace std;

const bool debug = true;
multimap<unsigned int, CBaseTransformRule*> mTransforms;
CHyperString  source;
CHyperString  dest;
CHyperString  target;

void cleanup()
{
    for (multimap<unsigned int, CBaseTransformRule*>::iterator it = mTransforms.begin();
         it != mTransforms.end(); ++it) {
        delete (*it).second;
    }
}

void dumpTransoforms()
{
    unsigned int index = 0;
    for (multimap<unsigned int, CBaseTransformRule*>::iterator it = mTransforms.begin();
         it != mTransforms.end(); ++it) {
        index++;
        CHyperString dummy;
        (*it).second->transform(target, dummy);
        cout << index << "," << dummy.getRawString() << "," << (*it).second->why();
        cout << "," << (*it).first << endl;
    }
}

int main(int argc, char** argv)
{
    // Worst CLP ever
    if (argc != 4)
    {
        cout << "Usage: mimicry S1 S2 S3" << endl << endl;
        cout << "  if S1 transforms to S2, what are possible solutions for S3" << endl;
        cout << "  under same transformation." << endl;
        return -1;
    }

    source.update(argv[1]);
    dest.update(argv[2]);
    target.update(argv[3]);

//    unsigned int i = 0;
//    do {
//        source.reconstruct();
//        cout << i++ << " : " << source.getRawString() << endl;

//    } while (next_permutation(source.getData().begin(), source.getData().end()));
//    return 0;

    if (!
            ((source.getSize() > 0) &&
             (dest.getSize() > 0) &&
             (target.getSize() > 0))
            ) {
        cout << "Error in data, valid chars are `a`..`z` only!" << endl;
        cleanup();
        return -2;
    }

    if (source.getSize() != dest.getSize())
    {
        cout << "Error in data, S1 and S2 must be HyperStrings of the same size." << endl;
        cleanup();
        return -3;
    }

    if (debug) {
        cout << source << " ~ " << source.getRawString() << endl;
        cout << dest << " ~ "<< dest.getRawString()<< endl;
        cout << target << " ~ "<< target.getRawString()<< endl;
    }

    // In Place Transforms
    CHStringTransform* t = new CHStringTransform(false, true);
    t->deduce(source, dest);
    /*for (unsigned int i = 0; i < source.getSize(); i++) {
        for (unsigned int j = 0; j < 2; j++)
        {
            CInPlaceTransformRule* t = new CInPlaceTransformRule("dummy", j == 0);
            if (t->deduce(source.getDataCst()[i], dest.getDataCst()[i])) {
                mTransforms.insert(pair<int, CBaseTransformRule*>(t->getCost(), t));
            }
        }
    }

    dumpTransoforms();*/
    if (debug) {
        cout << "Number of rules in transform: " << t->getSize() << endl;
    }
    CHyperString dummy;
    cout << "Rules : " << endl << *t << endl;
    cout << "Cost : " << t->transform(target, dummy) << endl;
    cout << "Result: " << dummy.getRawString() << endl;

    delete t;
    //cleanup();
    return 0;
}

