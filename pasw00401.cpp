///LIBRERIE
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

///DATI STRUTTURATI
///Definisco due nuovi tipi di dato per enumerazione che mi descrivono il dato Cella
typedef enum {pawn,rook,bishop,knight,queen,king,noPiece} Pezzo;
typedef enum {white,black,noColor} Colore;

///Nuovo dato "Cella" definito da "Pezzo" e "Colore"
struct Cella {
    Pezzo pezzo;
    Colore colore;
};

///Matrice 8x9 formata da variabili di tipo "Cella"
typedef Cella Scacchiera[8][9];

/// Dato per coordinate scacchistiche
struct Ccoord {
    char col;	// 'a' .. 'h'	da sinistra
    int riga;	// 1 .. 8 		dal "basso"
};

/// Dato per coordinate matriciali
struct Mcoord {
    int riga;	// 0 .. 7		dall'alto
    int col;	// 0 .. 7 		da sinistra
};

///PROTOTIPI FUNZIONI
/// Riceve in input un dato "Scacchiera" e la inizializza con "Celle" del tipo "noPiece" e "noColor"
void vuotaScacchiera(Scacchiera s);

///Legge da un file .txt i caratteri che rappresentano i pezzi, li converte in dati Cella e li inserisce nella matrice
void inserisciPezzi(Scacchiera s);

/// converte in formato Cella un pezzo p rappresentato come char
Cella convertiInCella(char p);

/// converte in char un pezzo p rappresentato in formato Cella
char convertiInChar(Cella p);

///stampa la scacchiera a video (debugging)
void visualizzaScacchiera(Scacchiera s);

///cerca i pezzi sulla scacchiera e richiama le funzioni corrispondenti per visualizzarne i movimenti
void ricerca_pezzi(Scacchiera s);

///Stampa sul file .txt le mosse possibili dell'alfiere
void mosse_alfiere(Scacchiera s,int riga, int colonna);

///Stampa sul file .txt le mosse possibili della torre
void mosse_torre(Scacchiera s, int riga, int colonna);

///Stampa sul file .txt le mosse possibili della regina
void mosse_regina(Scacchiera s, int riga, int colonna);

///Stampa sul file .txt le mosse possibili del re
void mosse_re(Scacchiera s, int riga, int colonna);

///Stampa sul file .txt le mosse possibili del pedone
void mosse_pedone(Scacchiera s, int riga, int colonna);

///Stampa sul file .txt le mosse possibili del cavallo
void mosse_cavallo(Scacchiera s, int riga, int colonna);

///controlla che le coordinate riga e colonna possano esistere (comprese da 0 e 7)
bool controllocoordinate(int riga, int colonna);

///controlla se la cella selezionata è vuota
bool controllocella (Cella cel);

///controlla se le due celle inserite hanno lo stesso colore
bool controllocolore (Cella c1, Cella c2);

///converte da coordinate scacchistiche a matriciali
Mcoord converti(Ccoord c);

///converte da coordinate matriciali a scacchistiche
Ccoord converti(Mcoord m);

///intestazione del file .txt
void intestazione();

///funzione che stampa sul file .txt
void scrittura(Scacchiera s, int riga, int colonna, bool mangia);

///funzione che stampa "no move", nel caso in cui il pezzo selezionato non possa muoversi in nessuona direzione
void no_move();

///MAIN()
int main() {
    Scacchiera s;
    intestazione();
    vuotaScacchiera(s);
    inserisciPezzi(s);
    ///visualizzaScacchiera(s);
    ricerca_pezzi(s);
    return 0;
}

///DEFINIZIONE FUNZIONI
/// Riceve in input un dato "Scacchiera" e la inizializza con "Celle" del tipo "noPiece" r "noColor"
void vuotaScacchiera(Scacchiera s){
    Cella vuota;
    int r,c;
    vuota.pezzo = noPiece;
    vuota.colore = noColor;
    for(r=0; r<8; r++)
        for(c=0; c<8; c++)
            s[r][c] = vuota;
}

///Legge da un file .txt i caratteri che rappresentano i pezzi, li converte in dati Cella e li inserisce nella matrice
void inserisciPezzi(Scacchiera s) {
    char ch;
    int r,c;
    ifstream mioFile;
    mioFile.open("scacchiera.txt");
    ///Viene letto un carattere alla volta dal file .txt e viene poi inserito nella matrice
    for(r=0; r<8; r++) {
        for(c=0; c<9; c++) {
            mioFile.get(ch);
            s[r][c] = convertiInCella(ch);
            ///cout << ch;      DEBUG
        }
    }
    cout << endl;
    mioFile.close();
}

