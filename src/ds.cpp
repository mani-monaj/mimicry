#include "ds.h"

CHyperString::CHyperString(const string &s): rawData(s)
{
    update(s);
}

void CHyperString::update(const string &s)
{
    char last;
    for (unsigned int i = 0; i < s.length(); i++) {
        if (last == s[i]) {
            data.back().count++;
        } else {
            data.push_back(SHyperChar(s[i], 1));
        }
        last = s[i];
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
        debug << "[" << data[i].c << "," << data[i].count << "]";
    }
    return debug.str();
}
