#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

using namespace std;

struct Jadwal {
    int idJadwal;
    string namaKegiatan;
    int waktuMulai;
    int waktuSelesai;
    string statusJadwal;
    string tanggal;
    string idRuangan;
    string namaRuangan;

    Jadwal* next;
};

void insertJadwal(Jadwal*& head, Jadwal*& tail, int id, string nama, 
                    string ruang, int mulai, int selesai, string tanggal, string status) {

    if(cekKonflik(head, ruang, tanggal, mulai, selesai)) {
        cout << "Gagal! Ada jadwal bentrok di ruangan " << ruang << " pada tanggal " << tanggal << "\n";
        return;
    }

    Jadwal* baru = new Jadwal;
    baru->idJadwal = id;
    baru->namaKegiatan = nama;
    baru->idRuangan = ruang;
    baru->waktuMulai = mulai;
    baru->waktuSelesai = selesai;
    baru->statusJadwal = status;
    baru->tanggal = tanggal;
    baru->next = NULL;

    if(head == NULL){
        head = tail = baru;
    } else {
        tail->next = baru;
        tail = baru;
    }
}

void searchRuang(Jadwal* head, string ruang) {
    Jadwal* temp = head;
    while(temp!= NULL){
        if(temp->idRuangan == ruang){
            cout << temp->idJadwal << " "<< temp->namaKegiatan << " "
                << temp->waktuMulai << " " << temp->waktuSelesai << endl;
        }
        temp = temp->next;
    }
}

void updateJadwal(Jadwal* head, int id){
    Jadwal* temp = head;

    while(temp != NULL){
        if(temp->idJadwal == id){
            string namaBaru;
            int mulaiBaru, selesaiBaru;

            cout << "Masukkan nama kegiatan baru: ";
            cin >> namaBaru;
            cout << "Waktu mulai baru: ";
            cin >> mulaiBaru;
            cout << "Waktu selesai baru: ";
            cin >> selesaiBaru;

            int oldMulai = temp->waktuMulai;
            int oldSelesai = temp->waktuSelesai;
            
            temp->waktuMulai = -1;
            temp->waktuSelesai = -1;

            if(cekKonflik(head, temp->idRuangan, temp->tanggal, mulaiBaru, selesaiBaru)) {
                cout << "Update gagal! Waktu bentrok dengan jadwal lain.\n";
                temp->waktuMulai = oldMulai;
                temp->waktuSelesai = oldSelesai;
            } else {
                temp->namaKegiatan = namaBaru;
                temp->waktuMulai = mulaiBaru;
                temp->waktuSelesai = selesaiBaru;
                cout << "Jadwal berhasil diupdate!\n";
            }
            return;
        }
        temp = temp->next;
    }

    cout << "Jadwal tidak ditemukan\n";
}

void deleteJadwal(Jadwal*& head, int id){
    Jadwal* temp = head;
    Jadwal* prev = NULL;

    while(temp != NULL){
        if(temp->idJadwal == id){
            if(prev == NULL){
                head = temp->next;
            } else {
                prev->next = temp->next;
            }

            delete temp;
            cout << "Jadwal berhasil dihapus\n";
            return;
        }
        prev = temp;
        temp = temp->next;
    }
}

bool cekKonflik(Jadwal* head, string ruang, string tanggal, int mulai, int selesai){
    Jadwal* temp = head;

    while(temp != NULL){
        if(temp->idRuangan == ruang && temp->tanggal == tanggal){
            if(mulai < temp->waktuSelesai && selesai > temp->waktuMulai) {
                return true;
            }
        }
        temp = temp->next;
    }
    return false;
}

void simpanFile(Jadwal* head){
    ofstream file("jadwal.txt");
    Jadwal* temp = head;

    while(temp != NULL){
         file << temp->idJadwal << " "
             << temp->namaKegiatan << " "
             << temp->idRuangan << " "
             << temp->waktuMulai << " "
             << temp->waktuSelesai << " "
             << temp->tanggal << " "
             << temp->statusJadwal << endl;

            temp = temp->next;
    }
    file.close();
}

void ambilFile(Jadwal*& head, Jadwal*& tail){
    ifstream file("jadwal.txt");
    
    if(!file.is_open()){
        return;
    }

    int id, mulai, selesai;
    string nama, ruang, tanggal, status;

    while(file >> id >> nama >> ruang >> mulai >> selesai >> tanggal >> status){
        Jadwal* baru = new Jadwal;
        baru->idJadwal = id;
        baru->namaKegiatan = nama;
        baru->idRuangan = ruang;
        baru->waktuMulai = mulai;
        baru->waktuSelesai = selesai;
        baru->tanggal = tanggal;
        baru->statusJadwal = status;
        baru->next = NULL;

        if(head == NULL){
            head = tail = baru;
        } else {
            tail->next = baru;
            tail = baru;
        }
    }
    file.close();
}

int main(){
    Jadwal* head = NULL;
    Jadwal* tail = NULL;
    ambilFile(head, tail);

    auto start_time = chrono::high_resolution_clock::now();

    int pilihan;
    do{
        cout << "\n==MENU==\n";
        cout << "1. INSERT JADWAL\n";
        cout << "2. SEARCH JADWAL\n";
        cout << "3. UPDATE JADWAL\n";
        cout << "4. DELETE JADWAL\n";
        cout << "5. KELUAR\n";
        cout << "PILIHAN: ";
        cin >> pilihan;

        if(pilihan == 1){
            int id, mulai, selesai;
            string nama, ruang, tanggal, status;

            cout << "ID: ";
            cin >> id;
            cin.ignore();
            cout << "NAMA KEGIATAN: ";
            
            getline(cin, nama);
            cout << "ID RUANG: ";
            cin >> ruang;
            cout << "WAKTU MULAI: ";
            cin >> mulai;
            cout << "WAKTU SELESAI: ";
            cin >> selesai;
            cin.ignore();
            cout << "TANGGAL: ";
            
            getline(cin, tanggal);
            cout << "STATUS: ";
            getline(cin, status);

            insertJadwal(head, tail, id, nama, ruang, mulai, selesai, tanggal, status);
            simpanFile(head);
        }

        else if(pilihan == 2) {
            string ruang;
            cout << "CARI RUANG: ";
            cin >> ruang;
            searchRuang(head, ruang);
        }

        else if(pilihan ==3){
            int id;
            cout << "ID JADWAL YANG INGIN DIUPDATE: ";
            cin >> id;
            updateJadwal(head, id);
            simpanFile(head);
        }

        else if(pilihan == 4){
            int id;
            cout << "ID JADWAL YANG INGIN DIHAPUS: ";
            cin >> id;

            deleteJadwal(head, id);
            simpanFile(head);
        }
    } while(pilihan != 5);

    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);
    
    cout << "Waktu: " << duration.count() << " ms\n";
    
    return 0;
}
