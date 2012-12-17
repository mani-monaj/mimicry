#include "transforms.h"

bool CDigitDiff::deduce(const char src, const char dest)
{
    if (src == dest) return false;
    search = src;
    replace = dest;
    cost = 26;
    updateReason();
    return true;
}

void CDigitDiff::updateReason()
{
    stringstream _reason;
    _reason << "Replace  " << search << " with " << replace;
    reason = _reason.str();
}

unsigned int CDigitDiff::apply(const char src, char &dest)
{
    unsigned int totalCost = 0;
    if (src == search)
    {
        dest = replace;
        totalCost = cost;
    }
    return totalCost;
}


bool CMathDiff::deduce(const char src, const char dest)
{
    if (src == dest) return false;
    incr = dest - src;
    cost = incr;
    updateReason();
    return true;
}

void CMathDiff::updateReason()
{
    stringstream _reason;
    _reason << "Increment by " << incr;
    reason = _reason.str();
}

unsigned int CMathDiff::apply(const char src, char &dest)
{
    dest = src + incr;
    return cost;
}
