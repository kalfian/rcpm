#include <iostream>
#include <random>
#include <future>
#include <sys/time.h>
#include <unistd.h>

using namespace std;

struct aktifitasKecil {
    int durasi;
    int r1;
    int r2;
    int r3;
    int r4;
    int aktifitas_pendahulu;
};

struct sumberdayaKecil {
    int r1;
    int r2;
    int r3;
    int r4;
};

long long getCurrentTimeMicroseconds() {
    struct timeval tv{};
    gettimeofday(&tv, nullptr);
    return static_cast<long long>(tv.tv_sec) * 1000000 + tv.tv_usec;
}

double generateRandomNumber() {
    // Get the current time in microseconds
    usleep(10);

    uint64_t  rdgen = getCurrentTimeMicroseconds();

    std::mt19937_64 generator(rdgen);

    // Generate a random double between 0 and 1 with 4 decimal places
    std::uniform_real_distribution<double> distribution(1.0, 9999.0);
    double randomDouble = distribution(generator);

    // Round to 4 decimal places
    randomDouble = round(randomDouble) / 10000.0;

    return randomDouble;
}

string convertJenisData(int jenisData) {
    switch(jenisData) {
        case 1:
            return "Kecil";
        case 2:
            return "Sedang";
        case 3:
            return "Besar";
        default:
            return "";
    }
}

int generateJumlahAktifitas(int jenisData) {
    switch(jenisData) {
        case 1:
            return 10;
        case 2:
            return 25;
        case 3:
            return 60;
        default:
            return 0;
    }
}

vector<vector<double>> generateAktifitasMurid(int murid, int aktifitas) {
    vector<vector<double>> matrix(murid, vector<double>(aktifitas));
    for(int i = 0; i < murid ; i++ ) {
        for(int j = 0; j < aktifitas; j++) {
            double randomNumber = generateRandomNumber();
            matrix[i][j] = randomNumber;
        }
    }
    return matrix;
}

void prosesDataKecil(int murid, int iterasi, int pelajaran) {
    // jenis data kecil
    int jenisData = 1;

    // Proses Pertama
    // Random berdarkan jumlah murid x jumlah aktifitas
    int jumlahAktifitas = generateJumlahAktifitas(jenisData);
    cout << "Jumlah Aktifitas: " << jumlahAktifitas << endl;


    vector<vector<double>> aktifitasMurid = generateAktifitasMurid(murid, jumlahAktifitas);

    // Debug Aktifitas Murid
    cout << "Data random: " << endl;
    for (const auto& row : aktifitasMurid) {
        for (double element : row) {
            std::cout << element << "\t";
        }
        cout << std::endl;
    }

    // Ambil data aktifitas dari data_kecil.csv
    // Convert data cvs ke struct

    // Ambil data sumber daya dari data_sumberdaya_kecil.csv
    // Convert data cvs ke struct

}

void prosesDataSedang(int murid, int iterasi, int pelajaran) {
    //    TODO:
    cout << "Not implemented yet!" << endl;
}
void prosesDataBesar(int murid, int iterasi, int pelajaran) {
    //    TODO:
    cout << "Not implemented yet!" << endl;
}

int main() {
    int murid;
    int iterasi;
    int pelajaran;
    int jenisData;

    cout << "Masukkan Jumlah Murid: ";
    cin >> murid;

    cout << "Masukkan Jumlah Iterasi: ";
    cin >> iterasi;

    cout << "Masukkan Jumlah Pelajaran: ";
    cin >> pelajaran;

    cout << "1: Kecil\n"
            "2: Sedang\n"
            "3: Besar\n"
            "Masukkan Jenis Data: ";
    cin >> jenisData;
    cout << endl;

    cout << "Jumlah murid: " << murid << endl;
    cout << "Jumlah Iterasi: " << iterasi << endl;
    cout << "Jumlah Pelajaran: " << pelajaran << endl;
    cout << "Jenis Data: " << convertJenisData(jenisData) << endl;
    cout << endl;


    switch(jenisData) {
        case 1:
            prosesDataKecil(murid, iterasi, pelajaran);
            break;
        case 2:
            prosesDataSedang(murid, iterasi, pelajaran);
            break;
        case 3:
            prosesDataBesar(murid, iterasi, pelajaran);
            break;
        default:
            cout << "Jenis Data Tidak valid!";
    }


    return 0;
}