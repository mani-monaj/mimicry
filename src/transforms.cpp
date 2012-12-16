#include "transforms.h"

bool CDigitTransform::deduce(const SHyperChar &src, const SHyperChar &dest)
{
    if (src.c == dest.c) return false;
    search = src.c;
    replace = dest.c;
    basePose = src.pose;
    cost = 26 * (1 + abs( (int) (src.pose - dest.pose)));
    updateReason();
    return true;
}

void CDigitTransform::updateReason()
{
    stringstream _reason;
    _reason << "Replace all " << search << " with " << replace << " (Prefered Pose: " << basePose << ")";
    reason = _reason.str();
}

unsigned int CDigitTransform::apply(const CHyperString &src, CHyperString &dest)
{
    unsigned int totalCost = 0;
    dest = src;
    for (unsigned int i = 0; i < dest.getData().size(); i++) {
        if (dest.getData()[i].c == search) {
            dest.getData()[i].c = replace;
            totalCost += cost;
        }
    }
    dest.reconstruct();
    return totalCost;
}

bool CSingleDigitTransform::deduce(const SHyperChar &src, const SHyperChar &dest)
{
    if ((src.c == dest.c) || (src.pose != dest.pose)) return false;
    search = src.c;
    replace = dest.c;
    pose = src.pose;
    cost = 26;
    updateReason();
    return true;
}

void CSingleDigitTransform::updateReason()
{
    stringstream _reason;
    _reason << "Replace  " << search << " with " << replace << " at Pose: " << pose;
    reason = _reason.str();
}

unsigned int CSingleDigitTransform::apply(const CHyperString &src, CHyperString &dest)
{
    assert(pose < src.getsize());

    unsigned int totalCost = 0;
    dest = src;

    if (dest.getData()[pose].c == search) {
        dest.getData()[pose].c = replace;
        totalCost += cost;
    }

    dest.reconstruct();
    return totalCost;
}
