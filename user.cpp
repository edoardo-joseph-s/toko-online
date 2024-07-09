#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <conio.h>

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
    system("cls");
    cout << "-----------------------------------------" << endl;
    cout << "                DAFTAR PRODUK            " << endl;
    cout << "-----------------------------------------" << endl;
    for (size_t i = 0; i < inventaris.size(); ++i) {
        cout << i + 1 << ". Nama        : " << inventaris[i].nama << endl;
        cout << "   Harga       : " << inventaris[i].harga << endl;
        cout << "   Stok        : " << inventaris[i].stok << ".000" << endl;
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
    cin.ignore();
    getline(cin, namaProduk);
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
        simpanDataKeFile();
        cout << "Produk berhasil ditambahkan ke keranjang!" << endl;
    } else {
        cout << "Produk tidak ditemukan atau stok tidak mencukupi." << endl;
    }
}

void lihatKeranjang() {
    system("cls");
    cout << "-----------------------------------------" << endl;
    cout << "             KERANJANG ANDA           " << endl;
    cout << "-----------------------------------------" << endl;
    if (keranjang.empty()) {
        cout << "Keranjang Anda kosong." << endl;
        return;
    }
    for (size_t i = 0; i < keranjang.size(); ++i) {
        cout << i + 1 << ". Nama Produk  : " << keranjang[i].namaProduk << endl;
        cout << "   Jumlah       : " << keranjang[i].jumlah << endl;
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
    cin.ignore();
    getline(cin, namaProduk);

    auto it = find_if(keranjang.begin(), keranjang.end(), [&](const KeranjangItem& item) {
        return item.namaProduk == namaProduk;
    });

    if (it != keranjang.end()) {
        auto produkIt = find_if(inventaris.begin(), inventaris.end(), [&](const Produk& produk) {
            return produk.nama == it->namaProduk;
        });
        if (produkIt != inventaris.end()) {
            produkIt->stok += it->jumlah;
        }
        keranjang.erase(it);
        simpanDataKeFile();
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
    cout << "Daftar Belanja Anda:" << endl;
    for (const auto& item : keranjang) {
        auto produkIt = find_if(inventaris.begin(), inventaris.end(), [&](const Produk& produk) {
            return produk.nama == item.namaProduk;
        });
        if (produkIt != inventaris.end()) {
            cout << "Nama Produk  : " << produkIt->nama << endl;
            cout << "Jumlah       : " << item.jumlah << endl;
            cout << "Harga        : Rp " << produkIt->harga << endl;
            cout << "Subtotal     : Rp " << item.jumlah * produkIt->harga << endl;
            cout << "-----------------------------------------" << endl;
            total += item.jumlah * produkIt->harga;
        }
    }
    cout << "\n-----------------------------------------" << endl;
    cout << "Total yang harus dibayar: Rp " << total << endl;
    cout << "Terima kasih telah berbelanja!" << endl;
    keranjang.clear();
}

void login();
void regis();
void reset();

int main() {
    int c;
    cout << "-----------------------------------------" << endl;
    cout << "             Masuk dulu skuyyy               " << endl;
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

    bacaDataDariFile();

    int pilihan;
    system("cls");
    do {
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
            system("cls");
                cout << "Terima kasih telah menggunakan aplikasi toko online!" << endl;
                return 0;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
        cout << "Tekan enter untuk melanjutkan...";
        _getch();
    } while (pilihan != 6);
    return 0;
}

void login() {
    int count;
    string userId, password, id, pass;

    system("cls");
    cout << "-----------------------------------------" << endl;
    cout << "                   Login                 " << endl;
    cout << "-----------------------------------------\n" << endl;
    cout << "Username\t: ";
    cin >> userId;
    cout << "Password\t: ";
    cin >> password;

    ifstream input("records.txt");

    while (input >> id >> pass) {
        if (id == userId && pass == password) {
            count = 1;
            system("cls");
        }
    }
    input.close();

    if (count == 1) {
        cout << userId << " Login Berhasil" << endl;
    } else {
        cout << "Sign In dulu baru Login..." << endl;
        main();
    }
}

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