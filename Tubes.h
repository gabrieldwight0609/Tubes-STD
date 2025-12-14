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

typedef struct ElmVertex *adrVertex;
typedef struct ElmEdge *adrEdge;

struct ElmEdge {
    string idLaguTujuan; 
    adrEdge next;
};

struct ElmVertex {
    string idLagu; 
    adrEdge firstEdge;
    adrVertex next;
};

struct Graph {
    adrVertex firstVertex;
};

void createLibrary(ListLibrary &L);
bool isEmptyLibrary(ListLibrary L);
adrArtis createElmArtis(InfotypeArtis data);
adrLagu createElmLagu(InfotypeLagu data);
void insertArtis(ListLibrary &L, adrArtis P);
void insertLagu(adrArtis PArtis, adrLagu P);
adrArtis searchArtis(ListLibrary L, string namaArtis);
adrLagu searchLagu(ListLibrary L, string judulLagu);
adrLagu searchLaguByID(ListLibrary L, string idLagu);
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

void initData(ListLibrary &L, Graph &G);
void menuAdmin(ListLibrary &L, ListPlaylist &PL, QueueLagu &Q, Graph &G);
void menuUser(ListLibrary &L, ListPlaylist &PL, QueueLagu &Q, Graph &G);


void removeSongFromPlaylist(ListPlaylist &PL, adrLagu songPtr);
void removeSongFromQueue(QueueLagu &Q, adrLagu songPtr);
void deleteLagu(ListLibrary &L, ListPlaylist &PL, QueueLagu &Q, Graph &G, string judulLagu);
void deleteArtis(ListLibrary &L, ListPlaylist &PL, QueueLagu &Q, Graph &G, string namaArtis);

void createGraph(Graph &G);
void addVertex(Graph &G, string idLagu);
void addEdge(Graph &G, string idLaguAsal, string idLaguTujuan);
void showRecommendations(Graph G, ListLibrary L, string idLaguCurrent);
bool isConnected(Graph G, string id1, string id2);
void removeSongFromGraph(Graph &G, string idLagu);
void playNextRecommendation(Graph G, ListLibrary L, adrLagu &laguSedangDiputar);



#endif // TUBES_H_INCLUDED
