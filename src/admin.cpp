#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream> // Tambahkan untuk penggunaan file
#include <sstream> // Tambahkan untuk penggunaan stringstream
#include <conio.h> // Tambahkan untuk penggunaan _getch()
#include <chrono> 
#include <thread> 


using namespace std;

// Struktur untuk mewakili produk
struct Produk {
    string nama;
    int harga;
    int stok;
    string deskripsi;
};

string username, password;
char ch;

vector<Produk> inventaris;

// Fungsi untuk menyimpan data ke file
/**
 * Fungsi ini digunakan untuk menyimpan data produk ke dalam file "inventaris.txt".
 * Setiap produk disimpan dalam format "nama,harga,stok,deskripsi" dan dipisahkan oleh koma.
 */
void simpanDataKeFile() {
    ofstream file("inventaris.txt");
    for (const auto& produk : inventaris) {
        file << produk.nama << "," << produk.harga << "," << produk.stok << "," << produk.deskripsi << endl;
    }
    file.close();
}

// Fungsi untuk membaca data dari file
/**
 * Fungsi ini digunakan untuk membaca data produk dari file "inventaris.txt" dan mengisi vektor inventaris.
 * Data produk dibaca berdasarkan format "nama,harga,stok,deskripsi" yang dipisahkan oleh koma.
 */
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
    cout << "\033[1;32mData berhasil dibaca dari file.\033[0m" << endl;
}

// Fungsi untuk menambah produk baru
/**
 * Fungsi ini digunakan untuk menambah produk baru ke dalam inventaris.
 * Pengguna dapat memasukkan nama, harga, stok, dan deskripsi produk baru.
 * Setelah produk ditambahkan, data akan disimpan ke file "inventaris.txt".
 */
void tambahProduk() {
    Produk produkBaru;
    char pilihan;
    
    do {
        system("cls");
        cout << "\033[1;34m-----------------------------------------\033[0m" << endl;
        cout << "\033[1;34m              TAMBAH PRODUK              \033[0m" << endl;
        cout << "\033[1;34m-----------------------------------------\033[0m" << endl;
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
        cout << "\033[1;32m-----------------------------------------\033[0m" << endl;
        cout << "\033[1;32mProduk berhasil ditambahkan!\033[0m" << endl;
        cout << "\033[1;32m-----------------------------------------\033[0m" << endl;
        cout << "Apakah Anda ingin menambahkan produk lagi? (y/t): ";
        cin >> pilihan;
    } while (pilihan == 'y' || pilihan == 'Y');
}

// Fungsi untuk menampilkan produk
/**
 * Fungsi ini digunakan untuk menampilkan daftar produk dalam inventaris.
 * Pengguna dapat memilih untuk menampilkan produk berdasarkan abjad nama, harga paling mahal, atau harga paling murah.
 */
