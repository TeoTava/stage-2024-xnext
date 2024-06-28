CC = gcc
CFLAGS = -Wall -Wextra -O2
TARGETS = ARRAY_gestione_macchine LIST_gestione_macchine

all: $(TARGETS)

%: %.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(TARGETS)


# SPIEGAZIONE:

# "CC" indica il compilatore che useremo

# "CFLAGS" indica le varie flag che si metteranno durante la compilazione 
# "-Wall" serve per mostrare errori come mancanza di variabili o della loro dichiarazione o altro
# "-Wextra" aggiunge altre funzioni mancanti a -Wall in modo da avere un controllo più ampio
# "-O2" inserisce un'ottimizzazione del programma di 2o livello (max sarebbe 3 ma è meglio usare 2)

# TARGETS sono i vari file eseguibili che si dovranno creare 

# "all" è il target principale, che dipende dai 2 target definiti dalla variabile TARGETS 

# "%:" indica un generico file qualsiasi e lo mette come target
# "%.c" è la dipendenza e indica un generico file qualsiasi che termina con .c e che avrà lo stesso nome del target prima (es: target "prog1" avrà dipendenza "prog1.c")

# Utilizzando il compilatore e i CFLAGS impostati, andremo a compilare il programma
# "-o $@" indica che l'output della compilazione sarà un file con il nome del target del momento (quello che si trova in %:)
# "&<" indica che il file che andrà compilato è quello della dipendenza del target soprastante (quello che si trova in "%.c")

# "clean" serve per togliere tutti i file eseguibili che si creano dalla compilazione, in modo da tenere un ambiente di lavoro più pulito e ordinato
# "rm" serve infatti per la rimozione del file (che poi saranno rimossi quelli delle variabili TARGETS)
# "-f" indica che tale rimozione dichiarata prima deve essere svolta in modo forzato, così da evitare errori o difficoltà durante la rimozione