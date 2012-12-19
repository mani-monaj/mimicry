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
    virtual bool deduce(const SMetaChar &src, const SMetaChar& dest) = 0;
    virtual unsigned int apply(const SMetaChar &src, SMetaChar& dest) const = 0;
    unsigned int transform(const CMetaString& src, CMetaString &dest) const;
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
    bool deduce(const SMetaChar &src, const SMetaChar &dest);
    unsigned int apply(const SMetaChar &src, SMetaChar &dest) const;
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
    bool deduce(const SMetaChar &src, const SMetaChar &dest);
    unsigned int apply(const SMetaChar &src, SMetaChar &dest) const;
};

class CMStringTransform
{
private:
    vector<CBaseTransformRule*> rules;
    unsigned int cost;
    bool isInPlace;
    bool isDigit;
public:
    CMStringTransform(bool _isInPlace, bool _isDigit): isInPlace(_isInPlace), isDigit(_isDigit) {;}
    ~CMStringTransform();
    unsigned int getSize() const {return rules.size(); }
    void reset();    
    bool deduce(const CMetaString& src, const CMetaString& dest);
    unsigned int transform(const CMetaString& src, CMetaString& dest) const;
    unsigned int getCost() const {return cost;}
    friend std::ostream& operator<< (std::ostream &out, const CMStringTransform &what);
};

#endif