/// Converte in formato Cella un pezzo p rappresentato come char
Cella convertiInCella(char p){
    Cella pc;
    pc.pezzo = noPiece; pc.colore = noColor;	// default vuoto
    if (p>='a' && p<='z') pc.colore = white;	// bianco
    if (p>='A' && p<='Z') pc.colore = black;	// nero
    switch (p) {
        case 'p':
            pc.pezzo = pawn; 	break;
        case 'r':
            pc.pezzo = rook; 	break;
        case 'b':
            pc.pezzo = bishop; 	break;
        case 'n':
            pc.pezzo = knight; 	break;
        case 'q':
            pc.pezzo = queen; 	break;
        case 'k':
            pc.pezzo = king; 	break;
        case 'P':
            pc.pezzo = pawn; 	break;
        case 'R':
            pc.pezzo = rook; 	break;
        case 'B':
            pc.pezzo = bishop; 	break;
        case 'N':
            pc.pezzo = knight; 	break;
        case 'Q':
            pc.pezzo = queen; 	break;
        case 'K':
            pc.pezzo = king; 	break;
    }
    return pc;
}

/// converte in char un pezzo p rappresentato in formato Cella
char convertiInChar(Cella p){
    string pChar = "prbnqk PRBNQK ";	/// caratteri dei pezzi
    int pCharPos = p.pezzo;
    if (p.colore == black) pCharPos+=7;	/// pezzi neri
    return pChar[pCharPos];
}

///stampa la scacchiera a video (debugging)
void visualizzaScacchiera(Scacchiera s){
    int r, c;
    for(r=0;r<8;r++) {
        cout << "-----------------" << endl;
        for(c=0;c<8;c++)
            cout << "|" << convertiInChar(s[r][c]);
        cout << "|" << endl;
    }
    cout << "-----------------" << endl;
}

///cerca i pezzi sulla scacchiera e richiama le funzioni corrispondenti per visualizzarne i movimenti
void ricerca_pezzi(Scacchiera s) {
    int riga, colonna;
    Mcoord mat;
    Ccoord sca;
    ofstream mioFile;
    mioFile.open("mosse.txt", ios::out | ios::app);
    char pezzo;
    /*
    Tramite due cicli for si scorre tutta la scacchiera.
    Per ogni pezzo trovato, si valuta che pezzo sia e, con uno switch(), si richiama la funzione corrispondente
    per visualizzarne le mosse.
    */
    ///BIANCHI
    for(riga=0; riga<8; riga++) {
        mat.riga = riga;
        for(colonna=0; colonna<8; colonna++) {
            mat.col = colonna;
            sca = converti(mat);
            pezzo = convertiInChar(s[riga][colonna]);
            switch (pezzo) {
                case 'p': {
                    mioFile << "pawn - white - ";
                    mioFile << sca.col;
                    mioFile << sca.riga << endl;
                    mosse_pedone(s, riga, colonna);
                    break;
                }
                case 'n':{
                    mioFile << "knight - white - ";
                    mioFile << sca.col;
                    mioFile << sca.riga << endl;
                    mosse_cavallo(s, riga, colonna);
                    break;
                }
                case 'b':{
                    mioFile << "bishop - white - ";
                    mioFile << sca.col;
                    mioFile << sca.riga << endl;
                    mosse_alfiere(s, riga, colonna);
                    break;
                }
                case 'r':{
                    mioFile << "rook - white - ";
                    mioFile << sca.col;
                    mioFile << sca.riga << endl;
                    mosse_torre(s, riga, colonna);
                    break;
                }
                case 'q':{
                    mioFile << "queen - white - ";
                    mioFile << sca.col;
                    mioFile << sca.riga << endl;
                    mosse_regina(s, riga, colonna);
                    break;
                }
                case 'k':{
                    mioFile << "king - white - ";
                    mioFile << sca.col;
                    mioFile << sca.riga << endl;
                    mosse_re(s, riga, colonna);
                    break;
                }
                default:
                    break;
            }
            ///NERI
            switch (pezzo) {
                case 'P': {
                    mioFile << "pawn - black - ";
                    mioFile << sca.col;
                    mioFile << sca.riga << endl;
                    mosse_pedone(s, riga, colonna);
                    break;
                }
                case 'N':{
                    mioFile << "knight - black - ";
                    mioFile << sca.col;
                    mioFile << sca.riga << endl;
                    mosse_cavallo(s, riga, colonna);
                    break;
                }
                case 'B':{
                    mioFile << "bishop - black - ";
                    mioFile << sca.col;
                    mioFile << sca.riga << endl;
                    mosse_alfiere(s, riga, colonna);
                    break;
                }
                case 'R':{
                    mioFile << "rook - black - ";
                    mioFile << sca.col;
                    mioFile << sca.riga << endl;
                    mosse_torre(s, riga, colonna);
                    break;
                }
                case 'Q':{
                    mioFile << "queen - black - ";
                    mioFile << sca.col;
                    mioFile << sca.riga << endl;
                    mosse_regina(s, riga, colonna);
                    break;
                }
                case 'K':{
                    mioFile << "king - black - ";
                    mioFile << sca.col;
                    mioFile << sca.riga << endl;
                    mosse_re(s, riga, colonna);
                    break;
                }
                default:
                    break;
            }
        }
    }
    mioFile.close();
}

