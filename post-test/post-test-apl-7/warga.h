#ifndef WARGA_H
#define WARGA_H

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

#define RESET   "\033[0m"
#define MERAH   "\033[31m"
#define HIJAU   "\033[32m"
#define KUNING  "\033[33m"
#define BIRU    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define ABU     "\033[90m"

struct DetailAlamat {
    string jalan;
    string nomor_jalan;
};

struct Warga {
    string nama;
    string nik;
    string status; 
    DetailAlamat alamat;
};

bool isHanyaHuruf(string s) {
    if (s.empty()) return false;
    for (char c : s) if (!isalpha(c) && c != ' ') return false;
    return true;
}

bool isHanyaAngka(string s) {
    if (s.empty()) return false;
    for (char c : s) if (!isdigit(c)) return false;
    return true;
}

void bubbleSortNama(Warga daftar[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (daftar[j].nama > daftar[j + 1].nama) swap(daftar[j], daftar[j+1]);
        }
    }
}

void selectionSortNIK(Warga daftar[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int max_idx = i;
        for (int j = i + 1; j < n; j++) if (daftar[j].nik > daftar[max_idx].nik) max_idx = j;
        swap(daftar[i], daftar[max_idx]);
    }
}

void insertionSortNamaDesc(Warga daftar[], int n) {
    for (int i = 1; i < n; i++) {
        Warga key = daftar[i];
        int j = i - 1;
        while (j >= 0 && daftar[j].nama < key.nama) {
            daftar[j + 1] = daftar[j];
            j--;
        }
        daftar[j + 1] = key;
    }
}

void urutkanNIKCepat(Warga *daftar, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if ((daftar + j)->nik > (daftar + j + 1)->nik) swap(*(daftar + j), *(daftar + j + 1));
        }
    }
}

int hitungTotalWarga(int n) {
    if (n <= 0) return 0;
    return 1 + hitungTotalWarga(n - 1);
}

int cariNikBinary(Warga *daftar, int low, int high, string target_nik) {
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if ((daftar + mid)->nik == target_nik) return mid;
        if ((daftar + mid)->nik < target_nik) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

#endif