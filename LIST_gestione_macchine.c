/* PROGRAMMA UGUALE A QUELLO DI ARRAY MA FUNZIONA CON LE LISTE, PUNTATORI, ALLOCAZIONE DI MEMORIA E ALTRO (vedi README) */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// definisco un tipo "Macchina" in modo da non dover scrivere sempre "struct Macchina"
typedef struct Macchina {
    int codice;
    char scopo[25];
    float tensione, corrente;
} Macchina;

// definisco un tipo "Nodo" perchè mi serve quando uso la lista e non gli array
typedef struct Nodo {
    Macchina dati;
    struct Nodo *next;
} Nodo;

//usato per la parte estetica, crea una fila orizzontale di righe
void linee () {
    int i, N=40;

    for (i=0; i<N; i++) {
        if (i!=N-1) {
            printf("-");
        }
        else {
            printf("-\n");
        }
    }
}

// prendo tutto ciò che è stato scritto di extra e lo ripulisco per evitare errori di buffering. getchar ha come return value un int
void clear_buffer () {
    int c;
    while ((c=getchar())!='\n' && c!= EOF);
}

// acquisico valori int
int acq_int (int mess) {
    int x, risultato;
    
    // messaggi per le varie casistiche
    switch (mess) {
        case 0: printf("Scegliere un'opzione fornendo il numero:\n0. Visualizza tutte le macchine con tutte le informazioni\n1. Salvare le nuove macchine in memoria\n2. Cancellare una Macchina a scelta dalla memoria\n3. Visualizzare i dati di una Macchina fornendo il codice\n4. Aggiungere una nuova Macchina\n5. Modificare un campo di una Macchina in memoria\n6. Visualizzare che Macchina ha potenza maggiore\n7. Fine Programma\n");
        break;
        case 1: printf("Fornisci il numero effettivo delle macchine [numero intero positivo]\n");
        break;
        case 2: printf("Fornisci codice della Macchina [numero intero]\n");
        break;
        case 3: printf("Fornisci codice della Macchina nuova [numero intero]\n");
        break;
        case 4: printf("Scegliere tra le seguenti opzioni:\n1. Riprendere le macchine precedentemente salvate nella memoria\n2. Inserire macchine da zero\n");
        break;
        case 5: printf("Fornisci la riga da cancellare dal file [numero intero]\n");
        break;
        case 6: printf("Fornisci codice della Macchina alla quale si vuole modificare un campo [numero intero]\n");
        break;
        case 7: printf("Selezionare che campo si vuole modificare:\n1. Scopo\n2. Tensione\n3. Corrente\n4. Fine modifica\n");
        break;
        case 8: printf("Decidere in che modo far lavorare il programma:\n1. Array\n2. Liste\n");
        break;
        default: printf("Fornisci un valore intero\n");
    }

    // prendo e controllo all'infinito il valore preso fino a che non è effettivamente un int
    while (1) {
        risultato = scanf("%d", &x);

        if (risultato==1) {
            char extra;

            if (scanf("%c", &extra)==1 && extra!='\n') {
                printf("Inserire valore valido: valore inserito non è un valore intero\n");
                clear_buffer();
            }
            else {
                break;
            }
        }
        else {
            printf("Inserire valore valido: valore inserito non è un valore intero\n");
            clear_buffer();
        }
    }

    return x;
}

// acquisico string per la struct
void acq_string_struct(Macchina *M, int mess) {
    // messaggi per le varie casistiche
    switch (mess) {
        case 0: printf("Fornisci lo scopo della Macchina [stringa, 1 sola parola]\n");
        break; 
        case 1: printf("Fornisci lo scopo della Macchina nuova [stringa, 1 sola parola]\n");
        break; 
        default: printf("Fornisci una stringa\n");
    }

    scanf("%24s", M->scopo);
}

// acquisisco una stringa
void acq_string(char *x, int mess) {
    // messaggi per le varie casistiche
    switch (mess) {
        case 0: printf("Fornisci il nuovo scopo della Macchina [stringa, 1 sola parola]\n");
        break;
        default: printf("Fornisci una stringa\n");
    }

    scanf("%24s", x);
}

// acquisisco valori float
float acq_float (int mess) {
    float x;
    int risultato;
    
    // messaggi per le varie casistiche
    switch (mess) {
        case 0: printf("Fornisci la tensione della Macchina [numero reale, in V]\n");
        break;
        case 1: printf("Fornisci la corrente della Macchina [numero reale, in A]\n");
        break;
        case 2: printf("Fornisci la tensione della Macchina nuova [numero reale, in V]\n");
        break;
        case 3: printf("Fornisci la corrente della Macchina nuova [numero reale, in A]\n");
        break;
        case 4: printf("Fornisci la nuova tensione della Macchina [numero reale, in V]\n");
        break;
        case 5: printf("Fornisci la nuova corrente della Macchina [numero reale, in A]\n");
        break;
        default: printf("Fornisci numero reale\n");
    }

    // prendo e controllo all'infinito il valore preso fino a che non è effettivamente un float
    while (1) {
        risultato = scanf("%f", &x);

        if (risultato==1) {
            char extra;

            if (scanf("%c", &extra)==1 && extra!='\n') {
                printf("Inserire valore valido: valore inserito non è un valore reale\n");
                clear_buffer();
            }
            else {
                break;
            }
        }
        else {
            printf("Inserire valore valido: valore inserito non è un valore reale\n");
            clear_buffer();
        }
    }

    return x;
}