///Stampa sul file .txt le mosse possibili dell'alfiere
void mosse_alfiere(Scacchiera s, int riga, int colonna) {
    ///L'alfiere si può muovere lungo le diagonali
    int cont_mosse=0;
    int i, num;
    /*
    A ogni direzione del pezzo assegnamo un numero da 0 a 4 e con un for le scorriamo tutte.
    Con un altro for consideriamo di quanto si può spostare l'alfiere in quella direzione (1, 2, 3 caselle ecc.)
    Per ogni movimento vengono controllate che le coordinate siano accettabili (che esistano sulla scacchiera) e
    se la casella di arrivo è occupata. Se questa è vuota il pezzo si sposta, mentre se è occupata si richiama la funzione
    controllocella() per vedere di che colore è il pezzo che occupa la cella di destinazione, se è dello stesso colore
    si esce dal ciclo, se è opposto invece mangia.
    */
    for (i=0; i<4;i++){
        for(num=1; num<8;num++) {
            ///movimento in alto a destra
            if (i==0){
                if(controllocoordinate(riga-num, colonna+num) == true) {
                    if(controllocella(s[riga-num][colonna+num]) == true) {
                        scrittura(s, riga-num, colonna+num, false);
                        cont_mosse++;
                    }
                    else{
                        if(controllocolore(s[riga][colonna], s[riga-num][colonna+num]) == true) {
                            break;
                        }
                        else {
                            scrittura(s, riga-num, colonna+num, true);
                            cont_mosse++;
                            break;
                        }
                    }
                }
            }
            ///movimento in basso a destra
            else if (i==1){
                if(controllocoordinate(riga+num, colonna+num) == true) {
                    if(controllocella(s[riga+num][colonna+num]) == true) {
                        scrittura(s, riga+num, colonna+num, false);
                        cont_mosse++;
                    }
                    else{
                        if(controllocolore(s[riga][colonna], s[riga+num][colonna+num]) == true) {
                            break;
                        }
                        else {
                            scrittura(s, riga+num, colonna+num, true);
                            cont_mosse++;
                            break;
                        }
                    }
                }
            }
            ///movimento in basso a sinistra
            else if (i==2){
                if(controllocoordinate(riga+num , colonna-num )== true) {
                    if(controllocella(s[riga+num][colonna-num]) == true) {
                        scrittura(s, riga+num, colonna-num, false);
                        cont_mosse++;
                    }///Stampa sul file .txt le mosse possibili dell'alfiere
                    else{///Stampa sul file .txt le mosse possibili dell'alfiere
                        if(controllocolore(s[riga][colonna], s[riga+num][colonna-num]) == true) {
                            break;
                        }
                        else {
                            scrittura(s, riga+num, colonna-num, true);
                            cont_mosse++;
                            break;
                        }
                    }
                }
            }
            ///movimento in alto a sinistra
            else if (i==3){
                if(controllocoordinate(riga-num, colonna-num) == true) {
                    if(controllocella(s[riga-num][colonna-num]) == true) {
                        scrittura(s, riga-num, colonna-num, false);
                        cont_mosse++;
                    }
                    else{
                        if(controllocolore(s[riga][colonna], s[riga-num][colonna-num]) == true) {
                            break;
                        }
                        else {
                            scrittura(s, riga-num, colonna-num, true);
                            cont_mosse++;
                            break;
                        }
                    }
                }
            }
        }
    }
    if (cont_mosse==0)
        no_move();
}

