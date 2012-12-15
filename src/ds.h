#ifndef _DS_H
#define _DS_H

#include <vector>
#include <string>
#include <sstream>

using namespace std;

struct SHyperChar {
    char c;
    unsigned int count;
    SHyperChar(char _c, unsigned int _count): c(_c), count(_count) {;}
    SHyperChar(void) {;}
};

class CHyperString {
private:
    string rawData;
    vector<SHyperChar> data;

public:
    CHyperString(const string &s);
    void update(const string &s);
    void clear();

    string getRawString() const;
    string getString() const;
};



#endif
