#include <iostream>
#include <string>

using namespace std;

int main() {
    string user, pw;
    int salah = 0;
    bool masuk = false;

    while (salah < 3) {
        cout << "========== LOGIN ==========" << endl;
        cout << "User: "; cin >> user;
        cout << "Pw: "; cin >> pw;

        if (user == "Rega" && pw == "085") {
            masuk = true;
            cout << "Login berhasil!\n" << endl;
            break;
        } else {
            salah++;
            cout << "user atau pw salah! Sisa percobaan: " << (3 - salah) << "\n" << endl;
        }
    }

    if (!masuk) {
        cout << "Sudah 3x salah. Program selesai." << endl;
        return 0;
    }

    int pilih;
    double n, m, km, cm;

    do {
        cout << "\n====================================\n";
        cout << "       MENU KONVERSI PANJANG          \n";
        cout << "====================================\n";
        cout << "1. M ke KM & CM\n";
        cout << "2. KM ke M & CM\n";
        cout << "3. CM ke M & KM\n";
        cout << "4. Keluar\n";
        cout << "\n======================\n";
        cout << "Pilih menu (1-4) : ";
        cin >> pilih;

        if (pilih == 1) {
            cout << "Masukkan panjang (M) : "; 
            cin >> n;
            km = n / 1000;
            cm = n * 100;
            cout << "\n>>> HASIL PERHITUNGAN <<<\n";
            cout << "Ke Kilometer : " << km << " KM\n";
            cout << "Ke Centimeter: " << cm << " CM\n";
        } 
        else if (pilih == 2) {
            cout << "Masukkan panjang (KM) : "; 
            cin >> n;
            m = n * 1000;
            cm = n * 100000;
            cout << "\n>>> HASIL PERHITUNGAN <<<\n";
            cout << "Ke Meter     : " << m << " M\n";
            cout << "Ke Centimeter: " << cm << " CM\n";
        } 
        else if (pilih == 3) {
            cout << "Masukkan panjang (CM) : "; 
            cin >> n;
            m = n / 100;
            km = n / 100000;
            cout << "\n>>> HASIL PERHITUNGAN <<<\n";
            cout << "Ke Meter     : " << m << " M\n";
            cout << "Ke Kilometer : " << km << " KM\n";
        } 
        else if (pilih == 4) {
            cout << "Babaiii.\n";
        } 
        else {
            cout << "Menu tidak ada.\n";
        }

    } while (pilih != 4);

    return 0;
}