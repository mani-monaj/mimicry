#include "transform.h"
#include <sstream>
#include <cstdlib>

#include<iostream>

unsigned int CBaseTransformRule::transform(const CHyperString &src, CHyperString &dest) const
{
    unsigned int totalCost = 0;
    dest.clear();
    //cout << "<DEBUG>" << endl;
    for (unsigned int i = 0; i < src.getSize(); i++) {
        SHyperChar dummy;
        totalCost += apply(src.getDataCst().at(i), dummy);
        //cout << i << " : " << src.getDataCst().at(i) << " -> " << dummy << " @ " << totalCost << endl;
        dest.getData().push_back(dummy);
    }
    dest.reconstruct();
    return totalCost;
}

CInPlaceTransformRule::CInPlaceTransformRule(string _name, bool _isDigit):
    CBaseTransformRule(_name, _isDigit),
    changeScale(false),
    changeChar(false)
{
    if (isDigit) {
        diffKernel = new CDigitDiff();
    } else {
        diffKernel = new CMathDiff();
    }
}

CInPlaceTransformRule::~CInPlaceTransformRule()
{
    delete diffKernel;
}

bool CInPlaceTransformRule::deduce(const SHyperChar &src, const SHyperChar &dest)
{
    // This is "INPLACE"
    //cout << "Comparing " << src.c << ":" << src.count << " with " << dest.c << ":" << dest.count <<endl;
    if (src.pose != dest.pose) return false;
    changeChar = (src.c != dest.c);
    changeScale = (src.count != dest.count);
    if (!changeChar && !changeScale) return false;
    searchPose = src.pose;
    unsigned int totalCost = 0;
    if (changeChar) {
        totalCost += diffKernel->deduce(src.c, dest.c);
    }
    if (changeScale) {
        searchScale = src.count;
        replaceScale = dest.count;
        totalCost += 25 * abs((int) searchScale - (int) replaceScale);
    }
    cost = totalCost;
    updateReason();
    return true;

}

unsigned int CInPlaceTransformRule::apply(const SHyperChar &src, SHyperChar &dest) const
{
    dest = src;
    if (src.pose != searchPose) return 0;
    if (changeChar) {
        unsigned int _c = diffKernel->apply(src.c, dest.c);
    }
    if (changeScale)
    {
        if (src.count == searchScale) {
            dest.count = replaceScale;
        }
    }
    return cost;
}

void CInPlaceTransformRule::updateReason()
{
    stringstream r;
    r << "At Pose " << searchPose << " : ";
    if (changeChar) r << diffKernel->why() << " ";
    if (changeScale) r << "Change scale from " << searchScale << " to " << replaceScale;
    reason = r.str();
}

CAnyPlaceTransformRule::CAnyPlaceTransformRule(string _name, bool _isDigit): CBaseTransformRule (_name, _isDigit)
{
    if (isDigit) {
        diffKernel = new CDigitDiff();
    } else {
        diffKernel = new CMathDiff();
    }
}

CAnyPlaceTransformRule::~CAnyPlaceTransformRule()
{
    delete diffKernel;
}

bool CAnyPlaceTransformRule::deduce(const SHyperChar &src, const SHyperChar &dest)
{
    if (src == dest) return false;
    changeChar = (src.c != dest.c);
    changeScale = (src.count != dest.count);
    if (src.pose == dest.pose)
    {
        if (changeChar) {
            searchChar = src.c;
            unsigned int totalCost = diffKernel->deduce(src.c, dest.c);
        }
        if (changeScale) {
            searchScale = src.count;
            replaceScale = dest.count;
        }
        updateReason();
        return true;
    } else {
        if ((!changeChar) && (changeScale)) {
            searchScale = src.count;
            replaceScale = dest.count;
            updateReason();
            return true;
        }
    }
    return false;
}

unsigned int CAnyPlaceTransformRule::apply(const SHyperChar &src, SHyperChar &dest) const
{
    dest = src;
    unsigned int totalCost = (25 * abs((int) src.pose - (int) dest.pose));

    if ((changeScale) && (src.count == searchScale)) {
        if ((!changeChar) || (src.c == searchChar)) {
            dest.count = replaceScale;
            totalCost += (25 * abs((int) searchScale - (int) replaceScale));
        }
    }

    if ((changeChar) && (src.c == searchChar)) {
        if ((!changeScale) || (src.count == searchScale)) {
            totalCost += diffKernel->apply(src.c, dest.c);
        }
    }

    return totalCost;
}

void CAnyPlaceTransformRule::updateReason()
{
    stringstream r;
//    if (isGeneralScale) {
//        r << "At any pose change scale from " << searchScale << " to " << replaceScale;
//    } else {
        r << "At any pose ";
        if (changeChar) r << "for " << searchChar << " " << diffKernel->why() << " ";
        if (changeScale) r << "change scale from " << searchScale << " to " << replaceScale;
//    }
    reason = r.str();
}

