#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <chrono>
#include <thread>
#include <conio.h>

using namespace std;

// Struktur untuk mewakili menu
struct Menu {
    string nama;
    int harga;
    string kategori; // Mengganti deskripsi dengan kategori
};

// Struktur untuk mewakili pesanan
struct Pesanan {
    string namaMenu;
    int jumlah;
};

vector<Menu> daftarMenu; // Vektor untuk menyimpan daftar menu
vector<Pesanan> daftarPesanan; // Vektor untuk menyimpan daftar pesanan

// Fungsi untuk menyimpan data ke file
void simpanDataKeFile() {
    ofstream file("menu_restoran.txt");
    for (const auto& menu : daftarMenu) {
        file << menu.nama << "," << menu.harga << "," << menu.kategori << endl; // Mengganti deskripsi dengan kategori
    }
    file.close();
}

// Fungsi untuk membaca data dari file
void bacaDataDariFile() {
    ifstream file("menu_restoran.txt");
    string line;
    while (getline(file, line)) {
        size_t pos = 0;
        string token;
        string delimiter = ",";
        vector<string> tokens;
        while ((pos = line.find(delimiter)) != string::npos) {
            token = line.substr(0, pos);
            tokens.push_back(token);
            line.erase(0, pos + delimiter.length());
        }
        tokens.push_back(line);
        if (tokens.size() == 3) {
            Menu menu;
            menu.nama = tokens[0];
            menu.harga = stoi(tokens[1]);
            menu.kategori = tokens[2]; // Mengganti deskripsi dengan kategori
            daftarMenu.push_back(menu);
        }
    }
    file.close();
}

// Fungsi untuk menampilkan menu
void tampilkanMenu() {
    system("cls");
    cout << "-----------------------------------------" << endl;
    cout << "                DAFTAR MENU              " << endl;
    cout << "-----------------------------------------" << endl;
    for (size_t i = 0; i < daftarMenu.size(); ++i) {
        cout << i + 1 << ". Nama        : " << daftarMenu[i].nama << endl;
        cout << "   Harga       : Rp. " << daftarMenu[i].harga << endl;
        cout << "   Kategori    : " << daftarMenu[i].kategori << endl; // Mengganti deskripsi dengan kategori
        cout << "-----------------------------------------" << endl;
    }
}

// Fungsi untuk menambahkan menu ke pesanan
void tambahKePesanan() {
    string namaMenu;
    int jumlah;

    system("cls");
    tampilkanMenu();
    cout << "-----------------------------------------" << endl;
    cout << "           TAMBAHKAN KE PESANAN          " << endl;
    cout << "-----------------------------------------" << endl;
    cout << "Masukkan nama menu yang ingin ditambahkan: ";
    cin.ignore();
    getline(cin, namaMenu);
    cout << "Masukkan jumlah menu yang ingin ditambahkan: ";
    cin >> jumlah;

    auto it = find_if(daftarMenu.begin(), daftarMenu.end(), [&](const Menu& menu) {
        return menu.nama == namaMenu;
    });

    if (it != daftarMenu.end()) {
        Pesanan pesanan;
        pesanan.namaMenu = namaMenu;
        pesanan.jumlah = jumlah;
        daftarPesanan.push_back(pesanan);
        simpanDataKeFile();
        cout << "Menu berhasil ditambahkan ke pesanan!" << endl;
    } else {
        cout << "Menu tidak ditemukan." << endl;
    }
}

// Fungsi untuk melihat pesanan
void lihatPesanan() {
    system("cls");
    cout << "-----------------------------------------" << endl;
    cout << "             PESANAN ANDA           " << endl;
    cout << "-----------------------------------------" << endl;
    if (daftarPesanan.empty()) {
        cout << "Pesanan Anda kosong." << endl;
        return;
    }
    for (size_t i = 0; i < daftarPesanan.size(); ++i) {
        cout << i + 1 << ". Nama Menu  : " << daftarPesanan[i].namaMenu << endl;
        cout << "   Jumlah       : " << daftarPesanan[i].jumlah << endl;
        cout << "-----------------------------------------" << endl;
    }
}

// Fungsi untuk menghapus menu dari pesanan
void hapusDariPesanan() {
    string namaMenu;

    system("cls");
    lihatPesanan();
    cout << "-----------------------------------------" << endl;
    cout << "         HAPUS MENU DARI PESANAN     " << endl;
    cout << "-----------------------------------------" << endl;
    cout << "Masukkan nama menu yang ingin dihapus: ";
    cin.ignore();
    getline(cin, namaMenu);

    auto it = find_if(daftarPesanan.begin(), daftarPesanan.end(), [&](const Pesanan& pesanan) {
        return pesanan.namaMenu == namaMenu;
    });

    if (it != daftarPesanan.end()) {
        daftarPesanan.erase(it);
        simpanDataKeFile();
        cout << "Menu berhasil dihapus dari pesanan!" << endl;
    } else {
        cout << "Menu tidak ditemukan di pesanan." << endl;
    }
}

