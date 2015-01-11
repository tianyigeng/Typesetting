/*
This is a C++ implement of the beautiful typesetting problem.
Dynamic methods.
Special thanks to Mr. Tan. 
*/

#include <cstdio>

class Typesetting {
public:
    int num; // Num of words
    int max_len; // Maximum length of a line
    int* word;
    long long* optiValuePre;
    long long* optiValuePost;

    Typesetting();
    ~Typesetting();

    void FindPostValue(); // Implement the optiValuePost array. 
    void FindPreValue(); // Implement the optiValuePre array. 
    void FindSolution();
};

void Typesetting::FindSolution() {
    FindPreValue();
    FindPostValue();
    
    long long minP = -1;
    int mina = 0;
    int minb = 0;
    int curr_len = 0;
    int j = 0;
    for (int i = 0; i < num; ++i) {
        if (minP >= 0 && optiValuePre[i] > minP) {
            continue;
        }
        curr_len = word[i];
        j = i + 1;
        while (j < num && curr_len + word[j] + 1 <= max_len) {
            curr_len += word[j] + 1;
            long long temp_P = optiValuePre[i] + optiValuePost[j];
            if (minP < 0 || temp_P <= minP) {
                if (temp_P != minP) {
                    minP = temp_P;
                    mina = i;
                    minb = j;
                }
                else {
                    if (i < mina) {
                        mina = i;
                        minb = j;
                    }
                    else if (j < minb) {
                        minb = j;
                    }
                }
            }
            j++;
        }
    }
    printf("%lld %d %d", minP, mina, minb);
    return;
}

Typesetting::Typesetting() {
    int temp = 0;
    scanf("%d%d", &num, &max_len);
    word = new int[num];
    optiValuePost = new long long[num];
    optiValuePre = new long long[num];

    for (int i = 0; i < num; ++i) {
        scanf("%d", &word[i]);
    }
    return;
}

Typesetting::~Typesetting() {
    delete[] word;
    delete[] optiValuePost;
    delete[] optiValuePre;
    return;
}

void Typesetting::FindPreValue() {

    optiValuePre[0] = 0;

    // Search from backward to forward 
    int curr_len = 0; // Length of current line

    // Dynamic begins
    for (int i = 1; i < num; ++i) {
        int temp_cut_pos = i - 1;
        curr_len = word[temp_cut_pos];
        optiValuePre[i] = (max_len - curr_len)*(max_len - curr_len) + optiValuePre[temp_cut_pos];

        // New words can be added to line begin with word[i]
        while (temp_cut_pos != 0 && curr_len + word[temp_cut_pos - 1] + 1 <= max_len) {
            temp_cut_pos--;
            curr_len += word[temp_cut_pos] + 1;
            long long int temp_P_val = (max_len - curr_len)*(max_len - curr_len) + optiValuePre[temp_cut_pos];
            // If the current cut position is better
            if (temp_P_val < optiValuePre[i]) {
                optiValuePre[i] = temp_P_val;
            }
        }
    }
}

void Typesetting::FindPostValue() {

    // Search from backward to forward 
    int curr_word = num - 1; // Index of current word
    int curr_len = word[curr_word]; // Length of current line

    // If all words can be put in a single line
    while (curr_word != 0 && curr_len + word[curr_word - 1] + 1 <= max_len) {
        curr_word--;
        curr_len += word[curr_word] + 1;
        optiValuePost[curr_word] = 0;
    }

    // Dynamic begins
    for (int i = curr_word - 1; i >= 0; --i) {
        int temp_cut_pos = i;
        curr_len = word[i];
        optiValuePost[i] = optiValuePost[i + 1] + (max_len - curr_len)*(max_len - curr_len);

        // New words can be added to line begin with word[i]
        while (temp_cut_pos != num - 1 && curr_len + word[temp_cut_pos + 1] + 1 <= max_len) {
            temp_cut_pos++;
            curr_len += word[temp_cut_pos] + 1;
            long long int temp_P_val = (max_len - curr_len)*(max_len - curr_len) + optiValuePost[temp_cut_pos + 1];
            // If the current cut position is better
            if (temp_P_val < optiValuePost[i]) {
                optiValuePost[i] = temp_P_val;
            }
        }
    }
}

int main() {

    Typesetting prob;
    prob.FindSolution();

    return 0;
}