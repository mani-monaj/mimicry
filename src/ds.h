#ifndef _DS_H
#define _DS_H

#include <vector>
#include <list>
#include <string>
#include <sstream>
#include <assert.h>

using namespace std;

// Lame Class, Converted from Struct
class SMetaChar
{
public:
    unsigned int pose;
    unsigned char c;
    unsigned int count;
    SMetaChar(unsigned int _pose, unsigned char _c, unsigned int _count): pose(_pose), c(_c), count(_count) {;}
    SMetaChar(void) {;}
    bool operator ==(const SMetaChar& rhs) const
    {
        return ((pose == rhs.pose) && (c == rhs.c) && (count == rhs.count));
    }
    bool operator <(const SMetaChar& rhs) const
    {
        return pose < rhs.pose;
    }
    friend std::ostream& operator<< (std::ostream &out, const SMetaChar &hc)
    {
        out << "[" << hc.pose << ":" << hc.c << "^" << hc.count << "]";
        return out;
    }
};

class CMetaString
{
private:
    string rawData;
    vector<SMetaChar> data;

public:
    CMetaString();
    CMetaString(const string &s);
    void update(const string &s);
    void clear();
    void reconstruct();

    unsigned int getSize() const { return data.size(); }
    const vector<SMetaChar>& getDataCst() const {return data;}
    vector<SMetaChar>& getData() {return data;}

    string getRawString() const;
    string getString() const;

    bool operator==(const CMetaString& rhs) const
    {
        return (rawData == rhs.rawData) && (data == rhs.data);
    }

    friend std::ostream& operator<< (std::ostream &out, const CMetaString &hs)
    {
        out << hs.getString();
        return out;
    }
};

#endif
