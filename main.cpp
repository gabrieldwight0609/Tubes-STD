#include <iostream>
#include "Tubes.h""

using namespace std;

int main() {
    // 1. Deklarasi Variabel Struktur Data
    ListLibrary Library;
    ListPlaylist Playlist;
    QueueLagu UpNext;

    // 2. Inisialisasi (Create)
    createLibrary(Library);
    createPlaylist(Playlist);
    createQueue(UpNext);

    // 3. Isi Data Dummy
    initData(Library);

    // 4. Variabel Menu
    int role = 1;      // Inisialisasi awal (bukan 0) agar loop jalan pertama kali
    string inputTemp;  // Variabel bantuan untuk membaca input

    // 5. Loop Menu Utama
    while (role != 0) {
        cout << "\n=== SPOTIPI MUSIC PLAYER ===" << endl;
        cout << "Masuk sebagai:" << endl;
        cout << "1. Admin" << endl;
        cout << "2. User" << endl;
        cout << "0. Keluar" << endl;

        cout << "Pilihan: ";
        getline(cin, inputTemp); // Pakai getline agar aman dari sisa buffer

        // Konversi string ke integer
        if (inputTemp.empty()) {
            role = -1; // Anggap pilihan tidak valid jika kosong
        } else {
            // Menggunakan stoi untuk konversi
            // (Bisa ditambahkan try-catch jika ingin menangani input huruf)
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
