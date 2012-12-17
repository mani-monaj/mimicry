#ifndef _DS_H
#define _DS_H

#include <vector>
#include <list>
#include <string>
#include <sstream>
#include <assert.h>

using namespace std;

// Lame Class, Converted from Struct
class SHyperChar
{
public:
    unsigned int pose;
    char c;
    unsigned int count;
    SHyperChar(unsigned int _pose, char _c, unsigned int _count): pose(_pose), c(_c), count(_count) {;}
    SHyperChar(void) {;}
    bool operator ==(const SHyperChar& rhs) const
    {
        return ((pose == rhs.pose) && (c == rhs.c) && (count == rhs.count));
    }
    bool operator <(const SHyperChar& rhs) const
    {
        return pose < rhs.pose;
    }
    friend std::ostream& operator<< (std::ostream &out, const SHyperChar &hc)
    {
        out << "[" << hc.pose << ":" << hc.c << "^" << hc.count << "]";
        return out;
    }
};

class CHyperString
{
private:
    string rawData;
    vector<SHyperChar> data;

public:
    CHyperString();
    CHyperString(const string &s);
    void update(const string &s);
    void clear();
    void reconstruct();

    unsigned int getSize() const { return data.size(); }
    const vector<SHyperChar>& getDataCst() const {return data;}
    vector<SHyperChar>& getData() {return data;}

    string getRawString() const;
    string getString() const;

    bool operator==(const CHyperString& rhs) const
    {
        return (rawData == rhs.rawData) && (data == rhs.data);
    }

    friend std::ostream& operator<< (std::ostream &out, const CHyperString &hs)
    {
        out << hs.getString();
        return out;
    }
};

#endif
