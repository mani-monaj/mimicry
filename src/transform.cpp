#include "transform.h"
#include <sstream>

#include<iostream>

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
        totalCost += 5 * abs((int) searchScale - (int) replaceScale);
    }
    cost = totalCost;
    updateReason();
    return true;

}

unsigned int CInPlaceTransformRule::apply(const SHyperChar &src, SHyperChar &dest) const
{
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
    if (changeChar) r << diffKernel->why() << ", ";
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
        isGeneralScale = false;
        updateReason();
        return true;
    } else {
        if ((!changeChar) && (changeScale)) {
            searchScale = src.count;
            replaceScale = dest.count;
            isGeneralScale = true;
            updateReason();
            return true;
        }
    }
    return false;
}

unsigned int CAnyPlaceTransformRule::apply(const SHyperChar &src, SHyperChar &dest) const
{
    return 0;
}

void CAnyPlaceTransformRule::updateReason()
{
    stringstream r;
    if (isGeneralScale) {
        r << "At any pose change scale from " << searchScale << " to " << replaceScale;
    } else {
        r << "At any pose ";
        if (changeChar) r << "for " << searchChar << " " << diffKernel->why() << " ";
        if (changeScale) r << "change scale from " << searchScale << " to " << replaceScale;
    }
    reason = r.str();
}
