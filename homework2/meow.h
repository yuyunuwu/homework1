#include <iostream>
#include <cstring>
using namespace std;

class P
{
private:
    int *c;
    int d;

public:
    P(int x = 0)
    {
        d = x;
        c = new int[d + 1];
        memset(c, 0, sizeof(int) * (d + 1));
    }

    ~P()
    {
        delete[] c;
    }

    P(const P &o)
    {
        d = o.d;
        c = new int[d + 1];
        for (int i = 0; i <= d; ++i)
            c[i] = o.c[i];
    }

    friend istream &operator>>(istream &in, P &p)
    {
        cout << "最高次方：";
        in >> p.d;
        delete[] p.c;
        p.c = new int[p.d + 1];
        memset(p.c, 0, sizeof(int) * (p.d + 1));
        for (int i = p.d; i >= 0; --i)
        {
            cout << "x^" << i << " 係數：";
            in >> p.c[i];
        }
        return in;
    }

    friend ostream &operator<<(ostream &out, const P &p)
    {
        bool f = false;
        for (int i = p.d; i >= 0; --i)
        {
            if (p.c[i] == 0)
                continue;
            if (f)
                out << " + ";
            if (i == 0)
                out << p.c[i];
            else if (i == 1)
                out << p.c[i] << "x";
            else
                out << p.c[i] << "x^" << i;
            f = true;
        }
        if (!f)
            out << "0";
        return out;
    }
};
