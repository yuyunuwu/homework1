# 51115140

作業3

### 題目一

## 解題說明


開發一個 C++ 類別 Polynomial 以循環串列方式儲存並操作整數係數的單變數多項式 每個節點包含三個成員：
coef：多項式係數
exp：多項式指數
link：指向下一節點的指標
程式需支援多項式的輸入輸出 加減乘運算 賦值運算 拷貝建構子 解構子 以及在指定變數值下的多項式求值



### 解題策略

資料結構設計

定義節點結構 Node，含 coef、exp 與 link

使用循環串列並設置 header node

核心功能實作

輸入運算子 >>：將外部表示轉換為循環串列

輸出運算子 <<：將循環串列輸出成外部表示

拷貝建構子：深拷貝多項式資料

賦值運算子：先釋放原串列，再複製來源多項式

解構子：釋放串列節點至可用空間串列

多項式運算（+, -, *）：依數學規則實作

Evaluate：輸入變數值，回傳計算結果

測試案例

建立多個多項式測試輸入、輸出、加減乘、複製、指派及求值


## 程式實作


```cpp
#include <iostream>
#include <cmath>
using namespace std;

struct Node {
    int coef;
    int exp;
    Node* link;
    Node(int c = 0, int e = 0, Node* l = nullptr) : coef(c), exp(e), link(l) {}
};

class Polynomial {
private:
    Node* head; // header node

    void clear() {
        Node* p = head->link;
        while (p != head) {
            Node* t = p;
            p = p->link;
            delete t;
        }
        head->link = head;
    }

    void copyFrom(const Polynomial& a) {
        Node* p = a.head->link;
        Node* last = head;
        while (p != a.head) {
            Node* n = new Node(p->coef, p->exp);
            last->link = n;
            last = n;
            p = p->link;
        }
        last->link = head;
    }

public:
    Polynomial() {
        head = new Node();
        head->link = head;
    }

    Polynomial(const Polynomial& a) {
        head = new Node();
        head->link = head;
        copyFrom(a);
    }

    ~Polynomial() {
        clear();
        delete head;
    }

    const Polynomial& operator=(const Polynomial& a) {
        if (this != &a) {
            clear();
            copyFrom(a);
        }
        return *this;
    }

    friend istream& operator>>(istream& is, Polynomial& x) {
        int n, c, e;
        x.clear();
        is >> n;
        Node* last = x.head;
        for (int i = 0; i < n; i++) {
            is >> c >> e;
            Node* p = new Node(c, e);
            last->link = p;
            last = p;
        }
        last->link = x.head;
        return is;
    }

    friend ostream& operator<<(ostream& os, Polynomial& x) {
        Node* p = x.head->link;
        bool first = true;
        while (p != x.head) {
            if (!first && p->coef >= 0) os << "+";
            os << p->coef;
            if (p->exp != 0) os << "x^" << p->exp;
            first = false;
            p = p->link;
        }
        return os;
    }

    Polynomial operator+(const Polynomial& b) const {
        Polynomial r;
        Node* aP = head->link;
        Node* bP = b.head->link;
        Node* last = r.head;

        while (aP != head && bP != b.head) {
            if (aP->exp == bP->exp) {
                int sum = aP->coef + bP->coef;
                if (sum != 0) {
                    last->link = new Node(sum, aP->exp);
                    last = last->link;
                }
                aP = aP->link;
                bP = bP->link;
            } else if (aP->exp > bP->exp) {
                last->link = new Node(aP->coef, aP->exp);
                last = last->link;
                aP = aP->link;
            } else {
                last->link = new Node(bP->coef, bP->exp);
                last = last->link;
                bP = bP->link;
            }
        }

        while (aP != head) {
            last->link = new Node(aP->coef, aP->exp);
            last = last->link;
            aP = aP->link;
        }
        while (bP != b.head) {
            last->link = new Node(bP->coef, bP->exp);
            last = last->link;
            bP = bP->link;
        }
        last->link = r.head;
        return r;
    }

    Polynomial operator-(const Polynomial& b) const {
        Polynomial negB(b);
        for (Node* p = negB.head->link; p != negB.head; p = p->link)
            p->coef = -p->coef;
        return *this + negB;
    }

    Polynomial operator*(const Polynomial& b) const {
        Polynomial r;
        for (Node* aP = head->link; aP != head; aP = aP->link) {
            Polynomial temp;
            Node* last = temp.head;
            for (Node* bP = b.head->link; bP != b.head; bP = bP->link) {
                last->link = new Node(aP->coef * bP->coef, aP->exp + bP->exp);
                last = last->link;
            }
            last->link = temp.head;
            r = r + temp;
        }
        return r;
    }

    float Evaluate(float x) const {
        float sum = 0;
        for (Node* p = head->link; p != head; p = p->link) {
            sum += p->coef * pow(x, p->exp);
        }
        return sum;
    }
};

// 測試主程式
int main() {
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

## 效能分析

時間複雜度：

輸入輸出：O(n)
加減運算：O(n + m)
乘法運算：O(n × m)

空間複雜度：O(n)（每項一個節點）

## 測試與驗證

```
```txt
輸入 3 4 3 2 2 1 0
輸出 4x^3 + 2x^2 + 1
```


### 編譯與執行指令

```shell
$ g++ hw3.cpp -o hw3 
$ ./hw3 < poly.txt

```

### 結論

學了一點運算子多載,拷貝結構之類的東西

## 心得
如果上機考考這個我應該直接放手了


