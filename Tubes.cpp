#include "Tubes.h"

void createLibrary(ListLibrary &L) {
    L.first = nullptr;
}

bool isEmptyLibrary(ListLibrary L) {
    return L.first == nullptr;
}

adrArtis createElmArtis(InfotypeArtis data) {
    adrArtis P = new ElmArtis;
    P->info = data;
    P->next = nullptr;
    P->child = nullptr;
    return P;
}

adrLagu createElmLagu(InfotypeLagu data) {
    adrLagu P = new ElmLagu;
    P->info = data;
    P->next = nullptr;
    return P;
}

void insertArtis(ListLibrary &L, adrArtis P) {
    if (isEmptyLibrary(L)) { 
        L.first = P;
    } else {
        adrArtis Q = L.first;
        while (Q->next != nullptr) {
            Q = Q->next;
        }
        Q->next = P;
    }
}

void insertLagu(adrArtis PArtis, adrLagu P) {
    if (PArtis->child == nullptr) {
        PArtis->child = P;
    } else {
        adrLagu Q = PArtis->child;
        while (Q->next != nullptr) {
            Q = Q->next;
        }
        Q->next = P;
    }
}

adrArtis searchArtis(ListLibrary L, string namaArtis) {
    adrArtis P = L.first;
    while (P != nullptr) {
        if (P->info.namaArtis == namaArtis) {
            return P;
        }
        P = P->next;
    }
    return nullptr;
}

adrLagu searchLagu(ListLibrary L, string judulLagu) {
    adrArtis P = L.first;
    while (P != nullptr) {
        adrLagu C = P->child;
        while (C != nullptr) {
            if (C->info.judul == judulLagu) {
                return C;
            }
            C = C->next;
        }
        P = P->next;
    }
    return nullptr;
}

void deleteArtis(ListLibrary &L, string namaArtis) {
    if (isEmptyLibrary(L)) {
        cout << "Library kosong." << endl;
        return;
    }

    adrArtis P = L.first;
    adrArtis Prec = nullptr;

    while (P != nullptr && P->info.namaArtis != namaArtis) {
        Prec = P;
        P = P->next;
    }

    if (P != nullptr) {
        adrLagu C = P->child;
        while (C != nullptr) {
            adrLagu hapus = C;
            C = C->next;
            hapus = nullptr;
        }

        if (Prec == nullptr) {
            L.first = P->next;
        } else {
            Prec->next = P->next;
        }
        P = nullptr;
        cout << "Artis '" << namaArtis << "' dan semua lagunya berhasil dihapus." << endl;
    } else {
        cout << "Artis tidak ditemukan." << endl;
    }
}

void showLibrary(ListLibrary L) {
    if (isEmptyLibrary(L)) { 
        cout << "Library Kosong." << endl;
        return;
    }

    adrArtis P = L.first;
    while (P != nullptr){
        cout << "[ARTIS] " << P->info.namaArtis << " (ID: " << P->info.idArtis << ")" << endl;
        adrLagu C = P->child;
        if (C == nullptr) {
            cout << "   (Belum ada lagu)" << endl;
        } else {
            while (C != nullptr) {
                cout << "   - " << C->info.judul << " (" << C->info.genre << ", " << C->info.tahun << ")" << endl;
                C = C->next;
            }
        }
        cout << endl;
        P = P->next;
    }
}

void createPlaylist(ListPlaylist &PL) {
    PL.first = nullptr;
    PL.last = nullptr;
    PL.current = nullptr;
}

bool isEmptyPlaylist(ListPlaylist PL) {
    return PL.first == nullptr;
}

void addToPlaylist(ListPlaylist &PL, adrLagu song) {
    adrPlaylist P = new ElmPlaylist;
    P->songPtr = song;
    P->next = nullptr;
    P->prev = nullptr;

    if (isEmptyPlaylist(PL)) {
        PL.first = P;
        PL.last = P;
        PL.current = P; 
    } else {
        P->prev = PL.last;
        PL.last->next = P;
        PL.last = P;
    }
    cout << "Lagu '" << song->info.judul << "' ditambahkan ke Playlist." << endl;
}

void showPlaylist(ListPlaylist PL) {
    if (isEmptyPlaylist(PL)) { 
        cout << "\n(Playlist Kosong)" << endl;
        return;
    }

    cout << "\n=== DAFTAR PLAYLIST ===" << endl;
    adrPlaylist P = PL.first;
    int i = 1;
    while (P != nullptr) {
        cout << i << ". " << P->songPtr->info.judul << " - " << P->songPtr->info.genre;
        if (P == PL.current) cout << " [NOW PLAYING]";
        cout << endl;
        P = P->next;
        i++;
    }
}

void playCurrent(ListPlaylist &PL) {
    if (PL.current != nullptr) {
        cout << "\n[PLAYER] Sedang Memutar: " << PL.current->songPtr->info.judul << endl;
    } else {
        cout << "\n[PLAYER] Tidak ada lagu yang dipilih atau Playlist kosong." << endl;
    }
}

void playNext(ListPlaylist &PL) {
    if (PL.current != nullptr && PL.current->next != nullptr) {
        PL.current = PL.current->next;
        playCurrent(PL);
    } else {
        cout << "[INFO] Sudah di akhir playlist." << endl;
    }
}

void playPrev(ListPlaylist &PL) {
    if (PL.current != nullptr && PL.current->prev != nullptr) {
        PL.current = PL.current->prev;
        playCurrent(PL);
    } else {
        cout << "[INFO] Ini adalah lagu pertama." << endl;
    }
}

void createQueue(QueueLagu &Q) {
    Q.head = nullptr;
    Q.tail = nullptr;
}

bool isEmptyQueue(QueueLagu Q) {
    return Q.head == nullptr;
}

