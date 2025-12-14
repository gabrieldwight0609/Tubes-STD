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

adrLagu searchLaguByID(ListLibrary L, string idLagu) {
    adrArtis P = L.first;
    while (P != nullptr) {
        adrLagu C = P->child;
        while (C != nullptr) {
            if (C->info.idLagu == idLagu) return C;
            C = C->next;
        }
        P = P->next;
    }
    return nullptr;
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

void createGraph(Graph &G) {
    G.firstVertex = nullptr;
}

void addVertex(Graph &G, string idLagu) {
    // Cek apakah vertex sudah ada
    adrVertex P = G.firstVertex;
    while (P != nullptr) {
        if (P->idLagu == idLagu)
            return; // Jika sudah ada
        P = P->next;
    }

    // Tambah vertex baru di depan (Insert First)
    adrVertex V = new ElmVertex;
    V->idLagu = idLagu;
    V->firstEdge = nullptr;
    V->next = G.firstVertex;
    G.firstVertex = V;
}

void addEdge(Graph &G, string idLaguAsal, string idLaguTujuan) {
    // 1. Cari vertex asal
    adrVertex V = G.firstVertex;
    while (V != nullptr && V->idLagu != idLaguAsal) {
        V = V->next;
    }

    if (V != nullptr) {
        // Cek apakah edge sudah ada (hindari duplikasi)
        adrEdge cek = V->firstEdge;
        while(cek != nullptr) {
            if(cek->idLaguTujuan == idLaguTujuan) return;
            cek = cek->next;
        }

        // 2. Tambah edge baru
        adrEdge E = new ElmEdge;
        E->idLaguTujuan = idLaguTujuan;
        E->next = V->firstEdge;
        V->firstEdge = E;
    }
}

void showRecommendations(Graph G, ListLibrary L, string idLaguCurrent) {
    // Cari vertex lagu saat ini
    adrVertex V = G.firstVertex;
    while (V != nullptr && V->idLagu != idLaguCurrent) {
        V = V->next;
    }

    cout << "\n=== REKOMENDASI LAGU SERUPA ===" << endl;
    if (V != nullptr) {
        adrEdge E = V->firstEdge;
        if (E == nullptr) {
            cout << "Tidak ada rekomendasi untuk lagu ini." << endl;
        }
        while (E != nullptr) {
            // Ambil detail lagu dari MLL biar bisa print Judulnya (bukan cuma ID)
            adrLagu recSong = searchLaguByID(L, E->idLaguTujuan);
            if (recSong != nullptr) {
                cout << "- " << recSong->info.judul << " (" << recSong->info.genre << ")" << endl;
            }
            E = E->next;
        }
    } else {
        cout << "Lagu ini belum terdaftar di sistem rekomendasi." << endl;
    }
}

void removeSongFromPlaylist(ListPlaylist &PL, adrLagu songPtr) {
    if (isEmptyPlaylist(PL)) return;

    adrPlaylist P = PL.first;
    while (P != nullptr) {
        adrPlaylist nextNode = P->next;

        if (P->songPtr == songPtr) {

            if (P == PL.current) PL.current = nullptr;

            if (P == PL.first && P == PL.last) {
                PL.first = nullptr; PL.last = nullptr;
            } else if (P == PL.first) {
                PL.first = P->next;
                PL.first->prev = nullptr;
            } else if (P == PL.last) {
                PL.last = P->prev;
                PL.last->next = nullptr;
            } else {
                P->prev->next = P->next;
                P->next->prev = P->prev;
            }
            P = nullptr;
        }
        P = nextNode;
    }
}

void removeSongFromQueue(QueueLagu &Q, adrLagu songPtr) {
    if (Q.head == nullptr) return;

    adrQueue P = Q.head;
    adrQueue prev = nullptr;

    while (P != nullptr) {
        adrQueue nextNode = P->next;
        if (P->songPtr == songPtr) {
            if (P == Q.head && P == Q.tail) {
                Q.head = nullptr; Q.tail = nullptr;
            } else if (P == Q.head) {
                Q.head = P->next;
            } else if (P == Q.tail) {
                Q.tail = prev;
                Q.tail->next = nullptr;
            } else {
                prev->next = P->next;
            }
            P = nullptr;
            P = nextNode;
            continue;
        }
        prev = P;
        P = nextNode;
    }
}

void removeSongFromGraph(Graph &G, string idLagu) {
    // 1. Hapus vertexnya sendiri
    adrVertex V = G.firstVertex;
    adrVertex prevV = nullptr;
    while(V != nullptr && V->idLagu != idLagu) {
        prevV = V;
        V = V->next;
    }

    if (V != nullptr) {
        // Hapus semua edge keluar dari vertex ini dulu
        adrEdge E = V->firstEdge;
        while (E != nullptr) {
            adrEdge hapusE = E;
            E = E->next;
            hapusE = nullptr;
        }
        // Hapus vertex dari list
        if (prevV == nullptr) G.firstVertex = V->next;
        else prevV->next = V->next;
        V = nullptr;
    }

    // 2. Hapus edge di vertex lain yang mengarah ke lagu ini
    V = G.firstVertex;
    while(V != nullptr) {
        adrEdge E = V->firstEdge;
        adrEdge prevE = nullptr;
        while(E != nullptr) {
            if (E->idLaguTujuan == idLagu) {
                if (prevE == nullptr) V->firstEdge = E->next;
                else prevE->next = E->next;

                adrEdge hapus = E;
                E = E->next;
                hapus = nullptr;
            } else {
                prevE = E;
                E = E->next;
            }
        }
        V = V->next;
    }
}

void playNextRecommendation(Graph G, ListLibrary L, adrLagu &laguSedangDiputar) {
    if (laguSedangDiputar == nullptr) {
        cout << "[INFO] Tidak ada lagu yang sedang aktif." << endl;
        return;
    }

    // 1. Cari posisi lagu saat ini di graf
    adrVertex V = G.firstVertex;
    while (V != nullptr && V->idLagu != laguSedangDiputar->info.idLagu) {
        V = V->next;
    }

    // 2. Cek apakah punya rekomendasi (edge)
    if (V != nullptr && V->firstEdge != nullptr) {
        // Ambil ID lagu rekomendasi pertama
        string nextID = V->firstEdge->idLaguTujuan;

        // Cari data aslinya di library
        adrLagu nextSong = searchLaguByID(L, nextID);

        if (nextSong != nullptr) {
            // Update lagu yang sedang diputar
            laguSedangDiputar = nextSong;
            cout << "[AUTOPLAY] Memutar Rekomendasi: " << nextSong->info.judul
                 << " (" << nextSong->info.genre << ")" << endl;
        }
    } else {
        cout << "[INFO] Tidak ada rekomendasi lagu selanjutnya." << endl;
    }
}

void deleteLagu(ListLibrary &L, ListPlaylist &PL, QueueLagu &Q, Graph &G ,string judulLagu) {
    adrArtis P = L.first;
    bool found = false;

    while (P != nullptr && !found) {
        adrLagu C = P->child;
        adrLagu prevC = nullptr;

        while (C != nullptr) {
            if (C->info.judul == judulLagu) {
                // 1. Bersihkan di playlist dan queue
                removeSongFromPlaylist(PL, C);
                removeSongFromQueue(Q, C);
                removeSongFromGraph(G, C ->info.idLagu);

                // 2. Hapus dari MLL
                if (prevC == nullptr) {
                    P->child = C->next;
                } else {
                    prevC->next = C->next;
                }

                C = nullptr;
                found = true;
                cout << "[SUKSES] Lagu '" << judulLagu << "' dihapus." << endl;
                break;
            }
            prevC = C;
            C = C->next;
        }
        P = P->next;
    }
    if (!found) cout << "[INFO] Lagu tidak ditemukan." << endl;
}

void deleteArtis(ListLibrary &L, ListPlaylist &PL, QueueLagu &Q, Graph &G ,string namaArtis) {
    if (isEmptyLibrary(L)) {
        cout << "[INFO] Library kosong." << endl;
        return;
    }

    adrArtis P = L.first;
    adrArtis Prec = nullptr;

    while (P != nullptr && P->info.namaArtis != namaArtis) {
        Prec = P;
        P = P->next;
    }

    if (P != nullptr) {
        // 1. Hapus semua anak (lagu) satu per satu
        adrLagu C = P->child;
        while (C != nullptr) {
            adrLagu hapus = C;
            C = C->next;

            // Bersihkan referensi user sebelum delete
            removeSongFromPlaylist(PL, hapus);
            removeSongFromQueue(Q, hapus);
            removeSongFromGraph(G, hapus ->info.idLagu);

            hapus = nullptr;
        }

        // 2. Hapus Node Artis
        if (Prec == nullptr) {
            L.first = P->next;
        } else {
            Prec->next = P->next;
        }
        P = nullptr;
        cout << "[SUKSES] Artis '" << namaArtis << "' dan semua lagunya dihapus." << endl;
    } else {
        cout << "[INFO] Artis tidak ditemukan." << endl;
    }
}



void initData(ListLibrary &L, Graph &G) {
    adrArtis A1 = createElmArtis({"A01", "Tulus"});
    adrArtis A2 = createElmArtis({"A02", "Sheila On 7"});
    insertArtis(L, A1);
    insertArtis(L, A2);

    insertLagu(A1, createElmLagu({"L01", "Hati-Hati di Jalan", "Pop", 2022}));
    insertLagu(A1, createElmLagu({"L02", "Monokrom", "Pop", 2016}));
    insertLagu(A2, createElmLagu({"L03", "Dan", "Pop Rock", 1999}));
    insertLagu(A2, createElmLagu({"L04", "Seberapa Pantas", "Pop Rock", 2002}));

    addVertex(G, "L01"); addVertex(G, "L02");
    addVertex(G, "L03"); addVertex(G, "L04");

    // 3. Data Koneksi (Edge) - Misal karena Genre sama
    // Tulus mirip Tulus
    addEdge(G, "L01", "L02"); addEdge(G, "L02", "L01");
    // SO7 mirip SO7
    addEdge(G, "L03", "L04"); addEdge(G, "L04", "L03");
}

void menuAdmin(ListLibrary &L, ListPlaylist &PL, QueueLagu &Q, Graph &G) {
    int pil = 1;
    string inputTemp;
    while (pil != 0) {
        cout << "\n--- MENU ADMIN ---" << endl;
        cout << "1. Tambah Artis" << endl;
        cout << "2. Tambah Lagu ke Artis (+ Auto Rekomendasi)" << endl;
        cout << "3. Lihat Library" << endl;
        cout << "4. Hapus Artis" << endl;
        cout << "5. Hapus Lagu" << endl;
        cout << "0. Kembali" << endl;

        cout << "Pilihan: "; getline(cin, inputTemp);
        if (inputTemp.empty()){
                pil = -1;
        } else {
            pil = stoi(inputTemp);
        }

        if (pil == 1) {
            InfotypeArtis data;
            cout << "ID Artis: "; getline(cin, data.idArtis);
            cout << "Nama Artis: "; getline(cin, data.namaArtis);
            insertArtis(L, createElmArtis(data));

        } else if (pil == 2) {
            string namaArtis;
            cout << "Nama Artis Tujuan: "; getline(cin, namaArtis);
            adrArtis P = searchArtis(L, namaArtis);

            if (P != nullptr) {
                InfotypeLagu data;
                cout << "ID Lagu: "; getline(cin, data.idLagu);
                cout << "Judul: "; getline(cin, data.judul);
                cout << "Genre: "; getline(cin, data.genre); // Genre menjadi penghubung
                cout << "Tahun: "; getline(cin, inputTemp);
                data.tahun = stoi(inputTemp);

                // 1. Masukkan ke library
                insertLagu(P, createElmLagu(data));

                // 2. Masukkan ke graf (Sebagai vertex Baru)
                addVertex(G, data.idLagu);

                cout << "[SYSTEM] Sedang mencari lagu dengan genre '" << data.genre << "'..." << endl;
                int countConnect = 0;

                // Loop ke seluruh Artis di library
                adrArtis scanArtis = L.first;
                while (scanArtis != nullptr) {
                    // Loop ke seluruh lagu milik artis tersebut
                    adrLagu scanLagu = scanArtis->child;
                    while (scanLagu != nullptr) {
                        if (scanLagu->info.genre == data.genre && scanLagu->info.idLagu != data.idLagu) {
                            addEdge(G, data.idLagu, scanLagu->info.idLagu);
                            addEdge(G, scanLagu->info.idLagu, data.idLagu);

                            countConnect++;
                        }
                        scanLagu = scanLagu->next;
                    }
                    scanArtis = scanArtis->next;
                }

                cout << "[SUKSES] Lagu ditambahkan." << endl;

                if (countConnect > 0) {
                    cout << "[INFO] Otomatis terhubung dengan " << countConnect << " lagu bergenre sama." << endl;
                } else {
                    cout << "[INFO] Belum ada lagu lain dengan genre ini." << endl;
                }
            } else {
                cout << "Artis tidak ditemukan!" << endl;
            }
        } else if (pil == 3) {
            showLibrary(L);
        } else if (pil == 4) {
            string nama;
            cout << "Nama Artis: "; getline(cin, nama);
            deleteArtis(L, PL, Q, G, nama);
        } else if (pil == 5) {
            string judul;
            cout << "Judul Lagu: "; getline(cin, judul);
            deleteLagu(L, PL, Q, G, judul);
        }
    }
}

void menuUser(ListLibrary &L, ListPlaylist &PL, QueueLagu &Q, Graph &G) {
    int pil = 1;
    string inputTemp;
    adrLagu laguSedangDiputar = nullptr;

    while (pil != 0) {
        cout << "\n--- MENU USER ---" << endl;

        if (laguSedangDiputar != nullptr) {
            cout << "[STATUS] Sedang Memutar: " << laguSedangDiputar->info.judul << endl;
        } else {
            cout << "[STATUS] Tidak ada lagu diputar." << endl;
        }

        cout << "1. Cari & Tambah ke Playlist" << endl;
        cout << "2. Cari & Putar Langsung (Dari Library)" << endl;
        cout << "3. Lihat Playlist" << endl;
        cout << "4. Play dari Playlist (Current)" << endl;
        cout << "5. Next Song" << endl;
        cout << "6. Prev Song" << endl;
        cout << "7. Tambah ke Queue" << endl;
        cout << "8. Lihat Queue" << endl;
        cout << "9. Cek Rekomendasi (Dari Lagu Sedang Diputar)" << endl;
        cout << "0. Kembali" << endl;

        cout << "Pilihan: "; getline(cin, inputTemp);
        if (inputTemp.empty()){
            pil = -1;
        } else {
            pil = stoi(inputTemp);
        }

        if (pil == 1) {
            string judul;
            cout << "Cari Judul Lagu: "; getline(cin, judul);
            adrLagu P = searchLagu(L, judul);
            if (P != nullptr) {
                addToPlaylist(PL, P);
            } else {
                cout << "Lagu tidak ditemukan." << endl;
            }
        } else if (pil == 2) {
            string judul;
            cout << "Cari Judul Lagu untuk Diputar: "; getline(cin, judul);
            adrLagu P = searchLagu(L, judul);
            if (P != nullptr) {
                laguSedangDiputar = P;
                cout << "[PLAYER] Memutar dari Library: " << P->info.judul << endl;
            } else {
                cout << "Lagu tidak ditemukan." << endl;
            }
        } else if (pil == 3) {
            showPlaylist(PL);
        } else if (pil == 4) {
            playCurrent(PL);
            if (PL.current != nullptr) laguSedangDiputar = PL.current->songPtr;
        } else if (pil == 5) {
            if (!isEmptyQueue(Q)) {
                adrLagu nextSong;
                dequeue(Q, nextSong);
                cout << "[QUEUE] Memutar: " << nextSong->info.judul << endl;
                laguSedangDiputar = nextSong;
            } else if (PL.current != nullptr) {
                if (PL.current->next != nullptr) {
                    playNext(PL);
                    laguSedangDiputar = PL.current->songPtr;
                } else {
                    cout << "[INFO] Akhir dari Playlist. Mencari rekomendasi..." << endl;
                    playNextRecommendation(G, L, laguSedangDiputar);
                    PL.current = nullptr;
                }
            } else {
                playNextRecommendation(G, L, laguSedangDiputar);
            }
        } else if (pil == 6) {
            playPrev(PL);
            if (PL.current != nullptr) laguSedangDiputar = PL.current->songPtr;
        } else if (pil == 7) {
            string judul;
            cout << "Judul Lagu: "; getline(cin, judul);
            adrLagu P = searchLagu(L, judul);
            if (P != nullptr){
                enqueue(Q, P);
            } else {
                cout << "Lagu tidak ditemukan." << endl;
            }
        } else if (pil == 8) {
            showQueue(Q);
        } else if (pil == 9) {
            if (laguSedangDiputar != nullptr) {
                cout << "Mencari rekomendasi serupa dengan: " << laguSedangDiputar->info.judul << endl;
                showRecommendations(G, L, laguSedangDiputar->info.idLagu);
            } else {
                cout << "Silakan putar lagu terlebih dahulu (dari Playlist atau Library)." << endl;
            }
        }
    }
}