///Stampa sul file .txt le mosse possibili dell'alfiere
void mosse_torre(Scacchiera s, int riga, int colonna) {
    ///La torre si può muovere formando una croce il cui centro è la sua posizione iniziale (alto, basso, destra, sinistra)
    ///Una delle due coordiante rimane fissa, mentre l'altra incrementa o decrementa
    int cont_mosse=0;
    /*
    A ogni direzione del pezzo assegnamo un numero da 0 a 4 e con un for le scorriamo tutte.
    Con un altro for consideriamo di quanto si può spostare la torre in quella direzione (1, 2, 3 caselle ecc.)
    Per ogni movimento vengono controllate che le coordinate siano accettabili (che esistano sulla scacchiera) e
    se la casella di arrivo è occupata. Se questa è vuota il pezzo si sposta, mentre se è occupata si richiama la funzione
    controllocella() per vedere di che colore è il pezzo che occupa la cella di destinazione, se è dello stesso colore si esce dal
    ciclo, se è opposto invece mangia.
    */
    for (int i=0; i<4;i++){
        for(int num=1; num<8;num++) {
            ///movimento verso l'alto
            if (i==0){
                if(controllocoordinate(riga-num, colonna) == true) {
                    if(controllocella(s[riga-num][colonna]) == true) {
                        scrittura(s, riga-num, colonna, false);
                        cont_mosse++;
                    }
                    else{
                        if(controllocolore(s[riga][colonna], s[riga-num][colonna]) == true) {
                            break;
                        }
                        else {
                            scrittura(s, riga-num, colonna, true);
                            cont_mosse++;
                            break;
                        }
                    }
                }
            }
            ///movimento verso destra
            else if (i == 1){
                if(controllocoordinate(riga, colonna+num)) {
                    if(controllocella(s[riga][colonna+num]) == true) {
                        scrittura(s, riga, colonna+num, false);
                        cont_mosse++;
                    }
                    else{
                        if(controllocolore(s[riga][colonna], s[riga][colonna+num]) == true) {
                            break;
                        }
                        else {
                            scrittura(s, riga, colonna+num, true);
                            cont_mosse++;
                            break;
                        }
                    }
                }
            }
            ///movimento verso il basso
            else if (i==2){
                if(controllocoordinate(riga+num, colonna) == true) {
                    if(controllocella(s[riga+num][colonna]) == true) {
                        scrittura(s, riga+num, colonna, false);
                        cont_mosse++;
                    }
                    else{
                        if(controllocolore(s[riga][colonna], s[riga+num][colonna]) == true) {
                            break;
                        }
                        else {
                            scrittura(s, riga+num, colonna, true);
                            cont_mosse++;
                            break;
                        }
                    }
                }
            }
            ///movimento verso sinistra
            else if (i==3){
                if(controllocoordinate(riga, colonna-num)==true) {
                    if(controllocella(s[riga][colonna-num])==true) {
                        scrittura(s, riga, colonna-num, false);
                        cont_mosse++;
                    }
                    else{
                        if(controllocolore(s[riga][colonna], s[riga][colonna-num]) == true){
                            break;
                        }
                        else {
                            scrittura(s, riga, colonna-num, true);
                            cont_mosse++;
                            break;
                        }
                    }
                }
            }
        }
    }
    if (cont_mosse==0)
        no_move();
}

///Stampa sul file .txt le mosse possibili della regina
void mosse_regina(Scacchiera s, int riga, int colonna){
    ///Le mosse della regina sono l'unione tra le mosse della torre e le mosse dell'alfiere
    mosse_alfiere(s, riga, colonna);
    mosse_torre(s, riga, colonna);
}

