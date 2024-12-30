#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int d = 256; // Number of characters in the input alphabet
const int q = 101; // A prime number

// Function to perform Rabin-Karp string matching
void rabinKarpSearch(const string& text, const string& pattern) {
    int M = pattern.length();
    int N = text.length();
    int i, j;
    int patternHash = 0; // Hash value for the pattern
    int textHash = 0;    // Hash value for the text window
    int h = 1;

    // Precompute the value of h = (d^(M-1)) % q
    for (i = 0; i < M - 1; i++) {
        h = (h * d) % q;
    }

    // Calculate the hash value of the pattern and the first window of the text
    for (i = 0; i < M; i++) {
        patternHash = (d * patternHash + pattern[i]) % q;
        textHash = (d * textHash + text[i]) % q;
    }

    // Slide the pattern over the text
    for (i = 0; i <= N - M; i++) {
        // If the hash values match, check for exact match
        if (patternHash == textHash) {
            for (j = 0; j < M; j++) {
                if (text[i + j] != pattern[j]) {
                    break;
                }
            }

            if (j == M) {
                cout << "Pattern found at index " << i << endl;
            }
        }

        // Calculate the hash value for the next window of text
        if (i < N - M) {
            textHash = (d * (textHash - text[i] * h) + text[i + M]) % q;

            // If the hash value is negative, convert it to positive
            if (textHash < 0) {
                textHash += q;
            }
        }
    }
}

int main() {
    string text = "ABABDABACDABABCABAB";
    string pattern = "ABABCABAB";

    rabinKarpSearch(text, pattern);

    return 0;
}
