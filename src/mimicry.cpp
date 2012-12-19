#include <map>
#include <iostream>
#include <assert.h>
#include <algorithm>
#include "ds.h"
#include "diff.h"
#include "transform.h"

using namespace std;

const bool debug = true;
multimap<unsigned int, CMStringTransform*> mTransforms;
CMetaString  source;
CMetaString  dest;
CMetaString  target;

void cleanup()
{
    for (multimap<unsigned int, CMStringTransform*>::iterator it = mTransforms.begin();
         it != mTransforms.end(); ++it) {
        delete (*it).second;
    }
    mTransforms.clear();
}

void dumpTransoforms()
{
    unsigned int index = 0;
    for (multimap<unsigned int, CMStringTransform*>::iterator it = mTransforms.begin();
         it != mTransforms.end(); ++it) {
        index++;
        CMetaString dummy;
        (*it).second->transform(target, dummy);
        cout << index << "," << dummy.getRawString() << "," << *((*it).second);
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
        cout << "Error in data, S1 and S2 must be MetaStrings of the same size." << endl;
        cleanup();
        return -3;
    }

    if (debug) {
        cout << source << " ~ " << source.getRawString() << endl;
        cout << dest << " ~ "<< dest.getRawString()<< endl;
        cout << target << " ~ "<< target.getRawString()<< endl;
    }


    // In Place Transforms
    for (unsigned int j = 0; j < 2; j++) {
        CMStringTransform *t = new CMStringTransform(true, j == 0);
        CMetaString dummy;
        if (t->deduce(source, dest)) {
            unsigned int cost = t->transform(target, dummy);
            mTransforms.insert(pair<unsigned int, CMStringTransform*>(cost, t));
        }
    }

    //Any Place Transforms
    unsigned int i = 0;
    do {
        for (unsigned int j = 0; j < 2; j++) {
            CMStringTransform *t = new CMStringTransform(false, j == 0);
            CMetaString dummy;
            if (t->deduce(source, dest)) {
                unsigned int cost = t->transform(target, dummy);
                mTransforms.insert(pair<unsigned int, CMStringTransform*>(cost, t));
            } else {
                delete t;
            }
        }
    } while (next_permutation(source.getData().begin(), source.getData().end()));

    dumpTransoforms();

    cleanup();
    return 0;
}

