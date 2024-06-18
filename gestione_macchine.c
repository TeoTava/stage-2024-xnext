/* 
Struttura con:
- codice numero intero positivo
- scopo stringa
- 2 float con voltaggio/tensione e con corrente

Permettere di: 
- Vedere float da codice
- Aggiungere
- Vedere chi ha potenza maggiore come voltaggio*corrente
*/

#include <stdio.h>
#include <string.h>

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
        case 0: printf("Scegliere un'opzione fornendo il numero:\n1. Visualizzare i dati di una macchina.\n2. Aggiungere una nuova macchina.\n3. Visualizzare chi ha potenza maggiore.\n4. Fine Programma.\n");
        break;
        case 1: printf("Fornisci il numero effettivo delle macchine.\n");
        break;
        case 2: printf("Fornisci codice della macchina.\n");
        break;
        case 3: printf("Fornisci codice della macchina nuova.\n");
        break;
        default: printf("Fornisci un valore intero.\n");
    }

    while (1) {
        risultato = scanf("%d", &x);

        if (risultato==1) {
            char extra;

            if (scanf("%c", &extra)==1 && extra!='\n') {
                printf("Inserire valore valido\n");
                clear_buffer();
            }
            else {
                break;
            }
        }
        else {
            printf("Inserire valore valido\n");
            clear_buffer();
        }
    }

    return x;
}

void acq_string(struct Macchina *M, int i, int mess) {
    switch (mess) {
        case 0: printf("Fornisci lo scopo della macchina.\n");
        break; 
        case 1: printf("Fornisci lo scopo della macchina nuova.\n");
        break; 
        default: printf("Fornisci una stringa di caratteri.\n");
    }

    scanf("%s", M[i].scopo);
}

float acq_float (int mess) {
    float x;
    int risultato;
    
    switch (mess) {
        case 0: printf("Fornisci la tensione della macchina.\n");
        break;
        case 1: printf("Fornisci la corrente della macchina.\n");
        break;
        case 2: printf("Fornisci la tensione della macchina nuova.\n");
        break;
        case 3: printf("Fornisci la corrente della macchina nuova.\n");
        break;
        default: printf("Fornisci numero reale.\n");
    }

    while (1) {
        risultato = scanf("%f", &x);

        if (risultato==1) {
            char extra;

            if (scanf("%c", &extra)==1 && extra!='\n') {
                printf("Inserire valore valido\n");
                clear_buffer();
            }
            else {
                break;
            }
        }
        else {
            printf("Inserire valore valido\n");
            clear_buffer();
        }
    }

    return x;
}



int main () {
    int scelta, N, i=0;
    struct Macchina M[10000];

    do {
        N=acq_int(1);
    } while (N<=0 || N>10000);

    for (i=0; i<N; i++) {
        do {
            M[i].codice=acq_int(2);
            acq_string(M, i, 0);
            M[i].tensione=acq_float(0);
            M[i].corrente=acq_float(1);
        } while (M[i].tensione<=0 || M[i].corrente<=0);
    }

    do {
        scelta=acq_int(0);

        switch (scelta) {
            case 1: {
                int nuovo, flag=0; 

                while (1) {
                    nuovo=acq_int(2);

                    for (i=0; i<N; i++) {
                        if (M[i].codice==nuovo) {
                            flag=1;
                            printf("Informazioni richieste:\n - Tensione = %f.\n - Corrente = %f.\n", M[i].tensione, M[i].corrente);
                        }
                    }

                    if (flag==0) {
                        printf("Macchina con codice fornito inesistente\n");
                    }
                    else {
                        break;
                    }
                }
            }
            break;

            case 2: {
                if (N==10000) {
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
            }
            break;

            case 3: {
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
                        printf(" - %d.\n", M[i].codice);
                    }
                }
            }
            break;
        }
    } while (scelta!=4);

    return 0;
}