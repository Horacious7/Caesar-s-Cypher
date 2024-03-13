#include <iostream>
#include <string>
#include <fstream>
#include <limits>

using namespace std;
float ENG_FREQ[26] = {0};

void read(float ENG_FREQ[])
{
    ifstream fin("distribution.txt"); //I added the numbers from the chart
    int i;
    for (i=0; i< 26; ++i)
        fin >> ENG_FREQ[i];
    fin.close();
}

string decode_caesar_cipher(const string& encrypted_text, int shift) //The decoder
{
    string decrypted_text = encrypted_text;
    for (char& c : decrypted_text) {
        if (isalpha(c)) {
            char base;
            if (c >= 'a' && c <= 'z')
            {
                base = 'a';
            }
            else
            {
                base = 'A';
            }
            c = ((c - base - shift + 26) % 26) + base;
        }
    }
    return decrypted_text;
}

void compute_frequency_distribution(const string& text, float letter_freq[]) //Computes the freq of the letters in a text
{
    int total_letters = 0;
    for (char c : text) {
        if (isalpha(c)) {
            char base = islower(c) ? 'a' : 'A';
            letter_freq[c-base]++;
            total_letters++;
        }
    }
    for (int i = 0; i < 26; ++i) {
        letter_freq[i] /= total_letters;
    }
}

double compute_chi_square_distance(const float freq1[], const float freq2[]) //Computes the Chi-square disance between two distributions
{
    double distance = 0;
    for (int i = 0; i < 26; ++i) {
        if (freq2[i] != 0) {
            double term = freq1[i] - freq2[i];
            distance = distance+term*term/freq2[i];
        }
    }
    return distance;
}

int break_caesar_cipher(const string& encrypted_text) //Breaks the Caesar's cipher
{
    double min_distance = numeric_limits<double>::max();
    int best_shift = 0;
    float freqofletters[26];
    compute_frequency_distribution(encrypted_text, freqofletters);
    int shift;
    for (shift=0; shift< 26; shift++) {
        string decrypted_text = decode_caesar_cipher(encrypted_text, shift);

        float decrypted_freq[26] = {0};
        compute_frequency_distribution(decrypted_text, decrypted_freq);

        double distance = compute_chi_square_distance(decrypted_freq, ENG_FREQ);
        if (distance<min_distance)
        {
            min_distance = distance;
            best_shift = shift;
        }
    }
    return best_shift;
}

int main() {
    read(ENG_FREQ); // the frequency of letters from the english alphabet
    int choice;
    string encrypted_text;
    do { //this is the menu that I've done
        cout << "Menu of the Caesar's Cipher:" << endl;
        cout << "1. Decrypt a message read from the keyboard" << endl;
        cout << "2. Decrypt the message from the exercise" << endl;
        cout << "3. Exit the program" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice)
        {
            case 1:
            {
                cout << "Enter the encrypted message: ";
                getline(cin, encrypted_text);
                int best_shift = break_caesar_cipher(encrypted_text);
                string decrypted_text = decode_caesar_cipher(encrypted_text, best_shift);
                cout << "Decrypted Text: " << decrypted_text << endl;
                break;
            }
            case 2:
            {
                string encrypted_text = "uf ime ftq nqef ar fuyqe, uf ime ftq iadef ar fuyqe, uf ime ftq msq ar iuepay, uf ime ftq msq ar raaxuetzqee, uf ime ftq qbaot ar nqxuqr, uf ime ftq qbaot ar uzodqpgxufk, uf ime ftq eqmeaz ar xustf, uf ime ftq eqmeaz ar pmdwzqee, uf ime ftq ebduzs ar tabq, uf ime ftq iuzfqd ar pqebmud.";
                int best_shift = break_caesar_cipher(encrypted_text);
                string decrypted_text = decode_caesar_cipher(encrypted_text, best_shift);
                cout << "Decrypted Text: " << decrypted_text << endl;
                break;
            }
            case 3:
            {
                cout << "Have a wonderful day!" << endl;
                return 0;
            }
            default:
            {
                cout << "Invalid choice. Please enter a valid option." << endl;
                break;
            }
        }
    } while (true);
    return 0;
}
