#include <iostream>
#include <bitset>
#include <cmath>
#include <fstream>
#include <omp.h>

using namespace std;

const int l1_len = 30;            //length of starting
const int l2_len = 31;            //bits of
const int l3_len = 32;            //registers
const int res_len = 2048;         //length of sequence generated by Geffe generator
const int C1 = 81;                //decision boundary for register L1
const int N1 = 258;               //number of bits needed to choose hypothesis for L1

const int C2 = 83;                //decision boundary for register L2
const int N2 = 265;               //number of bits needed to choose hypothesis for L2
const string zi = "00100111010111111011001000100001011110000101110011000101101011110100011010100100000111000010111100"
                  "10000000110111110010000111001111000111011111111111111101011011111010000101101101010000100110010111"
                  "00101110101100100000101100111100000111011101110010000101001010101100001100111011010000010101110100"
                  "11111011000011111101111101000111101100000111110010100101011110011010000101111011010001101010111001"
                  "01110000011011010110000001101101101100011010100111010101101110000001111010101101100000011110110101"
                  "10011001000101101110001111110001101000111010101011111101000100111101011100000000101110111111100100"
                  "01110111010111001011000001100100110000100110011011010011111101101100000010001011011000111011111101"
                  "01101110110111100011001001101010010111111101101111100110101110110011010100000010100011101010101010"
                  "00111000101011000011111111101011101110111011010100010001110001000111111001101011011100001111011100"
                  "11111110100101101100111110111000100100001001110100101010111011111010111111101100001010001111011111"
                  "00100101000000100101000001000111000011100111101111001101001110010110111101001011011111000001100011"
                  "00001000101000000011010010011010010011010000011000000100101001001010001110010110001000010101000100"
                  "10110110100010010001111011011010011100110000010101010001000100101100001011011011001011111010111000"
                  "00101001010101010010001111110110010010111101010001011011010110011001101111111111111010010100101100"
                  "00010111001000010111110001001100110010100101010110100100010101000011010000101000001001101001000101"
                  "01000011101010110110101010010100111000010000110111011000000001100101011011110001111111101011110010"
                  "11001100001100010001010101011011010010100111010101011010001111111010010011000110101100101111011110"
                  "00001111110110101010101000110010001000010110000101110011011001101011111001100000101110111111010100"
                  "11111000011000100111101011000010011001001110100011101011100001101111010000110001001110000010100101"
                  "00100110011011100001000111110111001101110010011101100011000100100101110000011100011100010111010001"
                  "1010000010011110011010110111010010010010000100101100101101111001010000010000100110111100";

bitset<2048> L1(string starting);
bitset<2048> L2(string starting);
bitset<2048> L3(string starting);
bitset<2048> Geffe(string L1_start, string L2_start, string L3_start);
bitset<258> L1_small(string starting);
void L1_break(const int C1, const int N1);
void L2_break(const int C2, const int N2);

int main() {

    //testing strings
    string l1_start = "110101001001111101101110001100";
    string l2_start = "0100100001100100010000001010110";
    string l3_start = "11011010011000001100111101101110";

    //L1_break(C1, N1);
    //L2_break(C2, N2);


    return 0;
}


bitset<2048> L1(string starting) {
    string res = starting.append(res_len-l1_len, '0');
    bitset<2048> L1_bitset(res);
    for (int i=res_len - 1; i>29; i--) {
        int temp = L1_bitset[i] ^ L1_bitset[i-1] ^ L1_bitset[i-4] ^ L1_bitset[i-6];
        if (temp) L1_bitset.set(i-l1_len);
    }
    return L1_bitset;
}

bitset<258> L1_small(string starting) {
    //generates first 258 (N1) bits for L1
    string res = starting.append(258-l1_len, '0');
    bitset<258> L1_bitset(res);
    for (int i=257; i>29; i--) {
        int temp = L1_bitset[i] ^ L1_bitset[i-1] ^ L1_bitset[i-4] ^ L1_bitset[i-6];
        if (temp) L1_bitset.set(i-l1_len);
    }
    return L1_bitset;
}

bitset<265> L2_small(string starting) {
    //generates first 258 (N2) bits for L2
    string res = starting.append(265-l2_len, '0');
    bitset<265> L2_bitset(res);
    for (int i=264; i>30; i--) {
        int temp = L2_bitset[i] ^ L2_bitset[i-3];
        if (temp) L2_bitset.set(i-l2_len);
    }
    return L2_bitset;
}

bitset<2048> L2(string starting) {
    string res = starting.append(res_len - l2_len, '0');
    bitset<2048> L2_bitset(res);
    for (int i = res_len - 1; i > 30; i--) {
        int temp = L2_bitset[i] ^L2_bitset[i - 3];
        if (temp) L2_bitset.set(i - l2_len);
    }
    return L2_bitset;
}

bitset<2048> L3(string starting) {
    string res = starting.append(res_len - l3_len, '0');
    bitset<2048> L3_bitset(res);
    for (int i = res_len - 1; i > 31; i--) {
        int temp = L3_bitset[i] ^ L3_bitset[i - 1] ^ L3_bitset[i - 2]^
                L3_bitset[i - 3]^ L3_bitset[i - 5]^ L3_bitset[i - 7];
        if (temp) L3_bitset.set(i - l3_len);
    }
    return L3_bitset;
}

bitset<2048> Geffe(string L1_start, string L2_start, string L3_start) {
    bitset<2048> x = L1(L1_start);
    bitset<2048> y = L2(L2_start);
    bitset<2048> s = L3(L3_start);
    bitset<2048> z;
    for (int i=res_len - 1; i>=0; i--) {
        int temp = (s[i] * x[i]) ^ (1 ^ s[i]) * y[i];
        if (temp) z.set(i);
    }
    return z;
}

void L1_break(const int C1, const int N1) {
    string z = zi.substr(0, N1);
    bitset<258> z_cut(z);
    ofstream file;
    long max_iter = pow(2, l1_len);
    cout << max_iter;
    for (int i=1; i < max_iter; ++i) {
        bitset<30> bin_set(i);
        string bin_str = bin_set.to_string();
        bitset<258> x = L1_small(bin_str);
        bitset<258> r = (x ^ z_cut);
        int R = r.count();
        if (R < C1) {
            file.open ("L1_res.txt", ios::app);
            file << bin_str << "\n";
            file.close();
        }
        if ( i % 1000000 == 0)
            cout << "iteration: " << i/1000000 << " million(s)" << "\n";
    }
}

void L2_break(const int C2, const int N2) {
    string z = zi.substr(0, N2);
    bitset<265> z_cut(z);
    ofstream file;
    long max_iter = pow(2, l2_len);
    double start = omp_get_wtime();
    #pragma omp parallel for
    for (int i=1; i < max_iter; ++i) {
        bitset<31> bin_set(i);
        string bin_str = bin_set.to_string();
        bitset<265> x = L2_small(bin_str);
        bitset<265> r = (x ^ z_cut);
        int R = r.count();
        if (R < C2) {
            file.open ("L2_res.txt", ios::app);
            cout << bin_str << "\n";
            file << bin_str << "\n";
            file.close();
        }
        if ( i % 1000000 == 0) //print every millionth iteration
            cout << "iteration: " << i/1000000 << " million(s)" << "\n";
    }
    double end = omp_get_wtime();
    cout << "Time: " <<  end-start;
}