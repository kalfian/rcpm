#include <iostream>
#include <random>
#include <sys/time.h>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

// DATA
const string DATA_KECIL = "../data_kecil_aktifitas.csv";
const string DATA_SUMBERDAYA_KECIL = "../data_kecil_sumberdaya.csv";
// END DATA

struct AktifitasKecil {
    int durasi;
    int r1;
    int r2;
    int r3;
    int r4;
    int aktifitas_pendahulu;
};

struct SumberdayaKecil {
    int r1;
    int r2;
    int r3;
    int r4;
};

vector<string> split(const string& line, char delimiter) {
    vector<string> tokens;
    istringstream tokenStream(line);
    string token;
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

vector<AktifitasKecil> convertAktifitasKecil(const std::string& filename, int startLine, char delimiter) {
    vector<AktifitasKecil> result;
    ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return result;
    }

    string line;
    for (int i = 0; i < startLine - 1; ++i) {
        std::getline(file, line); // Skip lines until reaching the start line
    }

    while (getline(file, line)) {
        vector<string> fields = split(line, delimiter);

        AktifitasKecil data{};
        data.durasi = stoi(fields[1]);
        data.r1 =  stoi(fields[2]);
        data.r2 =  stoi(fields[3]);
        data.r3 =  stoi(fields[4]);
        data.r4 =  stoi(fields[5]);
        data.aktifitas_pendahulu =  stoi(fields[6]);

        result.push_back(data);
    }

    file.close();
    return result;
}

SumberdayaKecil convertSumberdayaKecil(const std::string& filename, int startLine, char delimiter) {
    SumberdayaKecil result{};
    ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return result;
    }

    string line;
    for (int i = 0; i < startLine - 1; ++i) {
        std::getline(file, line); // Skip lines until reaching the start line
    }

    while (getline(file, line)) {
        vector<string> fields = split(line, delimiter);

        result.r1 =  stoi(fields[0]);
        result.r2 =  stoi(fields[1]);
        result.r3 =  stoi(fields[2]);
        result.r4 =  stoi(fields[3]);

    }

    file.close();
    return result;
}

long long getCurrentTimeMicroseconds() {
    struct timeval tv{};
    gettimeofday(&tv, nullptr);
    return static_cast<long long>(tv.tv_sec) * 1000000 + tv.tv_usec;
}

double generateRandomNumber() {
    // Get the current time in microseconds
    usleep(1000);

    uint64_t  rdgen = getCurrentTimeMicroseconds();

    mt19937_64 generator(rdgen);

    // Generate a random double between 0 and 1 with 4 decimal places
    uniform_real_distribution<double> distribution(1.0, 9999.0);
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
    vector<AktifitasKecil> data = convertAktifitasKecil(DATA_KECIL, 3, ';');

    // Ambil data sumber daya dari data_sumberdaya_kecil.csv
    // Convert data cvs ke struct
    SumberdayaKecil dataSumberdaya = convertSumberdayaKecil(DATA_SUMBERDAYA_KECIL, 2, ';');

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
    SumberdayaKecil data = convertSumberdayaKecil(DATA_SUMBERDAYA_KECIL, 2, ';');

    // Now 'data' contains the parsed CSV data in the form of YourStruct instances
    cout  << data.r1 << "\t" << data.r2 << "\t" << data.r3 << "\t" << data.r4 << "\t" <<  endl;

    return 0;
}

//int main() {
//    int murid;
//    int iterasi;
//    int pelajaran;
//    int jenisData;
//
//    cout << "Masukkan Jumlah Murid: ";
//    cin >> murid;
//
//    cout << "Masukkan Jumlah Iterasi: ";
//    cin >> iterasi;
//
//    cout << "Masukkan Jumlah Pelajaran: ";
//    cin >> pelajaran;
//
//    cout << "1: Kecil\n"
//            "2: Sedang\n"
//            "3: Besar\n"
//            "Masukkan Jenis Data: ";
//    cin >> jenisData;
//    cout << endl;
//
//    cout << "Jumlah murid: " << murid << endl;
//    cout << "Jumlah Iterasi: " << iterasi << endl;
//    cout << "Jumlah Pelajaran: " << pelajaran << endl;
//    cout << "Jenis Data: " << convertJenisData(jenisData) << endl;
//    cout << endl;
//
//
//    switch(jenisData) {
//        case 1:
//            prosesDataKecil(murid, iterasi, pelajaran);
//            break;
//        case 2:
//            prosesDataSedang(murid, iterasi, pelajaran);
//            break;
//        case 3:
//            prosesDataBesar(murid, iterasi, pelajaran);
//            break;
//        default:
//            cout << "Jenis Data Tidak valid!";
//    }
//
//
//    return 0;
//}