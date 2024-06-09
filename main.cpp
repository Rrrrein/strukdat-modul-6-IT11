#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <algorithm>

using namespace std;

// Kelas Media
class Media {
protected:  // Akses dibatasi untuk subclass
    string title;  // Atribut untuk menyimpan judul media
    string genre;  // Atribut untuk menyimpan genre media
    int year;      // Atribut untuk menyimpan tahun rilis media

public:
    // Konstruktor untuk menginisialisasi atribut media
    Media(string title, string genre, int year) : title(title), genre(genre), year(year) {}

    // Metode untuk menampilkan informasi media
    virtual void display() const {
        cout << "Judul: " << title << "\nGenre: " << genre << "\nTahun: " << year << endl;
    }

    // Getter untuk mendapatkan nilai atribut title
    string getTitle() const { return title; }

    // Getter untuk mendapatkan nilai atribut genre
    string getGenre() const { return genre; }

    // Getter untuk mendapatkan nilai atribut year
    int getYear() const { return year; }

    // Setter untuk mengubah nilai atribut title
    void setTitle(string newTitle) { title = newTitle; }

    // Setter untuk mengubah nilai atribut genre
    void setGenre(string newGenre) { genre = newGenre; }

    // Setter untuk mengubah nilai atribut year
    void setYear(int newYear) { year = newYear; }
};

// Kelas Movie
class Movie : public Media {
private:  // Akses hanya untuk anggota kelas ini
    int id;  // Atribut untuk menyimpan ID film
    vector<int> ratings;  // Atribut untuk menyimpan daftar rating film

public:
    // Konstruktor untuk menginisialisasi atribut film dan memanggil konstruktor kelas induk
    Movie(int id, string title, string genre, int year) : Media(title, genre, year), id(id) {}

    // Metode untuk menampilkan informasi film, termasuk memanggil metode display dari kelas induk
    void display() const override {
        cout << "ID: " << id << "\n";
        Media::display();  // Memanggil metode display dari kelas induk
        cout << "Rating Rata-rata: " << getAverageRating() << endl;
    }

    // Getter untuk mendapatkan nilai atribut id
    int getId() const { return id; }

    // Metode untuk menambahkan rating ke daftar ratings
    void addRating(int rating) {
        if (rating >= 1 && rating <= 5) {
            ratings.push_back(rating);
        } else {
            cout << "Rating harus antara 1 dan 5." << endl;
        }
    }

    // Metode untuk menghitung dan mengembalikan rata-rata rating
    double getAverageRating() const {
        if (ratings.empty()) return 0;
        int sum = 0;
        for (int rating : ratings) {
            sum += rating;
        }
        return static_cast<double>(sum) / ratings.size();
    }
};

// Kelas DiaryEntry
class DiaryEntry {
private:  // Akses hanya untuk anggota kelas ini
    int movieId;  // Atribut untuk menyimpan ID film yang ditonton
    string watchDate;  // Atribut untuk menyimpan tanggal menonton film (diganti menjadi string)
    string review;  // Atribut untuk menyimpan ulasan film

public:
    // Konstruktor untuk menginisialisasi atribut entri diary
    DiaryEntry(int movieId, const string& watchDate, const string& review) : movieId(movieId), watchDate(watchDate), review(review) {}

    // Metode untuk menampilkan informasi entri diary
    void display() const {
        cout << "ID Film: " << movieId << "\nTanggal Tonton: " << watchDate << "\nUlasan: " << review << endl;
    }

    // Getter untuk mendapatkan nilai atribut movieId
    int getMovieId() const { return movieId; }
};

// Kelas ManagementSystem
class ManagementSystem {
private:  // Akses hanya untuk anggota kelas ini
    vector<Movie> movies;  // Atribut untuk menyimpan daftar film
    vector<DiaryEntry> diary;  // Atribut untuk menyimpan daftar entri diary
    int nextId;  // Atribut untuk menyimpan ID berikutnya yang akan digunakan untuk film baru

     // Metode untuk membaca dan memparsing tanggal dari string
    bool readDate(const string& dateStr, string& date) {
        // Cek validitas format tanggal sesuai kebutuhan Anda
        // Misalnya, Anda dapat menggunakan regex untuk memeriksa format yang benar
        // Di sini, kita anggap bahwa tanggal yang dimasukkan sudah dalam format yang benar
        date = dateStr;
        return true;  // Mengembalikan true karena diasumsikan format sudah benar
    }

public:
    // Konstruktor untuk menginisialisasi atribut nextId
    ManagementSystem() : nextId(1) {}

