/* Nama : Irfan Maulid
   Kelas: 2B
   NIM  : 22040061
*/

#include <iostream>
#include <string>
#include <algorithm>
#include <windows.h>
#include <iomanip> 

using namespace std;

void cls() {
	system("cls");
}
void gotoXY(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

struct Produk {
    string nama;
    int harga;
    string kode;
};

void tambahProduk(Produk dataProduk[], int& jumlahProduk) {
    Produk barang;

    gotoXY(7, 1);
    
    cout << "Masukan Nama Barang  : ";
    cin.ignore();
    getline(cin, barang.nama);

    gotoXY(7, 2);
    
    cout << "Masukan Harga Barang :Rp. ";
    cin >> barang.harga;

    cin.ignore();
    gotoXY(7, 3);
    
    cout << "Masukan Kode Barang  : ";
    getline(cin, barang.kode);
    
    int insertPos = 0;
    while (insertPos < jumlahProduk && barang.harga > dataProduk[insertPos].harga) {
        insertPos++;
    }

    for (int i = jumlahProduk; i > insertPos; i--) {
        dataProduk[i] = dataProduk[i - 1];
    }

    dataProduk[insertPos] = barang;
    jumlahProduk++;

    gotoXY(7, 5);
    
    cout << "BARANG BERHASIL DI TAMBHKAN!!" << endl;
    gotoXY(2, 7);system("pause"); 
}

void tampilkanDaftarBarang(Produk dataProduk[], int jumlahProduk) {
    
    gotoXY(7, 1);cout << "========================================================" << endl;
    gotoXY(7, 2);cout << "| No |       Nama       |     Harga    |      Kode     |" << endl;
    gotoXY(7, 3);cout << "========================================================" << endl;
    for (int i = 0; i < jumlahProduk; i++) {
        gotoXY(7, 4 + i);
        cout << "| " << i + 1 << "  | ";
        cout << setw(16) << left << dataProduk[i].nama << " | ";
        cout << setw(12) << right << dataProduk[i].harga << " | ";
        cout << setw(13) << right << dataProduk[i].kode << " |" << endl;
    }
    gotoXY(7, 9);cout << "========================================================" << endl;
}

bool compareProduk(const Produk& a, const Produk& b) {
    return a.harga < b.harga;
}

void bubbleSortProduk(Produk dataProduk[], int jumlahProduk) {
    for (int i = 0; i < jumlahProduk - 1; i++) {
        for (int j = 0; j < jumlahProduk - i - 1; j++) {
            if (dataProduk[j].harga > dataProduk[j + 1].harga) {
                swap(dataProduk[j], dataProduk[j + 1]);
            }
        }
    }

    gotoXY(4, 10);
    cout << "Barang Berhasil Di Urutkan Berdasarkan Harga!" << endl;
}

void cariProduk(Produk dataProduk[], int jumlahProduk, const string& keyword) {
    bool found = false;

    gotoXY(4, 1);
    cout << "Hasil Pencarian Untuk Keyword '" << keyword << "':" << endl;

    for (int i = 0; i < jumlahProduk; i++) {
        if (dataProduk[i].nama.find(keyword) != string::npos) {
            gotoXY(10, 4 + i);
            cout << "Nama: " << dataProduk[i].nama 
			<< ", Harga:Rp. " << dataProduk[i].harga
			<< ", Kode: " << dataProduk[i].kode << endl;
            found = true;
            gotoXY(3, 7);system("pause");
        }
        
    }

    if (!found) {
        gotoXY(2, 5);
        cout << "Barang Tidak Di Temukan." << endl;
        gotoXY(0,7);system("pause");
    }
}
void prosesTransaksi(Produk dataProduk[], int jumlahProduk) {
    int nomorProduk;
    int jumlahBeli;
    char lagi;

    do {
        cls();

        gotoXY(3, 1);
        cout << "=== Proses Transaksi ===" << endl;
		gotoXY(3, 2);
        tampilkanDaftarBarang(dataProduk, jumlahProduk);
        
        gotoXY(3, 12);
        cout << "Pilih nomor produk yang akan dibeli: ";
        cin >> nomorProduk;

        if (nomorProduk >= 1 && nomorProduk <= jumlahProduk) {
            gotoXY(3, 13);
            cout << "Masukkan jumlah yang akan dibeli: ";
            cin >> jumlahBeli;

            if (jumlahBeli > 0) {
                int totalHarga = dataProduk[nomorProduk - 1].harga * jumlahBeli;
                gotoXY(3, 15);
                cout << "Total Harga: " << totalHarga << endl;

                // Tambahkan ke resume transaksi
                Produk barang = dataProduk[nomorProduk - 1];
                for (int i = 0; i < jumlahBeli; i++) {
                    dataProduk[jumlahProduk] = barang;
                    jumlahProduk++;
                }
            } else {
                gotoXY(3, 15);
                cout << "Jumlah beli harus lebih dari 0!" << endl;
            }
        } else {
            gotoXY(3, 13);
            cout << "Nomor produk tidak valid!" << endl;
        }

        gotoXY(3, 17);
        cout << "Apakah ingin membeli lagi? (Y/N): ";
        cin >> lagi;

    } while (toupper(lagi) == 'Y');

    cls();
    gotoXY(3, 1);
    cout << "Transaksi selesai!" << endl;
    gotoXY(3, 3);
    system("pause");
}

void tampilkanResumeTransaksi(Produk dataProduk[], int jumlahProduk) {
    int subtotal = 0;
    int total = 0;

    gotoXY(7, 2);cout << "=================================" << endl;
    gotoXY(7, 3);cout << "| No |       Nama       | Harga |" << endl;
    gotoXY(7, 4);cout << "=================================" << endl;
    for (int i = 0; i < jumlahProduk; i++) {
        gotoXY(7, 5 + i);
        cout << "| " << i + 1 << "  | ";
        cout << setw(16) << left << dataProduk[i].nama << " | ";
        cout << setw(5) << right << dataProduk[i].harga << " |" << endl;

        subtotal += dataProduk[i].harga;
    }
    gotoXY(7, 10);cout << "=================================" << endl;

    total = subtotal;

    gotoXY(5, 7 + jumlahProduk);
    cout << "Subtotal: " << subtotal << endl;
    gotoXY(5, 8 + jumlahProduk);
    cout << "Total   : " << total << endl;
     gotoXY(5, 15);system("pause");
}



int main() {
    const int MAX_PRODUK = 100;
    Produk dataProduk[MAX_PRODUK];
    int jumlahProduk = 0;
    int pilihan;
    int transaksi;
    int resumTransaksi;
    string nama, kelas;
    int nim;
    
cout <<"========================================[SILAHKAN ISI DATA DIRI ANDA UNTUK LOGIN!]======================================"<<endl;
    gotoXY(10, 2);
    cout << " [========== MASUKAN !! ==========]"<<endl;
    gotoXY(7,4);
    cout << " NIM  : ";
    cin >> nim;
    cin.ignore();
    gotoXY(7, 5);
    cout << " Nama : ";
    getline(cin, nama);
    gotoXY(7, 6);
    cout << " Kelas: ";
    getline(cin, kelas);
    
    cls();

    gotoXY(22, 2);cout << "====================[ PROGRAM KASIR TOKO SWALAYAN ]====================\n";
    gotoXY(22, 3);cout << "|        NIM        |            NAMA             |        KELAS      |\n";
    gotoXY(22, 4);cout << "=======================================================================\n";
    gotoXY(22, 5);cout << "|      " << nim << "     |        " << nama << "         |         " << kelas << "        |\n";
    gotoXY(22, 6);cout << "=======================================================================\n\n";
	gotoXY(19, 8);system("pause");
    do {
    	system("cls");
        gotoXY(22, 2);cout <<"========== PROGRAM KASIR TOKO SWALAYAN ==========" << endl;
        gotoXY(10, 4);cout <<"1. Tambahkan Barang yang Akan Di Masukan Maksimal [5]" << endl; 
        gotoXY(10, 5);cout <<"2. Tampilkan Barang Yang Telah Di Masukan" << endl;
        gotoXY(10, 6);cout <<"3. Urutkan Barang Berdasarkan Harga (Bubble Sort)" << endl;
        gotoXY(10, 7);cout <<"4. Cari Barang " << endl;
        gotoXY(10, 8);cout <<"5. Proses Transaksi " << endl;
        gotoXY(10, 9);cout <<"6. Tampilkan resumTransaksi" << endl;
        gotoXY(10, 10);cout <<"7. Keluar Dari Program ini" << endl;
        gotoXY(10, 11);cout <<"Pilihan Program Anda : ";
        cin >> pilihan;
        cls();

        switch (pilihan) {
            case 1:
            	
                tambahProduk(dataProduk, jumlahProduk);
                cls();
                break;
            case 2:
                tampilkanDaftarBarang(dataProduk, jumlahProduk);
                gotoXY(4, 11);system("pause");
                cls();
                break;
            case 3:
                bubbleSortProduk(dataProduk, jumlahProduk);
                tampilkanDaftarBarang(dataProduk, jumlahProduk); 
                gotoXY(5, 12);system("pause");
                break;
            case 4:
                {
                    cin.ignore();
                    gotoXY(4, 1);
                    cout << "Masukkan Keyword Pencarian: ";
                    string keyword;
                    getline(cin, keyword);
                    cariProduk(dataProduk, jumlahProduk, keyword);
                    cls();
                    break;
                }
            case 5:
                prosesTransaksi(dataProduk, jumlahProduk);
                break;
            case 6:
                tampilkanResumeTransaksi(dataProduk, jumlahProduk);
                cls();
                break;
            case 7:
                gotoXY(3, 3);
                cout << "===================================[Terimakasih telah menggunakan program ini]==================================" << endl;
                gotoXY(3, 5);
                system("pause");
                break;
            default:
                gotoXY(3, 1);
                cout << "Pilihan tidak valid!" << endl;
                gotoXY(3, 3);
                system("pause");
                break;
        }
    } while (pilihan != 7);

    return 0;
}

