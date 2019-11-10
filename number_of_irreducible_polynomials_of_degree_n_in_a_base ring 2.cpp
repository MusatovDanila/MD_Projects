#include <iostream>
#include <vector>

using namespace std;
const unsigned int one = 1;
void reducible_polynomials(vector<bool> &polynomials, unsigned int polynom, unsigned int polynom_now, unsigned int degree) {
    if (polynom < one << (degree + 1)) {
        polynomials[polynom] = false;
    }
    if (polynom_now < one << (degree + 1)) {
        polynomials[polynom_now] = false;
    }
    if (polynom < (one << degree)) {
        if (!polynom) reducible_polynomials(polynomials, polynom_now, polynom_now, degree);
        for (unsigned int i = one; i < degree; i++) {
            if ((polynom_now << i) > one << (degree + one)) {
                break;
            }
            reducible_polynomials(polynomials, (polynom ^ (polynom_now << i)), (polynom_now << i), degree);
            // 110=x^2+x 011=x+1 110^011=101=x^2+1 (sum(mod 2))
        }
    }
}
int main() {
    unsigned int n;
    unsigned int count = 0;
    cin >> n;
    vector<bool> polynomials(1 << (n + 1), true);
    for (unsigned int i = 2; i < (1 << ((n / 2) + 1)); i++) {
        if (polynomials[i]) {
            reducible_polynomials(polynomials, 0, i, n);
        }
    }
    for (unsigned int i = one << n; i < (one << (n + 1)); i++) {
        if (polynomials[i]) {
            count++;
        }
    }
    cout << count;
    system("pause");
    return 0;
}