void bacaProduk() {
    system("cls");
    cout << "\033[1;34m-----------------------------------------\033[0m" << endl;
    cout << "\033[1;34m              LIHAT PRODUK              \033[0m" << endl;
    cout << "\033[1;34m-----------------------------------------\033[0m" << endl;
    if (inventaris.empty()) {
        cout << "\033[1;31mTidak ada produk dalam inventaris.\033[0m" << endl;
        return;
    }
    
    int pilihan;
    cout << "Pilihan tampilan produk:" << endl;
    cout << "1. Berdasarkan abjad nama barang" << endl;
    cout << "2. Berdasarkan harga paling mahal" << endl;
    cout << "3. Berdasarkan harga paling murah" << endl;
    cout << "Masukkan pilihan: ";
    cin >> pilihan;
    if (pilihan == 1) {
        cout << "\033[1;34m-----------------------------------------\033[0m" << endl;
        cout << "\033[1;34m                  ABJAD              \033[0m" << endl;
        cout << "\033[1;34m-----------------------------------------\033[0m" << endl;
        sort(inventaris.begin(), inventaris.end(), [](const Produk& a, const Produk& b) {
            return a.nama < b.nama;
        });
    } else if (pilihan == 2) {
        cout << "\033[1;34m-----------------------------------------\033[0m" << endl;
        cout << "\033[1;34m               PALING MAHAL              \033[0m" << endl;
        cout << "\033[1;34m-----------------------------------------\033[0m" << endl;
        sort(inventaris.begin(), inventaris.end(), [](const Produk& a, const Produk& b) {
            return a.harga > b.harga;
        });
    } else if (pilihan == 3) {
        cout << "\033[1;34m-----------------------------------------\033[0m" << endl;
        cout << "\033[1;34m               PALING MURAH           \033[0m" << endl;
        cout << "\033[1;34m-----------------------------------------\033[0m" << endl;
        sort(inventaris.begin(), inventaris.end(), [](const Produk& a, const Produk& b) {
            return a.harga < b.harga;
        });
    } else {
        cout << "\033[1;31mPilihan tidak valid. Silakan coba lagi.\033[0m" << endl;
    }
    cout << "Daftar Produk:" << endl;
    for (size_t i = 0; i < inventaris.size(); ++i) {
        cout << "\033[1;34m-----------------------------------------\033[0m\n" << endl;
        cout << i + 1 << ". Nama        : " << inventaris[i].nama << endl;
        cout << "   Harga       : Rp " << inventaris[i].harga << ",000" << endl;
        cout << "   Stok        : " << inventaris[i].stok << endl;
        cout << "   Dekripsi    : " << inventaris[i].deskripsi << endl;
    }
}

// Fungsi untuk memperbarui produk
/**
 * Fungsi ini digunakan untuk memperbarui detail produk yang sudah ada dalam inventaris.
 * Pengguna dapat memasukkan nama produk yang ingin diperbarui, lalu mengubah harga, stok, dan deskripsi produk.
 * Setelah diperbarui, data akan disimpan ke file "inventaris.txt".
 */
void perbaruiProduk() {
    string namaProduk;

    system("cls");
    cout << "\033[1;34m-----------------------------------------\033[0m" << endl;
    cout << "\033[1;34m              UPDATE PRODUK           \033[0m" << endl;
    cout << "\033[1;34m-----------------------------------------\033[0m" << endl;
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
            cout << "\033[1;32m-----------------------------------------\033[0m" << endl;
            cout << "\033[1;32mProduk berhasil diperbarui!\033[0m" << endl;
            return;
        }
    }
    cout << "\033[1;31m-----------------------------------------\033[0m" << endl;
    cout << "\033[1;31mProduk tidak ditemukan.\033[0m" << endl;
}

// Fungsi untuk menghapus produk
/**
 * Fungsi ini digunakan untuk menghapus produk dari inventaris.
 * Pengguna dapat memasukkan nama produk yang ingin dihapus.
 * Setelah dihapus, data akan disimpan ke file "inventaris.txt".
 */
void hapusProduk() {
    string namaProduk;

    system("cls");
    cout << "\033[1;34m-----------------------------------------\033[0m" << endl;
    cout << "\033[1;34m              HAPUS PRODUK           \033[0m" << endl;
    cout << "\033[1;34m-----------------------------------------\033[0m" << endl;
    cout << "Masukkan nama produk: ";
    cin.ignore(); // Tambahkan untuk mengabaikan enter sebelumnya
    getline(cin, namaProduk); // Menggunakan getline untuk menerima input dengan spasi
    auto it = find_if(inventaris.begin(), inventaris.end(), [&](const Produk& produk) {
        return produk.nama == namaProduk;
    });

    cout << "\033[1;34m-----------------------------------------\033[0m" << endl;
    if (it != inventaris.end()) {
        inventaris.erase(it);
        simpanDataKeFile(); // Simpan data ke file setelah dihapus
        cout << "\033[1;32mProduk berhasil dihapus!\033[0m" << endl;
    } else {
        cout << "\033[1;31mProduk tidak ditemukan.\033[0m" << endl;
    }
}

