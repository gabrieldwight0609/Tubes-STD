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

typedef struct ElmArtis *adrArtis;
typedef struct ElmLagu *adrLagu;

struct ElmLagu {
    InfotypeLagu info;
    adrLagu next;
};

struct ElmArtis {
    InfotypeArtis info;
    adrArtis next;
    adrLagu child; 
};

struct ListLibrary {
    adrArtis first;
};

typedef struct ElmPlaylist *adrPlaylist;

struct ElmPlaylist {
    adrLagu songPtr; 
    adrPlaylist next;
    adrPlaylist prev;
};

struct ListPlaylist {
    adrPlaylist first;
    adrPlaylist last;
    adrPlaylist current; 
};

typedef struct ElmQueue *adrQueue;

struct ElmQueue {
    adrLagu songPtr; 
    adrQueue next;
};

struct QueueLagu {
    adrQueue head;
    adrQueue tail;
};

void createLibrary(ListLibrary &L);
bool isEmptyLibrary(ListLibrary L); 
adrArtis createElmArtis(InfotypeArtis data);
adrLagu createElmLagu(InfotypeLagu data);
void insertArtis(ListLibrary &L, adrArtis P);
void insertLagu(adrArtis PArtis, adrLagu P);
adrArtis searchArtis(ListLibrary L, string namaArtis);
adrLagu searchLagu(ListLibrary L, string judulLagu);
void deleteLagu(ListLibrary &L, string judulLagu);
void deleteArtis(ListLibrary &L, string namaArtis); 
void showLibrary(ListLibrary L);

void createPlaylist(ListPlaylist &PL);
bool isEmptyPlaylist(ListPlaylist PL);
void addToPlaylist(ListPlaylist &PL, adrLagu song);
void showPlaylist(ListPlaylist PL);
void playCurrent(ListPlaylist &PL);
void playNext(ListPlaylist &PL);
void playPrev(ListPlaylist &PL);

void createQueue(QueueLagu &Q);
bool isEmptyQueue(QueueLagu Q);
void enqueue(QueueLagu &Q, adrLagu song);
void dequeue(QueueLagu &Q, adrLagu &song); 
void showQueue(QueueLagu Q);

void initData(ListLibrary &L); 
void menuAdmin(ListLibrary &L);
void menuUser(ListLibrary &L, ListPlaylist &PL, QueueLagu &Q);


#endif // TUBES_H_INCLUDED

