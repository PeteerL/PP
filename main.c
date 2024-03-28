#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ACCOUNTS 100

void clear_screen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

typedef struct {
    char account_num[20];
    char customer_name[50];
    float balance;
} Account;

typedef struct {
    Account accounts[MAX_ACCOUNTS];
    int count;
} BankSystem;

void display_menu() {
    printf("\nMeniu Principal:\n");
    printf("1. Afisare conturi\n");
    printf("2. Adaugare cont nou\n");
    printf("3. Stergere cont existent\n");
    printf("4. Depunere suma in cont\n");
    printf("5. Retragere suma din cont\n");
    printf("6. Cautare dupa numar de cont\n");
    printf("7. Cautare dupa nume de client\n");
    printf("8. Iesire\n");
}

void display_accounts(Account accounts[], int count) {
    printf("\nConturi:\n");
    for (int i = 0; i < count; ++i) {
        printf("Numar cont: %s, Nume client: %s, Sold: %.2f\n", accounts[i].account_num, accounts[i].customer_name, accounts[i].balance);
    }
}

void add_account(Account accounts[], int *count) {
    if (*count >= MAX_ACCOUNTS) {
        printf("Nu se mai pot adauga conturi. Limita maximă a fost atinsa.\n");
        return;
    }

    printf("Introduceti numarul de cont nou: ");
    scanf("%s", accounts[*count].account_num);
    printf("Introduceti numele clientului: ");
    scanf("%s", accounts[*count].customer_name);
    accounts[*count].balance = 0.0;

    (*count)++;
    printf("Contul a fost adaugat cu succes!\n");
}

void delete_account(Account accounts[], int *count) {
    char account_num[20];
    printf("Introduceti numarul de cont de sters: ");
    scanf("%s", account_num);

    int found = 0;
    for (int i = 0; i < *count; ++i) {
        if (strcmp(accounts[i].account_num, account_num) == 0) {
            found = 1;
            for (int j = i; j < *count - 1; ++j) {
                accounts[j] = accounts[j + 1];
            }
            (*count)--;
            printf("Contul a fost sters cu succes!\n");
            break;
        }
    }

    if (!found) {
        printf("Numar de cont inexistent!\n");
    }
}

void deposit(Account accounts[], int count, char account_num[], float amount) {
    for (int i = 0; i < count; ++i) {
        if (strcmp(accounts[i].account_num, account_num) == 0) {
            accounts[i].balance += amount;
            printf("Suma de %.2f a fost depusa cu succes in contul %s.\n", amount, account_num);
            return;
        }
    }
    printf("Numar de cont inexistent!\n");
}

void withdraw(Account accounts[], int count, char account_num[], float amount) {
    for (int i = 0; i < count; ++i) {
        if (strcmp(accounts[i].account_num, account_num) == 0) {
            if (accounts[i].balance >= amount) {
                accounts[i].balance -= amount;
                printf("Suma de %.2f a fost retrasa cu succes din contul %s.\n", amount, account_num);
            } else {
                printf("Fonduri insuficiente în contul %s.\n", account_num);
            }
            return;
        }
    }
    printf("Numar de cont inexistent!\n");
}

void search_by_account_number(Account accounts[], int count, char account_num[]) {
    for (int i = 0; i < count; ++i) {
        if (strcmp(accounts[i].account_num, account_num) == 0) {
            printf("Numele clientului asociat cu contul %s este: %s\n", account_num, accounts[i].customer_name);
            return;
        }
    }
    printf("Numar de cont inexistent!\n");
}

void search_by_customer_name(Account accounts[], int count, char customer_name[]) {
    int found = 0;
    for (int i = 0; i < count; ++i) {
        if (strcmp(accounts[i].customer_name, customer_name) == 0) {
            printf("Contul asociat cu clientul %s este: %s\n", customer_name, accounts[i].account_num);
            found = 1;
        }
    }
    if (!found) {
        printf("Niciun cont asociat acestui nume de client!\n");
    }
}
void back_to_menu() {
    printf("\nApasa orice tasta pentru a reveni la meniul principal...");
    getchar();
    getchar();
    clear_screen();
    display_menu();
}
void readFile(Account accounts[100], int i){
    FILE *f = fopen("accounts.txt", "r");
    if (f == NULL)
        return;
    while (fscanf(f, "%d %s %d", &accounts[i].account_num, &accounts[i].customer_name, &accounts[i].balance ) == 3)
        (i)++;
    fclose(f);
}

void writeFile(Account * accounts, int n){
    FILE *f = fopen("accounts.txt", "w");
    for(int i=0; i<n; i++)
        fprintf(f, "%d %s %d\n", accounts[i].account_num, accounts[i].customer_name, accounts[i].balance );
    fclose(f);
}
/*    Account accounts[100];
    int n = 0;
    int count;
    readFile(accounts, &n);
    accounts[n] = count;
    n++;
    writeFile(accounts, n);
*/
int main() {
    BankSystem bank_system;
    bank_system.count = 0;
    int choice;

    do {
        display_menu();
        printf("Selectati o optiune: ");
        scanf("%d", &choice);


        switch (choice) {
            case 1:
                display_accounts(bank_system.accounts, bank_system.count);
                back_to_menu();
                break;
            case 2:
                add_account(bank_system.accounts, &bank_system.count);
                back_to_menu();
                break;
            case 3:
                delete_account(bank_system.accounts, &bank_system.count);
                back_to_menu();
                break;
            case 4: {
                char account_num[20];
                float amount;
                printf("Introduceti numarul de cont pentru depunere: ");
                scanf("%s", account_num);
                printf("Introduceti suma de depus: ");
                scanf("%f", &amount);
                deposit(bank_system.accounts, bank_system.count, account_num, amount);
                back_to_menu();
                break;
            }
            case 5: {
                char account_num[20];
                float amount;
                printf("Introduceti numarul de cont pentru retragere: ");
                scanf("%s", account_num);
                printf("Introduceti suma de retras: ");
                scanf("%f", &amount);
                withdraw(bank_system.accounts, bank_system.count, account_num, amount);
                back_to_menu();
                break;
            }
            case 6: {
                char account_num[20];
                printf("Introduceti numarul de cont de cautat: ");
                scanf("%s", account_num);
                search_by_account_number(bank_system.accounts, bank_system.count, account_num);
                back_to_menu();
                break;
            }
            case 7: {
                char customer_name[50];
                printf("Introduceti numele clientului de cautat: ");
                scanf("%s", customer_name);
                search_by_customer_name(bank_system.accounts, bank_system.count, customer_name);
                back_to_menu();
                break;
            }
            case 8:
                printf("La revedere!\n");
                return 0;
        }
    } while (1);
}
