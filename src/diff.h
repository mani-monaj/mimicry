#ifndef _TRANSFORMS_H
#define _TRANSFORMS_H

#include "ds.h"

class CBaseDiff
{
protected:
    string reason;
    unsigned int cost;
public:
    CBaseDiff(): reason(""), cost(0) {;}
    unsigned int getCost() const { return cost; }
    virtual ~CBaseDiff() {;}
    virtual string why() { return reason; }
    virtual bool deduce(const char src, const char dest) = 0;
    virtual unsigned int apply(const char src, char& dest) = 0;
};

/* Change search with replace */
class CDigitDiff: public CBaseDiff
{
private:
    char search;
    char replace;
public:
    CDigitDiff(char _s, char _r):
        search(_s),
        replace(_r)
    { updateReason(); }
    CDigitDiff() {;}
    void updateReason();
    bool deduce(const char src, const char dest);
    unsigned int apply(const char src, char& dest);
};

class CMathDiff: public CBaseDiff
{
private:
    char incr;
public:
    CMathDiff(char _i):
        incr(_i)
    { updateReason(); }
    CMathDiff() {;}
    void updateReason();
    bool deduce(const char src, const char dest);
    unsigned int apply(const char src, char& dest);
};

#endif
