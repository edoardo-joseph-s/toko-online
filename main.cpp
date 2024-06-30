#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

void login();
void regis();
void reset();

int main() {
        int c;
        
        cout<<"-----------------------------------------"<<endl;
        cout<<"                 Dashbord                "<<endl;
        cout<<"-----------------------------------------"<<endl;
        cout<<"\t1. Sign In"<<endl;
        cout<<"\t2. Sign Up"<<endl;
        cout<<"\t3. Forgot Password"<<endl;
        cout<<"\nMasukan Pilihan: ";
        cin>>c;

        switch (c)
        {
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
                cout<<"Masukan pilihan yang benar"<<endl;
                main();
        }
}

void login()
{
        int count;
        string userId, password, id, pass;
        system("cls");
        cout<<"-----------------------------------------"<<endl;
        cout<<"                   Login                 "<<endl;
        cout<<"-----------------------------------------\n"<<endl;
        cout<<"Username\t: ";
        cin>>userId;
        cout<<"Password\t: ";
        cin>>password;

        ifstream input("records.txt");

        while (input>>id>>pass)
        {
                if(id==userId && pass ==password)
                {
                        count=1;
                        system("cls");
                }
                input.close();

                if (count==1)
                {
                        cout<<userId<<"Login Berhasil"<<endl;
                        main();
                }
                else{
                        cout<<"Sign In dulu baru Login"<<endl;
                }
        }

}

void regis()
{
        string ruserId, rpassword, rid, rpass;

        system("cls");
        cout<<"-----------------------------------------"<<endl;
        cout<<"                 Registrasi              "<<endl;
        cout<<"-----------------------------------------"<<endl;
        cout<<"Masukan Username: ";
        cin>>ruserId;
        cout<<"Masukan Password: ";
        cin>>rpassword;

        ofstream f1("records.txt", ios::app);
        f1<<ruserId<<' '<<rpassword<<endl;
        
        system("cls");
        cout<<"Registrasi berhasil"<<endl;
        main();
}

// ganti password

void reset()
{
        int option;
        system("cls");
        cout<<"-----------------------------------------"<<endl;
        cout<<"                Reset Password           "<<endl;
        cout<<"-----------------------------------------"<<endl;
        cout<<"1. Cari Id by Username"<<endl;
        cout<<"2. Kembali ke menu"<<endl;
        cout<<"Masukan pilihan: ";
        cin>>option;
        
        switch (option)
        {
        case 1:
        {
                int count=0;
                string suserId,sId,spass;
                cout<<"Masukan Username: ";
                cin>>suserId;
                
                ifstream f2("records.txt");
                while(f2>>sId>>spass)
                {
                        if(sId==suserId)
                        {
                                count=1;
                        }
                }
                f2.close();
                if(count==1)
                {
                        cout<<"Akun di temukan"<<endl;
                        cout<<"Passow kamu adalah: "<<spass;
                        main();
                }
                else{
                        cout<<"Maff akun kamu tidak ditemukan"<<endl;
                }
                break;
        }
        case 2:
        {
                main();
                }        
        default:
                cout<<"Pilihan salah, tolong masukan lagi"<<endl;
                reset();
                break;
        }
        
}