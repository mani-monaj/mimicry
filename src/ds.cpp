#include "ds.h"

#include <iostream>

CHyperString::CHyperString() : rawData("")
{
    update("");
}

CHyperString::CHyperString(const string &s): rawData(s)
{
    update(s);
}

void CHyperString::update(const string &s)
{
    rawData = s;
    unsigned char last; // TODO: Init this
    unsigned int pose = 0;
    for (unsigned int i = 0; i < s.length(); i++) {
        if ((s[i] < 'a') || (s[i]) > 'z') continue;
        if (last == s[i]) {
            data.back().count++;
            //pose++;
        } else {
            data.push_back(SHyperChar(pose++, s[i], 1));
        }
        last = s[i];
    }
}

void CHyperString::reconstruct()
{
    unsigned int size = 0;
    for (unsigned int i = 0; i < data.size(); i++) {
        size += data.at(i).count;
    }
    rawData.resize(size);

    // The list should be sorted by pose
    unsigned int index = 0;
    for (unsigned int i = 0; i < data.size(); i++) {
        SHyperChar hc = data.at(i);
        for (unsigned int j = 0; j < hc.count; j++) {
            rawData[index++] = hc.c;
        }
    }
}

void CHyperString::clear()
{
    data.clear();
    rawData.clear();
}

string CHyperString::getRawString() const
{
    return rawData;
}

string CHyperString::getString() const
{
    stringstream debug;
    for (unsigned int i = 0; i < data.size(); i++)
    {
        debug << data[i];
    }
    return debug.str();
}