// Fungsi untuk melakukan checkout
void checkout() {
    system("cls");
    cout << "-----------------------------------------" << endl;
    cout << "                CHECKOUT                 " << endl;
    cout << "-----------------------------------------" << endl;
    if (daftarPesanan.empty()) {
        cout << "Pesanan Anda kosong." << endl;
        return;
    }
    int total = 0;
    cout << "Daftar Pesanan Anda:" << endl;
    for (const auto& pesanan : daftarPesanan) {
        auto menuIt = find_if(daftarMenu.begin(), daftarMenu.end(), [&](const Menu& menu) {
            return menu.nama == pesanan.namaMenu;
        });
        if (menuIt != daftarMenu.end()) {
            cout << "Nama Menu  : " << menuIt->nama << endl;
            cout << "Jumlah       : " << pesanan.jumlah << endl;
            cout << "Harga        : Rp " << menuIt->harga << endl;
            cout << "Subtotal     : Rp " << pesanan.jumlah * menuIt->harga << endl;
            cout << "-----------------------------------------" << endl;
            total += pesanan.jumlah * menuIt->harga;
        }
    }
    cout << "\n-----------------------------------------" << endl;
    cout << "Total yang harus dibayar: Rp " << total << endl;
    cout << "Terima kasih telah makan di restoran kami!" << endl;
    daftarPesanan.clear();
}

// Deklarasi fungsi login, registrasi, dan reset
void login();
void regis();
void reset();

int main() {
    int c;
    cout << "-----------------------------------------" << endl;
    cout << "               LOGINNN               " << endl;
    cout << "-----------------------------------------" << endl;
    cout << "\t1. Sign In" << endl;
    cout << "\t2. Sign Up" << endl;
    cout << "\t3. Forgot Password" << endl;
    cout << "\n-----------------------------------------" << endl;
    cout << "Masukan Pilihan: ";
    cin >> c;

    switch (c) {
        case 1:
            login();
            getch();
            break;
        case 2:
            regis();
            break;
        case 3:
            reset();
            break;
        default:
            system("cls");
            cout << "Masukkan pilihan yang benar..." << endl;
            main();
    }

    bacaDataDariFile(); // Membaca data dari file

    int pilihan;
    system("cls");
    do {
        cout << "-----------------------------------------" << endl;
        cout << "              RESTORAN KAMI                " << endl;
        cout << "-----------------------------------------" << endl;
        cout << "1. Lihat Menu" << endl;
        cout << "2. Tambah ke Pesanan" << endl;
        cout << "3. Lihat Pesanan" << endl; 
        cout << "4. Hapus dari Pesanan" << endl;
        cout << "5. Checkout" << endl;
        cout << "6. Keluar" << endl;
        cout << "-----------------------------------------" << endl;
        cout << "Masukkan pilihan: ";
        cin >> pilihan;
        switch (pilihan) {
            case 1:
                tampilkanMenu();
                break;
            case 2:
                tambahKePesanan();
                break;
            case 3:
                lihatPesanan();
                break;
            case 4:
                hapusDariPesanan();
                break;
            case 5:
                checkout();
                break;
            case 6:
            system("cls");
                cout << "Terima kasih telah makan di restoran kami!" << endl;
                return 0;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
        cout << "Tekan enter untuk melanjutkan...";
        _getch();
    } while (pilihan != 6);
    return 0;
}

// Fungsi untuk login
void login() {
    int count = 0;
    string userId, password, id, pass;
    char ch;

    system("cls");
    cout << "-----------------------------------------" << endl;
    cout << "                   Login                 " << endl;
    cout << "-----------------------------------------\n" << endl;
    cout << "Username\t: ";
    cin >> userId;
    cout << "Password\t: ";
    password.clear();
    ch = _getch(); // Menggunakan _getch() agar input password tidak terlihat
    while (ch != '\r') { // Loop sampai tombol Enter ditekan
        password.push_back(ch); // Menambahkan karakter ke password
        cout << '*'; // Menampilkan bintang sebagai input password
        ch = _getch(); // Membaca karakter berikutnya
    }
    cout << endl; // Pindah baris setelah memasukkan password

    ifstream input("records.txt");

    while (input >> id >> pass) {
        if (id == userId && pass == password) {
            count = 1;
            system("cls");
            cout << userId << " Telah berhasil masuk :)" << endl;
            break; // Keluar dari loop jika username dan password cocok
        }
    }
    input.close();

    if (count == 0) {
        cout << "Username atau Password salah. Silakan coba lagi." << endl;
        getch();
        main();
    }
}

// Fungsi untuk registrasi
void regis() {
    string ruserId, rpassword, rid, rpass;

    system("cls");
    cout << "-----------------------------------------" << endl;
    cout << "                 Registrasi              " << endl;
    cout << "-----------------------------------------" << endl;
    cout << "Masukan Username: ";
    cin >> ruserId;
    cout << "Masukan Password: ";
    cin >> rpassword;

    ofstream f1("records.txt", ios::app);
    f1 << ruserId << ' ' << rpassword << endl;
    system("cls");
    cout << "\nRegistrasi Berhasil..." << endl;
    main();
}

// Fungsi untuk reset password
void reset() {
    int option;
    system("cls");
    cout << "-----------------------------------------" << endl;
    cout << "           Lupa Password ?               " << endl;
    cout << "-----------------------------------------\n" << endl;
    cout << "1. Cari Akun Anda dari Username" << endl;
    cout << "2. Kembali ke Main Menu" << endl;
    cout << "Masukan Pilihan: ";
    cin >> option;

    switch (option) {
        case 1: {
            int count = 0;
            string suserId, sId, spass;
            cout << "\nMasukan Username yang diingat: ";
            cin >> suserId;

            ifstream f2("records.txt");
            while (f2 >> sId >> spass) {
                if (sId == suserId) {
                    count = 1;
                }
            }
            f2.close();

            if (count == 1) {
                cout << "\n\nAkun ditemukan...\n";
                cout << "\nPassword anda adalah: " << spass << endl;
                _getch();
                main();
            } else {
                cout << "\n\nMaaf, akun tidak ditemukan...\n";
                reset();
            }
            break;
        }
        case 2:
            main();
            break;
        default:
            cout << "\nMasukkan pilihan yang benar - coba lagi" << endl;
            reset();
    }
}