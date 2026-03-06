#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

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

int main() {
    string admin_user = "Rega";
    string admin_pw = "085";
    string member_user = "Warga";
    string member_pw = "999";

    Warga daftar_warga[100];
    int jumlah_warga = 0;
    bool program_jalan = true;

    while (program_jalan) {
        string input_nama, input_pw;
        string role_aktif = ""; 
        int sisa_percobaan = 3;
        bool login_berhasil = false;

        while (sisa_percobaan > 0) {
            cout << "===========================" << endl;
            cout << "      LOGIN SISTEM RT      " << endl;
            cout << "===========================" << endl;
            cout << "Username : ";
            getline(cin, input_nama);
            cout << "Password : ";
            getline(cin, input_pw);

            if (input_nama == admin_user && input_pw == admin_pw) {
                login_berhasil = true;
                role_aktif = "admin";
                break;
            } 
            else if (input_nama == member_user && input_pw == member_pw) {
                login_berhasil = true;
                role_aktif = "anggota";
                break;
            } 
            else {
                sisa_percobaan--;
                cout << "Login Gagal! Sisa: " << sisa_percobaan << endl << endl;
            }
        }

        if (!login_berhasil) {
            cout << "\nBukan admin ya? mana bisa." << endl;
            return 0;
        }

        cout << "\n>>> Login Berhasil! Welkamm, " << input_nama << " (" << role_aktif << ")" << endl;

        int pilihan;
        do {
            cout << "\n===============================" << endl;
            cout << "       MENU UTAMA RT 67        " << endl;
            cout << "       Role: " << role_aktif << endl;
            cout << "===============================" << endl;
            cout << "1. Tambah Data Warga" << endl;
            cout << "2. Lihat Daftar Warga" << endl;
            cout << "3. Update Status Warga" << endl;
            cout << "4. Hapus Data Warga" << endl;
            cout << "5. Logout" << endl;
            cout << "6. Keluar Program" << endl;
            cout << "-------------------------------" << endl;
            cout << "Pilih Menu: ";
            cin >> pilihan;
            cin.ignore();

            if (pilihan == 1) {
                if (role_aktif != "admin") {
                    cout << "\n[!] ERROR: Menu ini hanya untuk Admin!" << endl;
                } else {
                    if (jumlah_warga < 100) {
                        cout << "\n>>> Input Data Warga <<<" << endl;
                        cout << "Nama     : "; getline(cin, daftar_warga[jumlah_warga].nama);
                        cout << "NIK      : "; getline(cin, daftar_warga[jumlah_warga].nik);
                        cout << "Jalan    : "; getline(cin, daftar_warga[jumlah_warga].alamat.jalan);
                        cout << "No jalan : "; getline(cin, daftar_warga[jumlah_warga].alamat.nomor_jalan);
                        daftar_warga[jumlah_warga].status = "Aktif";
                        jumlah_warga++;
                        cout << ">>> Data Berhasil Ditambahkan!" << endl;
                    }
                }
            } 
            else if (pilihan == 2) {
                if (jumlah_warga == 0) {
                    cout << "\n[!] Belum ada data warga." << endl;
                } else {
                    cout << "\n" << setfill('=') << setw(80) << "=" << endl;
                    cout << setfill(' ');
                    cout << left << setw(5) << "NO" 
                         << setw(20) << "NAMA" 
                         << setw(15) << "NIK" 
                         << setw(15) << "STATUS" 
                         << "ALAMAT" << endl;
                    cout << setfill('-') << setw(80) << "-" << endl;
                    cout << setfill(' ');

                    for (int i = 0; i < jumlah_warga; i++) {
                        cout << left << setw(5) << i + 1 
                             << setw(20) << daftar_warga[i].nama 
                             << setw(15) << daftar_warga[i].nik 
                             << setw(15) << daftar_warga[i].status 
                             << daftar_warga[i].alamat.jalan << " No." << daftar_warga[i].alamat.nomor_jalan << endl;
                    }
                    cout << setfill('=') << setw(80) << "=" << endl;
                    cout << setfill(' ');
                }
            } 
            else if (pilihan == 3) {
                if (role_aktif != "admin") {
                    cout << "\n[!] ERROR: Menu ini hanya untuk Admin!" << endl;
                } else {
                    int index;
                    cout << "Masukkan Nomor Urut: "; cin >> index; cin.ignore();
                    if (index > 0 && index <= jumlah_warga) {
                        cout << "Status Baru: "; getline(cin, daftar_warga[index-1].status);
                        cout << ">>> Berhasil!" << endl;
                    }
                }
            } 
            else if (pilihan == 4) {
                if (role_aktif != "admin") {
                    cout << "\n[!] ERROR: Menu ini hanya untuk Admin!" << endl;
                } else {
                    int index;
                    cout << "Nomor yang Dihapus: "; cin >> index; cin.ignore();
                    if (index > 0 && index <= jumlah_warga) {
                        for (int i = index - 1; i < jumlah_warga - 1; i++) {
                            daftar_warga[i] = daftar_warga[i+1];
                        }
                        jumlah_warga--;
                        cout << ">>> Terhapus!" << endl;
                    }
                }
            }
            else if (pilihan == 5) {
                cout << "\nLogout berhasil! Balik ke login...\n" << endl;
            }
            else if (pilihan == 6) {
                cout << "\nTerima kasih Babaiii!" << endl;
                program_jalan = false;
            }
            else {
                cout << "\n[!]Dilihat baik baik dong.." << endl;
            }

        } while (pilihan != 5 && pilihan != 6);
    }

    return 0;
}