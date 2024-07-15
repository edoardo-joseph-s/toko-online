#include<bits/stdc++.h>
#include <conio.h>

using namespace std;

// Struktur data untuk menyimpan informasi produk
struct Produk {
    string nama;
    int harga;
    int stok;
    string deskripsi;
};

// Struktur data untuk menyimpan item dalam keranjang
struct KeranjangItem {
    string namaProduk;
    int jumlah;
};

vector<Produk> inventaris; // Vector untuk menyimpan daftar produk
vector<KeranjangItem> keranjang; // Vector untuk menyimpan item dalam keranjang

/**
 * Fungsi untuk menyimpan data inventaris ke dalam file
 * Data produk disimpan dalam format "nama,harga,stok,deskripsi" dan dipisahkan oleh koma.
 */
void simpanDataKeFile() {
    ofstream file("inventaris.txt");
    for (const auto& produk : inventaris) {
        file << produk.nama << "," << produk.harga << "," << produk.stok << "," << produk.deskripsi << endl;
    }
    file.close();
}

/**
 * Fungsi untuk membaca data inventaris dari file
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
}

/**
 * Fungsi untuk menampilkan daftar produk
 * Menampilkan semua produk yang ada di dalam inventaris.
 */
void tampilkanProduk() {
    system("cls");
    cout << "\033[1;34m-----------------------------------------\033[0m" << endl;
    cout << "\033[1;34m                DAFTAR PRODUK            \033[0m" << endl;
    cout << "\033[1;34m-----------------------------------------\033[0m" << endl;
    for (size_t i = 0; i < inventaris.size(); ++i) {
        cout << i + 1 << ". Nama        : " << inventaris[i].nama << endl;
        cout << "   Harga       : Rp. " << inventaris[i].harga << ",000"  << endl;
        cout << "   Stok        : " << inventaris[i].stok << endl;
        cout << "   Deskripsi   : " << inventaris[i].deskripsi << endl;
        cout << "-----------------------------------------" << endl;
    }
}

/**
 * Fungsi untuk menambahkan produk ke keranjang
 * Meminta pengguna untuk memasukkan nama produk dan jumlah yang ingin ditambahkan ke keranjang.
 */
void tambahKeKeranjang() {
    string namaProduk;
    int jumlah;

    system("cls");
    tampilkanProduk();
    cout << "\033[1;34m-----------------------------------------\033[0m" << endl;
    cout << "\033[1;34m           TAMBAHKAN KE KERANJANG        \033[0m" << endl;
    cout << "\033[1;34m-----------------------------------------\033[0m" << endl;
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

/**
 * Fungsi untuk melihat isi keranjang
 * Menampilkan semua item yang ada di dalam keranjang.
 */
void lihatKeranjang() {
    system("cls");
    cout << "\033[1;34m-----------------------------------------\033[0m" << endl;
    cout << "\033[1;34m             KERANJANG ANDA           \033[0m" << endl;
    cout << "\033[1;34m-----------------------------------------\033[0m" << endl;
    if (keranjang.empty()) {
        cout << "\033[1;31mKeranjang Anda kosong.\033[0m" << endl;
        return;
    }
    for (size_t i = 0; i < keranjang.size(); ++i) {
        cout << i + 1 << ". Nama Produk  : " << keranjang[i].namaProduk << endl;
        cout << "   Jumlah       : " << keranjang[i].jumlah << endl;
        cout << "-----------------------------------------" << endl;
    }
}

/**
 * Fungsi untuk menghapus produk dari keranjang
 * Meminta pengguna untuk memasukkan nama produk yang ingin dihapus dari keranjang.
 */
void hapusDariKeranjang() {
    string namaProduk;

    system("cls");
    lihatKeranjang();
    cout << "\033[1;34m-----------------------------------------\033[0m" << endl;
    cout << "\033[1;34m         HAPUS PRODUK DARI KERANJANG     \033[0m" << endl;
    cout << "\033[1;34m-----------------------------------------\033[0m" << endl;
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
        cout << "\033[1;31mProduk tidak ditemukan di keranjang.\033[0m" << endl;
    }
}

