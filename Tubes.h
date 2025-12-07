#ifndef TUBES_H_INCLUDED
#define TUBES_H_INCLUDED
#include <iostream>

using namespace std;

struct InfotypeLagu {
    string idLagu;
    string judul;
    string genre;
    int tahun;
};

struct InfotypeArtis {
    string idArtis;
    string namaArtis;
};

// Pointer untuk MLL
typedef struct ElmArtis *adrArtis;
typedef struct ElmLagu *adrLagu;

// Node Anak (Lagu) - Singly Linked List
struct ElmLagu {
    InfotypeLagu info;
    adrLagu next;
};

// Node Induk (Artis) - Singly Linked List
struct ElmArtis {
    InfotypeArtis info;
    adrArtis next;
    adrLagu child; // Pointer ke list anak (Lagu)
};

struct ListLibrary {
    adrArtis first;
};

// ==========================================
// 2. STRUKTUR DATA PLAYLIST (DLL)
// ==========================================

typedef struct ElmPlaylist *adrPlaylist;

struct ElmPlaylist {
    adrLagu songPtr; // Pointer menunjuk ke data lagu asli di MLL (Hemat Memori)
    adrPlaylist next;
    adrPlaylist prev;
};

struct ListPlaylist {
    adrPlaylist first;
    adrPlaylist last;
    adrPlaylist current; // Lagu yang sedang diputar
};

// ==========================================
// 3. STRUKTUR DATA QUEUE (ANTRIAN)
// ==========================================

typedef struct ElmQueue *adrQueue;

struct ElmQueue {
    adrLagu songPtr; // Pointer ke lagu di MLL
    adrQueue next;
};

struct QueueLagu {
    adrQueue head;
    adrQueue tail;
};

// ==========================================
// PROTOTYPE FUNGSI
// ==========================================

// --- MLL (Library) ---
void createLibrary(ListLibrary &L);
bool isEmptyLibrary(ListLibrary L); // [BARU]
adrArtis createElmArtis(InfotypeArtis data);
adrLagu createElmLagu(InfotypeLagu data);
void insertArtis(ListLibrary &L, adrArtis P);
void insertLagu(adrArtis PArtis, adrLagu P);
adrArtis searchArtis(ListLibrary L, string namaArtis);
adrLagu searchLagu(ListLibrary L, string judulLagu);
void deleteLagu(ListLibrary &L, string judulLagu);
void deleteArtis(ListLibrary &L, string namaArtis); // Cascading Delete
void showLibrary(ListLibrary L);

// --- DLL (Playlist) ---
void createPlaylist(ListPlaylist &PL);
bool isEmptyPlaylist(ListPlaylist PL); // [BARU]
void addToPlaylist(ListPlaylist &PL, adrLagu song);
void showPlaylist(ListPlaylist PL);
void playCurrent(ListPlaylist &PL);
void playNext(ListPlaylist &PL);
void playPrev(ListPlaylist &PL);

// --- Queue (Antrian) ---
void createQueue(QueueLagu &Q);
bool isEmptyQueue(QueueLagu Q); // [BARU]
void enqueue(QueueLagu &Q, adrLagu song);
void dequeue(QueueLagu &Q, adrLagu &song); // Output song
void showQueue(QueueLagu Q);

// --- Menu Helpers ---
void initData(ListLibrary &L); // Graph dihapus dari parameter
void menuAdmin(ListLibrary &L);
void menuUser(ListLibrary &L, ListPlaylist &PL, QueueLagu &Q);


#endif // TUBES_H_INCLUDED
