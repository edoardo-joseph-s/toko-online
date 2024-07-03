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

struct KeranjangItem {
    string namaProduk;
    int jumlah;
};

vector<Produk> inventaris;
vector<KeranjangItem> keranjang;

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
}

void tampilkanProduk() {
    cout << "-----------------------------------------" << endl;
    cout << "                DAFTAR PRODUK            " << endl;
    cout << "-----------------------------------------" << endl;
    for (size_t i = 0; i < inventaris.size(); ++i) {
        cout << i + 1 << ". Nama        : " << inventaris[i].nama << endl;
        cout << "   Harga       : " << inventaris[i].harga << endl;
        cout << "   Stok        : " << inventaris[i].stok << endl;
        cout << "   Deskripsi   : " << inventaris[i].deskripsi << endl;
        cout << "-----------------------------------------" << endl;
    }
}

void tambahKeKeranjang() {
    string namaProduk;
    int jumlah;
    
    system("cls");
    tampilkanProduk();
    cout << "-----------------------------------------" << endl;
    cout << "           TAMBAHKAN KE KERANJANG        " << endl;
    cout << "-----------------------------------------" << endl;
    cout << "Masukkan nama produk yang ingin ditambahkan: ";
    cin.ignore(); // Tambahkan untuk mengabaikan enter sebelumnya
    getline(cin, namaProduk); // Menggunakan getline untuk menerima input dengan spasi
    cout << "Masukkan jumlah produk yang ingin ditambahkan: ";
    cin >> jumlah;

    auto it = find_if(inventaris.begin(), inventaris.end(), [&](const Produk& produk) {
        return produk.nama == namaProduk;
    });

    if (it != inventaris.end() && it->stok >= jumlah) {
        KeranjangItem item;
        item.namaProduk = namaProduk;
        item.jumlah = jumlah;
        keranjang.push_back(item);
        it->stok -= jumlah;
        simpanDataKeFile(); // Simpan data ke file setelah stok diperbarui
        cout << "Produk berhasil ditambahkan ke keranjang!" << endl;
    } else {
        cout << "Produk tidak ditemukan atau stok tidak mencukupi." << endl;
    }
}

void lihatKeranjang() {
    system("cls");
    cout << "-----------------------------------------" << endl;
    cout << "                KERANJANG ANDA           " << endl;
    cout << "-----------------------------------------" << endl;
    if (keranjang.empty()) {
        cout << "Keranjang Anda kosong." << endl;
        return;
    }
    for (size_t i = 0; i < keranjang.size(); ++i) {
        cout << i + 1 << ". Nama Produk  : " << keranjang[i].namaProduk << endl;
        cout << "   Jumlah      : " << keranjang[i].jumlah << endl;
        cout << "-----------------------------------------" << endl;
    }
}

void hapusDariKeranjang() {
    string namaProduk;
    
    system("cls");
    lihatKeranjang();
    cout << "-----------------------------------------" << endl;
    cout << "         HAPUS PRODUK DARI KERANJANG     " << endl;
    cout << "-----------------------------------------" << endl;
    cout << "Masukkan nama produk yang ingin dihapus: ";
    cin.ignore(); // Tambahkan untuk mengabaikan enter sebelumnya
    getline(cin, namaProduk); // Menggunakan getline untuk menerima input dengan spasi

    auto it = find_if(keranjang.begin(), keranjang.end(), [&](const KeranjangItem& item) {
        return item.namaProduk == namaProduk;
    });

    if (it != keranjang.end()) {
        // Kembalikan stok produk ke inventaris
        auto produkIt = find_if(inventaris.begin(), inventaris.end(), [&](const Produk& produk) {
            return produk.nama == it->namaProduk;
        });
        if (produkIt != inventaris.end()) {
            produkIt->stok += it->jumlah;
        }
        keranjang.erase(it);
        simpanDataKeFile(); // Simpan data ke file setelah stok diperbarui
        cout << "Produk berhasil dihapus dari keranjang!" << endl;
    } else {
        cout << "Produk tidak ditemukan di keranjang." << endl;
    }
}

void checkout() {
    system("cls");
    cout << "-----------------------------------------" << endl;
    cout << "                CHECKOUT                 " << endl;
    cout << "-----------------------------------------" << endl;
    if (keranjang.empty()) {
        cout << "Keranjang Anda kosong." << endl;
        return;
    }
    int total = 0;
    for (const auto& item : keranjang) {
        auto produkIt = find_if(inventaris.begin(), inventaris.end(), [&](const Produk& produk) {
            return produk.nama == item.namaProduk;
        });
        if (produkIt != inventaris.end()) {
            total += item.jumlah * produkIt->harga;
        }
    }
    cout << "Total yang harus dibayar: Rp " << total << endl;
    cout << "Terima kasih telah berbelanja!" << endl;
    keranjang.clear(); // Kosongkan keranjang setelah checkout
}

int main() {
    int pilihan;
    bacaDataDariFile();

    do {
        system("cls");
        cout << "-----------------------------------------" << endl;
        cout << "              TOKO ONLINE                " << endl;
        cout << "-----------------------------------------" << endl;
        cout << "1. Lihat Produk" << endl;
        cout << "2. Tambah ke Keranjang" << endl;
        cout << "3. Lihat Keranjang" << endl;
        cout << "4. Hapus dari Keranjang" << endl;
        cout << "5. Checkout" << endl;
        cout << "6. Keluar" << endl;
        cout << "-----------------------------------------" << endl;
        cout << "Masukkan pilihan: ";
        cin >> pilihan;
        switch (pilihan) {
            case 1:
                tampilkanProduk();
                break;
            case 2:
                tambahKeKeranjang();
                break;
            case 3:
                lihatKeranjang();
                break;
            case 4:
                hapusDariKeranjang();
                break;
            case 5:
                checkout();
                break;
            case 6:
                cout << "Terima kasih telah menggunakan aplikasi toko online!" << endl;
                return 0;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
        cout << "Tekan tombol apa saja untuk melanjutkan...";
        _getch(); // Menunggu pengguna menekan tombol apa saja
    } while (pilihan != 6);
    return 0;
}
