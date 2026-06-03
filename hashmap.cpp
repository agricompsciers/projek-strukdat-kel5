#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map> 
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
};

void insertJadwal(unordered_map<int, Jadwal>& mapJadwal, int id, string nama, 
                    string ruang, int mulai, int selesai, string tanggal, string status) {

    if(cekKonflik(mapJadwal, ruang, tanggal, mulai, selesai)) {
        cout << "Gagal! Ada jadwal bentrok di ruangan " << ruang << " pada tanggal " << tanggal << "\n";
        return;
    }

    Jadwal baru;
    baru.idJadwal = id;
    baru.namaKegiatan = nama;
    baru.idRuangan = ruang;
    baru.waktuMulai = mulai;
    baru.waktuSelesai = selesai;
    baru.statusJadwal = status;
    baru.tanggal = tanggal;

    mapJadwal[id] = baru;
}

void searchRuang(const unordered_map<int, Jadwal>& mapJadwal, string ruang) {
    bool found = false;
    
    for(const auto& pair : mapJadwal) {
        const Jadwal& temp = pair.second;
        if(temp.idRuangan == ruang){
            cout << temp.idJadwal << " "<< temp.namaKegiatan << " "
                 << temp.waktuMulai << " " << temp.waktuSelesai << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "Tidak ada jadwal di ruangan ini.\n";
    }
}

void updateJadwal(unordered_map<int, Jadwal>& mapJadwal, int id){
    if(mapJadwal.find(id) != mapJadwal.end()){
        string namaBaru;
        int mulaiBaru, selesaiBaru;
        
        cout << "Masukkan nama kegiatan baru: ";
        cin >> namaBaru;
        cout << "Waktu mulai baru: ";
        cin >> mulaiBaru;
        cout << "Waktu selesai baru: ";
        cin >> selesaiBaru;

        string ruang = mapJadwal[id].idRuangan;
        string tanggal = mapJadwal[id].tanggal;

        Jadwal backup = mapJadwal[id];
        mapJadwal.erase(id);

        if(cekKonflik(mapJadwal, ruang, tanggal, mulaiBaru, selesaiBaru)) {
            cout << "Update gagal! Waktu bentrok dengan jadwal lain.\n";
            mapJadwal[id] = backup;
        } else {
            backup.namaKegiatan = namaBaru;
            backup.waktuMulai = mulaiBaru;
            backup.waktuSelesai = selesaiBaru;
            mapJadwal[id] = backup;
            cout << "Jadwal berhasil diupdate!\n";
        }
    } else {
        cout << "Jadwal tidak ditemukan\n";
    }
}

void deleteJadwal(unordered_map<int, Jadwal>& mapJadwal, int id){
    
    if(mapJadwal.erase(id)) {
        cout << "Jadwal berhasil dihapus\n";
    } else {
        cout << "Jadwal tidak ditemukan\n";
    }
}

bool cekKonflik(const unordered_map<int, Jadwal>& mapJadwal, string ruang, string tanggal, int mulai, int selesai){
    for(const auto& pair : mapJadwal){
        const Jadwal& temp = pair.second;
        if(temp.idRuangan == ruang && temp.tanggal == tanggal){
            if(mulai < temp.waktuSelesai && selesai > temp.waktuMulai) {
                return true;
            }
        }
    }
    return false;
}

void simpanFile(const unordered_map<int, Jadwal>& mapJadwal){
    ofstream file("jadwal.txt");

    for(const auto& pair : mapJadwal){
        const Jadwal& temp = pair.second;
        file << temp.idJadwal << " "
             << temp.namaKegiatan << " "
             << temp.idRuangan << " "
             << temp.waktuMulai << " "
             << temp.waktuSelesai << " "
             << temp.tanggal << " "
             << temp.statusJadwal << endl;
    }
    file.close();
}

void ambilFile(unordered_map<int, Jadwal>& mapJadwal){
    ifstream file("jadwal.txt");
    
    if(!file.is_open()){
        return;
    }

    int id, mulai, selesai;
    string nama, ruang, tanggal, status;

    while(file >> id >> nama >> ruang >> mulai >> selesai >> tanggal >> status){
        Jadwal baru;
        baru.idJadwal = id;
        baru.namaKegiatan = nama;
        baru.idRuangan = ruang;
        baru.waktuMulai = mulai;
        baru.waktuSelesai = selesai;
        baru.tanggal = tanggal;
        baru.statusJadwal = status;
        
        mapJadwal[id] = baru;
    }
    file.close();
}

int main(){
    unordered_map<int, Jadwal> mapJadwal;
    
    ambilFile(mapJadwal);

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

            insertJadwal(mapJadwal, id, nama, ruang, mulai, selesai, tanggal, status);
            simpanFile(mapJadwal);
        }
        else if(pilihan == 2) {
            string ruang;
            cout << "CARI RUANG: ";
            cin >> ruang;
            searchRuang(mapJadwal, ruang);
        }
        else if(pilihan ==3){
            int id;
            cout << "ID JADWAL YANG INGIN DIUPDATE: ";
            cin >> id;
            updateJadwal(mapJadwal, id);
            simpanFile(mapJadwal);
        }
        else if(pilihan == 4){
            int id;
            cout << "ID JADWAL YANG INGIN DIHAPUS: ";
            cin >> id;
            deleteJadwal(mapJadwal, id);
            simpanFile(mapJadwal);
        }
    } while(pilihan != 5);

    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);
    
    cout << "Waktu: " << duration.count() << " ms\n";
    
    return 0;
}