///Stampa sul file .txt le mosse possibili del re
void mosse_re(Scacchiera s, int riga, int colonna) {
    ///Il movimento del re è come quello della regina, ma lo spostamento è di una sola casella per volta.
    int cont_mosse=0;
    /*
    A ogni direzione del pezzo assegnamo un numero da 0 a 8 e con un for le scorriamo tutte.
    Per ogni movimento vengono controllate che le coordinate siano accettabili (che esistano sulla scacchiera) e
    se la casella di arrivo è occupata. Se questa è vuota il pezzo si sposta, mentre se è occupata si ferma.
    */
    int i;///Stampa sul file .txt le mosse possibili dell'alfiere
    for(i=0; i<8; i++) {
        ///spostamento verso l'alto
        if(i==0) {
            if(controllocoordinate(riga-1, colonna) == true) {
                    if(controllocella(s[riga-1][colonna]) == true) {
                        scrittura(s, riga-1, colonna, false);
                        cont_mosse++;
                    }
            }
        }
        ///spostamento in alto a destra
        if(i==1) {
            if(controllocoordinate(riga-1, colonna+1) == true) {
                    if(controllocella(s[riga-1][colonna+1]) == true) {
                        scrittura(s, riga-1, colonna+1, false);
                        cont_mosse++;
                    }
            }
        }
        ///spostamento verso destra
        if(i==2) {
            if(controllocoordinate(riga, colonna+1) == true) {
                    if(controllocella(s[riga][colonna+1]) == true) {
                        scrittura(s, riga, colonna+1, false);
                        cont_mosse++;
                    }
            }
        }
        ///spostamento in basso a destra
        if(i==3) {
            if(controllocoordinate(riga+1, colonna+1) == true) {
                    if(controllocella(s[riga+1][colonna+1]) == true) {
                        scrittura(s, riga+1, colonna+1, false);
                        cont_mosse++;
                    }
            }
        }
        ///spostamento verso il basso
        if(i==4) {
            if(controllocoordinate(riga+1, colonna) == true) {
                    if(controllocella(s[riga+1][colonna]) == true) {
                        scrittura(s, riga+1, colonna, false);
                        cont_mosse++;
                    }
            }
        }
        ///spostamento in basso a sinistra
        if(i==5) {
            if(controllocoordinate(riga+1, colonna-1) == true) {
                    if(controllocella(s[riga+1][colonna-1]) == true) {
                        scrittura(s, riga+1, colonna-1, false);
                        cont_mosse++;
                    }
            }
        }
        ///spostamento verso sinistra
        if(i==6) {
            if(controllocoordinate(riga, colonna-1 )== true) {
                    if(controllocella(s[riga][colonna-1]) == true) {
                        scrittura(s, riga, colonna-1, false);
                        cont_mosse++;
                    }
            }
        }
        ///spostamento in alto a sinistra
        if(i==7) {
            if(controllocoordinate(riga-1, colonna-1)==true) {
                    if(controllocella(s[riga-1][colonna-1])==true) {
                        scrittura(s, riga-1, colonna-1, false);
                        cont_mosse++;
                    }
            }
        }
    }
    if(cont_mosse==0)
        no_move();
}

///Stampa sul file .txt le mosse possibili del re
void mosse_pedone(Scacchiera s, int riga, int colonna) {
    ///Il pedone può muoversi in avanti di una casella e mangiare di lato.
    ///Non può muoversi lateralmente o mangiare in avanti.
    int cont_mosse=0;
    /*
    Differenziamo per prima cosa se il pedone considerato è bianco (il movimento sarà verso l'alto) o nero
    (il movimento sarà verso il basso).
    Controlliamo prima se a destra o a sinistra ci sono dei pezzi di colore opposto che il pedone può mangiare.
    Se non ci sono controlliamo la casella davanti (bianco) o dietro (nera). Se questa è libera effettuiamo lo
    spostamento.
    */
    if(s[riga][colonna].colore == white) {
        ///controllo cella a sinistra
        if (controllocoordinate(riga-1, colonna-1) == true) {
            if(controllocella(s[riga-1][colonna-1]) == false) {
                if(controllocolore(s[riga][colonna], s[riga-1][colonna-1]) == false) {
                    scrittura(s, riga-1, colonna-1, true);
                    cont_mosse++;
                }
            }
        }
        ///controllo cella a destra
        if(controllocoordinate(riga-1, colonna+1) == true) {
            if(controllocella(s[riga-1][colonna+1]) == false) {
                if(controllocolore(s[riga][colonna], s[riga-1][colonna+1]) == false) {
                    scrittura(s, riga-1, colonna+1, true);
                    cont_mosse++;
                }
            }
        }
        ///movimento in avanti
        if(controllocoordinate(riga-1, colonna) == true) {
            if(controllocella(s[riga-1][colonna]) == true) {
                scrittura(s, riga-1, colonna, false);
                cont_mosse++;
            }
        }
   }
   else {
        ///controllo cella a destra
        if (controllocoordinate(riga+1, colonna-1) == true) {
            if(controllocella(s[riga+1][colonna-1]) == false) {
                if(controllocolore(s[riga][colonna], s[riga+1][colonna-1]) == false) {
                    scrittura(s, riga+1, colonna-1, true);
                    cont_mosse++;
                }
            }
        }
        ///controllo cella a sinistra
        if(controllocoordinate(riga+1, colonna+1) == true) {
            if(controllocella(s[riga+1][colonna+1]) == false) {
                if(controllocolore(s[riga][colonna], s[riga+1][colonna+1]) == false) {
                    scrittura(s, riga+1, colonna+1, true);
                    cont_mosse++;
                }
            }
        }
        ///movimento in avanti
        if(controllocoordinate(riga+1, colonna) == true) {
            if(controllocella(s[riga+1][colonna]) == true) {
                scrittura(s, riga+1, colonna, false);
                cont_mosse++;
            }
        }
   }
   if (cont_mosse==0)
        no_move();
}

