#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
#include <stack>
#include <list>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <conio.h> // Tambahkan header ini untuk menggunakan _getch()

using namespace std;

// Definisi Struct
struct Membership {
    string type;
    string benefits;
    string room;
    string trainer;
    string time;
    double price;
};

struct User {
    string username;
    string password;
    vector<Membership> memberships;
};

// Definisi Array
vector<User> users;
vector<Membership> memberships = {
    {"Silver", "Use all the basic tools and machines", "Silver's clean and neat changing rooms / bathrooms (no locker)", "No trainer", "Everyday 10:00am-05:00pm", 10},
    {"Gold", "Use all the premium tools and machines", "Gold's premium changing rooms / bathrooms (no locker)", "With a trainer (not a personal trainer)", "Everyday 10:00am-05:00pm", 15},
    {"Platinum", "Use all the premium tools and machines", "Platinum's premium changing rooms / bathrooms (with a locker)", "With a personal trainer", "Everyday (24 hours open)", 20}
};

// Definisi Stack
stack<string> operationHistory;

// Definisi Queue
queue<int> membershipQueue;

// Definisi Linked List
list<string> memberList;

bool adminLoggedIn = false;
const string adminUsername = "admin";
const string adminPassword = "admin123";

// Deklarasi Fungsi
void adminLogin();
void userSignUp();
bool userSignIn(string &currentUsername);
void viewMemberships();
void searchMembership();
void buyMembership(string currentUsername);
void viewUserMemberships(string currentUsername);
void cancelMembership(string currentUsername);
void manageAccount(string currentUsername);
void displayMenu();
void displayInitialMenu();
void saveUsersToFile();
void loadUsersFromFile();
void saveMembershipsToFile();
void loadMembershipsFromFile();
void viewMemberList();

// Fungsi Utama
int main() {
    int choice;
    string currentUsername;

    loadUsersFromFile();
    loadMembershipsFromFile();
    
    while (true) {
        displayInitialMenu();
        cout << "Masukkan pilihan Anda: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                system("cls");
                cout << "1. Sign In User\n2. Sign In Admin\nPilih opsi: ";
                cin >> choice;
                if (choice == 1) {
                    if (userSignIn(currentUsername)) {
                        while (true) {
                            system("cls");
                            cout << "\n===============================\n";
                            cout << "|         User Menu           |\n";
                            cout << "===============================\n";
                            cout << "1. Cari Membership\n";
                            cout << "2. Beli Membership\n";
                            cout << "3. Lihat Membership Saya\n";
                            cout << "4. Batalkan Membership\n";
                            cout << "5. Atur Akun\n";
                            cout << "0. Keluar\n";
                            cout << "===============================\n";
                            cout << "Masukkan pilihan Anda: ";
                            cin >> choice;
                            switch (choice) {
                                case 1:
                                    system("cls");
                                    searchMembership();
                                    cout << "Tekan Enter untuk melanjutkan...";
                                    cin.ignore();
                                    break;
                                case 2:
                                    system("cls");
                                    buyMembership(currentUsername);
                                    break;
                                case 3:
                                    system("cls");
                                    viewUserMemberships(currentUsername);
                                    cout << "Tekan Enter untuk melanjutkan...";
                                    cin.ignore();
                                    break;
                                case 4:
                                    system("cls");
                                    cancelMembership(currentUsername);
                                    break;
                                case 5:
                                    system("cls");
                                    manageAccount(currentUsername);
                                    break;
                                case 0:
                                    system("cls");
                                    cout << "Keluar...\n";
                                    goto mainMenu;
                                default:
                                    system("cls");
                                    cout << "Pilihan tidak valid. Silakan coba lagi.\n";
                            }
                        }
                    }
                } else if (choice == 2) {
                    system("cls");
                    adminLogin();
                    if (adminLoggedIn) {
                        while (true) {
                            system("cls");
                            cout << "\n===============================\n";
                            cout << "|         Admin Menu          |\n";
                            cout << "===============================\n";
                            cout << "1. Lihat Membership\n";
                            cout << "2. Lihat Daftar Member\n";
                            cout << "0. Keluar\n";
                            cout << "===============================\n";
                            cout << "Masukkan pilihan Anda: ";
                            cin >> choice;
                            switch (choice) {
                                case 1:
                                    system("cls");
                                    viewMemberships();
                                    cout << "Tekan Enter untuk melanjutkan...";
                                    cin.ignore();
                                    break;
                                case 2:
                                    system("cls");
                                    viewMemberList();
                                    cout << "Tekan Enter untuk melanjutkan...";
                                    cin.ignore();
                                    cin.get(); 
                                    break;
                                case 0:
                                    system("cls");
                                    cout << "Keluar...\n";
                                    adminLoggedIn = false;
                                    goto mainMenu;
                                default:
                                    system("cls");
                                    cout << "Pilihan tidak valid. Silakan coba lagi.\n";
                            }
                        }
                    }
                } else {
                    system("cls");
                    cout << "Pilihan tidak valid. Silakan coba lagi.\n";
                }
                break;
            case 2:
                system("cls");
                userSignUp();
                break;
            case 0:
                system("cls");
                cout << "Keluar dari program...\n";
                return 0;
            default:
                system("cls");
                cout << "Pilihan tidak valid. Silakan coba lagi.\n";
        }
        mainMenu:
        continue;
    }
    return 0;
}