void enqueue(QueueLagu &Q, adrLagu song) {
    adrQueue P = new ElmQueue;
    P->songPtr = song;
    P->next = nullptr;

    if (isEmptyQueue(Q)) { 
        Q.head = P;
        Q.tail = P;
    } else {
        Q.tail->next = P;
        Q.tail = P;
    }
    cout << "Lagu '" << song->info.judul << "' masuk antrian Up Next." << endl;
}

void dequeue(QueueLagu &Q, adrLagu &song) {
    if (isEmptyQueue(Q)) { 
        song = nullptr;
    } else {
        adrQueue P = Q.head;
        song = P->songPtr;
        Q.head = Q.head->next;
        if (Q.head == nullptr) {
            Q.tail = nullptr;
        }
        P = nullptr;
    }
}

void showQueue(QueueLagu Q) {
    if (isEmptyQueue(Q)) { 
        cout << "\n(Antrian Up Next Kosong)" << endl;
        return;
    }

    cout << "\n=== UP NEXT (QUEUE) ===" << endl;
    adrQueue P = Q.head;
    while (P != nullptr) {
        cout << "> " << P->songPtr->info.judul << endl;
        P = P->next;
    }
}

void initData(ListLibrary &L) {
    adrArtis A1 = createElmArtis({"A01", "Tulus"});
    adrArtis A2 = createElmArtis({"A02", "Sheila On 7"});
    insertArtis(L, A1);
    insertArtis(L, A2);

    insertLagu(A1, createElmLagu({"L01", "Hati-Hati di Jalan", "Pop", 2022}));
    insertLagu(A1, createElmLagu({"L02", "Monokrom", "Pop", 2016}));
    insertLagu(A2, createElmLagu({"L03", "Dan", "Pop Rock", 1999}));
    insertLagu(A2, createElmLagu({"L04", "Seberapa Pantas", "Pop Rock", 2002}));
}

void menuAdmin(ListLibrary &L) {
    int pil = 1;
    string inputTemp; 

    while (pil != 0) {
        cout << "\n--- MENU ADMIN ---" << endl;
        cout << "1. Tambah Artis" << endl;
        cout << "2. Tambah Lagu ke Artis" << endl;
        cout << "3. Lihat Library" << endl;
        cout << "4. Hapus Artis (Cascading)" << endl;
        cout << "0. Kembali" << endl;

        cout << "Pilihan: ";
        getline(cin, inputTemp); 

        if (inputTemp.empty()) {
            pil = -1;
        } else {
            pil = stoi(inputTemp); 
        }

        if (pil == 1) {
            InfotypeArtis data;

            cout << "ID Artis: ";
            getline(cin, data.idArtis);

            cout << "Nama Artis: ";
            getline(cin, data.namaArtis);

            insertArtis(L, createElmArtis(data));

        } else if (pil == 2) {
            string namaArtis;
            cout << "Nama Artis Tujuan: ";
            getline(cin, namaArtis);

            adrArtis P = searchArtis(L, namaArtis);
            if (P != NULL) {
                InfotypeLagu data;

                cout << "ID Lagu: ";
                getline(cin, data.idLagu);

                cout << "Judul: ";
                getline(cin, data.judul);

                cout << "Genre: ";
                getline(cin, data.genre);

                cout << "Tahun: ";
                getline(cin, inputTemp); 
                data.tahun = stoi(inputTemp); 

                insertLagu(P, createElmLagu(data));
            } else {
                cout << "Artis tidak ditemukan!" << endl;
            }
        } else if (pil == 3) {
            showLibrary(L);
        } else if (pil == 4) {
            string nama;
            cout << "Nama Artis yang dihapus: ";
            getline(cin, nama);

            deleteArtis(L, nama);
        }
    }
}

void menuUser(ListLibrary &L, ListPlaylist &PL, QueueLagu &Q) {
    int pil = 1;      
    string inputTemp; 

    while (pil != 0) {
        cout << "\n--- MENU USER ---" << endl;
        cout << "1. Cari & Tambah ke Playlist" << endl;
        cout << "2. Lihat Playlist" << endl;
        cout << "3. Play Current Song" << endl;
        cout << "4. Next Song" << endl;
        cout << "5. Prev Song" << endl;
        cout << "6. Tambah ke Queue (Up Next)" << endl;
        cout << "7. Lihat Queue" << endl;
        cout << "0. Kembali" << endl;

        cout << "Pilihan: ";
        getline(cin, inputTemp); 

        if (inputTemp.empty()) {
            pil = -1;
        } else {
            pil = stoi(inputTemp);
        }

        if (pil == 1) {
            string judul;
            cout << "Cari Judul Lagu: ";
            getline(cin, judul);

            adrLagu P = searchLagu(L, judul);
            if (P != NULL) {
                addToPlaylist(PL, P);
            } else {
                cout << "Lagu tidak ditemukan." << endl;
            }

        } else if (pil == 2) {
            showPlaylist(PL);

        } else if (pil == 3) {
            playCurrent(PL);

        } else if (pil == 4) {
            if (!isEmptyQueue(Q)) {
                adrLagu nextSong;
                dequeue(Q, nextSong);
                cout << "[QUEUE] Memutar antrian: " << nextSong->info.judul << endl;
            } else {
                playNext(PL);
            }

        } else if (pil == 5) {
            playPrev(PL);

        } else if (pil == 6) {
            string judul;
            cout << "Judul Lagu: ";
            getline(cin, judul); 

            adrLagu P = searchLagu(L, judul);
            if (P != NULL) {
                enqueue(Q, P);
            } else {
                cout << "Lagu tidak ditemukan." << endl;
            }

        } else if (pil == 7) {
            showQueue(Q);
        }
    }
}


