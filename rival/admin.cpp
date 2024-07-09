#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream> 
#include <sstream> 
#include <conio.h>
#include <chrono> 
#include <thread> 

using namespace std;

struct Menu {
    string nama;
    int harga;
    int stok;
    string deskripsi;
};

string username, password;
char ch;

vector<Menu> inventaris;

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
    cout << "Data berhasil dibaca dari file." << endl;
}

void tambahMenu() {
    Menu menuBaru;
    char pilihan;
    
    do {
        system("cls");
        cout << "=========================================" << endl;
        cout << "              TAMBAH MENU              " << endl;
        cout << "=========================================" << endl;
        cout << "Masukkan nama menu       : ";
        cin.ignore(); 
        getline(cin, menuBaru.nama); 
        cout << "Masukkan harga menu      : ";
        cin >> menuBaru.harga;
        cout << "Masukkan stok menu       : ";
        cin >> menuBaru.stok;
        cout << "Masukkan deskripsi menu  : ";
        cin.ignore(); 
        getline(cin, menuBaru.deskripsi); 
        inventaris.push_back(menuBaru);
        simpanDataKeFile(); 
        cout << "=========================================" << endl;
        cout << "Menu berhasil ditambahkan!" << endl;
        cout << "=========================================" << endl;
        cout << "Apakah Anda ingin menambahkan menu lagi? (y/t): ";
        cin >> pilihan;
    } while (pilihan == 'y' || pilihan == 'Y');
}

void bacaMenu() {
    system("cls");
    cout << "=========================================" << endl;
    cout << "              LIHAT MENU              " << endl;
    cout << "=========================================" << endl;
    if (inventaris.empty()) {
        cout << "Tidak ada menu dalam inventaris." << endl;
        return;
    }
    
    int pilihan;
    cout << "Pilihan tampilan menu:" << endl;
    cout << "1. Berdasarkan abjad nama menu" << endl;
    cout << "2. Berdasarkan harga paling mahal" << endl;
    cout << "3. Berdasarkan harga paling murah" << endl;
    cout << "Masukkan pilihan: ";
    cin >> pilihan;
    if (pilihan == 1) {
        cout << "=========================================" << endl;
        cout << "                  ABJAD              " << endl;
        cout << "=========================================" << endl;
        sort(inventaris.begin(), inventaris.end(), [](const Menu& a, const Menu& b) {
            return a.nama < b.nama;
        });
    } else if (pilihan == 2) {
        cout << "=========================================" << endl;
        cout << "               PALING MAHAL              " << endl;
        cout << "=========================================" << endl;
        sort(inventaris.begin(), inventaris.end(), [](const Menu& a, const Menu& b) {
            return a.harga > b.harga;
        });
    } else if (pilihan == 3) {
        cout << "=========================================" << endl;
        cout << "               PALING MURAH           " << endl;
        cout << "=========================================" << endl;
        sort(inventaris.begin(), inventaris.end(), [](const Menu& a, const Menu& b) {
            return a.harga < b.harga;
        });
    } else {
        cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
    }
    cout << "Daftar Menu:" << endl;
    for (size_t i = 0; i < inventaris.size(); ++i) {
        cout << "=========================================\n" << endl;
        cout << i + 1 << ". Nama        : " << inventaris[i].nama << endl;
        cout << "   Harga       : " << inventaris[i].harga << endl;
        cout << "   Stok        : " << inventaris[i].stok << endl;
        cout << "   Dekripsi    : " << inventaris[i].deskripsi << endl;
    }
}

void perbaruiMenu() {
    string namaMenu;

    system("cls");
    cout << "=========================================" << endl;
    cout << "              UPDATE MENU           " << endl;
    cout << "=========================================" << endl;
            cout << "Masukkan nama menu       : ";
    cin.ignore(); 
    getline(cin, namaMenu); 
    for (auto& menu : inventaris) {
        if (menu.nama == namaMenu) {
            cout << "Masukkan harga baru        : ";
            cin >> menu.harga;
            cout << "Masukkan stok baru         : ";
            cin >> menu.stok;
            cout << "Masukkan deskripsi baru    : ";
            cin.ignore(); 
            getline(cin, menu.deskripsi); 
            simpanDataKeFile(); 
            cout << "=========================================" << endl;
            cout << "Menu berhasil diperbarui!" << endl;
            return;
        }
    }
    cout << "=========================================" << endl;
    cout << "Menu tidak ditemukan." << endl;
}

void hapusMenu() {
    string namaMenu;

    system("cls");
    cout << "=========================================" << endl;
    cout << "              HAPUS MENU           " << endl;
    cout << "=========================================" << endl;
    cout << "Masukkan nama menu: ";
    cin.ignore(); 
    getline(cin, namaMenu); 
    auto it = find_if(inventaris.begin(), inventaris.end(), [&](const Menu& menu) {
        return menu.nama == namaMenu;
    });

    cout << "=========================================" << endl;
    if (it != inventaris.end()) {
        inventaris.erase(it);
        simpanDataKeFile(); 
        cout << "Menu berhasil dihapus!" << endl;
    } else {
        cout << "Menu tidak ditemukan." << endl;
    }
}

void login() {
    system("cls");
    cout << "==============================================" << endl;
    cout << "           L O G I N  A P L I K A S I        " << endl;
    cout << "==============================================" << endl;
    cout << "Masukan Username: ";
    cin >> username;
    cout << "Masukan Password: ";
    ch = _getch(); 
    while (ch != '\r') { 
        password.push_back(ch); 
        cout << '*'; 
        ch = _getch(); 
    }
    cout << endl; 

    do {
        if (username == "admin" && password == "admin") {
            cout << "Berhasil login" << endl;
            break; 
        } else {
            cout << "\nUsername atau password salah. Silakan coba lagi." << endl;
            password.clear(); 
            cout << "Masukan Password: ";
            ch = _getch(); 
            while (ch != '\r') { 
                password.push_back(ch); 
                cout << '*'; 
                ch = _getch(); 
            }
            cout << endl; 
        }
    } while (username != "admin" || password != "admin");
}

int main() {
    int pilihan;
    char chose;

    login();

    do {
        system("cls");
        cout << "=========================================" << endl;
        cout << "                  M E N U                " << endl;
        cout << "=========================================" << endl;
        cout << "1. Tambah Menu" << endl;
        cout << "2. Lihat Menu" << endl;
        cout << "3. Perbarui Menu" << endl;
        cout << "4. Hapus Menu" << endl;
        cout << "5. Keluar" << endl;
        cout << "=========================================" << endl;
        cout << "Masukkan pilihan: ";
        cin >> pilihan;
        switch (pilihan) {
            case 1:
                tambahMenu();
                break;
            case 2:
                bacaMenu();
                getch();
                break;
            case 3:
                perbaruiMenu();
                break;
            case 4:
                hapusMenu();
                break;
            case 5:
                system("cls");
                cout << "Anda Telah Keluar Dari Aplikasi....." << endl;
                return 0; 
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    } while (pilihan != 5);
    return 0;
}   
