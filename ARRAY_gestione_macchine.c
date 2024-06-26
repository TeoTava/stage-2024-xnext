/* IL PROGRAMMA È CREATO PER FUNZIONARE CON GLI ARRAY, QUINDI UTILIZZA LE CARATTERISTICHE CLASSICHE GIÀ VISTE IN CLASSE INSIEME AD ALTRA ROBA NUOVA AGGIUNTA (vedi README) */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

// definisco un tipo "macchina" in modo da non dover scrivere sempre "struct macchina"
typedef struct macchina {
    int codice;
    char scopo[25];
    float tensione, corrente;
} macchina;

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
        case 1: printf("Fornisci il numero effettivo delle macchine [numero intero positivo]\n");
        break;
        case 2: printf("Fornisci codice della macchina [numero intero]\n");
        break;
        case 3: printf("Fornisci codice della macchina nuova [numero intero]\n");
        break;
        case 4: printf("Scegliere tra le seguenti opzioni:\n1. Riprendere le macchine precedentemente salvate nella memoria\n2. Inserire macchine da zero\n");
        break;
        case 5: printf("Fornisci la riga da cancellare dal file [numero intero]\n");
        break;
        case 6: printf("Fornisci codice della macchina alla quale si vuole modificare un campo [numero intero]\n");
        break;
        case 7: printf("Selezionare che campo si vuole modificare:\n1. Scopo\n2. Tensione\n3. Corrente\n4. Fine modifica\n");
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
void acq_string_struct(macchina *M, int i, int mess) {
    // messaggi per le varie casistiche
    switch (mess) {
        case 0: printf("Fornisci lo scopo della macchina [stringa, 1 sola parola]\n");
        break; 
        case 1: printf("Fornisci lo scopo della macchina nuova [stringa, 1 sola parola]\n");
        break; 
        default: printf("Fornisci una stringa\n");
    }

    scanf("%s", (M+i)->scopo);
}

