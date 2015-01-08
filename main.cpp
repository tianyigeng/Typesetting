/*
    This is a C++ implement of the beautiful typesetting problem. 
    Dynamic methods. 
    Copyright @ Mr. Geng Tianyi
    Contact: gty12[at]mails[dot]tsinghua[dot]edu[dot]cn. 
*/

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

inline static int square(int x) {
    // Thanks to god tan. 
    return x*x;
}

class Tuple {
public:
    int a; // First word of last line of first paragraph
    int b; // First word of first line of last paragraph
    int min_P; // Minimum value of P1+P2

    Tuple(int a_, int b_, int P_): a(a_), b(b_), min_P(P_)
    {
        //
    }
};

class Typesetting {
public: 
    unsigned long int num = 0; // Num of words
    int max_len = 0; // Maximum length of a line
    vector<int> word;
    vector<int> optiValuePre;
    vector<int> optiValuePost;
    vector<int> cut_point_post; // Index of ending words in all lines @last paragraph.
    vector<int> cut_point_pre; // Index of starting words in all lines @first paragraph.

    Typesetting();
    ~Typesetting();

    bool inOneLine(int, int); // If word[i:j-1] can be put in a single line
    bool FindPostValue(); // Implement the optiValuePost array. 
    bool FindPreValue(); // Implement the optiValuePre array. 
    void FindSolution();
};

bool Typesetting::inOneLine(int i, int j) {
    int sum = word[i];
    while (i < j) {
        i++;
        sum += word[i] + 1;
        if (sum > max_len) {
            return false;
        }
    }
    return true;
}

void Typesetting::FindSolution() {
    Tuple solution(0, 0, -1);
    for (int i = 0; i < num; ++i) {
        int j = i + 1;
        while (j < num && inOneLine(i, j)) {
            int temp_P = optiValuePre[i] + optiValuePost[j];
            if (solution.min_P < 0 || temp_P < solution.min_P) {
                solution = Tuple(i, j, temp_P);
            }
            j++;
        }
    }
    return ;
}

Typesetting::Typesetting() {
    int temp = 0;
    cin >> num >> max_len; 
    for (int i = 0; i < max_len; ++i) {
        cin >> temp;
        word.push_back(temp);
    }
    return ;
}

Typesetting::~Typesetting() {
    return ;
}

bool Typesetting::FindPreValue() {
    if (optiValuePre.length() != word.length()) { // Sanity check
        return false;
    }

    optiValuePre[0] = 0; 

    // Search from backward to forward 
    // int curr_word = -1; // Index of current word
    int curr_len = 0; // Length of current line
    // int prev_len = 0; // Length of previous line

    // // If all words can be put in a single line
    // while (curr_len + word[curr_word + 1] + 1 <= max_len) {
    //     curr_word++;
    //     curr_len += word[curr_word] + 1; 
    //     optiValuePre[curr_word] = 0; 
    //     cut_point_pre[curr_word] = 0;
    // }
    // prev_len = curr_len;

    // Dynamic begins
    for (int i = 1; i < num; ++i) {
        int temp_cut_pos = i - 1;
        curr_len = word[temp_cut_pos];

        // New words can be added to line begin with word[i]
        while (temp_cut_pos != 0 && curr_len + word[temp_cut_pos - 1] + 1 <= max_len) {
            temp_cut_pos--;
            curr_len += word[temp_cut_pos] + 1; 
            // prev_len -= word[temp_cut_pos] - 1;
            int temp_P_val = square(max_len - curr_len) + optiValuePre[temp_cut_pos];
            // If the current cut position is better
            if (temp_P_val < optiValuePre[i]) {
                optiValuePre[i] = temp_P_val;
                cut_point_pre[i] = temp_cut_pos;
            }
        }
    }
}

bool Typesetting::FindPostValue() {
    if (optiValuePost.length() != word.length()) { // Sanity check 
        return false;
    }

    // Search from backward to forward 
    int curr_word = num; // Index of current word
    int curr_len = 0; // Length of current line

    // If all words can be put in a single line
    while (curr_len + word[curr_word - 1] + 1 <= max_len) {
        curr_word--;
        curr_len += word[curr_word] + 1; 
        optiValuePost[curr_word] = 0; 
        cut_point_post[curr_word] = num - 1;
    }

    // Dynamic begins
    for (int i = curr_word - 1; i >= 0; --i) {
        int temp_cut_pos = i;
        curr_len = word[i];
        cut_point_post[curr_word] = i;

        // New words can be added to line begin with word[i]
        while (curr_len + word[temp_cut_pos - 1] + 1 <= max_len) {
            temp_cut_pos++;
            curr_len += word[temp_cut_pos] + 1; 
            int temp_P_val = square(max_len - curr_len) + optiValuePost[temp_cut_pos + 1];
            // If the current cut position is better
            if (temp_P_val < optiValuePost[i]) {
                optiValuePost[i] = temp_P_val;
                cut_point_post[i] = temp_cut_pos;
            }
        }

    }
    return true;
}








int main() {
    

    Typesetting prob;
    prob.solve();



    return 0;
}
