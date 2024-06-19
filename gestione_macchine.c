#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct Macchina {
    int codice;
    char scopo[25];
    float tensione, corrente;
};

void clear_buffer () {
    int c;
    while ((c=getchar())!='\n' && c!= EOF);
}

int acq_int (int mess) {
    int x, risultato;
    
    switch (mess) {
        case 0: printf("Scegliere un'opzione fornendo il numero:\n0. Visualizza tutte le macchine con tutte le informazioni\n1. Salvare le nuove macchine in memoria\n2. Visualizzare i dati di una macchina fornendo il codice\n3. Aggiungere una nuova macchina\n4. Visualizzare che macchina ha potenza maggiore\n5. Fine Programma\n");
        break;
        case 1: printf("Fornisci il numero effettivo delle macchine [numero intero positivo]\n");
        break;
        case 2: printf("Fornisci codice della macchina [numero intero]\n");
        break;
        case 3: printf("Fornisci codice della macchina nuova [numero intero]\n");
        break;
        case 4: printf("Scegliere tra le seguenti opzioni:\n1. Riprendere le macchine precedentemente salvate nella memoria\n2. Inserire macchine da zero\n");
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
        case 2: printf("Vuoi salvare le macchine non ancora registrate in memoria? [Y/N]\n");
        break;
        case 3: printf("Vuoi salvare quest'ultima macchina aggiunta in memoria? [Y/N]\n");
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
    int scelta, N, i=0, dim=10000, controllo=0;
    struct Macchina M[dim];
    FILE *file_point;
    char file_memoria[21]="memoria_macchine.txt";

    while (controllo==0) {
        scelta=acq_int(4);
        
        switch (scelta) {
            case 1: {
                controllo=1;

                file_point=fopen(file_memoria, "r");
                if (file_point==NULL) {
                    printf("Errore di apertura del file\n");
                    break;
                }

                fscanf(file_point, "%d", &N);

                for (i=0; i<N; i++) {
                    fscanf(file_point, "%d %s %f %f", &M[i].codice, M[i].scopo, &M[i].tensione, &M[i].corrente);
                }

                fclose(file_point);
                printf("Valori ripristinati correttamente\n");
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
            }
            break;
            
            default: {
                printf("Inserire una scelta valida\n");
            }
        }
    }

    do {
        scelta=acq_int(0);

        switch (scelta) {
            case 1: {
                file_point = fopen (file_memoria, "w");
                if (file_point==NULL) {
                    printf("Errore nell'apertura del file\n");
                    break;
                }
                
                fprintf(file_point, "%d\n", N);
                for (i=0; i<N; i++) {
                    fprintf(file_point, "%d %s %f %f\n", M[i].codice, M[i].scopo, M[i].tensione, M[i].corrente);
                }

                fclose(file_point);
                printf("Informazioni delle macchine salvate correttamente su \"%s\"\n", file_memoria);
            }
            break;

            case 2: {
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
            }
            break;

            case 3: {
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

                salva=acq_char(3);
                if (salva=='Y') {
                    file_point = fopen (file_memoria, "w");
                    if (file_point==NULL) {
                        printf("Errore nell'apertura del file\n");
                        break;
                    }
                
                    fprintf(file_point, "%d\n", N);
                    for (i=0; i<N; i++) {
                        fprintf(file_point, "%d %s %f %f\n", M[i].codice, M[i].scopo, M[i].tensione, M[i].corrente);
                    }

                    fclose(file_point);
                    printf("Informazioni delle macchine salvate correttamente su \"%s\"\n", file_memoria);
                }
            }
            break;

            case 4: {
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
            }
            break;

            case 0: {
                printf("Ci sono un totale di %d macchine\n", N);
                
                for (i=0; i<N; i++) {
                    printf("MACCHINA %d\n - Codice: %d\n - Scopo: %s\n - Tensione = %f V\n - Corrente = %f A\n", i+1, M[i].codice, M[i].scopo, M[i].tensione, M[i].corrente);
                }
            }
        }
    } while (scelta!=6);

    return 0;
}