void acq_string(char *x, int mess) {
    // messaggi per le varie casistiche
    switch (mess) {
        case 0: printf("Fornisci il nuovo scopo della macchina [stringa, 1 sola parola]\n");
        break;
        default: printf("Fornisci una stringa\n");
    }

    scanf("%s", x);
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
        case 2: printf("Fornisci la tensione della macchina nuova [numero reale, in V]\n");
        break;
        case 3: printf("Fornisci la corrente della macchina nuova [numero reale, in A]\n");
        break;
        case 4: printf("Fornisci la nuova tensione della macchina [numero reale, in V]\n");
        break;
        case 5: printf("Fornisci la nuova corrente della macchina [numero reale, in A]\n");
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
        case 2: printf("Vuoi salvare tutte le macchine compresa quest'ultima macchina aggiunta in memoria? [Y/N]\n");
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
                if (mess==1 || mess==2) {
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

// per ordinare tutte le macchine secondo il codice (ordine crescente)
void bubble_sort(macchina *M, int N, int *contr_sort) {
    int i, j, scambio;
    macchina temp;

    // faccio girare tutte le macchine
    for (i=0; i<N-1; i++) {
        scambio=0;

        //controllo tutte le macchine che potrebbero non essere modificate
        for (j=0; j<N-i-1; j++) {
            if ((M+j)->codice>(M+(j+1))->codice) {
                temp=*(M+j);
                *(M+j)=*(M+(j+1));
                *(M+(j+1))=temp;

                scambio=1;
                (*contr_sort)=1;
            }
        }

        // se scambio non è diventato 1 allora il vettore è già ordinato
        if (scambio==0) {
            break;
        }
    }

    printf("Ordinamento del vettore completato correttamente\n");
}

// ricerca più ottimale per il codice avendo il bubble sort che ordina il vettore
int binary_seach (macchina *M, int N, int codice) {
    int low=0, high=N-1, mid;

    // il while del do-while controlla se effettivamente il codice dato esiste, ma mentre cerca gira all'infinito diminuendo sempre più la finestra dei valori possibili
    do {
        mid=(high+low)/2;

        // se questo è vero, allora abbiamo trovato ciò che cercavamo
        if ((M+mid)->codice==codice) {
            return mid;
        }
        // se questo è vero, allora il valore medio è più grande di quello che cerchiamo e quindi eliminiamo dai valori possibili tutta la metà sopra il valore medio
        else if ((M+mid)->codice>codice) {
            high=mid-1;
        }
        // se no il valore medio è più piccolo di quello che cerchiamo e quindi eliminiamo dai valori possibili tutta la metà sotto il valore medio
        else {
            low=mid+1;
        }
    } while(low<=high);

    // nel caso di codice inesistente
    return -1;
}

// funzione per salvare le macchine che sono presenti nel programma sul file "memoria_macchine.txt"
void salvataggio_file (macchina *M, int N, char *file_memoria, FILE **mem_point) {
    // apro il file in modalità "write"
    *mem_point=fopen(file_memoria, "w");
    if (*mem_point==NULL) {
        printf("Errore nell'apertura del file\n");
        return;
    }
                
    // copio le info delle macchine nel file in un modo preciso
    for (int i=0; i<N; i++) {
        fprintf(*mem_point, "%d %s %f %f\n", (M+i)->codice, (M+i)->scopo, (M+i)->tensione, (M+i)->corrente);
    }

    // chiudo il file
    fclose(*mem_point);
    printf("Informazioni delle macchine salvate correttamente su \"%s\"\n", file_memoria);

    linee();
}

void visual_codici_if_Y(macchina *M, int N) {
    int i=0;
    char vis;
    
    vis=acq_char(1);
    if (vis=='Y') {
        printf("Ecco tutti i codici disponibili:\n");
            for (i=0; i<N; i++) {
                printf(" - %d\n", (M+i)->codice);
            }
    }
}

// ramificazione della funzione "modifica_campo_struct" per la modifica dello scopo
void modifica_scopo(macchina *M, int N, int i) {
    // modifico direttamente la stringa
    acq_string((M+i)->scopo, 0);

    printf("Modifica del campo \"scopo\" della macchina con codice \"%d\" effettuata con successo\n", (M+i)->codice);
}

// ramificazione della funzione "modifica_campo_struct" per la modifica della tensione
void modifica_tensione(macchina *M, int N, int i) {
    // modifico direttamente il numero
    (M+i)->tensione=acq_float(4);

    printf("Modifica del campo \"tensione\" della macchina con codice \"%d\" effettuata con successo\n", (M+i)->codice);
}

// ramificazione della funzione "modifica_campo_struct" per la modifica della corrente
void modifica_corrente(macchina *M, int N, int i) {
    // modifico direttamente il numero
    (M+i)->corrente=acq_float(4);

    printf("Modifica del campo \"corrente\" della macchina con codice \"%d\" effettuata con successo\n", (M+i)->codice);
}

// funzione per modificare un campo a scelta
int modifica_campo_struct (macchina *M, int N) {
    int opzione, i=0, codice;

    // uso il codice per ricercare la macchina voluta, anche perchè ho la ricerca dicotomica che aiuta
    codice=acq_int(6);
    i=binary_seach(M, N, codice);
    if (i==-1) {
        printf("La ricerca non ha trovato nessun valore\n");

        // se non è stato dato un codice esistente, allora chiedo se si vuole vedere tutti i possibili codici
        visual_codici_if_Y(M, N);
        
        // 0 fa tenere la condizione nel main del "while" vera, in modo che poi la funzione si può ripetere fino a che non viene dato un codice giusto
        return 0;
    }
    else {
        do {
            opzione=acq_int(7);

            switch (opzione) {
                case 1: {
                    /* MODIFICA DEL CAMPO "SCOPO" */
                    modifica_scopo(M, N, i);
                }
                break;

                case 2: {
                    /* MODIFICA DEL CAMPO "TENSIONE" */
                    modifica_tensione(M, N, i);
                }
                break;

                case 3: {
                    /* MODIFICA DEL CAMPO "CORRENTE" */
                    modifica_corrente(M, N, i);
                }
                break;
                
                // senza il numero di fine funzione, messaggio per avvisare di fare una scelta valida
                case 4: break;
                default: printf("Fornisci una scelta valida");
                break;
            }
        } while (opzione!=4);
    } 

    return 1;
}



int main () {
    int scelta, N, i=0, controllo=0, dim_struct=10000, elementi_struct=4, contr_sort=0;
    macchina M[dim_struct];
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

                // apro il file in modalità "write"
                mem_point=fopen(file_memoria, "r");
                if (mem_point==NULL) {
                    printf("Errore di apertura del file: è necessario inserire tutti i valori con la scelta 2\n");
                    controllo=0;
                    break;
                }

                // continuo a copiare ciò che ho nel file nel vettore fino a che non c'è più nulla da copiare (fscanf ha return value di quante variabili copia)
                while (fscanf(mem_point, "%d %s %f %f", &(M+i)->codice, (M+i)->scopo, &(M+i)->tensione, &(M+i)->corrente)==elementi_struct) {
                    i++;
                    N++;
                }

                // controllo se il file "memoria_macchine.txt" è vuoto
                if (N==0) {
                    printf("Impossibile riprendere i dati: il file di memoria non presenta alcun dato disponibile\nÈ necessario reimpostare i dati selezionando la 2a opzione dal menù\n");
                    controllo=0;
                }
                else {
                    printf("Valori ripristinati correttamente\n");
                }

                // chiudo il file
                fclose(mem_point);

                linee();
            }
            break; 

            case 2: {
                /* INSERIRE MACCHINE DA ZERO */
                controllo=1;

                // acquisisco il numero di macchine
                do {
                    N=acq_int(1);
                } while (N<=0 || N>dim_struct);

                // acquisico i vari campi della struttura per tutte le macchine
                for (i=0; i<N; i++) {
                    printf("MACCHINA NUMERO %d\n", i+1);

                    (M+i)->codice=acq_int(2);
                    acq_string_struct(M, i, 0);
                    (M+i)->tensione=acq_float(0);
                    (M+i)->corrente=acq_float(1);
                }

                linee();
            }
            break;
            
            default: {
                printf("Inserire una scelta valida\n");
            }
        }
    }

    // in qualunque caso ordino il vettore rispetto al codice, in modo da avere ricerche più rapide
    bubble_sort(M, N, &contr_sort);

    // controllo se è veramente necessario o no salvare le modifiche in base a se ce ne sono state alcune
    if (contr_sort==1) {
        printf("L'ordinamento ha apportato modifiche: salvo l'ordine nuovo nel file\n");
        salvataggio_file(M, N, file_memoria, &mem_point);
    }
    else {
        printf("Ordinamento non ha portato ulteriori modifiche\n");
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
                
                for (i=0; i<N; i++) {
                    printf("MACCHINA %d\n - Codice: %d\n - Scopo: %s\n - Tensione = %f V\n - Corrente = %f A\n", i+1, (M+i)->codice, (M+i)->scopo, (M+i)->tensione, (M+i)->corrente);
                }

                linee();
            }
            break;
            
            case 1: {
                /* SALVARE LE NUOVE MACCHINE IN MEMORIA */
                // guarda la funzione per spiegazione rapida su come funziona
                salvataggio_file(M, N, file_memoria, &mem_point);
            }
            break;

            case 2: {
                /* CANCELLARE UNA MACCHINA A SCELTA DALLA MEMORIA */
                FILE *temp_point;
                char file_temp[9] = "temp.txt", ch;
                int canc, j=1, flag=0;
                float grand_file;

                // apro il file in modalità "read"
                mem_point = fopen (file_memoria, "r");
                if (mem_point==NULL) {
                    printf("Errore nell'apertura del file\n");
                    break;
                }
                
                // guardo quanto effettivamente grande è il file che ho
                fseek(mem_point, 0, SEEK_END);
                grand_file=ftell(mem_point);
                rewind(mem_point);

                // se il file dentro di sè ha qualche macchina, allora ha senso mostrare i contenuti di tale file
                if (grand_file!=0) {
                    printf("Contenuto attuale del file \"%s\" (numero all'inizio indica la riga del file, in ordine i valori sono per ogni macchina: codice, scopo, tensione, corrente):\n", file_memoria);
                    printf("%d)   ", j);
                    j++;
                    //faccio girare tutto il file printando lettera per lettera i suoi contenuti fino alla End-of-File (EOF)
                    ch=getc(mem_point);
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
                        ch=getc(mem_point);
                    }
                    // riporto il puntatore a inizio file perchè mi servirà anche dopo
                    rewind(mem_point);
                    j=1;

                    // mi faccio fornire la riga del file (quindi effettivamente la macchina) che l'utente vuole cancellare
                    do {
                        if (flag==0) {
                            flag=1;
                        }
                        else {
                            printf("Valore fornito non è una riga nel file\n");
                        }
                        
                        canc=acq_int(5);
                    } while(canc>N);

                    // apro il file temporaneo in modalità "write"
                    temp_point = fopen (file_temp, "w");
                    if (temp_point==NULL) {
                        printf("Errore nell'apertura del file temporaneo\n");
                        break;
                    }

                    // vado lettera per lettera attraverso il primo file e copio tutti i contenuti in quello temporaneo a parte per quelli della riga che si vuole cancellare
                    ch=getc(mem_point);
                    while (ch!=EOF) {
                        if (j!=canc) {
                            putc(ch, temp_point);
                        }
                        else {
                            flag=2;
                        }

                        if (ch=='\n') {
                            j++;
                        }
                        
                        ch=getc(mem_point);
                    }

                    // se la cancellazione è stata effettuata, allora entro nell'if
                    if (flag=2) {
                        // chiudo entrambi i file, rimuovo il file originale e rinomino quello temporaneo con il valore cancellato con lo stesso nome dell'originale 
                        fclose(mem_point);
                        fclose(temp_point);
                        remove(file_memoria);
                        rename(file_temp, file_memoria);
                        
                        // devo anche cancellare nel programma la riga che volevo eliminare, non solamente a livello di file
                        for (i=0; i<N; i++) {
                            if (canc==i+1) {
                                for (j=i; j<N-1; j++) {
                                    *(M+j)=*(M+(j+1));
                                }
                            }
                        }
                        N--;

                        printf("Cancellazione andata a buon fine: è stata cancellata correttamente la riga %d\n", canc);
                        printf("Informazioni delle macchine salvate correttamente su \"%s\"\n", file_memoria);
                    }
                    // se la cancellazione non è stata effettuata, allora tengo tutto come se nulla fosse successo
                    else {
                        printf("Cancellazione fallita, è stato mantenuto il file originale\n");
                        remove(file_temp);
                    }
                }
                // se il file non ha contenuti, non c'è nulla da visualizzare e cancellare
                else {
                    printf("File \"%s\" è vuoto: non c'è nessun valore da cancellare\n", file_memoria);
                }

                linee();
            }
            break;

            case 3: {
                /* VISUALIZZARE I DATI DI UNA MACCHINA FORNENDO IL CODICE */
                int codice;

                // ciclo infinito fino a che non viene dato un codice esistente
                while (1) {
                    codice=acq_int(2);

                    // controllo quale macchina ha codice uguale a quello fornito prima, stampando anche tutte le varie informazioni
                    
                    i=binary_seach(M, N, codice);
                    if (i==-1) {
                        char vis;

                        printf("La ricerca non ha trovato nessun valore\n");

                        // se non è stato dato un codice esistente, allora chiedo se si vuole vedere tutti i possibili codici
                        visual_codici_if_Y(M, N);
                    }
                    else {
                        printf("Informazioni richieste:\n - Tensione = %f V\n - Corrente = %f A\n", (M+i)->tensione, (M+i)->corrente);
                        printf("Altre informazioni sulla macchina:\n - Codice: %d\n - Scopo: %s\n", (M+i)->codice, (M+i)->scopo);
                        
                        // quando viene fornito il codice, esco dal ciclo infinito
                        break;
                    }
                }

                linee();
            }
            break;

            case 4: {
                /* AGGIUNGERE UNA NUOVA MACCHINA */
                char salva;
                
                // impossibile aggiungere una nuova macchina se il vettore è già pieno
                if (N==dim_struct) {
                    printf("Aggiunta impossibile: vettore dati già pieno.\n");
                }
                // se posso aggiungere una macchina nuova, chiedo tutte le caratteristiche
                else {
                    (M+N)->codice=acq_int(3);
                    acq_string_struct(M, N, 1);
                    (M+N)->tensione=acq_float(2);
                    (M+N)->corrente=acq_float(3);

                    N++;
                }

                // effettuo il sorting per mantenere le macchine ordinate per codice
                bubble_sort(M, N, &contr_sort);
                
                // salvo il file per mantenere nel tempo le modifiche e l'ordine
                salvataggio_file(M, N, file_memoria, &mem_point);
            }
            break;

            case 5: {
                /* MODIFICARE UN CAMPO DI UNA MACCHINA IN MEMORIA */
                int modifica=0;
                
                // ripeto fino a che non viene fornito un codice corretto
                while (modifica==0) {
                    modifica=modifica_campo_struct(M, N);
                }

                // alla fine delle modifiche salvo il file con i cambiamenti
                salvataggio_file(M, N, file_memoria, &mem_point);
            } 
            break;

            case 6: {
                /* VISUALIZZARE CHE MACCHINA HA POTENZA MAGGIORE */
                float max, potenza;

                // cerco qual'è il valore max di potenza
                for (i=0; i<N; i++) {
                    potenza=(M+i)->tensione*(M+i)->corrente;
                    
                    if (i==0) {
                        max=potenza;
                    }
                    else if (potenza>max) {
                        max=potenza;
                    }
                }

                // mostro le infomazioni delle sole macchine con potenza uguale a quella max
                printf("Elenco codici macchine con potenza massima (di %f W):\n", max);
                for (i=0; i<N; i++) {
                    potenza=(M+i)->tensione*(M+i)->corrente;
                    if (potenza==max) {
                        printf(" - Codice: %d\n", (M+i)->codice);
                        printf("    - Scopo: %s\n    - Tensione: %f V\n    - Corrente: %f A\n", (M+i)->scopo, (M+i)->tensione, (M+i)->corrente);
                    }
                }

                linee();
            }
            break;
            
            // senza il numero di fine programma, messaggio per avvisare di fare una scelta valida
            case 7: break;
            default: printf("Fornisci una scelta valida");
            break;
        }
    /* FINE PROGRAMMA */
    } while (scelta!=7); 

    printf("Chiusura del programma in corso...\n");
    linee();

    return 0;
}