#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

struct Karyawan {
    string nama;
    string gender;
    string jabatan;
    double gaji;
};

// =================== FUNCTION TAMBAHAN ===================
void garis() {
    cout << "=====================================\n";
}

void header(string judul) {
    garis();
    cout << "        " << judul << "\n";
    garis();
}

void tunggu() {
    cout << "\nTekan ENTER untuk lanjut...";
    cin.ignore();
    cin.get();
}

// =================== LOGIN ===================
bool login() {
    string user, pass;

    header("GENDERINSIGHT SYSTEM");
    cout << "Username : ";
    cin >> user;
    cout << "Password : ";
    cin >> pass;

    if (user == "Kelompok8" && pass == "123") {
        cout << "\nLogin berhasil!\n\n";
        return true;
    }
    else {
        cout << "\nUsername atau password salah.\n\n";
        return false;
    }
}

// =================== INPUT DATA (DIPISAH JADI FUNCTION) ===================
void inputKaryawan(Karyawan data[], int &jmlL, int &jmlP,
                    double &totalGajiL, double &totalGajiP,
                    int &manL, int &manP, int &staffL, int &staffP, int &internL, int &internP)
{
    int n;
    cout << "Masukkan jumlah karyawan: ";
    cin >> n;

    cin.ignore();
    for (int i = 0; i < n; i++) {
        cout << "\nKaryawan ke-" << i + 1 << ":\n";
        cout << "Nama     : ";
        getline(cin, data[i].nama);

        cout << "Gender (L/P): ";
        cin >> data[i].gender;

        cout << "Jabatan  : ";
        cin.ignore();
        getline(cin, data[i].jabatan);

        cout << "Gaji (Rp): ";
        cin >> data[i].gaji;
        cin.ignore();

        // hitung statistik
        if (data[i].gender == "L" || data[i].gender == "l") {
            jmlL++;
            totalGajiL += data[i].gaji;
            if (data[i].jabatan == "Manager" || data[i].jabatan == "manager") manL++;
            else if (data[i].jabatan == "Staff" || data[i].jabatan == "staff") staffL++;
            else internL++;
        }
        else if (data[i].gender == "P" || data[i].gender == "p") {
            jmlP++;
            totalGajiP += data[i].gaji;
            if (data[i].jabatan == "Manager" || data[i].jabatan == "manager") manP++;
            else if (data[i].jabatan == "Staff" || data[i].jabatan == "staff") staffP++;
            else internP++;
        }
    }
}

// =================== ANALISIS ===================
void analisisData() {
    Karyawan data[100];

    int jmlL = 0, jmlP = 0;
    double totalGajiL = 0, totalGajiP = 0;
    int manL = 0, manP = 0, staffL = 0, staffP = 0, internL = 0, internP = 0;

    inputKaryawan(data, jmlL, jmlP, totalGajiL, totalGajiP,
                    manL, manP, staffL, staffP, internL, internP);

    header("HASIL ANALISIS");
    cout << fixed << setprecision(2);

    double rataL = (jmlL > 0) ? totalGajiL / jmlL : 0;
    double rataP = (jmlP > 0) ? totalGajiP / jmlP : 0;

    cout << "\n-- Statistik Gaji --\n";
    cout << "Rata-rata gaji Laki-laki : Rp " << rataL << endl;
    cout << "Rata-rata gaji Perempuan : Rp " << rataP << endl;

    cout<< "\n-- Distribusi Jabatan --\n";
    cout<< setw(10) << left << "Jabatan"
        << setw(12) << "Laki-laki"
        << setw(12) << "Perempuan" << endl;
    cout<< setw(10) << "Manager" << setw(12) << manL << setw(12) << manP << endl;
    cout<< setw(10) << "Staff"   << setw(12) << staffL << setw(12) << staffP << endl;
    cout<< setw(10) << "Intern"  << setw(12) << internL << setw(12) << internP << endl;

    cout << "\n-- Kesimpulan Analisis --\n";
    bool kesenjangan = false;

    if (rataL > rataP + 500000) {
        cout << "[PERINGATAN] Indikasi kesenjangan upah: Laki-laki lebih tinggi.\n";
        kesenjangan = true;
    }
    else if (rataP > rataL + 500000) {
        cout << "[PERINGATAN] Indikasi kesenjangan upah: Perempuan lebih tinggi.\n";
        kesenjangan = true;
    }
    else {
        cout << "[STABIL] Tidak ada kesenjangan signifikan dalam gaji.\n";
    }

    int totalMan = manL + manP;
    if (totalMan > 0) {
        double proporsiPManager = (double)manP / totalMan * 100;
        if (proporsiPManager >= 40 && proporsiPManager <= 60)
            cout << "[STABIL] Jabatan manager cukup seimbang.\n";
        else if (proporsiPManager < 40) {
            cout << "[PERINGATAN] Jabatan manager didominasi laki-laki.\n";
            kesenjangan = true;
        }
        else {
            cout << "[PERINGATAN] Jabatan manager didominasi perempuan.\n";
            kesenjangan = true;
        }
    }

    cout << "\n=== REKOMENDASI PROGRAM ===\n";
    if (kesenjangan) {
        if (rataL > rataP + 500000)
            cout << "- Review struktur gaji agar lebih adil.\n";
        if (rataP > rataL + 500000)
            cout << "- Evaluasi kinerja harus objektif.\n";
        if (manL > manP)
            cout << "- Tingkatkan peluang promosi untuk perempuan.\n";
        if (manP > manL)
            cout << "- Lakukan pemerataan promosi.\n";
    }
    else {
        cout << "[SEIMBANG] Lingkungan kerja sudah cukup adil.\n";
    }

    cout << "\n=== Analisis & Solusi selesai ===\n";
    tunggu();
}

// =================== MENU ===================
void menu() {
    int pilihan;

    do {
        header("MENU");
        cout << "1. Input & Analisis Data\n";
        cout << "2. Keluar\n";
        cout << "Pilih: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                analisisData();
                break;

            case 2:
                cout << "\nTerima kasih telah menggunakan program!\n";
                break;

            default:
                cout << "\nPilihan tidak valid!\n";
        }

    } while (pilihan != 2);
}

// =================== MAIN ===================
int main() {
    bool berhasil = false;

    while (!berhasil) {
        berhasil = login();
    }

    menu();
    return 0;
}
