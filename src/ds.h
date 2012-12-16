#ifndef _DS_H
#define _DS_H

#include <vector>
#include <string>
#include <sstream>

using namespace std;

struct SHyperChar
{
    unsigned int pose;
    char c;
    unsigned int count;
    SHyperChar(unsigned int _pose, char _c, unsigned int _count): pose(_pose), c(_c), count(_count) {;}
    SHyperChar(void) {;}
};

class CHyperString
{
private:
    string rawData;
    vector<SHyperChar> data;

public:
    CHyperString(const string &s);
    void update(const string &s);
    void clear();
    const vector<SHyperChar>& getData() const {return data;}

    string getRawString() const;
    string getString() const;
};


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
};

#endif