// Fungsi untuk proses login
/**
 * Fungsi ini digunakan untuk proses autentikasi login.
 * Pengguna harus memasukkan username dan password yang valid untuk dapat masuk ke dalam sistem.
 */
void login() {
    system("cls");
    cout << "\033[1;34m==============================================\033[0m" << endl;
    cout << "\033[1;34m                 L O G I N        \033[0m" << endl;
    cout << "\033[1;34m==============================================\033[0m" << endl;
    cout << "\033[1;34mMasukan Username dan Password untuk login.....\033[0m" << endl;
    cout << "\033[1;34m==============================================\033[0m" << endl;
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    ch = _getch(); // Menggunakan _getch() agar input password tidak terlihat
    while (ch != '\r') { // Loop sampai tombol Enter ditekan
        password.push_back(ch); // Menambahkan karakter ke password
        cout << '*'; // Menampilkan bintang sebagai input password
        ch = _getch(); // Membaca karakter berikutnya
    }
    cout << endl; // Pindah baris setelah memasukkan password

    // Proses autentikasi dengan menggunakan do-while untuk mengulang jika password salah
    do {
        if (username == "admin" && password == "ulan") {
            cout << "\033[1;32mBerhasil login\033[0m" << endl;
            break; // Keluar dari loop jika autentikasi berhasil
        } else {
            cout << "\033[1;31mUsername atau password salah. Silakan coba lagi.\033[0m" << endl;
            cout << "Masukan Username: ";
            cin >> username; // Meminta input username kembali
            cout << "Masukan Password: ";
            password.clear(); // Bersihkan password untuk input baru
            ch = _getch(); // Menggunakan _getch() agar input password tidak terlihat
            while (ch != '\r') { // Loop sampai tombol Enter ditekan
                password.push_back(ch); // Menambahkan karakter ke password
                cout << '*'; // Menampilkan bintang sebagai input password
                ch = _getch(); // Membaca karakter berikutnya
            }
            cout << endl; // Pindah baris setelah memasukkan password
        }
    } while (username != "admin" || password != "ulan");
}

int main() {
    int pilihan;
    char chose;

    login();

    do {
        system("cls");
        cout << "\n\033[1;34m-----------------------------------------\033[0m" << endl;
        cout << "\033[1;34m                  M E N U                \033[0m" << endl;
        cout << "\033[1;34m-----------------------------------------\033[0m" << endl;
        cout << "1. Tambah Produk" << endl;
        cout << "2. Lihat Produk" << endl;
        cout << "3. Perbarui Produk" << endl;
        cout << "4. Hapus Produk" << endl;
        cout << "5. Keluar" << endl;
        cout << "\033[1;34m-----------------------------------------\033[0m" << endl;
        cout << "Masukkan pilihan: ";
        cin >> pilihan;
        switch (pilihan) {
            case 1:
                tambahProduk();
                break;
            case 2:
                bacaProduk();
                cout << "\033[1;32mTekan enter untuk melanjutkan....\033[0m" << getch();
                break;
            case 3:
                perbaruiProduk();
                break;
            case 4:
                hapusProduk();
                break;
            case 5:
            system("cls");
                cout << "\033[1;34m==============================================\033[0m" << endl;
                cout << "\033[1;34m                    E X I T                   \033[0m" << endl;
                cout << "\033[1;34m==============================================\033[0m" << endl;
                cout << "\033[1;32m         Anda Telah Keluar Dari Aplikasi        \033[0m" << endl;
                cout << "\033[1;32m                                               \033[0m" << endl;
                return 0; // Keluar dari program
            default:
                cout << "\033[1;31mPilihan tidak valid. Silakan coba lagi.\033[0m" << endl;
        }
    } while (pilihan != 5);
    return 0;
}   
