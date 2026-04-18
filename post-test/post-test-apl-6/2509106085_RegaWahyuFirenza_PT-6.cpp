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

void cariNamaLinear(Warga *daftar, int jumlah, string target) {
    bool ketemu = false;
    cout << CYAN << "\n=== HASIL PENCARIAN NAMA: " << target << " ===" << RESET << endl;
    for (int i = 0; i < jumlah; i++) {
        if ((daftar + i)->nama == target) {
            cout << "[+] NIK    : " << (daftar + i)->nik << endl;
            cout << "[+] Alamat : " << (daftar + i)->alamat.jalan << " No." << (daftar + i)->alamat.nomor_jalan << endl;
            cout << "[+] Status : " << (daftar + i)->status << endl;
            cout << "-----------------------------------" << endl;
            ketemu = true;
        }
    }
    if (!ketemu) cout << MERAH << "[!] Nama tidak ditemukan!" << RESET << endl;
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

void urutkanNIKCepat(Warga *daftar, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if ((daftar + j)->nik > (daftar + j + 1)->nik) {
                Warga temp = *(daftar + j);
                *(daftar + j) = *(daftar + j + 1);
                *(daftar + j + 1) = temp;
            }
        }
    }
}

void bubbleSortNama(Warga daftar[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (daftar[j].nama > daftar[j + 1].nama) {
                Warga temp = daftar[j];
                daftar[j] = daftar[j + 1];
                daftar[j + 1] = temp;
            }
        }
    }
}

void selectionSortNIK(Warga daftar[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int max_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (daftar[j].nik > daftar[max_idx].nik) {
                max_idx = j;
            }
        }
        Warga temp = daftar[max_idx];
        daftar[max_idx] = daftar[i];
        daftar[i] = temp;
    }
}

void insertionSortNamaDesc(Warga daftar[], int n) {
    for (int i = 1; i < n; i++) {
        Warga key = daftar[i];
        int j = i - 1;
        while (j >= 0 && daftar[j].nama < key.nama) {
            daftar[j + 1] = daftar[j];
            j = j - 1;
        }
        daftar[j + 1] = key;
    }
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
    } else {
        cout << BIRU << "1." << RESET << " Lihat Data Warga" << endl;
    }
    
    cout << BIRU << "5." << RESET << " Cari Data Warga" << endl;
    cout << BIRU << "6." << RESET << " Logout" << endl;
    cout << BIRU << "7." << RESET << " Keluar Program" << endl;
    cout << CYAN << "-------------------------------" << RESET << endl;
    cout << "Pilih Menu: ";
}

void tambahWarga(Warga daftar[], int *jumlah) {
    if (*jumlah < 5) {
        Warga *baru = &daftar[*jumlah]; 
        cout << KUNING << "\n>>> Input Data Warga <<<" << RESET << endl;
        cout << "Nama     : "; getline(cin, baru->nama);
        cout << "NIK      : "; getline(cin, baru->nik);
        cout << "Jalan    : "; getline(cin, baru->alamat.jalan);
        cout << "No jalan : "; getline(cin, baru->alamat.nomor_jalan);
        baru->status = "Aktif";
        (*jumlah)++; 
        konfirmasi("Penambahan Data");
    } else {
        cout << MERAH << "[!] Kapasitas penuh!" << RESET << endl;
    }
}

void lihatWarga(Warga daftar[], int jumlah, string role) {
    if (jumlah == 0) {
        cout << MERAH << "\n[!] Belum ada warganya." << RESET << endl;
        return;
    }

    if (role == "admin") {
        int pilSort;
        cout << "\nUrutkan Berdasarkan:\n";
        cout << "1. Nama (Ascending - Bubble Sort)\n";
        cout << "2. NIK (Descending - Selection Sort)\n";
        cout << "3. Nama (Descending - Insertion Sort)\n";
        cout << "4. Tanpa Pengurutan\n";
        cout << "Pilih: "; cin >> pilSort; cin.ignore();

        if (pilSort == 1) bubbleSortNama(daftar, jumlah);
        else if (pilSort == 2) selectionSortNIK(daftar, jumlah);
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
        cout << left << setw(5) << i + 1 << setw(20) << p.nama << setw(15) << p.nik << warnaStatus << setw(15) << p.status << RESET << p.alamat.jalan << " No." << p.alamat.nomor_jalan << endl;
    }
    cout << ABU << setfill('=') << setw(80) << "=" << RESET << endl;
    cout << setfill(' ');
}

