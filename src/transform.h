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
    unsigned int getCost() const {return cost;}
    virtual ~CBaseTransformRule() {;}
    virtual string why() const { return reason; }
    virtual bool deduce(const SHyperChar &src, const SHyperChar& dest) = 0;
    virtual unsigned int apply(const SHyperChar &src, SHyperChar& dest) const = 0;
    unsigned int transform(const CHyperString& src, CHyperString &dest) const;
    friend std::ostream& operator<< (std::ostream &out, const CBaseTransformRule &what);
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
    unsigned char searchChar;
    unsigned int searchScale;
    unsigned int replaceScale;
    void updateReason();
public:
    CAnyPlaceTransformRule(string _name, bool _isDigit);
    ~CAnyPlaceTransformRule();
    bool deduce(const SHyperChar &src, const SHyperChar &dest);
    unsigned int apply(const SHyperChar &src, SHyperChar &dest) const;
};

class CHStringTransform
{
private:
    vector<CBaseTransformRule*> rules;
    unsigned int cost;
    bool isInPlace;
    bool isDigit;
public:
    CHStringTransform(bool _isInPlace, bool _isDigit): isInPlace(_isInPlace), isDigit(_isDigit) {;}
    ~CHStringTransform();
    unsigned int getSize() const {return rules.size(); }
    void reset();    
    bool deduce(const CHyperString& src, const CHyperString& dest);
    unsigned int transform(const CHyperString& src, CHyperString& dest) const;
    unsigned int getCost() const {return cost;}
    friend std::ostream& operator<< (std::ostream &out, const CHStringTransform &what);
};

#endif