// acquisisco un char
char acq_char (int mess) {
    char x;
    int risultato;

    // messaggi per le varie casistiche
    switch (mess) {
        case 1: printf("Vuoi visualizzare tutti i codici possibili? [Y/N]\n");
        break;
        case 2: printf("Vuoi salvare tutte le macchine compresa quest'ultima Macchina aggiunta in memoria? [Y/N]\n");
        break;
        case 3: printf("Vuoi aggiungere un'altra Macchina? [Y/N]\n");
        break;
        default: printf("Fornisci un carattere letterale\n");
    }

    // prendo e controllo all'infinito il valore preso fino a che non è effettivamente un char
    while (1) {
        risultato = scanf(" %c", &x);

        if (risultato==1) {
            char extra;

            if (scanf("%c", &extra)==1 && extra!='\n') {
                printf("Inserire valore valido: valore inserito non è un carattere lettera\n");
                clear_buffer();
            }
            // devo controllare se sono effettivamente le lettere che voglio in certi casi
            else {
                if (mess==1 || mess==2 || mess==3) {
                    if (x!='y' && x!='Y' && x!='n' && x!='N') {
                        printf("Inserire valore valido: non è stata inserita una scelta possibile\n");
                    }
                    else {
                        return toupper(x);
                    }
                }
                else {
                    return x;
                }
            }
        }
        else {
            printf("Inserire valore valido: valore inserito non è un carattere lettera\n");
            clear_buffer();
        }
    }
}

// funzione per leggere le macchine da un file e inserirle in una lista
Nodo* copy_lista_su_programma (char *nome_file, int elementi_struct, int *N, int *controllo) {
    int flag=0;
    
    // apro il file in modalità "read"
    FILE *file=fopen(nome_file, "r");
    if (file == NULL) {
        perror("Errore nell'apertura del file\n");
        *controllo=0;
        return NULL;
    }

    // inizzializzo il puntatore iniziale e finale che saranno entrambi NULL perchè quello alla fine lo è per definizione e quello all'inizio perchè all'inizio sul programma non c'è salvato nulla
    Nodo* testa=NULL;
    Nodo* ultimo=NULL;

    // acquisisco i valori fino a che non arrivo a EOF nel file di memoria
    while (!feof(file)) {
        Macchina nuova_macchina;
        
        // acquisisco i nuovi valori dal file di memoria e controllo se sono stati presi degli elementi o meno
        int letti=fscanf(file, "%d %24s %f %f", &nuova_macchina.codice, nuova_macchina.scopo, &nuova_macchina.tensione, &nuova_macchina.corrente);
        printf("LETTI: %d\n", letti);
        if (letti==elementi_struct) {
            flag=1;
            
            // alloco della memoria nuova per i nuovi dati che ho preso
            Nodo* nuovo_nodo=(Nodo*)malloc(sizeof(Nodo));
            if (nuovo_nodo==NULL) {
                printf("Errore di allocazione della memoria\n");
                break;
            }

            // imposto i dati nuovi nella macchina nel nodo insieme al puntatore "next" e aumento il numero di macchine presenti
            nuovo_nodo->dati=nuova_macchina;
            nuovo_nodo->next=NULL;
            (*N)++;

            printf("N: %d\n", *N);

            // controllo per valutare se è il primo valore del file che sto acquisendo, quindi per il primo valore della lista e per la prima riga della memoria
            if (testa==NULL) {
                testa=nuovo_nodo;
                ultimo=nuovo_nodo;
            }
            // questo è dalla 2a macchina in poi
            else {
                ultimo->next=nuovo_nodo;
                ultimo=nuovo_nodo;
            }
        }
        // se non sono stati presi i valori prima
        else if (flag==0) {
            printf("Errore nella lettura dei dati dal file\n");
            *controllo=0;
            break;
        }
    }

    // chiudo il file
    fclose(file);
    return testa;
}

// acquisisce la variabile N
int acq_num_macchine (int dim_struct) {
    int N; 
    do {
        N=acq_int(1);
    } while (N<=0 || N>dim_struct);
}

void stampa_lista (Nodo* testa) {
    Nodo* current=testa;
    int i=1;

    while (current!=NULL) {
        printf("MACCHINA %d\n - Codice: %d\n - Scopo: %s\n - Tensione = %f V\n - Corrente = %f A\n", i, current->dati.codice, current->dati.scopo, current->dati.tensione, current->dati.corrente);
        i++;
        current=current->next;
    }
}


int main () {
    int scelta, N, i=0, controllo=0, elementi_struct=4, contr_sort=0;

    Nodo* Lista = NULL;

    FILE *mem_point;
    char file_memoria[21]="memoria_macchine.txt", sort_save;

    // loop per acquisizione iniziale delle macchine
    while (controllo==0) {
        scelta=acq_int(4);

        linee();

        switch (scelta) {
            case 1: {
                /* RIPRENDERE LE MACCHINE PRECEDENTEMENTE SALVATE NELLA MEMORIA */
                controllo=1;
                N=0;

                Lista=copy_lista_su_programma(file_memoria, elementi_struct, &N, &controllo);

                // controllo se il file "memoria_macchine.txt" è vuoto
                if (N==0) {
                    printf("Impossibile riprendere i dati: il file di memoria non presenta alcun dato disponibile\nÈ necessario reimpostare i dati selezionando la 2a opzione dal menù\n");
                    controllo=0;
                }
                else if (controllo!=0) {
                    printf("Valori ripristinati correttamente\n");
                }

                linee();
            }
            break; 
            
            default: {
                printf("Inserire una scelta valida\n");
            }
        }
    }

    // faccio partire il menù principale con le varie opzioni
    do {
        scelta=acq_int(0);

        linee();

        switch (scelta) {
            case 0: {
                /* VISUALIZZA TUTTE LE MACCHINE CON TUTTE LE INFORMAZIONI */
                printf("Ci sono un totale di %d macchine\n", N);
                
                stampa_lista(Lista);

                linee();
            }
            break;
        }
    } while (scelta!=7);

    return 0;
}