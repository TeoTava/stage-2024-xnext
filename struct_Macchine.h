/* Header file per dichiarare con "#include" la struct delle macchine a inizio programma sia per ARRAY che per LIST */

// inizio con una funzione in preprocessore cosiddetta "Header Guard", in modo da evitare errori di compilazione
#ifndef IMPL_MACCHINE
    #define IMPL_MACCHINE

    // definisco un tipo "Macchina" in modo da non dover scrivere sempre "struct Macchina"
    typedef struct Macchina {
        int codice;
        char scopo[25];
        float tensione, corrente;
    } Macchina;
#endif