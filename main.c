#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int main() {
    int choice;

    while (1) {
        display_menu();
        printf("Selectati o optiune: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Afisare cont");
                break;
            case 2:
                printf("Adaugare cont\n");
                break;
            case 3:
                printf("Stergere cont existent\n");
                break;
            case 4:
                printf("Depunere suma in cont\n");
                break;
            case 5:
                printf("Retragere suma in cont");
                break;
            case 6:
                printf("Cautare dupa numar de cont");
                break;
            case 7:
                printf("Cautare dupa numa de client");
                break;
            case 8:
                printf("La revedere!\n");
                exit(0);
            default:
                printf("Opțiune invalidă!\n");
        }
    }

    return 0;
}
