#include <iostream>
#include <string>

using namespace std;

int main() {
    string user, pw;
    int salah = 0;
    bool masuk = false;

    while (salah < 3) {
        cout << "== LOGIN ==" << endl;
        cout << "User: "; cin >> user;
        cout << "Pw: "; cin >> pw;

        if (user == "Rega" && pw == "085") {
            masuk = true;
            cout << "Login sukses!\n" << endl;
            break;
        } else {
            salah++;
            cout << "Gagal! Sisa percobaan: " << (3 - salah) << "\n" << endl;
        }
    }

    if (!masuk) {
        cout << "Sudah 3x salah. Program selesai." << endl;
        return 0;
    }

    int pilih;
    float n, m, km, cm;

    do {
        cout << "--- MENU KONVERSI ---" << endl;
        cout << "1. Meter ke KM & CM" << endl;
        cout << "2. KM ke Meter & CM" << endl;
        cout << "3. CM ke Meter & KM" << endl;
        cout << "4. Keluar" << endl;
        cout << "Pilih: ";
        cin >> pilih;

        if (pilih == 1) {
            cout << "Input meter: "; cin >> n;
            km = n / 1000;
            cm = n * 100;
            cout << "Hasil: " << km << " km dan " << cm << " cm\n" << endl;
        } 
        else if (pilih == 2) {
            cout << "Input km: "; cin >> n;
            m = n * 1000;
            cm = n * 100000;
            cout << "Hasil: " << m << " m dan " << cm << " cm\n" << endl;
        } 
        else if (pilih == 3) {
            cout << "Input cm: "; cin >> n;
            m = n / 100;
            km = n / 100000;
            cout << "Hasil: " << m << " m dan " << km << " km\n" << endl;
        } 
        else if (pilih == 4) {
            cout << "Babaaii!" << endl;
        } 
        else {
            cout << "Menu tidak ada, coba lagi.\n" << endl;
        }

    } while (pilih != 4);

    return 0;
}