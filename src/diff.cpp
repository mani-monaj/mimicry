#include "diff.h"

bool CDigitDiff::deduce(const char src, const char dest)
{
    if (src == dest) return false;
    replace = dest;
    cost = 25;
    updateReason();
    return true;
}

void CDigitDiff::updateReason()
{
    stringstream _reason;
    _reason << "Replace with " << replace;
    reason = _reason.str();
}

unsigned int CDigitDiff::apply(const char src, char &dest) const
{
    unsigned int totalCost = 0;
    if (src != replace)
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
    _reason << "Increment by " << (int) incr;
    reason = _reason.str();
}

unsigned int CMathDiff::apply(const char src, char &dest) const
{
    dest = src + incr;
    if (dest > 'z') dest -= ('z' - 'a' + 1);
    return cost;
}