///Stampa sul file .txt le mosse possibili del cavallo
void mosse_cavallo(Scacchiera s, int riga, int colonna) {
    ///Il cavallo effettua un movimento a L in ogni direzione
    int cont_mosse = 0;
    /*
    A ogni direzione del pezzo assegnamo un numero da 0 a 4 e con un for le scorriamo tutte.
    Il cavallo può effettuare una sola L alla volta per ogni direzione./*
    A ogni direzione del pezzo assegnamo un numero da 0 a 4 e con un for le scorriamo tutte.
    Con un altro for consideriamo di quanto si può spostare la torre in quella direzione (1, 2, 3 caselle ecc.)
    Per ogni movimento vengono controllate che le coordinate siano accettabili (che esistano sulla scacchiera) e
    se la casella di arrivo è occupata. Se questa è vuota il pezzo si sposta, mentre se è occupata si richiama la funzione
    controllocella() per vedere di che colore è il pezzo che occupa la cella di destinazione, se è bianco si esce dal ciclo
    se è nero invece mangia.
    */
    int i;
    for(i=0; i<8; i++) {
        if(i == 0) {
            if(controllocoordinate(riga-2, colonna+1) == true) {
                if(controllocella(s[riga-2][colonna+1]) == true) {
                    scrittura(s, riga-2, colonna+1, false);
                    cont_mosse++;
                }
                else {
                    if(controllocolore(s[riga][colonna], s[riga-2][colonna+1]) == false) {
                        scrittura(s, riga-2, colonna+1, true);
                        cont_mosse++;
                    }
                }
            }
        }
        if(i == 1) {
            if(controllocoordinate(riga-1, colonna+2) == true) {
                if(controllocella(s[riga-1][colonna+2]) == true) {
                    scrittura(s, riga-1, colonna+2, false);
                    cont_mosse++;
                }
                else {
                    if(controllocolore(s[riga][colonna], s[riga-1][colonna+2]) == false) {
                        scrittura(s, riga-1, colonna+2, true);
                        cont_mosse++;
                    }
                }
            }
        }
        if(i == 2) {
            if(controllocoordinate(riga+1, colonna+2) == true) {
                if(controllocella(s[riga+1][colonna+2]) == true) {
                    scrittura(s, riga+1, colonna+2, false);
                    cont_mosse++;
                }
                else {
                    if(controllocolore(s[riga][colonna], s[riga+1][colonna+2]) == false) {
                        scrittura(s, riga+1, colonna+2, true);
                        cont_mosse++;
                    }
                }
            }
        }
        if(i == 3) {
            if(controllocoordinate(riga+2, colonna+1) == true) {
                if(controllocella(s[riga+2][colonna+1]) == true) {
                    scrittura(s, riga+2, colonna+1, false);
                    cont_mosse++;
                }
                else {
                    if(controllocolore(s[riga][colonna], s[riga+2][colonna+1]) == false) {
                        scrittura(s, riga+2, colonna+1, true);
                        cont_mosse++;
                    }
                }
            }
        }
        if(i == 4) {
            if(controllocoordinate(riga+2, colonna-1) == true) {
                if(controllocella(s[riga+2][colonna-1]) == true) {
                    scrittura(s, riga+2, colonna-1, false);
                    cont_mosse++;
                }
                else {
                    if(controllocolore(s[riga][colonna], s[riga+2][colonna-1]) == false) {
                        scrittura(s, riga+2, colonna-1, true);
                        cont_mosse++;
                    }
                }
            }
        }
        if(i == 5) {
            if(controllocoordinate(riga+1, colonna-2) == true) {
                if(controllocella(s[riga+1][colonna-2]) == true) {
                    scrittura(s, riga+1, colonna-2, false);
                    cont_mosse++;
                }
                else {
                    if(controllocolore(s[riga][colonna], s[riga+1][colonna-2]) == false) {
                        scrittura(s, riga+1, colonna-2, true);
                        cont_mosse++;
                    }
                }
            }
        }
        if(i == 6) {
            if(controllocoordinate(riga-1, colonna-2) == true) {
                if(controllocella(s[riga-1][colonna-2]) == true) {
                    scrittura(s, riga-1, colonna-2, false);
                    cont_mosse++;
                }
                else {
                    if(controllocolore(s[riga][colonna], s[riga-1][colonna-2]) == false) {
                        scrittura(s, riga-1, colonna-2, true);
                        cont_mosse++;
                    }
                }
            }
        }
        if(i == 7) {
            if(controllocoordinate(riga-2, colonna-1) == true) {
                if(controllocella(s[riga-2][colonna-1]) == true) {
                    scrittura(s, riga-2, colonna-1, false);
                    cont_mosse++;
                }
                else {
                    if(controllocolore(s[riga][colonna], s[riga-2][colonna-1]) == false) {
                        scrittura(s, riga-2, colonna-1, true);
                        cont_mosse++;
                    }
                }
            }
        }
    }
    if(cont_mosse == 0)
        no_move();
}

