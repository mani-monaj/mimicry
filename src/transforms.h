#ifndef _TRANSFORMS_H
#define _TRANSFORMS_H

#include "ds.h"

class CBaseTransform
{
protected:
    string name;
    string reason;
    unsigned int cost;
public:
    CBaseTransform(): name("undefined"), reason(""), cost(0) {;}
    CBaseTransform(string _name): name(_name), reason(""), cost(0) {;}
    unsigned int getCost() const { return cost; }
    virtual ~CBaseTransform() {;}
    virtual string why() { return reason; }
    virtual bool deduce(const SHyperChar& src, const SHyperChar& dest) = 0;
    virtual unsigned int apply(const CHyperString& src, CHyperString& dest) = 0;
};

/* Search/Replace for all occurances */
class CDigitTransform: public CBaseTransform
{
private:
    char search;
    char replace;
    unsigned int basePose;
public:
    CDigitTransform(char _s, char _r, unsigned int _bp):
        search(_s),
        replace(_r),
        basePose(_bp)
    { updateReason(); }
    CDigitTransform() {;}
    void updateReason();
    bool deduce(const SHyperChar &src, const SHyperChar &dest);
    unsigned int apply(const CHyperString &src, CHyperString &dest);
};

/* Search/Replace for any occurances at pose only */
class CSingleDigitTransform: public CBaseTransform
{
private:
    char search;
    char replace;
    unsigned int pose;
public:
    CSingleDigitTransform(char _s, char _r, unsigned int _p):
        search(_s),
        replace(_r),
        pose(_p)
    { updateReason(); }
    CSingleDigitTransform() {;}
    void updateReason();
    bool deduce(const SHyperChar &src, const SHyperChar &dest);
    unsigned int apply(const CHyperString &src, CHyperString &dest);
};


#endif
