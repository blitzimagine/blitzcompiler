#include "stdutil.h"

#include <set>
#include <cmath>
#include <cstdlib>

#ifdef _WIN32
#include <Windows.h>
#endif

using namespace std;

int atoi(const string& s)
{
    return atoi(s.c_str());
}

double atof(const string& s)
{
    return atof(s.c_str());
}

string itoa(int n)
{
    char buff[32];
    _itoa_s(n, buff, (size_t)32, 10);
    return string(buff);
}

static int b_finite(double n)
{
    // definition: exponent anything but 2047.

    int e; // 11 bit exponent
    const int eMax = 2047; // 0x7ff, all bits = 1	

    int* pn = (int *)&n;

    e = *++pn; // Intel order!
    e = (e >> 20) & eMax;

    return e != eMax;
}

static int b_isnan(double n)
{
    // definition: exponent 2047, nonzero fraction.

    int e; // 11 bit exponent
    const int eMax = 2047; // 0x7ff, all bits = 1	

    int* pn = (int *)&n;

    e = *++pn; // Intel order!
    e = (e >> 20) & eMax;

    if (e != 2047) return 0; // almost always return here

    int fHi, fLo; // 52 bit fraction

    fHi = (*pn) & 0xfffff; // first 20 bits
    fLo = *--pn; // last 32 bits

    return (fHi | fLo) != 0; // returns 0,1 not just 0,nonzero
}

/////////////
//By FLOYD!//
/////////////
string ftoa(float n)
{
    static const int digits = 6;

    int eNeg = -4, ePos = 8; // limits for e notation.

    char buffer[50]; // from MSDN example, 25 would probably suffice
    string t;
    int dec, sign;

    if (b_finite(n))
    {
        //		if ( digits < 1 ) digits = 1;	// less than one digit is nonsense
        //		if ( digits > 8 ) digits = 8;	// practical maximum for float

        //t = _ecvt(n, digits, &dec, &sign);

        char* tmp = new char[64];
        errno_t err = _ecvt_s(tmp, 64, n, digits, &dec, &sign);
        t = tmp;
        delete tmp;

        if (dec <= eNeg + 1 || dec > ePos)
        {
            _gcvt_s(buffer, 50, n, digits);

            t = buffer;
            return t;
        }

        // Here is the tricky case. We want a nicely formatted
        // number with no e-notation or multiple trailing zeroes.

        if (dec <= 0)
        {
            t = "0." + string(-dec, '0') + t;
            dec = 1; // new location for decimal point
        } else if (dec < digits)
        {
            t = t.substr(0, dec) + "." + t.substr(dec);
        } else
        {
            t = t + string(dec - digits, '0') + ".0";
            dec += dec - digits;
        }

        // Finally, trim off excess zeroes.

        int dp1 = dec + 1, p = t.length();
        while (--p > dp1 && t[p] == '0');
        t = string(t, 0, ++p);

        return sign ? "-" + t : t;
    } // end of finite case

    if (b_isnan(n)) return "NaN";
    if (n > 0.0) return "Infinity";
    if (n < 0.0) return "-Infinity";

    abort();
    return nullptr;
}

string tolower(const string& s)
{
    string t = s;
    for (int k = 0; k < (int)t.size(); ++k) t[k] = tolower(t[k]);
    return t;
}

string toupper(const string& s)
{
    string t = s;
    for (int k = 0; k < (int)t.size(); ++k) t[k] = toupper(t[k]);
    return t;
}

string fullfilename(const string& t)
{
#ifdef _WIN32
    char buff[MAX_PATH + 1], *p;
    GetFullPathName(t.c_str(),MAX_PATH, buff, &p);
    return string(buff);
#else
    // Use realpath(3)
#endif
}

string filenamepath(const string& t)
{
#ifdef _WIN32
    char buff[MAX_PATH + 1], *p;
    GetFullPathName(t.c_str(),MAX_PATH, buff, &p);
    if (!p) return "";
    *p = 0;
    return string(buff);
#else
    // Use realpath(3)
#endif
}

string filenamefile(const string& t)
{
#ifdef _WIN32
    char buff[MAX_PATH + 1], *p;
    GetFullPathName(t.c_str(),MAX_PATH, buff, &p);
    if (!p) return "";
    return string(p);
#else
    // Use realpath(3)
#endif
}

const int MIN_SIZE = 256;

qstreambuf::qstreambuf()
{
    buf = d_new char[MIN_SIZE];
    setg(buf, buf, buf);
    setp(buf, buf, buf + MIN_SIZE);
}

qstreambuf::~qstreambuf()
{
    delete buf;
}

int qstreambuf::size()
{
    return pptr() - gptr();
}

char* qstreambuf::data()
{
    return gptr();
}

qstreambuf::int_type qstreambuf::underflow()
{
    if (gptr() == egptr())
    {
        if (gptr() == pptr()) return traits_type::eof();
        setg(gptr(), gptr(), pptr());
    }

    return traits_type::to_int_type(*gptr());
}

qstreambuf::int_type qstreambuf::overflow(int_type c)
{
    if (c == traits_type::eof()) return c;

    if (pptr() == epptr())
    {
        int sz = size();
        int n_sz = sz * 2;
        if (n_sz < MIN_SIZE) n_sz = MIN_SIZE;
        char* n_buf = d_new char[ n_sz ];
        memcpy(n_buf, gptr(), sz);
        delete buf;
        buf = n_buf;
        setg(buf, buf, buf + sz);
        setp(buf + sz, buf + sz, buf + n_sz);
    }

    *pptr() = traits_type::to_char_type(c);
    pbump(1);
    return traits_type::not_eof(c);
}

std::string getBestPathName(const std::string& path)
{
#ifdef _WIN32
    char buff[MAX_PATH + 1], *p;
    if (GetFullPathName(path.c_str(), MAX_PATH, buff, &p))
        return string(buff);
    *p = 0;
    return path;
#else
    // Use realpath(3)
#endif
}

int setCurrentDirectory(const std::string& path)
{
#ifdef _WIN32
    return SetCurrentDirectory(path.c_str());
#else
    return chdir(in_file.substr(0, n).c_str());
#endif
}
