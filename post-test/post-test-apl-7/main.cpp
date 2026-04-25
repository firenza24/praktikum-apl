#include "warga.h"
#include <limits>

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

int main() {
    string admin_user = "Rega", admin_pw = "085";
    string member_user = "Warga", member_pw = "999";
    Warga daftar_warga[10]; 
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

        bool login_aktif = true;
        while (login_aktif) {
            tampilkanMenu(role_aktif);
            int pilihan;

            try {
                if (!(cin >> pilihan)) {
                    throw "Input menu harus berupa angka!";
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                if (pilihan == 1 && role_aktif == "admin") {
                    if (jumlah_warga >= 10) throw "Kapasitas penuh!";
                    Warga &baru = daftar_warga[jumlah_warga];
                    cout << KUNING << "\n>>> Input Data Warga <<<" << RESET << endl;
                    cout << "Nama     : "; getline(cin, baru.nama);
                    if (baru.nama.empty() || !isHanyaHuruf(baru.nama)) throw "Nama tidak valid!";
                    cout << "NIK      : "; getline(cin, baru.nik);
                    if (baru.nik.empty() || !isHanyaAngka(baru.nik)) throw "NIK tidak valid!";
                    cout << "Jalan    : "; getline(cin, baru.alamat.jalan);
                    cout << "No jalan : "; getline(cin, baru.alamat.nomor_jalan);
                    baru.status = "Aktif";
                    jumlah_warga++;
                    cout << HIJAU << ">>> Berhasil ditambah!" << RESET << endl;

                } else if ((pilihan == 2 && role_aktif == "admin") || (pilihan == 1 && role_aktif == "anggota")) {
                    if (jumlah_warga == 0) throw "Belum ada warganya.";
                    if (role_aktif == "admin") {
                        cout << "\nUrutkan Berdasarkan:\n1. Nama (Asc)\n2. NIK (Desc)\n3. Nama (Desc)\n4. Tanpa Pengurutan\nPilih: ";
                        int s; cin >> s; cin.ignore();
                        if (s == 1) bubbleSortNama(daftar_warga, jumlah_warga);
                        else if (s == 2) selectionSortNIK(daftar_warga, jumlah_warga);
                        else if (s == 3) insertionSortNamaDesc(daftar_warga, jumlah_warga);
                    }
                    cout << "\nTotal Data: " << KUNING << hitungTotalWarga(jumlah_warga) << RESET << endl;
                    cout << ABU << setfill('=') << setw(80) << "=" << RESET << endl;
                    cout << setfill(' ');
                    cout << CYAN << left << setw(5) << "NO" << setw(20) << "NAMA" << setw(15) << "NIK" << setw(15) << "STATUS" << "ALAMAT" << RESET << endl;
                    cout << ABU << setfill('-') << setw(80) << "-" << RESET << endl;
                    cout << setfill(' ');
                    for (int i = 0; i < jumlah_warga; i++) {
                        string warnaStatus = (daftar_warga[i].status == "Aktif") ? HIJAU : MERAH;
                        cout << left << setw(5) << i + 1 << setw(20) << daftar_warga[i].nama << setw(15) << daftar_warga[i].nik 
                             << warnaStatus << setw(15) << daftar_warga[i].status << RESET 
                             << daftar_warga[i].alamat.jalan << " No." << daftar_warga[i].alamat.nomor_jalan << endl;
                    }
                    cout << ABU << setfill('=') << setw(80) << "=" << RESET << endl;
                    cout << setfill(' ');

                } else if (pilihan == 3 && role_aktif == "admin") {
                    if (jumlah_warga == 0) throw "Data kosong!";
                    int idx; cout << "Masukkan Nomor Urut: "; cin >> idx; cin.ignore();
                    if (idx < 1 || idx > jumlah_warga) throw "Nomor tidak valid!";
                    Warga &p = daftar_warga[idx-1];
                    cout << KUNING << "\n>>> Edit Data: " << p.nama << " <<<" << RESET << endl;
                    cout << "1. Nama\n2. NIK\n3. Status\n4. Alamat\nPilih: ";
                    int sub; cin >> sub; cin.ignore();
                    if (sub == 1) { cout << "Nama Baru: "; getline(cin, p.nama); if(!isHanyaHuruf(p.nama)) throw "Nama harus huruf!"; }
                    else if (sub == 2) { cout << "NIK Baru: "; getline(cin, p.nik); if(!isHanyaAngka(p.nik)) throw "NIK harus angka!"; }
                    else if (sub == 3) { cout << "Status Baru: "; getline(cin, p.status); }
                    else if (sub == 4) { cout << "Jalan Baru: "; getline(cin, p.alamat.jalan); cout << "No Baru: "; getline(cin, p.alamat.nomor_jalan); }
                    else throw "Pilihan tidak ada!";
                    cout << HIJAU << ">>> Berhasil melakukan Update Data!" << RESET << endl;

                } else if (pilihan == 4 && role_aktif == "admin") {
                    if (jumlah_warga == 0) throw "Data kosong!";
                    int idx; cout << "Nomor yang dihapus: "; cin >> idx; cin.ignore();
                    if (idx < 1 || idx > jumlah_warga) throw "Nomor tidak valid!";
                    for (int i = idx - 1; i < jumlah_warga - 1; i++) daftar_warga[i] = daftar_warga[i+1];
                    jumlah_warga--;
                    cout << HIJAU << ">>> Berhasil dihapus!" << RESET << endl;

                } else if (pilihan == 5) {
                    if (jumlah_warga == 0) throw "Data masih kosong!";
                    string t_nik; cout << "Masukkan NIK yang dicari: "; getline(cin, t_nik);
                    if (!isHanyaAngka(t_nik)) throw "NIK harus angka!";
                    urutkanNIKCepat(daftar_warga, jumlah_warga);
                    int hasil = cariNikBinary(daftar_warga, 0, jumlah_warga - 1, t_nik);
                    if (hasil != -1) {
                        cout << HIJAU << "\nData Ditemukan!" << RESET << endl;
                        cout << "Nama: " << daftar_warga[hasil].nama << " | NIK: " << daftar_warga[hasil].nik << endl;
                    } else throw "NIK tidak ditemukan!";

                } else if (pilihan == 6) {
                    cout << HIJAU << "\nLogout berhasil!" << RESET << endl;
                    login_aktif = false;

                } else if (pilihan == 7) {
                    login_aktif = false; program_jalan = false;

                } else throw "Pilihan tidak tersedia atau akses ditolak!";

            } catch (const char* e) {
                cout << MERAH << "\n[!] ERROR: " << e << RESET << endl;
                cin.clear();
            }
        }
    }
    return 0;
}