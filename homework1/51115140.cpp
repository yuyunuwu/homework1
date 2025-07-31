#include <iostream>
using namespace std;

int a(int m, int n) {
    if (m == 0) return n + 1;
    if (n == 0) return a(m - 1, 1);
    return a(m - 1, a(m, n - 1));
}

int main() {
    int m, n;
    cout << "輸入m n: ";
    cin >> m >> n;
    cout << "A(" << m << "," << n << ")=" << a(m, n) << endl;
    return 0;
}


//第二題//
#include <iostream>
using namespace std;

void generate(char s[], int n, int i, char* sub, int size) {
    if (i == n) {
        cout << "{ ";
        for (int j = 0; j < size; j++)
            cout << sub[j] << " ";
        cout << "}" << endl;
        return;
    }

    generate(s, n, i + 1, sub, size); 

    sub[size] = s[i];                
    generate(s, n, i + 1, sub, size + 1);
}

int main() {
    char s[] = {'a', 'b', 'c'};
    int n = 3;
    char* sub = new char[n]; 

    generate(s, n, 0, sub, 0);

    delete[] sub; 
    return 0;
}