int main() {
    string admin_user = "Rega", admin_pw = "085";
    string member_user = "Warga", member_pw = "999";
    Warga daftar_warga[3]; 
    int jumlah_warga = 0;
    bool program_jalan = true;

    while (program_jalan) {
        string input_nama, input_pw, role_aktif = ""; 
        int sisa_percobaan = 3;
        bool login_berhasil = false;

        while (sisa_percobaan > 0) {
            cout << CYAN << "==========================" << endl;
            cout << "    LOGIN SISTEM RT 67    " << endl;
            cout << "==========================" << RESET << endl;
            cout << "Username : "; getline(cin, input_nama);
            cout << "Password : "; getline(cin, input_pw);

            if (input_nama == admin_user && input_pw == admin_pw) {
                login_berhasil = true; role_aktif = "admin"; break;
            } else if (input_nama == member_user && input_pw == member_pw) {
                login_berhasil = true; role_aktif = "anggota"; break;
            } else {
                sisa_percobaan--;
                cout << MERAH << "Login Gagal! Sisa: " << sisa_percobaan << RESET << endl << endl;
            }
        }

        if (!login_berhasil) return 0;

        int pilihan;
        bool login_aktif = true;
        while (login_aktif && program_jalan) {
            tampilkanMenu(role_aktif);
            if (!(cin >> pilihan)) {
                cin.clear(); cin.ignore(1000, '\n');
                cout << MERAH << "[!] Masukkan angka saja!" << RESET << endl;
                continue;
            }
            cin.ignore();

            if (pilihan == 1 && role_aktif == "admin") {
                tambahWarga(daftar_warga, &jumlah_warga); 
            } else if (pilihan == 2) {
                lihatWarga(daftar_warga, jumlah_warga, role_aktif);
            } else if (pilihan == 3 && role_aktif == "admin") {
                int idx; cout << "Masukkan Nomor Urut: "; cin >> idx; cin.ignore();
                if (idx > 0 && idx <= jumlah_warga) {
                    Warga &p = daftar_warga[idx-1];
                    cout << KUNING << "\n>>> Edit Data: " << p.nama << " <<<" << RESET << endl;
                    cout << "1. Nama\n2. NIK\n3. Status\n4. Alamat\nPilih: ";
                    int subPilihan; cin >> subPilihan; cin.ignore();
                    if (subPilihan == 1) { cout << "Nama Baru: "; getline(cin, p.nama); }
                    else if (subPilihan == 2) { cout << "NIK Baru: "; getline(cin, p.nik); }
                    else if (subPilihan == 3) { cout << "Status Baru: "; getline(cin, p.status); }
                    else if (subPilihan == 4) { 
                        cout << "Jalan Baru: "; getline(cin, p.alamat.jalan);
                        cout << "No Baru   : "; getline(cin, p.alamat.nomor_jalan);
                    }
                    konfirmasi("Update Data");
                }
            } else if (pilihan == 4 && role_aktif == "admin") {
                int index; cout << "Nomor yang Dihapus: "; cin >> index; cin.ignore();
                if (index > 0 && index <= jumlah_warga) {
                    for (int i = index - 1; i < jumlah_warga - 1; i++) {
                        daftar_warga[i] = daftar_warga[i + 1];
                    }
                    jumlah_warga--; konfirmasi("Penghapusan Data");
                }
            } else if (pilihan == 5) {
                if (jumlah_warga == 0) {
                    cout << MERAH << "[!] Data masih kosong!" << RESET << endl;
                } else {
                    int pilCari;
                    cout << "\nMetode Pencarian:\n";
                    cout << "1. Cari Nama (Linear Search)\n";
                    cout << "2. Cari NIK (Binary Search)\n";
                    cout << "Pilih: "; cin >> pilCari; cin.ignore();
                    
                    if (pilCari == 1) {
                        string t_nama; cout << "Masukkan Nama yang dicari: "; getline(cin, t_nama);
                        cariNamaLinear(daftar_warga, jumlah_warga, t_nama);
                    } else if (pilCari == 2) {
                        string t_nik; cout << "Masukkan NIK yang dicari: "; getline(cin, t_nik);
                        urutkanNIKCepat(daftar_warga, jumlah_warga);
                        int hasil = cariNikBinary(daftar_warga, 0, jumlah_warga - 1, t_nik);
                        if (hasil != -1) {
                            cout << HIJAU << "\n[✔] Data Ditemukan!" << RESET << endl;
                            cout << "Nama: " << daftar_warga[hasil].nama << " | NIK: " << daftar_warga[hasil].nik << endl;
                        } else cout << MERAH << "[!] NIK tidak ditemukan!" << RESET << endl;
                    } else cout << MERAH << "Pilihan tidak ada!" << RESET << endl;
                }
            } else if (pilihan == 6) {
                login_aktif = false;
                cout << HIJAU << "\n[✔] Logout berhasil!" << RESET << endl;
            } else if (pilihan == 7) {
                program_jalan = false; login_aktif = false;
            } else {
                cout << MERAH << "Pilihan tidak ada dalam menu!" << RESET << endl;
            }
        }
    }
    return 0;
}