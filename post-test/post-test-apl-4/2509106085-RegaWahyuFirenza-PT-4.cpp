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
        cout << BIRU << "2." << RESET << " Lihat Daftar Warga" << endl;
        cout << BIRU << "3." << RESET << " Update Data Warga" << endl;
        cout << BIRU << "4." << RESET << " Hapus Data Warga" << endl;
    } else {
        cout << BIRU << "1." << RESET << " Lihat Daftar Warga" << endl;
    }
    
    cout << BIRU << "5." << RESET << " Logout" << endl;
    cout << BIRU << "6." << RESET << " Keluar Program" << endl;
    cout << CYAN << "-------------------------------" << RESET << endl;
    cout << "Pilih Menu: ";
}

void tambahWarga(Warga *daftar, int *jumlah) {
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

void lihatWarga(Warga *daftar, int jumlah) {
    if (jumlah == 0) {
        cout << MERAH << "\n[!] Belum ada warganya." << RESET << endl;
    } else {
        cout << "\nTotal Data: " << KUNING << hitungTotalWarga(jumlah) << RESET << endl; 
        
        cout << ABU << setfill('=') << setw(80) << "=" << RESET << endl;
        cout << setfill(' '); 
        
        cout << CYAN << left << setw(5) << "NO" 
             << setw(20) << "NAMA" 
             << setw(15) << "NIK" 
             << setw(15) << "STATUS" 
             << "ALAMAT" << RESET << endl;
        
        cout << ABU << setfill('-') << setw(80) << "-" << RESET << endl;
        cout << setfill(' ');

        for (int i = 0; i < jumlah; i++) {
            Warga *p = (daftar + i);
            string warnaStatus = (p->status == "Aktif") ? HIJAU : MERAH;
            
            cout << left << setw(5) << i + 1 
                 << setw(20) << p->nama 
                 << setw(15) << p->nik 
                 << warnaStatus << setw(15) << p->status << RESET 
                 << p->alamat.jalan << " No." << p->alamat.nomor_jalan << endl;
        }
        
        cout << ABU << setfill('=') << setw(80) << "=" << RESET << endl;
        cout << setfill(' ');
    }
}

void updateWarga(Warga *p) {
    int subPilihan;
    cout << KUNING << "\n>>> Edit Data: " << p->nama << " <<<" << RESET << endl;
    cout << "1. Nama\n2. NIK\n3. Status\n4. Alamat\nPilih: ";
    cin >> subPilihan; cin.ignore();

    switch(subPilihan) {
        case 1: cout << "Nama Baru: "; getline(cin, p->nama); break;
        case 2: cout << "NIK Baru: "; getline(cin, p->nik); break;
        case 3: cout << "Status Baru: "; getline(cin, p->status); break;
        case 4: 
            cout << "Jalan Baru: "; getline(cin, p->alamat.jalan);
            cout << "No Baru   : "; getline(cin, p->alamat.nomor_jalan);
            break;
        default:
            cout << MERAH << "[!] Pilihan edit tidak tersedia!" << RESET << endl;
            return;
    }
    konfirmasi("Update Data");
}

void hapusWarga(Warga *daftar, int *jumlah) {
    int index;
    cout << "Nomor yang Dihapus: "; cin >> index; cin.ignore();
    if (index > 0 && index <= *jumlah) {
        for (int i = index - 1; i < *jumlah - 1; i++) {
            *(daftar + i) = *(daftar + i + 1);
        }
        (*jumlah)--;
        konfirmasi("Penghapusan Data");
    } else {
        cout << MERAH << "[!] Nomor tidak valid!" << RESET << endl;
    }
}

int main() {
    string admin_user = "Rega", admin_pw = "085";
    string member_user = "Warga", member_pw = "999";
    
    Warga daftar_warga[5];
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
        do {
            tampilkanMenu(role_aktif);
            cin >> pilihan; cin.ignore();

            if (role_aktif == "admin") {
                switch(pilihan) {
                    case 1: tambahWarga(daftar_warga, &jumlah_warga); break;
                    case 2: lihatWarga(daftar_warga, jumlah_warga); break;
                    case 3: 
                        int idx;
                        cout << "Masukkan Nomor Urut: "; cin >> idx; cin.ignore();
                        if (idx > 0 && idx <= jumlah_warga) {
                            updateWarga(&daftar_warga[idx-1]);
                        } else {
                            cout << MERAH << "[!] Nomor tidak tersedia!" << RESET << endl;
                        }
                        break;
                    case 4: hapusWarga(daftar_warga, &jumlah_warga); break;
                    case 5: break;
                    case 6: program_jalan = false; break;
                    default: cout << MERAH << "[!] Menu tidak tersedia!" << RESET << endl; break;
                }
            } else {
                if (pilihan == 1) {
                    lihatWarga(daftar_warga, jumlah_warga);
                } else if (pilihan == 5) {
                    break;
                } else if (pilihan == 6) {
                    program_jalan = false; break;
                } else {
                    cout << MERAH << "[!] Menu tidak tersedia!" << RESET << endl;
                }
            }
        } while (pilihan != 5 && program_jalan);
    }
    return 0;
}