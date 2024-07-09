#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <conio.h>

using namespace std;

struct Menu {
    string nama;
    int harga;
    int stok;
    string deskripsi;
};

struct Pesanan {
    string namaMenu;
    int jumlah;
};

struct RiwayatPesanan {
    vector<Pesanan> pesanan;
    int totalBiaya;
};

vector<Menu> inventaris;
vector<Pesanan> pesanan;
vector<RiwayatPesanan> riwayatPesanan;

void simpanDataKeFile() {
    ofstream file("inventaris.txt");
    for (const auto& menu : inventaris) {
        file << menu.nama << "," << menu.harga << "," << menu.stok << "," << menu.deskripsi << endl;
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
            Menu menu;
            menu.nama = tokens[0];
            menu.harga = stoi(tokens[1]);
            menu.stok = stoi(tokens[2]);
            menu.deskripsi = tokens[3];
            inventaris.push_back(menu);
        }
    }
    file.close();
}

void tampilkanMenu() {
    system("cls");
    cout << "=========================================" << endl;
    cout << "                DAFTAR MENU            " << endl;
    cout << "=========================================" << endl;
    for (size_t i = 0; i < inventaris.size(); ++i) {
        cout << i + 1 << ". Nama        : " << inventaris[i].nama << endl;
        cout << "   Harga       : " << inventaris[i].harga << endl;
        cout << "   Stok        : " << inventaris[i].stok << endl;
        cout << "   Deskripsi   : " << inventaris[i].deskripsi << endl;
        cout << "=========================================" << endl;
    }
    cout << "Masukkan nama menu yang ingin dicari: ";
    string keyword;
    cin.ignore();
    getline(cin, keyword);
    cout << "=========================================" << endl;
    cout << "                HASIL PENCARIAN            " << endl;
    cout << "=========================================" << endl;
    for (size_t i = 0; i < inventaris.size(); ++i) {
        if (inventaris[i].nama.find(keyword) != string::npos) {
            cout << i + 1 << ". Nama        : " << inventaris[i].nama << endl;
            cout << "   Harga       : " << inventaris[i].harga << endl;
            cout << "   Stok        : " << inventaris[i].stok << endl;
            cout << "   Deskripsi   : " << inventaris[i].deskripsi << endl;
            cout << "=========================================" << endl;
        }
    }
}

void tambahKePesanan() {
    string namaMenu;
    int jumlah;

    system("cls");
    tampilkanMenu();
    cout << "=========================================" << endl;
    cout << "           TAMBAHKAN KE PESANAN        " << endl;
    cout << "=========================================" << endl;
    cout << "Masukkan nama menu yang ingin ditambahkan: ";
    cin.ignore();
    getline(cin, namaMenu);
    cout << "Masukkan jumlah menu yang ingin ditambahkan: ";
    cin >> jumlah;

    auto it = find_if(inventaris.begin(), inventaris.end(), [&](const Menu& menu) {
        return menu.nama == namaMenu;
    });

    if (it != inventaris.end() && it->stok >= jumlah) {
        Pesanan pesan;
        pesan.namaMenu = namaMenu;
        pesan.jumlah = jumlah;
        pesanan.push_back(pesan);
        it->stok -= jumlah;
        simpanDataKeFile();
        cout << "Menu berhasil ditambahkan ke pesanan!" << endl;
    } else {
        cout << "Menu tidak ditemukan atau stok tidak mencukupi." << endl;
    }
}

void lihatPesanan() {
    system("cls");
    cout << "=========================================" << endl;
    cout << "             PESANAN ANDA           " << endl;
    cout << "=========================================" << endl;
    if (pesanan.empty()) {
        cout << "Pesanan Anda kosong." << endl;
        return;
    }
    for (size_t i = 0; i < pesanan.size(); ++i) {
        cout << i + 1 << ". Nama Menu  : " << pesanan[i].namaMenu << endl;
        cout << "   Jumlah       : " << pesanan[i].jumlah << endl;
        cout << "=========================================" << endl;
    }
}

void hapusDariPesanan() {
    string namaMenu;

    system("cls");
    lihatPesanan();
    cout << "=========================================" << endl;
    cout << "         HAPUS MENU DARI PESANAN     " << endl;
    cout << "=========================================" << endl;
    cout << "Masukkan nama menu yang ingin dihapus: ";
    cin.ignore();
    getline(cin, namaMenu);

    auto it = find_if(pesanan.begin(), pesanan.end(), [&](const Pesanan& pesan) {
        return pesan.namaMenu == namaMenu;
    });

    if (it != pesanan.end()) {
        auto menuIt = find_if(inventaris.begin(), inventaris.end(), [&](const Menu& menu) {
            return menu.nama == it->namaMenu;
        });
        if (menuIt != inventaris.end()) {
            menuIt->stok += it->jumlah;
        }
        pesanan.erase(it);
        simpanDataKeFile();
        cout << "Menu berhasil dihapus dari pesanan!" << endl;
    } else {
        cout << "Menu tidak ditemukan di pesanan." << endl;
    }
}

