#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream> // Tambahkan untuk penggunaan file
#include <sstream> // Tambahkan untuk penggunaan stringstream
#include <conio.h> // Tambahkan untuk penggunaan _getch()

using namespace std;

struct Produk {
    string nama;
    int harga;
    int stok;
    string deskripsi;
};

string username, password;
char ch;

vector<Produk> inventaris;

void simpanDataKeFile() {
    ofstream file("inventaris.txt");
    for (const auto& produk : inventaris) {
        file << produk.nama << "," << produk.harga << "," << produk.stok << "," << produk.deskripsi << endl;
    }
    file.close();
}

void bacaDataDariFile() {
    ifstream file("inventaris.txt");
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
        if (tokens.size() == 4) {
            Produk produk;
            produk.nama = tokens[0];
            produk.harga = stoi(tokens[1]);
            produk.stok = stoi(tokens[2]);
            produk.deskripsi = tokens[3];
            inventaris.push_back(produk);
        }
    }
    file.close();
    cout << "Data berhasil dibaca dari file." << endl;
}

void tambahProduk() {
    Produk produkBaru;
    char pilihan;
    
    do {
        system("cls");
        cout << "-----------------------------------------" << endl;
        cout << "              TAMBAH PRODUK              " << endl;
        cout << "-----------------------------------------" << endl;
        cout << "Masukkan nama produk       : ";
        cin.ignore(); // Tambahkan untuk mengabaikan enter sebelumnya
        getline(cin, produkBaru.nama); // Menggunakan getline untuk menerima input dengan spasi
        cout << "Masukkan harga produk      : ";
        cin >> produkBaru.harga;
        cout << "Masukkan stok produk       : ";
        cin >> produkBaru.stok;
        cout << "Masukkan deskripsi produk  : ";
        cin.ignore(); // Tambahkan untuk mengabaikan enter sebelumnya
        getline(cin, produkBaru.deskripsi); // Menggunakan getline untuk menerima input dengan spasi
        inventaris.push_back(produkBaru);
        simpanDataKeFile(); // Simpan data ke file setelah ditambahkan
        cout << "-----------------------------------------" << endl;
        cout << "Produk berhasil ditambahkan!" << endl;
        cout << "-----------------------------------------" << endl;
        cout << "Apakah Anda ingin menambahkan produk lagi? (y/t): ";
        cin >> pilihan;
    } while (pilihan == 'y' || pilihan == 'Y');
}