// Definisi Fungsi
void adminLogin() {
    string username, password;
    cout << "Masukkan username admin: ";
    cin.ignore();
    getline(cin, username);
    cout << "Masukkan password admin: ";
    char ch = _getch(); // Menggunakan _getch() agar input password tidak terlihat
    while (ch != '\r') { // Loop sampai tombol Enter ditekan
        password.push_back(ch); // Menambahkan karakter ke password
        cout << '*'; // Menampilkan bintang sebagai input password
        ch = _getch(); // Membaca karakter berikutnya
    }
    cout << endl; // Pindah baris setelah memasukkan password
    if (username == adminUsername && password == adminPassword) {
        adminLoggedIn = true;
        cout << "Admin berhasil masuk.\n";
    } else {
        cout << "Kredensial admin tidak valid.\n";
    }
}

void userSignUp() {
    User newUser;
    cout << "Masukkan username: ";
    cin.ignore();
    getline(cin, newUser.username);
    cout << "Masukkan password: ";
    char ch = _getch(); // Menggunakan _getch() agar input password tidak terlihat
    while (ch != '\r') { // Loop sampai tombol Enter ditekan
        newUser.password.push_back(ch); // Menambahkan karakter ke password
        cout << '*'; // Menampilkan bintang sebagai input password
        ch = _getch(); // Membaca karakter berikutnya
    }
    cout << endl; // Pindah baris setelah memasukkan password
    users.push_back(newUser);
    saveUsersToFile();
    cout << "Pendaftaran pengguna berhasil.\n";
}

bool userSignIn(string &currentUsername) {
    string username, password;
    cout << "Masukkan username: ";
    cin.ignore();
    getline(cin, username);
    cout << "Masukkan password: ";
    char ch = _getch(); // Menggunakan _getch() agar input password tidak terlihat
    while (ch != '\r') { // Loop sampai tombol Enter ditekan
        password.push_back(ch); // Menambahkan karakter ke password
        cout << '*'; // Menampilkan bintang sebagai input password
        ch = _getch(); // Membaca karakter berikutnya
    }
    cout << endl; // Pindah baris setelah memasukkan password
    for (const auto &user : users) {
        if (user.username == username && user.password == password) {
            currentUsername = username;
            cout << "Pengguna berhasil masuk.\n";
            return true;
        }
    }
    cout << "Kredensial pengguna tidak valid.\n\n";
    return false;
}

void viewMemberships() {
    sort(memberships.begin(), memberships.end(), [](const Membership &a, const Membership &b) {
        return a.type < b.type;
    });

    cout << "\n=============================== Daftar Membership ===============================\n";
    for (const auto &membership : memberships) {
        cout << "Tipe: " << membership.type << "\n";
        cout << "Benefits: " << membership.benefits << "\n";
        cout << "Room: " << membership.room << "\n";
        cout << "Trainer: " << membership.trainer << "\n";
        cout << "Time: " << membership.time << "\n";
        cout << "Harga: Rp" << membership.price << "\n";
        cout << "--------------------------------------------\n";
    }
    cout << "=================================================================================\n";
    cout << "Tekan Enter untuk melanjutkan...";
    cin.ignore();
}

void searchMembership() {
    string type;
    cout << "Masukkan tipe membership untuk mencari: ";
    cin.ignore();
    getline(cin, type);
    transform(type.begin(), type.end(), type.begin(), ::tolower);
    cout << "Hasil Pencarian:\n";
    for (const auto &membership : memberships) {
        string membershipType = membership.type;
        transform(membershipType.begin(), membershipType.end(), membershipType.begin(), ::tolower);
        if (membershipType.find(type) != string::npos) {
            cout << "Tipe: " << membership.type << "\n";
            cout << "Benefits: " << membership.benefits << "\n";
            cout << "Room: " << membership.room << "\n";
            cout << "Trainer: " << membership.trainer << "\n";
            cout << "Time: " << membership.time << "\n";
            cout << "Harga: Rp" << membership.price << "\n";
            cout << "--------------------------------------------\n";
        }
    }
    cout << "Tekan Enter untuk melanjutkan...";
}