/**
 * Fungsi untuk melakukan checkout
 * Menampilkan daftar belanja dan total harga yang harus dibayar, serta mengosongkan keranjang setelah checkout.
 */
void checkout() {
    system("cls");
    cout << "\033[1;34m-----------------------------------------\033[0m" << endl;
    cout << "\033[1;34m                CHECKOUT                 \033[0m" << endl;
    cout << "\033[1;34m-----------------------------------------\033[0m" << endl;
    if (keranjang.empty()) {
        cout << "\033[1mKeranjang Anda kosong.\033[0m" << endl;
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
            cout << "Harga        : Rp " << produkIt->harga << ",000" << endl;
            cout << "Subtotal     : Rp " << item.jumlah * produkIt->harga << ",000" << endl;
            cout << "-----------------------------------------" << endl;
            total += item.jumlah * produkIt->harga;
            produkIt->stok -= item.jumlah;
        }
    }
    cout << "\n-----------------------------------------" << endl;
    cout << "\033[1mTotal yang harus dibayar: Rp " << total << "\033[0m" << endl;
    cout << "Terima kasih telah berbelanja!" << endl;
    keranjang.clear();
}

/**
 * Fungsi untuk mencari produk berdasarkan nama
 * Meminta pengguna untuk memasukkan nama produk yang ingin dicari dan menampilkan informasi produk tersebut.
 */
void cariProduk() {
    string namaProduk;
    int jumlah;
    system("cls");
    cout << "\033[1;34m-----------------------------------------\033[0m" << endl;
    cout << "\033[1;34m                CARI PRODUK              \033[0m" << endl;
    cout << "\033[1;34m-----------------------------------------\033[0m" << endl;
    cout << "Masukkan nama produk yang ingin dicari: ";
    cin.ignore();
    getline(cin, namaProduk);

    auto it = find_if(inventaris.begin(), inventaris.end(), [&](const Produk& produk) {
        return produk.nama == namaProduk;
    });

    if (it != inventaris.end()) {
        cout << "\033[1;32mProduk ditemukan:\033[0m" << endl;
        cout << "Nama        : " << it->nama << endl;
        cout << "Harga       : Rp. " << it->harga << ",000" << endl;
        cout << "Stok        : " << it->stok << endl;
        cout << "Deskripsi   : " << it->deskripsi << endl;
        cout << "-----------------------------------------" << endl;
        cout << "Masukkan jumlah produk yang ingin ditambahkan ke keranjang: ";
        cin >> jumlah;

        if (it->stok >= jumlah) {
            KeranjangItem item;
            item.namaProduk = namaProduk;
            item.jumlah = jumlah;
            keranjang.push_back(item);
            it->stok -= jumlah;
            simpanDataKeFile();
            cout << "Produk berhasil ditambahkan ke keranjang!" << endl;
        } else {
            cout << "Stok tidak mencukupi." << endl;
        }
    } else {
        cout << "\033[1;31mProduk tidak ditemukan.\033[0m" << endl;
    }
}

// Deklarasi fungsi login, registrasi, dan reset password
void login();
void regis();
void reset();

/**
 * Fungsi utama
 * Menampilkan menu utama dan mengarahkan pengguna ke fungsi yang sesuai berdasarkan pilihan mereka.
 */
