#include <bits/stdc++.h>
using namespace std;
#define NO_OF_CHARS 256

void badCharHeuristic(string str, int size, int badchar[NO_OF_CHARS]) {
    for (int i = 0; i < NO_OF_CHARS; i++)
        badchar[i] = -1;
    for (int i = 0; i < size; i++)
        badchar[(int)str[i]] = i;
}

void preprocessGoodSuffix(string pat, int m, vector<int>& shift, vector<int>& border) {
    int i = m, j = m + 1;
    border[i] = j;

    while (i > 0) {
        while (j <= m && pat[i - 1] != pat[j - 1]) {
            if (shift[j] == 0)
                shift[j] = j - i;
            j = border[j];
        }
        i--; 
        j--;
        border[i] = j;
    }

    j = border[0];
    for (i = 0; i <= m; i++) {
        if (shift[i] == 0)
            shift[i] = j;
        if (i == j)
            j = border[j];
    }
}

void search(string txt, string pat) {
    int n = txt.size();
    int m = pat.size();
    int badchar[NO_OF_CHARS];
    vector<int> shift(m + 1, 0);
    vector<int> border(m + 1, 0);

    badCharHeuristic(pat, m, badchar);
    preprocessGoodSuffix(pat, m, shift, border);

    int s = 0;
    while (s <= (n - m)) {
        int j = m - 1;
        while (j >= 0 && pat[j] == txt[s + j])
            j--;
        if (j < 0) {
            cout << "Pattern occurs at shift = " << s << endl;
            s += shift[0];
        } else {
            s += max(shift[j + 1], j - badchar[txt[s + j]]);
        }
    }
}

int main() {
    string txt = "ABAAABCD";
    string pat = "ABC";
    search(txt, pat);
    return 0;
}