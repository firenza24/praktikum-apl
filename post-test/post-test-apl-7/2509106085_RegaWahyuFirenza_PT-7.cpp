#include <iostream>
#include <string>
#include <iomanip>
#include <limits>

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

void selectionSortNIKDesc(Warga daftar[], int n) {
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

void urutkanNIKAsc(Warga daftar[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (daftar[j].nik > daftar[j + 1].nik) swap(daftar[j], daftar[j+1]);
        }
    }
}

int cariNikBinary(Warga daftar[], int low, int high, string target_nik) {
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (daftar[mid].nik == target_nik) return mid;
        if (daftar[mid].nik < target_nik) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

int hitungTotalWarga(int n) {
    if (n <= 0) return 0;
    return 1 + hitungTotalWarga(n - 1);
}

void konfirmasi(string aksi) {
    cout << HIJAU << ">>> Berhasil melakukan " << aksi << "!" << RESET << endl;
}

void tampilkanMenu(string role) {
    cout << CYAN << "\n===============================" << endl;
    cout << "        MENU UTAMA RT 67        " << endl;
    cout << "        ROLE: " << MAGENTA << role << CYAN << endl;
    cout << "===============================" << RESET << endl;
    if (role == "admin") {
        cout << BIRU << "1." << RESET << " Tambah Data Warga" << endl;
        cout << BIRU << "2." << RESET << " Lihat & Urutkan Warga" << endl;
        cout << BIRU << "3." << RESET << " Update Data Warga" << endl;
        cout << BIRU << "4." << RESET << " Hapus Data Warga" << endl;
        cout << BIRU << "5." << RESET << " Cari Data Warga" << endl;
    } else {
        cout << BIRU << "1." << RESET << " Lihat Data Warga" << endl;
    }
    cout << BIRU << "6." << RESET << " Logout" << endl;
    cout << BIRU << "7." << RESET << " Keluar Program" << endl;
    cout << CYAN << "-------------------------------" << RESET << endl;
    cout << "Pilih Menu: ";
}

void tambahWarga(Warga daftar[], int *jumlah) {
    if (*jumlah >= 10) throw "Kapasitas penuh!";
    Warga &baru = daftar[*jumlah];
    cout << KUNING << "\n>>> Input Data Warga <<<" << RESET << endl;
    cout << "Nama     : "; getline(cin, baru.nama);
    if (!isHanyaHuruf(baru.nama)) throw "Nama tidak valid (Harus huruf)!";
    cout << "NIK      : "; getline(cin, baru.nik);
    if (!isHanyaAngka(baru.nik)) throw "NIK tidak valid (Harus angka)!";
    cout << "Jalan    : "; getline(cin, baru.alamat.jalan);
    cout << "No jalan : "; getline(cin, baru.alamat.nomor_jalan);
    baru.status = "Aktif";
    (*jumlah)++;
    konfirmasi("Penambahan Data");
}

void lihatWarga(Warga daftar[], int jumlah, string role) {
    if (jumlah == 0) throw "Belum ada warganya.";
    
    if (role == "admin") {
        int pilSort;
        cout << "\nUrutkan Berdasarkan:\n";
        cout << "1. Nama (Ascending - Bubble Sort)\n";
        cout << "2. NIK (Descending - Selection Sort)\n";
        cout << "3. Nama (Descending - Insertion Sort)\n";
        cout << "4. Tanpa Pengurutan\n";
        cout << "Pilih: "; 
        if (!(cin >> pilSort)) { cin.clear(); throw "Input harus angka!"; }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (pilSort == 1) bubbleSortNama(daftar, jumlah);
        else if (pilSort == 2) selectionSortNIKDesc(daftar, jumlah);
        else if (pilSort == 3) insertionSortNamaDesc(daftar, jumlah);
    }

    cout << "\nTotal Data: " << KUNING << hitungTotalWarga(jumlah) << RESET << endl; 
    cout << ABU << setfill('=') << setw(80) << "=" << RESET << endl;
    cout << setfill(' '); 
    cout << CYAN << left << setw(5) << "NO" << setw(20) << "NAMA" << setw(15) << "NIK" << setw(15) << "STATUS" << "ALAMAT" << RESET << endl;
    cout << ABU << setfill('-') << setw(80) << "-" << RESET << endl;
    cout << setfill(' ');

    for (int i = 0; i < jumlah; i++) {
        Warga &p = daftar[i];
        string warnaStatus = (p.status == "Aktif") ? HIJAU : MERAH;
        cout << left << setw(5) << i + 1 << setw(20) << p.nama << setw(15) << p.nik 
             << warnaStatus << setw(15) << p.status << RESET 
             << p.alamat.jalan << " No." << p.alamat.nomor_jalan << endl;
    }
    cout << ABU << setfill('=') << setw(80) << "=" << RESET << endl;
    cout << setfill(' ');
}

int main() {
    string admin_user = "Rega", admin_pw = "085";
    string member_user = "Warga", member_pw = "999";
    Warga daftar_warga[10];
    int jumlah_warga = 0;
    bool program_jalan = true;

    while (program_jalan) {
        string in_nama, in_pw, role_aktif = "";
        int sisa = 3;
        bool login_ok = false;

        while (sisa > 0) {
            cout << CYAN << "==========================" << endl;
            cout << "    LOGIN SISTEM RT 67    " << endl;
            cout << "==========================" << RESET << endl;
            cout << "Username : "; getline(cin, in_nama);
            cout << "Password : "; getline(cin, in_pw);
            if (in_nama == admin_user && in_pw == admin_pw) { login_ok = true; role_aktif = "admin"; break; }
            else if (in_nama == member_user && in_pw == member_pw) { login_ok = true; role_aktif = "anggota"; break; }
            else { sisa--; cout << MERAH << "Login Gagal! Sisa: " << sisa << RESET << endl << endl; }
        }

        if (!login_ok) return 0;

        bool login_aktif = true;
        while (login_aktif) {
            tampilkanMenu(role_aktif);
            int pil;
            try {
                if (!(cin >> pil)) throw "Input menu harus berupa angka!";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                if (pil == 1 && role_aktif == "admin") {
                    tambahWarga(daftar_warga, &jumlah_warga);
                } else if ((pil == 2 && role_aktif == "admin") || (pil == 1 && role_aktif == "anggota")) {
                    lihatWarga(daftar_warga, jumlah_warga, role_aktif);
                } else if (pil == 3 && role_aktif == "admin") {
                    if (jumlah_warga == 0) throw "Data kosong!";
                    int idx; cout << "Masukkan Nomor Urut: "; cin >> idx; 
                    if (cin.fail()) { cin.clear(); throw "Nomor harus angka!"; }
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    
                    if (idx > 0 && idx <= jumlah_warga) {
                        Warga &p = daftar_warga[idx-1];
                        cout << KUNING << "\n>>> Edit Data: " << p.nama << " <<<" << RESET << endl;
                        cout << "1. Nama\n2. NIK\n3. Status\n4. Alamat\nPilih: ";
                        int sub; cin >> sub; cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        if (sub == 1) { cout << "Nama Baru: "; getline(cin, p.nama); if(!isHanyaHuruf(p.nama)) throw "Nama tidak valid!"; }
                        else if (sub == 2) { cout << "NIK Baru: "; getline(cin, p.nik); if(!isHanyaAngka(p.nik)) throw "NIK tidak valid!"; }
                        else if (sub == 3) { cout << "Status Baru: "; getline(cin, p.status); }
                        else if (sub == 4) { 
                            cout << "Jalan Baru: "; getline(cin, p.alamat.jalan);
                            cout << "No Baru   : "; getline(cin, p.alamat.nomor_jalan);
                        } else throw "Pilihan menu edit salah!";
                        konfirmasi("Update Data");
                    } else throw "Nomor urut tidak ditemukan!";
                } else if (pil == 4 && role_aktif == "admin") {
                    if (jumlah_warga == 0) throw "Data kosong!";
                    int idx; cout << "Nomor yang Dihapus: "; cin >> idx; 
                    if (cin.fail()) { cin.clear(); throw "Nomor harus angka!"; }
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    if (idx < 1 || idx > jumlah_warga) throw "Nomor tidak valid!";
                    for (int i = idx - 1; i < jumlah_warga - 1; i++) daftar_warga[i] = daftar_warga[i+1];
                    jumlah_warga--; konfirmasi("Penghapusan Data");
                } else if (pil == 5 && role_aktif == "admin") {
                    if (jumlah_warga == 0) throw "Data masih kosong!";
                    string t_nik; cout << "Masukkan NIK yang dicari: "; getline(cin, t_nik);
                    if (!isHanyaAngka(t_nik)) throw "NIK harus angka!";
                    
                    urutkanNIKAsc(daftar_warga, jumlah_warga); 
                    
                    int hasil = cariNikBinary(daftar_warga, 0, jumlah_warga - 1, t_nik);
                    if (hasil != -1) {
                        cout << HIJAU << "\nData Ditemukan!" << RESET << endl;
                        cout << "Nama: " << daftar_warga[hasil].nama << " | NIK: " << daftar_warga[hasil].nik << endl;
                    } else throw "NIK tidak ditemukan!";
                } else if (pil == 6) {
                    cout << HIJAU << "Logout berhasil!" << RESET << endl;
                    login_aktif = false;
                } else if (pil == 7) {
                    login_aktif = false; program_jalan = false;
                } else throw "Pilihan tidak tersedia!";

            } catch (const char* e) {
                cout << MERAH << "\n[!] ERROR: " << e << RESET << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    }
    return 0;
}