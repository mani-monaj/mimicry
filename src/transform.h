#ifndef _TRANSFORM_H
#define _TRANSFROM_H

#include "diff.h"

class CBaseTransformRule
{
protected:
    string name;
    string reason;
    bool isDigit; // True: Digit Diff / False: Math Diff
    unsigned int cost;
    CBaseDiff* diffKernel;
public:
    CBaseTransformRule(string _name, bool _isDigit): name(_name), reason(""), isDigit(_isDigit), cost(0) {;}
    virtual ~CBaseTransformRule() {;}
    virtual string why() const { return reason; }
    virtual bool deduce(const SHyperChar &src, const SHyperChar& dest) = 0;
    virtual unsigned int apply(const SHyperChar &src, SHyperChar& dest) const = 0;
};

class CInPlaceTransformRule : public CBaseTransformRule
{
private:
    unsigned int searchPose;
    bool changeScale;
    bool changeChar;
    unsigned int searchScale;
    unsigned int replaceScale;

    void updateReason();
public:
    CInPlaceTransformRule(string _name, bool _isDigit);
    ~CInPlaceTransformRule();
    bool deduce(const SHyperChar &src, const SHyperChar &dest);
    unsigned int apply(const SHyperChar &src, SHyperChar &dest) const;
};

class CAnyPlaceTransformRule: public CBaseTransformRule
{
private:
    bool changeChar;
    bool changeScale;
    char searchChar;
    unsigned int searchScale;
    unsigned int replaceScale;
    bool isGeneralScale;
    void updateReason();
public:
    CAnyPlaceTransformRule(string _name, bool _isDigit);
    ~CAnyPlaceTransformRule();
    bool deduce(const SHyperChar &src, const SHyperChar &dest);
    unsigned int apply(const SHyperChar &src, SHyperChar &dest) const;
};

#endif