int main() {
    int c;
    cout << "\033[1;32m-----------------------------------------\033[0m" << endl;
    cout << "\033[1;32m             M A S U K  D U L U              \033[0m" << endl;
    cout << "\033[1;32m-----------------------------------------\033[0m" << endl;
    cout << "\033[1;32m\t1. Sign In\033[0m" << endl;
    cout << "\033[1;32m\t2. Sign Up\033[0m" << endl;
    cout << "\033[1;32m\t3. Forgot Password\033[0m" << endl;
    cout << "\n\033[1;32m-----------------------------------------\033[0m" << endl;
    cout << "\033[1;32mMasukan Pilihan: \033[0m";
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
            cout << "\033[1;31mMasukkan pilihan yang benar...\033[0m" << endl;
            main();
    }

    bacaDataDariFile();

    int pilihan;
    system("cls");
    do {
        cout << "\n\033[1;34m-----------------------------------------\033[0m" << endl;
        cout << "\033[1;34m              TOKO ONLINE                \033[0m" << endl;
        cout << "\033[1;34m-----------------------------------------\033[0m" << endl;
        cout << "1. Lihat Produk" << endl;
        cout << "2. Tambah ke Keranjang" << endl;
        cout << "3. Lihat Keranjang" << endl; 
        cout << "4. Hapus dari Keranjang" << endl;
        cout << "5. Checkout" << endl;
        cout << "6. Cari Produk" << endl;
        cout << "7. Keluar" << endl;
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
                cariProduk();
                break;
            case 7:
            system("cls");
                cout << "\033[1;34mTerima kasih telah menggunakan aplikasi toko online!\033[0m" << endl;
                return 0;
            default:
                cout << "\033[1;31mPilihan tidak valid. Silakan coba lagi.\033[0m" << endl;
        }
        cout << "Tekan enter untuk melanjutkan...";
        _getch();
    } while (pilihan != 7);
    return 0;
}

/**
 * Fungsi untuk login
 * Meminta pengguna untuk memasukkan username dan password, kemudian memverifikasi dengan data yang ada di file "records.txt".
 */
void login() {
    int count = 0;
    string userId, password, id, pass;
    char ch;

    system("cls");
    cout << "\033[1;34m-----------------------------------------" << endl;
    cout << "                   Login                 " << endl;
    cout << "-----------------------------------------\n\033[0m" << endl;
    cout << "Username\t: ";
    cin >> userId;
    cout << "Password\t: ";
    password.clear();
    ch = _getch();
    while (ch != '\r') {
        password.push_back(ch);
        cout << '*';
        ch = _getch();
    }
    cout << endl;

    ifstream input("records.txt");

    while (input >> id >> pass) {
        if (id == userId && pass == password) {
            count = 1;
            system("cls");
            cout << "\033[1;32mSelamat datang " << userId << "\033[0m" << endl;
            break;
        }
    }
    input.close();

    if (count == 0) {
        cout << "\033[1;31mUsername atau Password salah. Silakan coba lagi.\033[0m" << endl;
        getch();
        main();
    }
}

/**
 * Fungsi untuk registrasi
 * Meminta pengguna untuk memasukkan username dan password, kemudian menyimpannya ke dalam file "records.txt".
 */
void regis() {
    string ruserId, rpassword, rid, rpass;

    system("cls");
    cout << "\033[1;32m-----------------------------------------\033[0m" << endl;
    cout << "\033[1;32m                 Registrasi              \033[0m" << endl;
    cout << "\033[1;32m-----------------------------------------\033[0m" << endl;
    cout << "Masukan Username: ";
    cin >> ruserId;
    cout << "Masukan Password: ";
    cin >> rpassword;

    ofstream f1("records.txt", ios::app);
    f1 << ruserId << ' ' << rpassword << endl;
    system("cls");
    cout << "\033[1;32m\nRegistrasi Berhasil...\033[0m" << endl;
    main();
}

/**
 * Fungsi untuk reset password
 * Meminta pengguna untuk memasukkan username yang diingat, kemudian menampilkan password jika akun ditemukan.
 */
void reset() {
    int option;
    system("cls");
    cout << "\033[1;34m-----------------------------------------\033[0m" << endl;
    cout << "\033[1;34m           Lupa Password ?               \033[0m" << endl;
    cout << "\033[1;34m-----------------------------------------\033[0m\n" << endl;
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
                cout << "\033[1;32m\n\nAkun ditemukan...\033[0m\n";
                cout << "\nPassword anda adalah: " << spass << endl;
                _getch();
                main();
            } else {
                cout << "\033[1;31m\n\nMaaf, akun tidak ditemukan...\033[0m\n";
                reset();
            }
            break;
        }
        case 2:
            main();
            break;
        default:
            cout << "\033[1;31m\nMasukkan pilihan yang benar - coba lagi\033[0m" << endl;
            reset();
    }
}