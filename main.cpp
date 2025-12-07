#include <iostream>
#include "Tubes.h"

using namespace std;

int main() {
    ListLibrary Library;
    ListPlaylist Playlist;
    QueueLagu UpNext;

    createLibrary(Library);
    createPlaylist(Playlist);
    createQueue(UpNext);

    initData(Library);

    int role = 1;     
    string inputTemp;  

    while (role != 0) {
        cout << "\n=== SPOTIPI MUSIC PLAYER ===" << endl;
        cout << "Masuk sebagai:" << endl;
        cout << "1. Admin" << endl;
        cout << "2. User" << endl;
        cout << "0. Keluar" << endl;

        cout << "Pilihan: ";
        getline(cin, inputTemp); 

        if (inputTemp.empty()) {
            role = -1; 
        } else {
            role = stoi(inputTemp);
        }

        if (role == 1) {
            menuAdmin(Library);
        } else if (role == 2) {
            menuUser(Library, Playlist, UpNext);
        }
    }

    return 0;
}

