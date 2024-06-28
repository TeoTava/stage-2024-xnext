/* PROGRAMMA UGUALE A QUELLO DI ARRAY MA FUNZIONA CON LE LISTE, PUNTATORI, ALLOCAZIONE DI MEMORIA E ALTRO (vedi README) */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// questo prende dall'header file "struct_Macchine.h" la definizione della struttura, in modo che posso usarla anche per l'altro file .c dato che tanto sono identiche le definizioni
#include "struct_Macchine.h"

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
        case 0: printf("Scegliere un'opzione fornendo il numero:\n0. Visualizza tutte le macchine con tutte le informazioni\n1. Salvare le nuove macchine in memoria\n2. Cancellare una macchina a scelta dalla memoria\n3. Visualizzare i dati di una macchina fornendo il codice\n4. Aggiungere una nuova macchina\n5. Modificare un campo di una macchina in memoria\n6. Visualizzare che macchina ha potenza maggiore\n7. Fine Programma\n");
        break;
        case 1: printf("Fornisci codice della macchina [numero intero]\n");
        break;
        case 2: printf("Scegliere tra le seguenti opzioni:\n1. Riprendere le macchine precedentemente salvate nella memoria\n2. Inserire macchine da zero\n");
        break;
        case 3: printf("Fornisci la riga da cancellare dal file [numero intero]\n");
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

