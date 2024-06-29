#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

void login();
void regis();
void forgot();


int main() {
        int c;
        
        cout<<"-----------------------------------------"<<endl;
        cout<<"                 Dashbord                "<<endl;
        cout<<"-----------------------------------------"<<endl;
        cout<<"\t1. Sign In"<<endl;
        cout<<"\t2. Sign Up"<<endl;
        cout<<"\t3. Forgot Password"<<endl;
        cout<<"\nMasukan Pilihan: "<<endl;
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
                forgot();
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