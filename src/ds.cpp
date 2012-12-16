#include "ds.h"

CHyperString::CHyperString(const string &s): rawData(s)
{
    update(s);
}

void CHyperString::update(const string &s)
{
    char last; // TODO: Init this
    unsigned int pose = 0;
    for (unsigned int i = 0; i < s.length(); i++) {
        if ((s[i] < 'a') || (s[i]) > 'z') continue;
        if (last == s[i]) {
            data.back().count++;
        } else {
            data.push_back(SHyperChar(pose++, s[i], 1));
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
        debug << "[" << data[i].pose << ":" << data[i].c << "," << data[i].count << "]";
    }
    return debug.str();
}

bool CSingleDigitTransform::deduce(const SHyperChar &src, const SHyperChar &dest)
{
    if (src.c == dest.c) return false;
    search = src.c;
    replace = dest.c;
    cost = 26;

    updateReason();
    return true;
}

void CSingleDigitTransform::updateReason()
{
    stringstream _reason;
    _reason << "Replace all " << search << " with " << replace;
    reason = _reason.str();
}