// acquisisco una stringa
void acq_string(char *x, int mess) {
    // messaggi per le varie casistiche
    switch (mess) {
        case 0: printf("Fornisci lo scopo della macchina [stringa, 1 sola parola]\n");
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
        case 0: printf("Fornisci la tensione della macchina [numero reale, in V]\n");
        break;
        case 1: printf("Fornisci la corrente della macchina [numero reale, in A]\n");
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
        case 0: printf("Vuoi aggiungere un'altra macchina? [Y/N]\n");
        break;
        case 1: printf("Vuoi visualizzare tutti i codici possibili? [Y/N]\n");
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
                if (mess==0 || mess==1) {
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

// funzione per aggiungere alla lista presente nel programma un certo numero non definito di macchine
Nodo* inserimento_macchine_su_lista (int *N) {
    char ins='Y';
    Macchina nuova_macchina;

    // inizzializzo il puntatore iniziale e finale che saranno entrambi NULL perchè quello alla fine lo è per definizione e quello all'inizio perchè all'inizio sul programma non c'è salvato nulla
    Nodo* testa=NULL;
    Nodo* ultimo=NULL;

    while (ins=='Y') {
        // acquisisco le varie informazioni della struct
        printf("MACCHINA %d:\n", (*N)+1);
        
        nuova_macchina.codice=acq_int(1);
        acq_string(nuova_macchina.scopo, 0);
        nuova_macchina.tensione=acq_float(0);
        nuova_macchina.corrente=acq_float(1);

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

        // prendo un nuovo valore in modo da poter prendere infinite macchine fino a che l'utente non inserisce 'N'
        ins=acq_char(0);
    }

    return testa;
}

// ramificazione della funzione "bubble_sort", serve per scambiare l'ordine dei nodi
Nodo* scambia (Nodo* p1, Nodo* p2) {
    Nodo* temp=p2->next;
    p2->next=p1;
    p1->next=temp;

    return p2;
}

// algoritmo di Bubble Sorting per le liste (è uguale il concetto a quello degli array, cambia solo la sintassi e il fatto che si lavora non con le posizioni "i" ma con i puntatori)
void bubble_sort (Nodo** testa, int N, int *contr_sort) {
    Nodo** T;
    int i, j, cambio;

    for (i=0; i<N; i++) {
        T=testa;
        cambio=0;

        for (j=0; j<N-i-1; j++) {
            Nodo* p1=*T;
            Nodo* p2=(*T)->next;

            if (p1->dati.codice>p2->dati.codice) {
                *T=scambia(p1, p2);
                cambio=1;
                (*contr_sort)=1;
            }

            T=&(*T)->next;
        }

        if (cambio==0) {
            break;
        }
    }
}

// funzione per salvare dal programma tutte le informazioni acquisite al file "gestione_macchine.txt"
void salvataggio_file (Nodo* testa, char *nome_file) {
    // apro il file in modalità "write"
    FILE* file=fopen(nome_file, "w");
    if (file==NULL) {
        printf("Errore di apertura del file\n");
        return;
    }

    // scorro per la lista e salvo tutto sul file
    Nodo* current=testa;
    while (current!=NULL) {
        fprintf(file, "%d %s %f %f\n", current->dati.codice, current->dati.scopo, current->dati.tensione, current->dati.corrente);
        current=current->next;
    }

    // chiudo il file
    fclose(file);
    printf("Elementi salvati in \"%s\" correttamente\n", nome_file);
}

// funzione per visualizzare tutti i campi della lista
void stampa_lista (Nodo* testa) {
    Nodo* current=testa;
    int i=1;

    while (current!=NULL) {
        printf("MACCHINA %d\n - Codice: %d\n - Scopo: %s\n - Tensione = %f V\n - Corrente = %f A\n", i, current->dati.codice, current->dati.scopo, current->dati.tensione, current->dati.corrente);
        i++;
        current=current->next;
    }
}

// prima parte della cancellazione dove si vedono tutte le macchine con le righe e bisogna effettuare la scelta di quale riga cancellare
int visualizzazione_pre_cancellazione (int N, FILE *point, char *nome_file) {
    char ch;
    int canc, j=1, flag=0;
    float grand_file;

    // apro il file in modalità "read"
    point = fopen (nome_file, "r");
    if (point==NULL) {
        printf("Errore nell'apertura del file\n");
        return -2;
    }
                
    // guardo quanto effettivamente grande è il file che ho
    fseek(point, 0, SEEK_END);
    grand_file=ftell(point);
    rewind(point);

    // se il file dentro di sè ha qualche macchina, allora ha senso mostrare i contenuti di tale file
    if (grand_file!=0) {
        printf("Contenuto attuale del file \"%s\" (numero all'inizio indica la riga del file, in ordine i valori sono per ogni macchina: codice, scopo, tensione, corrente):\n", nome_file);
        printf("%d)   ", j);
        j++;
        //faccio girare tutto il file printando lettera per lettera i suoi contenuti fino alla End-of-File (EOF)
        ch=getc(point);
        while (ch!=EOF) {
            if (j>N && ch=='\n') {
                printf("%c", ch);
            }
            else if (ch=='\n') {
                printf("\n%d)   ", j);
                j++;
            }
            else {
                printf("%c", ch);
            }
            ch=getc(point);
        }

        // mi faccio fornire la riga del file (quindi effettivamente la macchina) che l'utente vuole cancellare
        do {
            if (flag==0) {
                flag=1;
            }
            else {
                printf("Valore fornito non è una riga nel file\n");
            }
                        
            canc=acq_int(3);
        } while(canc>N);
        
        // chiudo il file ora anche se poi dovrò riaprirlo nella funzione dopo
        fclose(point);
        return canc;
    }
    else {
        return -1;
    }
}

// funzione dove avviene la cancellazione effettiva dell'elemento dal file
void cancellazione_da_lista (Nodo** testa, FILE *point, char *nome_file, int canc, int *N) {
    char file_temp[9] = "temp.txt", ch, scopo[25];
    int j=1, flag=0, codice;
    float tensione, corrente;
    
    // riapro il file in modalità "read"
    point = fopen (nome_file, "r");
    if (point==NULL) {
        printf("Errore nell'apertura del file\n");
        return;
    }

    // apro il file temporaneo in modalità "write"
    FILE *temp_point = fopen (file_temp, "w");
    if (temp_point==NULL) {
        printf("Errore nell'apertura del file temporaneo\n");
        return;
    }

    // vado lettera per lettera attraverso il primo file e copio tutti i contenuti in quello temporaneo a parte per quelli della riga che si vuole cancellare 
    ch=getc(point);
    while (ch!=EOF) {
        if (j!=canc) {
            putc(ch, temp_point);
        }
        else {
            flag=1;
        }

        if (ch=='\n') {
            j++;
        }
                        
        ch=getc(point);
    }

    // se la cancellazione è stata effettuata, allora entro nell'if
    if (flag==1) {
        // chiudo entrambi i file, rimuovo il file originale e rinomino quello temporaneo con il valore cancellato con lo stesso nome dell'originale 
        fclose(point);
        fclose(temp_point);
        remove(nome_file);
        rename(file_temp, nome_file);

        j=0;

        // inizio la cancellazione nel programma dichiarando i nodi che mi servono
        Nodo* temp=*testa;
        Nodo* prima=NULL;

        // svolgo questo passaggio nel caso il valore richiesto è in testa
        if (temp!=NULL && canc==j) {
            *testa=temp->next;
            free(temp);
        }
        else {
            j=1;

            // cerco che nodo della lista che voglio eliminare leggendoli in ordine e comparando quanti nodi sono andato avanti con il valore della riga del file che l'utente aveva fornito
            while (temp!=NULL && j<canc) {
                prima=temp;
                temp=temp->next;
                j++;
            }
        
            // cancello saltando il nodo non voluto e poi liberando la memoria che occupava
            /*
                esempio:
                A -> B -> C -> D -> NULL
            
                voglio cancellare B, quindi faccio:
                A -> C -> D -> NULL

                dove si avrà nel momento di cancellazione: 
                - A = prima
                - B = temp / prima->next
                - C = temp->next
            */
            prima->next=temp->next;
            free(temp);
            (*N)--;
        }

        printf("Cancellazione andata a buon fine: è stata cancellata correttamente la riga %d\n", canc);
        printf("Informazioni delle macchine salvate correttamente su \"%s\"\n", nome_file);
    }
    // se la cancellazione non è stata effettuata, allora tengo tutto come se nulla fosse successo
    else {
        printf("Cancellazione fallita, è stato mantenuto il file originale\n");
        remove(file_temp);
    }
}

// ramificazione della funzione "ricerca_binaria", serve per fornire all'algoritmo l'effettivo valore che si trova nella posizione centrale della lista
Nodo* nodo_in_centro(Nodo* testa, int mid) {
    int i=0;
    while (testa != NULL && i<mid) {
        testa=testa->next;
        i++;
    }
    return testa;
}

// algoritmo di Ricerca Dicotomica, come per il Bubble Sort il concetto è uguale però si lavora in modo diverso dato che si usano le liste
Nodo* ricerca_binaria (Nodo* testa, int N, int codice) {
    int low=0, high=N-1, mid;

    // il while del do-while controlla se effettivamente il codice dato esiste, ma mentre cerca gira all'infinito diminuendo sempre più la finestra dei valori possibili
    do {
        mid=(high+low)/2;
        Nodo* nodo_centrale=nodo_in_centro(testa, mid);

        // Caso di errore
        if (nodo_centrale == NULL) {
            return NULL;
        }
        
        // se questo è vero, allora abbiamo trovato ciò che cercavamo
        if (nodo_centrale->dati.codice==codice) {
            return nodo_centrale;
        }
        // se questo è vero, allora il valore medio è più grande di quello che cerchiamo e quindi eliminiamo dai valori possibili tutta la metà sopra il valore medio
        else if (nodo_centrale->dati.codice>codice) {
            high=mid-1;
        }
        // se no il valore medio è più piccolo di quello che cerchiamo e quindi eliminiamo dai valori possibili tutta la metà sotto il valore medio
        else {
            low=mid+1;
        }
    } while(low<=high);

    // nel caso di codice inesistente
    return NULL;
}

// funzione che permette di visualizzare tutti i codici se viene fornita la scelta 'Y' dall'utente
void visual_codici_if_Y(Nodo* testa) {
    int i=0;
    char vis;
    
    vis=acq_char(1);
    if (vis=='Y') {
        printf("Ecco tutti i codici disponibili:\n");
        Nodo* current=testa;
        while (current!=NULL) {
            printf(" - %d\n", current->dati.codice);
            current=current->next;
        }
    }
}

// funzione che stampa i vari campi della macchina indicando anche in che posizione della lista si trovava tale macchina
void stampa_numero_e_elementi (Nodo* testa, Nodo* elemento) {
    int i=1;
    Nodo* current=testa;
    
    while (current!=NULL) {
        if (current->dati.codice==elemento->dati.codice) {
            printf("MACCHINA NUMERO %d NELLA LISTA\n", i);
            break;
        }
        else {
            i++;
            current=current->next;
        }
    }

    printf("Informazioni macchina:\n - Codice: %d\n - Scopo: %s\n - Tensione = %f V\n - Corrente = %f A\n", elemento->dati.codice, elemento->dati.scopo, elemento->dati.tensione, elemento->dati.corrente);
}




// funzione finale che permette di deallocare la memoria prima allocata a fine programma, in modo da completare in modo corretto la chiusura senza problemi
void deallocazione (Nodo* testa) {
    Nodo* current=testa;

    while (testa!=NULL) {
        current=testa;
        testa=testa->next;
        free(current);
    }

    printf("Deallocazione effettuata con successo\n");
}



int main () {
    int scelta, N, i=0, controllo=0, elementi_struct=4, contr_sort=0;

    Nodo* Lista = NULL;

    FILE *point;
    char file_memoria[21]="memoria_macchine.txt", sort_save;

    // loop per acquisizione iniziale delle macchine
    while (controllo==0) {
        scelta=acq_int(2);

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

            case 2: {
                /* INSERIRE MACCHINE DA ZERO */
                controllo=1;
                N=0;

                Lista=inserimento_macchine_su_lista(&N);

                linee();
            }
            break;

            default: {
                printf("Inserire una scelta valida\n");
            }
        }
    }

    // in qualunque caso ordino il vettore rispetto al codice, in modo da avere ricerche più rapide
    bubble_sort(&Lista, N, &contr_sort);

    // controllo se è veramente necessario o no salvare le modifiche in base a se ce ne sono state alcune
    if (contr_sort==1) {
        printf("L'ordinamento ha apportato modifiche: salvo l'ordine nuovo nel file\n");
        
        salvataggio_file(Lista, file_memoria);
        
        linee();
    }
    else {
        printf("Ordinamento non ha portato ulteriori modifiche\n");

        salvataggio_file(Lista, file_memoria);

        linee();
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

            case 1: {
                /* SALVARE LE NUOVE MACCHINE IN MEMORIA */
                // guarda la funzione per spiegazione rapida su come funziona
                salvataggio_file(Lista, file_memoria);
            }
            break;

            case 2: {
                /* CANCELLARE UNA MACCHINA A SCELTA DALLA MEMORIA */
                int canc=visualizzazione_pre_cancellazione(N, point, file_memoria);
                
                if (canc==-1) {
                    printf("Cancellazione impossibile: il file non ha niente al suo interno\n");
                    fclose(point);
                }
                else {
                    cancellazione_da_lista(&Lista, point, file_memoria, canc, &N);
                }

                linee();
            }
            break;

            case 3: {
                /* VISUALIZZARE I DATI DI UNA MACCHINA FORNENDO IL CODICE */
                while (1) {
                    int codice=acq_int(1);

                    Nodo* nodo_ricerca=ricerca_binaria(Lista, N, codice);
                    if (nodo_ricerca==NULL) {
                        printf("Codice fornito non è uno che è presente tra i codici della lista\n");

                        // se non è stato dato un codice esistente, allora chiedo se si vuole vedere tutti i possibili codici
                        visual_codici_if_Y(Lista);
                    }
                    else {
                        stampa_numero_e_elementi(Lista, nodo_ricerca);
                        break;
                    }
                }

                linee();
            }
            break;

        }
    } while (scelta!=7);

    printf("Deallocazione di memoria della lista in corso...\n");
    deallocazione(Lista);
    
    printf("\nChiusura del programma in corso...\n");
    linee();

    return 0;
}