    // Metode untuk menambah film baru ke dalam daftar
    void createMovie(string title, string genre, int year) {
        movies.emplace_back(nextId++, title, genre, year);
        cout << "Film berhasil ditambahkan!" << endl;
    }

    // Metode untuk menampilkan daftar semua film
    void readMovies() const {
        for (const Movie& movie : movies) {
            movie.display();
        }
    }

    // Metode untuk menampilkan judul semua film
    void readMovieTitles() const {
        cout << "\n******* Daftar Film *******\n";
        for (const Movie& movie : movies) {
            cout << "ID: " << movie.getId() << ", Judul: " << movie.getTitle() << endl;
        }
        cout << "***************************\n";
    }

    // Metode untuk menampilkan detail film berdasarkan ID
    void readMovieDetails(int id) const {
        for (const Movie& movie : movies) {
            if (movie.getId() == id) {
                cout << "\n******* Detail Film *******\n";
                movie.display();
                cout << "\n******* Diary Film *******\n";
                for (const DiaryEntry& entry : diary) {
                    if (entry.getMovieId() == id) {
                        entry.display();
                        cout << "---------------------------\n";
                    }
                }
                cout << "***************************\n";
                return;
            }
        }
        cout << "Film dengan ID " << id << " tidak ditemukan." << endl;
    }

    // Metode untuk memperbarui informasi film berdasarkan ID
    void updateMovie(int id, string title, string genre, int year) {
        for (Movie& movie : movies) {
            if (movie.getId() == id) {
                movie.setTitle(title);
                movie.setGenre(genre);
                movie.setYear(year);
                cout << "Film berhasil diperbarui!" << endl;
                return;
            }
        }
        cout << "Film dengan ID " << id << " tidak ditemukan." << endl;
    }

    // Metode untuk menghapus film berdasarkan ID
    void deleteMovie(int id) {
        for (auto it = movies.begin(); it != movies.end(); ++it) {
            if (it->getId() == id) {
                movies.erase(it);
                cout << "Film berhasil dihapus!" << endl;
                return;
            }
        }
        cout << "Film dengan ID " << id << " tidak ditemukan." << endl;
    }

 	// Metode untuk menambah entri diary baru
    void addDiaryEntry(int movieId, const string& dateStr, const string& review) {
        string date;
        if (readDate(dateStr, date)) {
            diary.emplace_back(movieId, date, review);
            cout << "Entri diary berhasil ditambahkan!" << endl;
        } else {
            cout << "Format tanggal tidak valid!" << endl;
        }
    }

    // Metode untuk menampilkan semua entri diary
    void viewDiary() const {
        cout << "\n******* Diary *******\n";
        for (const DiaryEntry& entry : diary) {
            entry.display();
            cout << "---------------------\n";
        }
        cout << "*********************\n";
    }

    // Metode untuk mencari film berdasarkan kata kunci di judul atau genre
    void searchMovies(const string& keyword) const {
        cout << "\nHasil pencarian untuk \"" << keyword << "\":" << endl;
        for (const Movie& movie : movies) {
            if (movie.getTitle().find(keyword) != string::npos || movie.getGenre().find(keyword) != string::npos) {
                movie.display();
                cout << "---------------------\n";
            }
        }
    }

    // Metode untuk memberikan rating pada film
    void rateMovie(int id, int rating) {
        for (Movie& movie : movies) {
            if (movie.getId() == id) {
                movie.addRating(rating);
                cout << "Rating berhasil ditambahkan!" << endl;
                return;
            }
        }
        cout << "Film dengan ID " << id << " tidak ditemukan." << endl;
    }

    // Metode untuk merekomendasikan film berdasarkan rating tertinggi
    void recommendMovies() const {
        if (movies.empty()) {
            cout << "Tidak ada film yang tersedia untuk direkomendasikan." << endl;
            return;
        }

        // Menemukan film dengan rating rata-rata tertinggi
        auto it = max_element(movies.begin(), movies.end(), [](const Movie& a, const Movie& b) {
            return a.getAverageRating() < b.getAverageRating();
        });

        cout << "\nFilm rekomendasi berdasarkan rating tertinggi:\n";
        it->display();
    }
};