void buyMembership(string currentUsername) {
    int choice;
    cout << "Pilih tipe membership untuk membeli:\n";
    for (size_t i = 0; i < memberships.size(); ++i) {
        cout << i + 1 << ". " << memberships[i].type << " - Rp" << memberships[i].price << "\n";
    }
    cout << "Masukkan pilihan Anda: ";
    cin >> choice;
    if (choice > 0 && choice <= memberships.size()) {
        const auto &selectedMembership = memberships[choice - 1];
        for (auto &user : users) {
            if (user.username == currentUsername) {
                user.memberships.push_back(selectedMembership);
                saveUsersToFile();
                cout << "Membership berhasil dibeli.\n";
                return;
            }
        }
    } else {
        cout << "Pilihan tidak valid.\n";
    }
}

void viewUserMemberships(string currentUsername) {
    cout << "Membership Anda:\n";
    for (const auto &user : users) {
        if (user.username == currentUsername) {
            for (const auto &membership : user.memberships) {
                cout << "Tipe: " << membership.type << ", Benefits: " << membership.benefits << "\n";
            }
            cout << "Tekan Enter untuk melanjutkan...";
            cin.ignore();
            return;
        }
    }
}

void cancelMembership(string currentUsername) {
    string type;
    cout << "Masukkan tipe membership untuk membatalkan: ";
    cin.ignore();
    getline(cin, type);
    for (auto &user : users) {
        if (user.username == currentUsername) {
            for (auto it = user.memberships.begin(); it != user.memberships.end(); ++it) {
                if (it->type == type) {
                    user.memberships.erase(it);
                    saveUsersToFile();
                    cout << "Membership berhasil dibatalkan.\n";
                    return;
                }
            }
        }
    }
    cout << "Membership tidak ditemukan.\n";
}

void manageAccount(string currentUsername) {
    string newPassword;
    cout << "Masukkan password baru: ";
    cin.ignore();
    getline(cin, newPassword);
    for (auto &user : users) {
        if (user.username == currentUsername) {
            user.password = newPassword;
            saveUsersToFile();
            cout << "Password berhasil diperbarui.\n";
            return;
        }
    }
}

void displayMenu() {
    cout << "\n===============================================\n";
    cout << "|                 Gym Membership              |\n";
    cout << "===============================================\n";
    cout << "1. Sign Up \n";
    cout << "2. Sign In \n";
    cout << "0. Keluar\n";
    cout << "===============================================\n";
    cout << "|            SILAKAN PILIH MENU ANDA           |\n";
    cout << "===============================================\n";
}

void displayInitialMenu() {
    cout << "\n===============================================\n";
    cout << "|                 Gym Membership              |\n";
    cout << "===============================================\n";
    cout << "1. Sign In \n";
    cout << "2. Sign Up \n";
    cout << "0. Keluar\n";
    cout << "===============================================\n";
    cout << "|            SILAKAN PILIH MENU ANDA           |\n";
    cout << "===============================================\n";
}

void saveUsersToFile() {
    ofstream file("users.txt");
    if (file.is_open()) {
        for (const auto &user : users) {
            file << user.username << "\n" << user.password << "\n";
            for (const auto &membership : user.memberships) {
                file << membership.type << " " << membership.benefits << "\n";
            }
            file << "-\n";
        }
        file.close();
    } else {
        cout << "Gagal membuka file users.txt\n";
    }
}

void loadUsersFromFile() {
    ifstream file("users.txt");
    if (file.is_open()) {
        users.clear();
        string line;
        while (getline(file, line)) {
            if (line.empty()) continue;
            User user;
            user.username = line;
            getline(file, user.password);
            while (getline(file, line) && line != "-") {
                istringstream iss(line);
                Membership membership;
                iss >> membership.type >> membership.benefits;
                user.memberships.push_back(membership);
            }
            users.push_back(user);
        }
        file.close();
    } else {
        cout << "Gagal membuka file users.txt\n";
    }
}

void saveMembershipsToFile() {
    ofstream file("memberships.txt");
    if (file.is_open()) {
        for (const auto &membership : memberships) {
            file << membership.type << "\n" << membership.benefits << "\n" << membership.room << "\n" << membership.trainer << "\n" << membership.time << "\n" << membership.price << "\n";
        }
        file.close();
    } else {
        cout << "Gagal membuka file memberships.txt\n";
    }
}

void loadMembershipsFromFile() {
    ifstream file("memberships.txt");
    if (file.is_open()) {
        memberships.clear();
        string line;
        while (getline(file, line)) {
            if (line.empty()) continue;
            Membership membership;
            membership.type = line;
            getline(file, membership.benefits);
            getline(file, membership.room);
            getline(file, membership.trainer);
            getline(file, membership.time);
            getline(file, line);
            membership.price = stod(line);
            memberships.push_back(membership);
        }
        file.close();
    } else {
        cout << "Gagal membuka file memberships.txt\n";
    }
}

void viewMemberList() {
    cout << "Daftar Member:\n";
    for (const auto &user : users) {
        for (const auto &membership : user.memberships) {
            cout << "Tipe Membership: " << membership.type << ", Nama Member: " << user.username << "\n";
        }
    }
    cout << "Tekan Enter untuk melanjutkan...";
    cin.ignore();
    cin.get();
}