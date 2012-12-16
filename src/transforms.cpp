#include "transforms.h"

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

unsigned int CSingleDigitTransform::apply(const CHyperString &src, CHyperString &dest)
{
    unsigned int totalCost = 0;
    dest = src;
    for (unsigned int i = 0; i < dest.getData().size(); i++)
    {
        if (dest.getData()[i].c == search) dest.getData()[i].c = replace;
    }
    dest.reconstruct();
    return totalCost;
}
