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
    cout << "Data berhasil disimpan ke file." << endl;
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
    cout << "Produk berhasil ditambahkan!" << endl;
}

void bacaProduk() {
    system("cls");
    cout << "-----------------------------------------" << endl;
    cout << "              TAMBAH PRODUK              " << endl;
    cout << "-----------------------------------------" << endl;
    if (inventaris.empty()) {
        cout << "Tidak ada produk dalam inventaris." << endl;
        return;
    }
    int pilihan;
    cout << "Pilihan tampilan produk:" << endl;
    cout << "1. Berdasarkan abjad nama barang" << endl;
    cout << "2. Berdasarkan harga paling mahal" << endl;
    cout << "3. Berdasarkan harga paling murah" << endl;
    cout << "Masukkan pilihan: ";
    cin >> pilihan;
    switch (pilihan) {
        case 1:
            sort(inventaris.begin(), inventaris.end(), [](const Produk& a, const Produk& b) {
                return a.nama < b.nama;
            });
            break;
        case 2:
            sort(inventaris.begin(), inventaris.end(), [](const Produk& a, const Produk& b) {
                return a.harga > b.harga;
            });
            break;
        case 3:
            sort(inventaris.begin(), inventaris.end(), [](const Produk& a, const Produk& b) {
                return a.harga < b.harga;
            });
            break;
        default:
            cout << "Pilihan tidak valid. Menampilkan produk berdasarkan abjad nama barang." << endl;
            sort(inventaris.begin(), inventaris.end(), [](const Produk& a, const Produk& b) {
                return a.nama < b.nama;
            });
    }
    cout << "Daftar Produk:" << endl;
    for (const auto& produk : inventaris) {
        cout << "Nama: " << produk.nama << ", Harga: " << produk.harga << ", Stok: " << produk.stok << ", Deskripsi: " << produk.deskripsi << endl;
    }
}

void perbaruiProduk() {
    string namaProduk;
    cout << "Masukkan nama produk yang ingin diperbarui: ";
    cin.ignore(); // Tambahkan untuk mengabaikan enter sebelumnya
    getline(cin, namaProduk); // Menggunakan getline untuk menerima input dengan spasi
    for (auto& produk : inventaris) {
        if (produk.nama == namaProduk) {
            cout << "Masukkan harga baru: ";
            cin >> produk.harga;
            cout << "Masukkan stok baru: ";
            cin >> produk.stok;
            cout << "Masukkan deskripsi baru: ";
            cin.ignore(); // Tambahkan untuk mengabaikan enter sebelumnya
            getline(cin, produk.deskripsi); // Menggunakan getline untuk menerima input dengan spasi
            simpanDataKeFile(); // Simpan data ke file setelah diperbarui
            cout << "Produk berhasil diperbarui!" << endl;
            return;
        }
    }
    cout << "Produk tidak ditemukan." << endl;
}

void hapusProduk() {
    string namaProduk;
    cout << "Masukkan nama produk yang ingin dihapus: ";
    cin.ignore(); // Tambahkan untuk mengabaikan enter sebelumnya
    getline(cin, namaProduk); // Menggunakan getline untuk menerima input dengan spasi
    auto it = find_if(inventaris.begin(), inventaris.end(), [&](const Produk& produk) {
        return produk.nama == namaProduk;
    });
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
            cout << "Keluar dari program" << endl;
        default:
            cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
    }
    return 0;
}