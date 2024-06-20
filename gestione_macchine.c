#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct Macchina {
    int codice;
    char scopo[25];
    float tensione, corrente;
};

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

void clear_buffer () {
    int c;
    while ((c=getchar())!='\n' && c!= EOF);
}

int acq_int (int mess) {
    int x, risultato;
    
    switch (mess) {
        case 0: printf("Scegliere un'opzione fornendo il numero:\n0. Visualizza tutte le macchine con tutte le informazioni\n1. Salvare le nuove macchine in memoria\n2. Cancellare una macchina a scelta dalla memoria\n3. Visualizzare i dati di una macchina fornendo il codice\n4. Aggiungere una nuova macchina\n5. Visualizzare che macchina ha potenza maggiore\n6. Fine Programma\n");
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
        default: printf("Fornisci un valore intero\n");
    }

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

void acq_string(struct Macchina *M, int i, int mess) {
    switch (mess) {
        case 0: printf("Fornisci lo scopo della macchina [stringa, 1 sola parola]\n");
        break; 
        case 1: printf("Fornisci lo scopo della macchina nuova [stringa, 1 sola parola]\n");
        break; 
        default: printf("Fornisci una stringa\n");
    }

    scanf("%s", M[i].scopo);
}

float acq_float (int mess) {
    float x;
    int risultato;
    
    switch (mess) {
        case 0: printf("Fornisci la tensione della macchina [numero reale, in V]\n");
        break;
        case 1: printf("Fornisci la corrente della macchina [numero reale, in A]\n");
        break;
        case 2: printf("Fornisci la tensione della macchina nuova [numero reale, in V]\n");
        break;
        case 3: printf("Fornisci la corrente della macchina nuova [numero reale, in A]\n");
        break;
        default: printf("Fornisci numero reale\n");
    }

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

char acq_char (int mess) {
    char x;
    int risultato;

    switch (mess) {
        case 1: printf("Vuoi visualizzare tutti i codici possibili? [Y/N]\n");
        break;
        case 2: printf("Vuoi salvare tutte le macchine compresa quest'ultima macchina aggiunta in memoria? [Y/N]\n");
        break;
        default: printf("Fornisci un carattere letterale\n");
    }

    while (1) {
        risultato = scanf(" %c", &x);

        if (risultato==1) {
            char extra;

            if (scanf("%c", &extra)==1 && extra!='\n') {
                printf("Inserire valore valido: valore inserito non è un carattere lettera\n");
                clear_buffer();
            }
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



int main () {
    int scelta, N, i=0, dim=10000, controllo=0, elementi_struct=4;
    struct Macchina M[dim];
    FILE *mem_point;
    char file_memoria[21]="memoria_macchine.txt";

    while (controllo==0) {
        scelta=acq_int(4);

        linee();

        switch (scelta) {
            case 1: {
                controllo=1;
                N=0;

                mem_point=fopen(file_memoria, "r");
                if (mem_point==NULL) {
                    printf("Errore di apertura del file: è necessario inserire tutti i valori con la scelta 2\n");
                    controllo=0;
                    break;
                }

                while (fscanf(mem_point, "%d %s %f %f", &M[i].codice, M[i].scopo, &M[i].tensione, &M[i].corrente)==elementi_struct) {
                    i++;
                    N++;
                }

                if (N==0) {
                    printf("Impossibile riprendere i dati: il file di memoria non presenta alcun dato disponibile\nÈ necessario reimpostare i dati selezionando la 2a opzione dal menù\n");
                    controllo=0;
                }
                else {
                    printf("Valori ripristinati correttamente\n");
                }

                fclose(mem_point);

                linee();
            }
            break; 

            case 2: {
                controllo=1;

                do {
                    N=acq_int(1);
                } while (N<=0 || N>dim);

                for (i=0; i<N; i++) {
                    printf("MACCHINA NUMERO %d\n", i+1);

                    do {
                        M[i].codice=acq_int(2);
                        acq_string(M, i, 0);
                        M[i].tensione=acq_float(0);
                        M[i].corrente=acq_float(1);
                    } while (M[i].tensione<=0 || M[i].corrente<=0);
                }

                linee();
            }
            break;
            
            default: {
                printf("Inserire una scelta valida\n");
            }
        }
    }

    do {
        scelta=acq_int(0);

        linee();

        switch (scelta) {
            case 0: {
                printf("Ci sono un totale di %d macchine\n", N);
                
                for (i=0; i<N; i++) {
                    printf("MACCHINA %d\n - Codice: %d\n - Scopo: %s\n - Tensione = %f V\n - Corrente = %f A\n", i+1, M[i].codice, M[i].scopo, M[i].tensione, M[i].corrente);
                }

                linee();
            }
            break;
            
            case 1: {
                mem_point = fopen (file_memoria, "w");
                if (mem_point==NULL) {
                    printf("Errore nell'apertura del file\n");
                    break;
                }
                
                for (i=0; i<N; i++) {
                    fprintf(mem_point, "%d %s %f %f\n", M[i].codice, M[i].scopo, M[i].tensione, M[i].corrente);
                }


                fclose(mem_point);
                printf("Informazioni delle macchine salvate correttamente su \"%s\"\n", file_memoria);

                linee();
            }
            break;

            case 2: {
                FILE *temp_point;
                char file_temp[9] = "temp.txt", ch;
                int canc, j=1, flag=0;
                float grand_file;

                mem_point = fopen (file_memoria, "r");
                if (mem_point==NULL) {
                    printf("Errore nell'apertura del file\n");
                    break;
                }
                
                fseek(mem_point, 0, SEEK_END);
                grand_file=ftell(mem_point);
                rewind(mem_point);

                if (grand_file!=0) {
                    printf("Contenuto attuale del file \"%s\" (numero all'inizio indica la riga del file, in ordine i valori sono per ogni macchina: codice, scopo, tensione, corrente):\n", file_memoria);
                    printf("%d)   ", j);
                    j++;
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
                    rewind(mem_point);
                    j=1;

                    do {
                        if (flag==0) {
                            flag=1;
                        }
                        else {
                            printf("Valore fornito non è una riga nel file\n");
                        }
                        
                        canc=acq_int(5);
                    } while(canc>N);

                    temp_point = fopen (file_temp, "w");
                    if (temp_point==NULL) {
                        printf("Errore nell'apertura del file temporaneo\n");
                        break;
                    }

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

                    if (flag=2) {
                        fclose(mem_point);
                        fclose(temp_point);
                        remove(file_memoria);
                        rename(file_temp, file_memoria);
                        N--;

                        printf("Cancellazione andata a buon fine: è stata cancellata correttamente la riga %d\n", canc);
                    }
                    else {
                        printf("Cancellazione fallita, è stato mantenuto il file originale\n");
                    }
                }
                else {
                    printf("File \"%s\" è vuoto: non c'è nessun valore da cancellare\n", file_memoria);
                }

                linee();
            }
            break;

            case 3: {
                int nuovo, flag=0; 

                while (1) {
                    nuovo=acq_int(2);

                    for (i=0; i<N; i++) {
                        if (M[i].codice==nuovo) {
                            flag=1;
                            printf("Informazioni richieste:\n - Tensione = %f V\n - Corrente = %f A\n", M[i].tensione, M[i].corrente);
                            printf("Altre informazioni sulla macchina:\n - Codice: %d\n - Scopo: %s\n", M[i].codice, M[i].scopo);
                        }
                    }

                    if (flag==0) {
                        char vis;
                        printf("Macchina con codice fornito inesistente\n");
                        
                        vis=acq_char(1);
                        if (vis=='Y') {
                            printf("Ecco tutti i codici disponibili:\n");
                            for (i=0; i<N; i++) {
                                printf(" - %d\n", M[i].codice);
                            }
                        }
                    }
                    else {
                        break;
                    }
                }

                linee();
            }
            break;

            case 4: {
                char salva;
                
                if (N==dim) {
                    printf("Aggiunta impossibile: vettore dati già pieno.\n");
                }
                else {
                    do {
                        M[N].codice=acq_int(3);
                        acq_string(M, N, 1);
                        M[N].tensione=acq_float(2);
                        M[N].corrente=acq_float(3);
                    } while (M[N].tensione<=0 || M[N].corrente<=0);

                    N++;
                }

                salva=acq_char(2);
                if (salva=='Y') {
                    mem_point = fopen (file_memoria, "w");
                    if (mem_point==NULL) {
                        printf("Errore nell'apertura del file\n");
                        break;
                    }
                
                    for (i=0; i<N; i++) {
                        fprintf(mem_point, "%d %s %f %f\n", M[i].codice, M[i].scopo, M[i].tensione, M[i].corrente);
                    }

                    fclose(mem_point);
                    printf("Informazioni delle macchine salvate correttamente su \"%s\"\n", file_memoria);
                }

                linee();
            }
            break;

            case 5: {
                float max, potenza;

                for (i=0; i<N; i++) {
                    potenza=M[i].tensione*M[i].corrente;
                    
                    if (i==0) {
                        max=potenza;
                    }
                    else if (potenza>max) {
                        max=potenza;
                    }
                }

                printf("Elenco codici macchine con potenza massima (di %f W):\n", max);
                for (i=0; i<N; i++) {
                    potenza=M[i].tensione*M[i].corrente;
                    if (potenza==max) {
                        printf(" - Codice: %d\n", M[i].codice);
                        printf("    - Scopo: %s\n    - Tensione: %f V\n    - Corrente: %f A\n", M[i].scopo, M[i].tensione, M[i].corrente);
                    }
                }

                linee();
            }
            break;
        }
    } while (scelta!=6);

    return 0;
}