#ifndef _DS_H
#define _DS_H

#include <vector>
#include <list>
#include <string>
#include <sstream>
#include <assert.h>

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
    void reconstruct();

    unsigned int getsize() const { return data.size(); }
    const vector<SHyperChar>& getDataCst() const {return data;}
    vector<SHyperChar>& getData() {return data;}

    string getRawString() const;
    string getString() const;
};

#endif
