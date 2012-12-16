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

class CSingleDigitTransform: public CBaseTransform
{
private:
    char search;
    char replace;
public:
    CSingleDigitTransform(char _s, char _r):
        search(_s),
        replace(_r)
    { updateReason(); }
    CSingleDigitTransform() {;}
    void updateReason();
    bool deduce(const SHyperChar &src, const SHyperChar &dest);
    unsigned int apply(const CHyperString &src, CHyperString &dest);
};

#endif