///controlla se le due celle inserite hanno lo stesso colore
bool controllocoordinate(int riga, int colonna) {
     bool controllo = false;
     if((riga>=0)&&(riga<8)&&(colonna>=0)&&(colonna<8)) {
        controllo = true;
     }
     return controllo;
}

///controlla se la cella selezionata è vuota
bool controllocella(Cella cel){
     bool controllo = false;
     if((cel.colore == noColor)&&(cel.pezzo == noPiece))
        controllo = true;
     return controllo;
}

///controlla se le due celle inserite hanno lo stesso colore
bool controllocolore(Cella c1, Cella c2){
     bool controllo = false;
     if(c1.colore == c2.colore)
        controllo = true;
     return controllo;
}

///funzione che stampa sul file .txt
void scrittura(Scacchiera s, int riga, int colonna, bool mangia) {
    Mcoord mat;
    mat.riga=riga;
    mat.col=colonna;
    Ccoord sca;
    sca = converti(mat);
    ofstream mioFile;
    mioFile.open("mosse.txt", ios::out| ios::app);
    if (mangia == true){
        mioFile << "*";
        mioFile << convertiInChar(s[riga][colonna]);
        mioFile << "-";
        mioFile << sca.col;
        mioFile <<sca.riga<<endl;
    }
    else {
        mioFile << sca.col;
        mioFile << sca.riga<<endl;
    }
    mioFile.close();
}

/// converte coordinate matrice in coordinate scacchistiche
Ccoord converti(Mcoord m){
	Ccoord c;
	c.col = 'a'+(m.col);
	c.riga = 8 - m.riga;
	return c;
}

/// converte coordinate scacchistiche in coordinate matrice
Mcoord converti(Ccoord c){
    Mcoord m;
    m.col = c.col - 'a';
    m.riga = 8 - c.riga;
    return m;
}

///funzione che stampa l'intestazione sul file .txt
void intestazione() {
    ofstream mioFile;
    mioFile.open("mosse.txt", ios::out);
    mioFile << "Alessia D'Aniello 285143" << endl;
    mioFile << "Camilla Franceschini 282280" << endl;
    mioFile.close();
}

///funzione che stampa sul file .txt "no move" nel caso in cui il pezzo selezionato non possa muoversi in nessuna direzione
void no_move() {
    ofstream mioFile;
    mioFile.open("mosse.txt", ios::out | ios::app);
    mioFile << "no move" << endl;
    mioFile.close();
}