void bacaProduk() {
    system("cls");
    cout << "-----------------------------------------" << endl;
    cout << "              LIHAT PRODUK              " << endl;
    cout << "-----------------------------------------" << endl;
    if (inventaris.empty()) {
        cout << "Tidak ada produk dalam inventaris." << endl;
        return;
    }
    int pilihan;
    do {
        cout << "Pilihan tampilan produk:" << endl;
        cout << "1. Berdasarkan abjad nama barang" << endl;
        cout << "2. Berdasarkan harga paling mahal" << endl;
        cout << "3. Berdasarkan harga paling murah" << endl;
        cout << "Masukkan pilihan: ";
        cin >> pilihan;
        switch (pilihan) {
            case 1:
                cout << "-----------------------------------------" << endl;
                cout << "                  ABJAD              " << endl;
                cout << "-----------------------------------------" << endl;
                sort(inventaris.begin(), inventaris.end(), [](const Produk& a, const Produk& b) {
                    return a.nama < b.nama;
                });
                break;
            case 2:
                cout << "-----------------------------------------" << endl;
                cout << "               PALING MAHAL              " << endl;
                cout << "-----------------------------------------" << endl;
                sort(inventaris.begin(), inventaris.end(), [](const Produk& a, const Produk& b) {
                    return a.harga > b.harga;
                });
                break;
            case 3:
                cout << "-----------------------------------------" << endl;
                cout << "               PALING MURAH           " << endl;
                cout << "-----------------------------------------" << endl;
                sort(inventaris.begin(), inventaris.end(), [](const Produk& a, const Produk& b) {
                    return a.harga < b.harga;
                });
                break;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
        cout << "Daftar Produk:" << endl;
        for (size_t i = 0; i < inventaris.size(); ++i) {
            cout << "-----------------------------------------\n" << endl;
            cout << i + 1 << ". Nama        : " << inventaris[i].nama << endl;
            cout << "   Harga       : " << inventaris[i].harga << endl;
            cout << "   Stok        : " << inventaris[i].stok << endl;
            cout << "   Dekripsi    : " << inventaris[i].deskripsi << endl;
        }
        cout << "Apakah Anda ingin melihat produk lagi? (y/t): ";
        cin >> pilihan;
    } while (pilihan == 'y' || pilihan == 'Y');
}

void perbaruiProduk() {
    string namaProduk;

    system("cls");
    cout << "-----------------------------------------" << endl;
    cout << "              UPDATE PRODUK           " << endl;
    cout << "-----------------------------------------" << endl;
            cout << "Masukkan nama produk       : ";
    cin.ignore(); // Tambahkan untuk mengabaikan enter sebelumnya
    getline(cin, namaProduk); // Menggunakan getline untuk menerima input dengan spasi
    for (auto& produk : inventaris) {
        if (produk.nama == namaProduk) {
            cout << "Masukkan harga baru        : ";
            cin >> produk.harga;
            cout << "Masukkan stok baru         : ";
            cin >> produk.stok;
            cout << "Masukkan deskripsi baru    : ";
            cin.ignore(); // Tambahkan untuk mengabaikan enter sebelumnya
            getline(cin, produk.deskripsi); // Menggunakan getline untuk menerima input dengan spasi
            simpanDataKeFile(); // Simpan data ke file setelah diperbarui
            cout << "-----------------------------------------" << endl;
            cout << "Produk berhasil diperbarui!" << endl;
            return;
        }
    }
    cout << "-----------------------------------------" << endl;
    cout << "Produk tidak ditemukan." << endl;
}

void hapusProduk() {
    string namaProduk;

    system("cls");
    cout << "-----------------------------------------" << endl;
    cout << "              HAPUS PRODUK           " << endl;
    cout << "-----------------------------------------" << endl;
    cout << "Masukkan nama produk: ";
    cin.ignore(); // Tambahkan untuk mengabaikan enter sebelumnya
    getline(cin, namaProduk); // Menggunakan getline untuk menerima input dengan spasi
    auto it = find_if(inventaris.begin(), inventaris.end(), [&](const Produk& produk) {
        return produk.nama == namaProduk;
    });

    cout << "-----------------------------------------" << endl;
    if (it != inventaris.end()) {
        inventaris.erase(it);
        simpanDataKeFile(); // Simpan data ke file setelah dihapus
        cout << "Produk berhasil dihapus!" << endl;
    } else {
        cout << "Produk tidak ditemukan." << endl;
    }
}

void login() {
    system("cls");
    cout << "==============================================" << endl;
    cout << "           L O G I N  A P L I K A S I        " << endl;
    cout << "==============================================" << endl;
    cout << "Masukan Username dan Password untuk login....." << endl;
    cout << "==============================================" << endl;
    cout << "Masukan Username: ";
    cin >> username;
    cout << "Masukan Password: ";
    ch = _getch(); // Menggunakan _getch() agar input password tidak terlihat
    while (ch != '\r') { // Loop sampai tombol Enter ditekan
        password.push_back(ch); // Menambahkan karakter ke password
        cout << '*'; // Menampilkan bintang sebagai input password
        ch = _getch(); // Membaca karakter berikutnya
    }
    cout << endl; // Pindah baris setelah memasukkan password

    // Proses autentikasi (anda bisa menambahkan logika autentikasi di sini)
    if (username == "admin" && password == "ulan") {
        cout << "Berhasil login" << endl;
    } else {
        cout << "\nUsername atau password salah" << endl;
    } while (username!="admin"|| password!="ulan");
}

int main() {
    int pilihan;
    char chose;

    login();

    system("cls");
    cout << "-----------------------------------------" << endl;
    cout << "                  M E N U                " << endl;
    cout << "-----------------------------------------" << endl;
    cout << "1. Tambah Produk" << endl;
    cout << "2. Lihat Produk" << endl;
    cout << "3. Perbarui Produk" << endl;
    cout << "4. Hapus Produk" << endl;
    cout << "5. Keluar" << endl;
    cout << "-----------------------------------------" << endl;
    cout << "Masukkan pilihan: ";
    cin >> pilihan;
    switch (pilihan) {
        case 1:
            tambahProduk();
            break;
        case 2:
            bacaProduk();
            break;
        case 3:
            perbaruiProduk();
            break;
        case 4:
            hapusProduk();
            break;
        case 5:
            cout << "==============================================" << endl;
            cout << "==============================================" << endl;
            cout << "                   M E N U             " << endl;
            cout << "                                               " << endl;
            cout << "       Anda Telah Keluar Dari Aplikasi" << endl;
            return 0; // Keluar dari program
        default:
            cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
    }
    return 0;
}   