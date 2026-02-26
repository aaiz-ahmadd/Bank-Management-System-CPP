#include <iostream>

using namespace std;

void copyArray(char dest[], char src[]){
    int i = 0;
    while(src[i] != '\0'){
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

class BankAccount{
    int account_number;
    char owner_name[50];
    double balance;
    public:
        void setAccount(int acc_no, char owner[], double bal){
            account_number = acc_no;
            copyArray(owner_name, owner);
            balance = bal;
        }
        int deposit(double cash){
            if(cash >= 0){
                balance += cash;
                return 1;
            }
            if(cash < 0)
                return 0;
            return 0;
        }
        int withdraw(double cash){
            if(balance >= cash){
                balance -= cash;
                return 1;
            }
            if(balance < 0)
                return 0;
            return 0;
        }
        int getAccountNumber(){
            return account_number;
        }
        double getBalance(){
            return balance;
        }
        char* getOwnerName(){
            return owner_name;
        }
        void display(){
            cout << owner_name << "\t" << account_number << "\t" << balance << endl;
        }
};

class Bank{
    BankAccount* accounts;
    int total_accounts;
    int capacity;
    public:
        Bank(int cap){
            capacity = cap;
            total_accounts = 0;
            accounts = new BankAccount[capacity];
        }
        Bank(const Bank &other){
            this->capacity = other.capacity;
            this->total_accounts = other.total_accounts;

            // Allocate new memory
            this->accounts = new BankAccount[capacity];

            // Copy each account object
            for(int i = 0; i < total_accounts; i++){
                this->accounts[i] = other.accounts[i];
    }
}
        int addAccount(BankAccount acc){
            if(total_accounts >= capacity)
                return 0;
            for(int i = 0; i < total_accounts; i++){
                if(accounts[i].getAccountNumber() == acc.getAccountNumber())
                    return 0;
            }
            accounts[total_accounts++] = acc;
            return 1;
        }
        int findAccount(int acc_no){
            for(int i = 0; i < total_accounts; i++){
                if(accounts[i].getAccountNumber() == acc_no){
                    return i;
                }
            }
            return -1;
        }
        int depositToAccount(int acc_no, double cash){
            int idx = findAccount(acc_no);
            if(idx == -1)
                return 0;
            return accounts[idx].deposit(cash);
        }
        int withdrawFromAccount(int acc_no, double cash){
            int idx = findAccount(acc_no);
            if(idx == -1)
                return 0;
            
            return accounts[idx].withdraw(cash);
        }
        int transfer(int from_acc, int to_acc, double cash){
            int sender_acc = findAccount(from_acc);
            if(sender_acc == -1)
                return 0;
            int rec_acc = findAccount(to_acc);
            if(rec_acc == -1)
                return 0;
            if(!withdrawFromAccount(from_acc, cash))
                return 0;
            depositToAccount(to_acc, cash);
            return 1;
        }
        void displayAllAccounts(){
            for(int i = 0; i < total_accounts; i++){
                accounts[i].display();
            }
        }
        ~Bank(){
            delete [] accounts;
        }
};

void menu(){
    cout << "\n--- BANK MENU ---\n";
    cout << "1. Add Account\n";
    cout << "2. Deposit\n";
    cout << "3. Withdraw\n";
    cout << "4. Transfer\n";
    cout << "5. Display All Accounts\n";
    cout << "0. Exit\n";
    cout << "Enter your choice: ";
}

int main(){
    double amount;
    int total_accounts, acc_number;
    char name[50];
    cout << "Enter total number of Accounts: ";
    cin >> total_accounts;
    Bank bank(total_accounts);
    BankAccount acc[total_accounts];
    int choice;

    do{
        menu();
        cin >> choice;

        if(choice == 1){
            for(int i = 0; i < total_accounts; i++){
                cout << "Enter Account number: ";
                cin >> acc_number;
                cin.ignore();
                cout << "Enter owner name: ";
                cin.getline(name, 50);
                cout << "Enter Amount: ";
                cin >> amount;
                acc[i].setAccount(acc_number, name, amount);
            }

            for(int i = 0; i < total_accounts; i++){
                if(bank.addAccount(acc[i]) > 0)
                    cout << "Account added Successfully!" << endl;
                else
                    cout << "Err: Bank capacity reached or Account Number Duplication!" << endl;
            }
        }
        else if(choice == 2){
            cout << "Enter Account NO: ";
            cin >> acc_number;
            cout << "Enter amount to deposit: ";
            cin >> amount;

            if(bank.depositToAccount(acc_number, amount) > 0){
                cout << "Deposit successful!" << endl;
                cout << "Results after Deposit: " << endl;
                bank.displayAllAccounts();
            }
            else
                cout << "Deposit Failed!" << endl;
        } 
        else if(choice == 3){
            cout << "Enter Account NO: ";
            cin >> acc_number;
            cout << "Enter amount to withdraw: ";
            cin >> amount;
            if(amount <= 0){
                cout << "Amount should be greater than 0" << endl;
                continue;
            }

            if(bank.withdrawFromAccount(acc_number, amount) > 0){
                cout << "Withrawal Successful!" << endl;
                cout << "Results after Withdrawal: " << endl;
                bank.displayAllAccounts();
            }
            else
                cout << "Withdrawal Unsuccessful!" << endl;
        }
        else if(choice == 4){
            int src_acc, dsc_acc;
            cout << "Enter Source & Dest. Accounts: ";
            cin >> src_acc >> dsc_acc;
            cout << "Enter Amount to Transfer: ";
            cin >> amount;
            if(amount <= 0){
                cout << "Amount should be greater than 0" << endl;
                continue;
            }

            if(bank.transfer(src_acc, dsc_acc, amount) > 0){
                cout << "Transfer Successful!" << endl;
                cout << "Results after Transfer: " << endl;
                bank.displayAllAccounts();
            }
            else
                cout << "Transfer Failed!" << endl;
        }
        else if(choice == 5){
            cout << "Displaying all Accounts: " << endl;
            bank.displayAllAccounts();
        }
        else if(choice == 0){
            cout << "Exiting....!" << endl;
        }
        else
            cout << "Invalid Option.... Try Again!!" << endl;
    }while(choice != 0);
    return 0;
}