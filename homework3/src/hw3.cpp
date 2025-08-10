#include <iostream>
#include <cmath>
using namespace std;

struct Node
{
    int coef;
    int exp;
    Node *link;
    Node(int c = 0, int e = 0, Node *l = nullptr) : coef(c), exp(e), link(l) {}
};

class Polynomial
{
private:
    Node *head; // header node

    void clear()
    {
        Node *p = head->link;
        while (p != head)
        {
            Node *t = p;
            p = p->link;
            delete t;
        }
        head->link = head;
    }

    void copyFrom(const Polynomial &a)
    {
        Node *p = a.head->link;
        Node *last = head;
        while (p != a.head)
        {
            Node *n = new Node(p->coef, p->exp);
            last->link = n;
            last = n;
            p = p->link;
        }
        last->link = head;
    }

public:
    Polynomial()
    {
        head = new Node();
        head->link = head;
    }

    Polynomial(const Polynomial &a)
    {
        head = new Node();
        head->link = head;
        copyFrom(a);
    }

    ~Polynomial()
    {
        clear();
        delete head;
    }

    const Polynomial &operator=(const Polynomial &a)
    {
        if (this != &a)
        {
            clear();
            copyFrom(a);
        }
        return *this;
    }

    friend istream &operator>>(istream &is, Polynomial &x)
    {
        int n, c, e;
        x.clear();
        is >> n;
        Node *last = x.head;
        for (int i = 0; i < n; i++)
        {
            is >> c >> e;
            Node *p = new Node(c, e);
            last->link = p;
            last = p;
        }
        last->link = x.head;
        return is;
    }

    friend ostream &operator<<(ostream &os, Polynomial &x)
    {
        Node *p = x.head->link;
        bool first = true;
        while (p != x.head)
        {
            if (!first && p->coef >= 0)
                os << "+";
            os << p->coef;
            if (p->exp != 0)
                os << "x^" << p->exp;
            first = false;
            p = p->link;
        }
        return os;
    }

    Polynomial operator+(const Polynomial &b) const
    {
        Polynomial r;
        Node *aP = head->link;
        Node *bP = b.head->link;
        Node *last = r.head;

        while (aP != head && bP != b.head)
        {
            if (aP->exp == bP->exp)
            {
                int sum = aP->coef + bP->coef;
                if (sum != 0)
                {
                    last->link = new Node(sum, aP->exp);
                    last = last->link;
                }
                aP = aP->link;
                bP = bP->link;
            }
            else if (aP->exp > bP->exp)
            {
                last->link = new Node(aP->coef, aP->exp);
                last = last->link;
                aP = aP->link;
            }
            else
            {
                last->link = new Node(bP->coef, bP->exp);
                last = last->link;
                bP = bP->link;
            }
        }

        while (aP != head)
        {
            last->link = new Node(aP->coef, aP->exp);
            last = last->link;
            aP = aP->link;
        }
        while (bP != b.head)
        {
            last->link = new Node(bP->coef, bP->exp);
            last = last->link;
            bP = bP->link;
        }
        last->link = r.head;
        return r;
    }

    Polynomial operator-(const Polynomial &b) const
    {
        Polynomial negB(b);
        for (Node *p = negB.head->link; p != negB.head; p = p->link)
            p->coef = -p->coef;
        return *this + negB;
    }

    Polynomial operator*(const Polynomial &b) const
    {
        Polynomial r;
        for (Node *aP = head->link; aP != head; aP = aP->link)
        {
            Polynomial temp;
            Node *last = temp.head;
            for (Node *bP = b.head->link; bP != b.head; bP = bP->link)
            {
                last->link = new Node(aP->coef * bP->coef, aP->exp + bP->exp);
                last = last->link;
            }
            last->link = temp.head;
            r = r + temp;
        }
        return r;
    }

    float Evaluate(float x) const
    {
        float sum = 0;
        for (Node *p = head->link; p != head; p = p->link)
        {
            sum += p->coef * pow(x, p->exp);
        }
        return sum;
    }
};

// 測試主程式
int main()
{
    Polynomial p1, p2;
    cout << "Enter polynomial 1 (n c1 e1 ...): ";
    cin >> p1;
    cout << "Enter polynomial 2 (n c1 e1 ...): ";
    cin >> p2;

    cout << "P1 = " << p1 << endl;
    cout << "P2 = " << p2 << endl;
    cout << "P1 + P2 = " << (p1 + p2) << endl;
    cout << "P1 - P2 = " << (p1 - p2) << endl;
    cout << "P1 * P2 = " << (p1 * p2) << endl;

    float x;
    cout << "Enter x value: ";
    cin >> x;
    cout << "P1(" << x << ") = " << p1.Evaluate(x) << endl;
    cout << "P2(" << x << ") = " << p2.Evaluate(x) << endl;
}
