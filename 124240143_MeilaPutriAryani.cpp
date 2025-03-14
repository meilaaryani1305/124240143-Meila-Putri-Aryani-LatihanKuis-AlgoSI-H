#include <iostream>
#include <string>
#include <iomanip>
#include <cstring>
using namespace std;

struct admin
{
    string username, password;
};
admin adm;

struct buku
{
    string id;
    int stok;
    char judul[50], penulis[50];
};
buku Buku;

buku daftarBuku[100];
int jumlahBuku = 0;

bool loginadmin()
{
    int kesempatan = 3;
    do
    {
        cout << "LOGIN KE DATABASE PERPUSTAKAAN INFORMATIKA" << endl;
        cout << "Masukkan username = ";
        cin >> adm.username;

        cout << "Masukkan password = ";
        cin >> adm.password;

        if (adm.username == "meila" && adm.password == "143")
        {
            cout << "BERHASIL\n";
            return true;
        }
        else
        {
            cout << "Username atau password salah\n"
                 << endl;
            kesempatan--;
        }
    } while (kesempatan > 0);
    return false;
}

void tambahBuku()
{
    FILE *hiu = fopen("data.dat", "ab");
    if (!hiu)
    {
        perror("Gagal membuka file data.dat");
        exit(1);
    }

    cout << "Masukkan ID Buku: ";
    cin >> Buku.id;
    cin.ignore();
    cout << "Masukkan Judul Buku: ";
    cin.getline(Buku.judul, 50);
    cout << "Masukkan Nama Penulis: ";
    cin.getline(Buku.penulis, 50);
    cout << "Masukkan Stok Buku: ";
    cin >> Buku.stok;

    if (fwrite(&Buku, sizeof(buku), 1, hiu) != 1)
    {
        perror("Gagal menulis data ke file");
    }
    else
    {
        cout << "Buku berhasil ditambahkan!" << endl;
    }

    fclose(hiu);
}

void tampilkanBuku()
{
    FILE *hiu = fopen("data.dat", "rb");
    if (!hiu)
    {
        cout << "Data buku belum tersedia atau file tidak ditemukan!\n";
        return;
    }

    jumlahBuku = 0;
    while (fread(&daftarBuku[jumlahBuku], sizeof(buku), 1, hiu))
    {
        jumlahBuku++;
        if (jumlahBuku >= 100)
            break;
    }
    fclose(hiu);

    if (jumlahBuku == 0)
    {
        cout << "Belum ada data buku!\n";
        return;
    }

    cout << setfill('=') << setw(80) << "=" << endl;
    cout << left << setw(10) << "Id"
         << "|\t" << left << setw(30) << "Judul"
         << "|\t" << left << setw(20) << "Penulis"
         << "|\t" << left << setw(10) << "Stok"
         << endl;
    cout << setfill('=') << setw(80) << "=" << endl;

    for (int i = 0; i < jumlahBuku; i++)
    {
        cout << left << setw(10) << daftarBuku[i].id
             << "| " << left << setw(30) << daftarBuku[i].judul
             << "| " << left << setw(20) << daftarBuku[i].penulis
             << "| " << left << setw(10) << daftarBuku[i].stok
             << endl;
    }
    cout << setfill('=') << setw(80) << "=" << endl;
}

void cariBuku()
{
    FILE *hiu = fopen("data.dat", "rb");
    if (hiu == NULL)
    {
        cout << "Data buku belum tersedia atau file tidak ditemukan!\n";
        return;
    }

    jumlahBuku = 0;
    while (fread(&daftarBuku[jumlahBuku], sizeof(buku), 1, hiu))
    {
        jumlahBuku++;
        if (jumlahBuku >= 100)
            break;
    }
    fclose(hiu);

    if (jumlahBuku == 0)
    {
        cout << "Belum ada data buku!\n";
        return;
    }

    cout << "Masukkan kata kunci judul buku: ";
    cin.ignore();
    char keyword[50];
    cin.getline(keyword, 50);

    bool ditemukan = false;
    cout << setfill('=') << setw(80) << "=" << endl;
    cout << left << setw(10) << "Id"
         << "| " << left << setw(30) << "Judul"
         << "| " << left << setw(20) << "Penulis"
         << "| " << left << setw(10) << "Stok"
         << endl;
    cout << setfill('=') << setw(80) << "=" << endl;

    for (int i = 0; i < jumlahBuku; i++)
    {
        if (strstr(daftarBuku[i].judul, keyword) != NULL)
        {
            ditemukan = true;
            cout << left << setw(10) << daftarBuku[i].id
                 << "| " << left << setw(30) << daftarBuku[i].judul
                 << "| " << left << setw(20) << daftarBuku[i].penulis
                 << "| " << left << setw(10) << daftarBuku[i].stok
                 << endl;
        }
    }
    cout << setfill('=') << setw(80) << "=" << endl;

    if (!ditemukan)
    {
        cout << "Buku dengan kata kunci \"" << keyword << "\" tidak ditemukan.\n";
    }
}

void hapusBuku()
{
    string idHapus;
    cout << "Masukkan ID Buku yang ingin dihapus: ";
    cin >> idHapus;

    FILE *hiu = fopen("data.dat", "rb");
    if (hiu == NULL)
    {
        cout << "Data buku belum tersedia atau file tidak ditemukan!\n";
        return;
    }

    FILE *tempFile = fopen("temp.dat", "wb");
    if (tempFile == NULL)
    {
        cout << "Gagal membuat file sementara!\n";
        fclose(hiu);
        return;
    }

    bool ditemukan = false;
    while (fread(&Buku, sizeof(buku), 1, hiu))
    {
        if (Buku.id != idHapus)
        {
            fwrite(&Buku, sizeof(buku), 1, tempFile);
        }
        else
        {
            ditemukan = true;
        }
    }

    fclose(hiu);
    fclose(tempFile);

    remove("data.dat");
    rename("temp.dat", "data.dat");

    if (ditemukan)
    {
        cout << "Buku dengan ID " << idHapus << " berhasil dihapus.\n";
    }
    else
    {
        cout << "Buku dengan ID " << idHapus << " tidak ditemukan.\n";
    }
}

void keluar()
{
    cout << "Program akan ditutup";
    exit(0);
}

int main()
{
    if (!loginadmin())
    {
        keluar();
    }
    int pilih;
    do
    {
        cout << "1. Tambah Data Buku\n"
             << endl;
        cout << "2. Tampilkan Daftar Buku\n"
             << endl;
        cout << "3. Cari Buku\n"
             << endl;
        cout << "4. Hapus Buku\n"
             << endl;
        cout << "5. Keluar\n"
             << endl;
        cout << "Pilih: ";
        cin >> pilih;

        switch (pilih)
        {
        case 1:
            tambahBuku();
            break;
        case 2:
            tampilkanBuku();
            break;
        case 3:
            cariBuku();
            break;
        case 4:
            hapusBuku();
            break;
        case 5:
            keluar();
            break;
        default:
            cout << "Pilihan tidak valid!\n";
        }
    } while (pilih != 5);

    return 0;
}