void checkout() {
    system("cls");
    cout << "=========================================" << endl;
    cout << "                CHECKOUT                 " << endl;
    cout << "=========================================" << endl;
    if (pesanan.empty()) {
        cout << "Pesanan Anda kosong." << endl;
        return;
    }
    int total = 0;
    cout << "Daftar Pesanan Anda:" << endl;
    for (const auto& pesan : pesanan) {
        auto menuIt = find_if(inventaris.begin(), inventaris.end(), [&](const Menu& menu) {
            return menu.nama == pesan.namaMenu;
        });
        if (menuIt != inventaris.end()) {
            cout << "Nama Menu  : " << menuIt->nama << endl;
            cout << "Jumlah       : " << pesan.jumlah << endl;
            cout << "Harga        : Rp " << menuIt->harga << endl;
            cout << "Subtotal     : Rp " << pesan.jumlah * menuIt->harga << endl;
            cout << "=========================================" << endl;
            total += pesan.jumlah * menuIt->harga;
        }
    }
    cout << "\n=========================================" << endl;
    cout << "Total yang harus dibayar: Rp " << total << endl;
    cout << "Terima kasih telah memesan!" << endl;
    RiwayatPesanan riwayat;
    riwayat.pesanan = pesanan;
    riwayat.totalBiaya = total;
    riwayatPesanan.push_back(riwayat);
    pesanan.clear();
}

void lihatRiwayatPesanan() {
    system("cls");
    cout << "=========================================" << endl;
    cout << "             RIWAYAT PESANAN           " << endl;
    cout << "=========================================" << endl;
    if (riwayatPesanan.empty()) {
        cout << "Tidak ada riwayat pesanan." << endl;
        return;
    }
    for (size_t i = 0; i < riwayatPesanan.size(); ++i) {
        cout << "Riwayat Pesanan " << i + 1 << ":" << endl;
        cout << "=========================================" << endl;
        cout << "Daftar Pesanan:" << endl;
        for (const auto& pesan : riwayatPesanan[i].pesanan) {
            auto menuIt = find_if(inventaris.begin(), inventaris.end(), [&](const Menu& menu) {
                return menu.nama == pesan.namaMenu;
            });
            if (menuIt != inventaris.end()) {
                cout << "Nama Menu  : " << menuIt->nama << endl;
                cout << "Jumlah       : " << pesan.jumlah << endl;
                cout << "Harga        : Rp " << menuIt->harga << endl;
                cout << "Subtotal     : Rp " << pesan.jumlah * menuIt->harga << endl;
                cout << "=========================================" << endl;
            }
        }
        cout << "Total Biaya  : Rp " << riwayatPesanan[i].totalBiaya << endl;
        cout << "=========================================" << endl;
    }
}

void login();
void regis();
void reset();

int main() {
    int c;
    cout << "=========================================" << endl;
    cout << "             L O G I N N N             " << endl;
    cout << "=========================================" << endl;
    cout << "1. Sign In" << endl;
    cout << "2. Sign Up" << endl;
    cout << "3. Forgot Password" << endl;
    cout << "=========================================" << endl;
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
        cout << "\n=========================================" << endl;
        cout << "              RESTORAN ONLINE                " << endl;
        cout << "=========================================" << endl;
        cout << "1. Lihat Menu" << endl;
        cout << "2. Tambah ke Pesanan" << endl;
        cout << "3. Lihat Pesanan" << endl; 
        cout << "4. Hapus dari Pesanan" << endl;
        cout << "5. Checkout" << endl;
        cout << "6. Lihat Riwayat Pesanan" << endl;
        cout << "7. Keluar" << endl;
        cout << "=========================================" << endl;
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
                lihatRiwayatPesanan();
                break;
            case 7:
            system("cls");
                cout << "Terima kasih telah menggunakan aplikasi restoran online!" << endl;
                return 0;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
        cout << "Tekan enter untuk melanjutkan...";
        _getch();
    } while (pilihan != 7);
    return 0;
}

void login() {
    int count;
    string userId, password, id, pass;

    system("cls");
    cout << "=========================================" << endl;
    cout << "                   Login                 " << endl;
    cout << "=========================================\n" << endl;
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
    cout << "=========================================" << endl;
    cout << "                 Registrasi              " << endl;
    cout << "=========================================" << endl;
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
    cout << "=========================================" << endl;
    cout << "           Lupa Password ?               " << endl;
    cout << "=========================================\n" << endl;
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