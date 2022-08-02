#include <stdio.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
using namespace std;

class Account
{
    public:
    long int acc_no;
    char name[30];
    float balance;
    public:
    void accept()
    {
        cout<<endl<<"Enter account number"<<endl;
        cin>>acc_no;
        cout<<endl<<"Enter name"<<endl;
        cin>>name;
        cout<<endl<<"Enter balance"<<endl;
        cin>>balance;
        cout<<"Account Created...";
    }
    void display()
    {
        cout<<endl<<acc_no<<"\t"<<name<<"\t"<<balance;
    }
};

int main()
{
    int ch;
    fstream f,f2;
   
    while(1)
    {
        cout<<endl<<"** Main Menu **";
        cout<<endl<<"1. Create New Account";        
        cout<<endl<<"2. Display Accounts";
        cout<<endl<<"3. Deposit";
        cout<<endl<<"4. Withdraw";
        cout<<endl<<"5. Delete Account";
        cout<<endl<<"6. Exit";
        cout<<endl<<"Enter your choice"<<endl;
        cin>>ch;
        switch(ch)
        {
            case 1: 
                    {
                        Account ob1;
                        ob1.accept();
                    
                        f.open("Bank_records.dat",ios::out | ios::app);
                        f.write((char *)&ob1,sizeof(ob1));
                        f.close();
                    }
                    break;
            case 2:
                    {
                        Account ob2;
                        f.open("Bank_records.dat",ios::in);
                        f.seekg(0,ios::beg);
                    
                        cout<<endl<<"** Accountants in Bank ***";
                        while(f.read((char *)&ob2,sizeof(ob2))){
                        ob2.display();
                        
                        }
                        f.close();
                    }
                    break;
                    
            case 3: {
                        long int an;
                        int amt;
                        cout<<endl<<"Enter account number"<<endl;
                        cin>>an;
                        cout<<endl<<"Enter amount to deposit"<<endl;
                        cin>>amt;

                        Account ob3;
                        f.open("Bank_records.dat",ios::in|ios::out);
                        f.seekg(0,ios::beg);
                    
                        int counter=0;
                            while(f.read((char *)&ob3,sizeof(ob3))){
                            if(ob3.acc_no==an)
                            {
                            Account temp;
                            temp.acc_no=ob3.acc_no;
                            strcpy(temp.name,ob3.name);
                            temp.balance=ob3.balance+amt;
                            
                            f.seekp(-sizeof(ob3),ios::cur);
                            f.write((char *)&temp,sizeof(temp));
                            cout<<endl<<"Amout is deposited successfully";
                            break;
                            }
                        }
                        f.close();
                    }
                    break;
            
            case 4: {
                        long int an;
                        int amt;
                        cout<<endl<<"Enter account number"<<endl;
                        cin>>an;
                        cout<<endl<<"Enter amount to withdraw"<<endl;
                        cin>>amt;
                        
                        Account ob4;
                        f.open("Bank_records.dat",ios::in|ios::out);
                        f.seekg(0,ios::beg);
                    
                        int counter=0;
                    
                        while(f.read((char *)&ob4,sizeof(ob4)))
                        {
                            if(ob4.acc_no==an)
                            {
                            
                            
                            Account temp;
                            temp.acc_no=ob4.acc_no;
                            strcpy(temp.name,ob4.name);
                            
                            if(amt>ob4.balance)
                            {
                                cout<<endl<<"Insufficient balance";
                                break;
                            }
                            else
                            {
                                temp.balance=ob4.balance-amt;
                            
                            
                                f.seekp(-sizeof(ob4),ios::cur);
                                f.write((char *)&temp,sizeof(temp));
                                cout<<"\n"<<"Amount withdrawl successfully...";
                                break;
                            }
                            }
                        }
                        f.close();
                    }
                    break;
            case 5: {
                        long int an;
                        
                        cout<<endl<<"Enter account number"<<endl;
                        cin>>an;
                       
                        f2.open("temp.dat",ios::out | ios::app);
                        
                        
                        Account ob4;
                        f.open("Bank_records.dat",ios::in|ios::out);
                        f.seekg(0,ios::beg);
                    
                       
                        int counter=0;
                    
                        while(f.read((char *)&ob4,sizeof(ob4)))
                        {
                            if(ob4.acc_no==an)
                            {
                                cout<<endl<<"Account deleted successfully...";
                            }
                            else
                            {
                                Account temp;
                                temp.acc_no=ob4.acc_no;
                                strcpy(temp.name,ob4.name);
                                temp.balance=ob4.balance;
                            
                            
                                f2.write((char *)&temp,sizeof(temp));
                                
                            }
                            
                        }
                        f2.close();
                        f.close();
                        
                        remove("Bank_records.dat");
                        rename("temp.dat", "Bank_records.dat");
                    }
                    break;
            case 6:exit(0);
            default:cout<<endl<<"Wrong choice";
        
            
        }
    }
    
    return 0;
}