#ifndef _DIFF_H
#define _DIFF_H

#include "ds.h"

class CBaseDiff
{
protected:
    string reason;
    unsigned int cost;
public:
    CBaseDiff(): reason(""), cost(0) {;}
    CBaseDiff(string _r, unsigned int _c): reason(_r), cost(_c) {;}
    unsigned int getCost() const { return cost; }
    virtual ~CBaseDiff() {;}
    virtual string why() const { return reason; }
    virtual bool deduce(const char src, const char dest) = 0;
    virtual unsigned int apply(const char src, char& dest) const = 0;
};

class CNullDiff: public CBaseDiff
{
public:
    CNullDiff(): CBaseDiff("null", 0) {;}
    bool deduce(const char src, const char dest) {return true;}
    unsigned int apply(const char src, char& dest) const {dest = src; return 0;}
};

/* Change anything with replace */
class CDigitDiff: public CBaseDiff
{
private:
    char replace;
public:
    CDigitDiff(char _r):
        replace(_r)
    { updateReason(); }
    CDigitDiff() {;}
    void updateReason();
    bool deduce(const char src, const char dest);
    unsigned int apply(const char src, char& dest) const;
};

/* Increment Diff */
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
    unsigned int apply(const char src, char& dest) const;
};

#endif
