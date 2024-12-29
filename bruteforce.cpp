

#include <iostream>
#include <string>
using namespace std;

// Function to perform brute force string matching
void bruteForceSearch(const string& text, const string& pattern) {
    int N = text.length();
    int M = pattern.length();

    // Loop through all positions in the text
    for (int i = 0; i <= N - M; i++) {
        int j;
        // Compare the pattern with the substring of text starting at i
        for (j = 0; j < M; j++) {
            if (text[i + j] != pattern[j]) {
                break;
            }
        }

        // If all characters matched, print the position
        if (j == M) {
            cout << "Pattern found at index " << i << endl;
        }
    }
}

int main() {
    string text = "ABABDABACDABABCABAB";
    string pattern = "ABABCABAB";

    bruteForceSearch(text, pattern);

    return 0;
}