// Fungsi untuk menampilkan menu utama
void displayMenu() {
    cout << "\n********* Sistem Manajemen Film *********\n";
    cout << "1. Tambah Film Baru\n";
    cout << "2. Perbarui Film\n";
    cout << "3. Hapus Film\n";
    cout << "4. Kelola Diary\n";
    cout << "5. Tampilkan Film\n";
    cout << "6. Cari Film\n";
    cout << "7. Beri Rating Film\n";
    cout << "8. Rekomendasi Film\n";
    cout << "9. Keluar\n";
    cout << "Pilih opsi: ";
}

// Fungsi untuk menampilkan menu diary
void displayDiaryMenu() {
    cout << "\n********* Kelola Diary *********\n";
    cout << "1. Tambah Entri Diary\n";
    cout << "2. Lihat Diary\n";
    cout << "3. Kembali ke Menu Utama\n";
    cout << "Pilih opsi: ";
}

// Fungsi utama, titik masuk program
int main() {
    ManagementSystem system;  // Membuat objek ManagementSystem
    int choice;

    do {
        displayMenu();  // Memanggil fungsi untuk menampilkan menu utama
        cin >> choice;
        cin.ignore();  // Membersihkan karakter newline dari buffer input

        switch (choice) {
            case 1: {
                string title, genre;
                int year;
                cout << "\nMasukkan Judul: ";
                getline(cin, title);
                cout << "Masukkan Genre: ";
                getline(cin, genre);
                cout << "Masukkan Tahun: ";
                cin >> year;
                system.createMovie(title, genre, year);  // Memanggil metode untuk menambah film baru
                break;
            }
            case 2: {
                int id;
                string title, genre;
                int year;
                cout << "\nMasukkan ID Film yang akan diperbarui: ";
                cin >> id;
                cin.ignore();
                cout << "Masukkan Judul Baru: ";
                getline(cin, title);
                cout << "Masukkan Genre Baru: ";
                getline(cin, genre);
                cout << "Masukkan Tahun Baru: ";
                cin >> year;
                system.updateMovie(id, title, genre, year);  // Memanggil metode untuk memperbarui informasi film
                break;
            }
            case 3: {
                int id;
                cout << "\nMasukkan ID Film yang akan dihapus: ";
                cin >> id;
                system.deleteMovie(id);  // Memanggil metode untuk menghapus film
                break;
            }
            case 4: {
                int diaryChoice;
                do {
                    displayDiaryMenu();  // Memanggil fungsi untuk menampilkan menu diary
                    cin >> diaryChoice;
                    cin.ignore();

                    switch (diaryChoice) {
                        case 1: {
                            int movieId;
                            string timestampStr, review;
                            cout << "\nMasukkan ID Film: ";
                            cin >> movieId;
                            cin.ignore();
                            cout << "Masukkan Tanggal Tonton (YYYY-MM-DD HH:MM:SS): ";
                            getline(cin, timestampStr);
                            cout << "Masukkan Ulasan: ";
                            getline(cin, review);
                            system.addDiaryEntry(movieId, timestampStr, review);  // Memanggil metode untuk menambah entri diary baru
                            break;
                        }
                        case 2:
                            system.viewDiary();  // Memanggil metode untuk melihat semua entri diary
                            break;
                        case 3:
                            cout << "Kembali ke Menu Utama." << endl;
                            break;
                        default:
                            cout << "Opsi tidak valid. Coba lagi." << endl;
                    }
                } while (diaryChoice != 3);
                break;
            }
            case 5: {
                system.readMovieTitles();  // Memanggil metode untuk menampilkan judul semua film
                int movieId;
                cout << "\nMasukkan ID Film untuk melihat detail: ";
                cin >> movieId;
                system.readMovieDetails(movieId);  // Memanggil metode untuk melihat detail film berdasarkan ID
                break;
            }
            case 6: {
                string keyword;
                cout << "\nMasukkan kata kunci untuk mencari film: ";
                getline(cin, keyword);
                system.searchMovies(keyword);  // Memanggil metode untuk mencari film berdasarkan kata kunci
                break;
            }
            case 7: {
                int id, rating;
                cout << "\nMasukkan ID Film yang akan diberi rating: ";
                cin >> id;
                cout << "Masukkan rating (1-5): ";
                cin >> rating;
                system.rateMovie(id, rating);  // Memanggil metode untuk memberikan rating pada film
                break;
            }
            case 8:
                system.recommendMovies();  // Memanggil metode untuk merekomendasikan film
                break;
            case 9:
                cout << "Keluar dari program." << endl;
                break;
            default:
                cout << "Opsi tidak valid. Coba lagi." << endl;
        }
    } while (choice != 9);

    return 0;
}

