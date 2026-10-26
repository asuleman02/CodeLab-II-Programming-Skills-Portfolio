
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <limits>
using namespace std;

// Store the information about each book
class Book {
public:
    string title, author, id;
    int pages;
    bool borrowed;

    Book(string t, string a, int p, string i, bool b) {
        title = t;
        author = a;
        pages = p;
        id = i;
        borrowed = b;
    }

    void showBook() {
        cout << "\nID: " << id << endl;
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "Pages: " << pages << endl;
        cout << "Status: "
             << (borrowed ? "Borrowed" : "Available") << endl;
    }
};

// Read the books from the text file
void loadBooks(vector<Book>& books) {
    ifstream file("Challenge3/bookData.txt");
    string line;

    if (!file) {
        cout << "Could not open bookData.txt" << endl;
        return;
    }

    while (getline(file, line)) {
        string title, author, pages, id, status;
        stringstream ss(line);

        getline(ss, title, ',');
        getline(ss, author, ',');
        getline(ss, pages, ',');
        getline(ss, id, ',');
        getline(ss, status);

        if (!title.empty() && !status.empty()) {
            books.push_back(Book(title, author, stoi(pages),
                                 id, status == "true"));
        }
    }
    file.close();
}

// Save changes to the text file
void saveBooks(vector<Book>& books) {
    ofstream file("Challenge3/bookData.txt");

    if (!file) {
        cout << "Could not save book data." << endl;
        return;
    }

    for (Book& book : books) {
        file << book.title << "," << book.author << ","
             << book.pages << "," << book.id << ","
             << (book.borrowed ? "true" : "false") << endl;
    }
    file.close();
}

// Find a book using its ID
Book* findBook(vector<Book>& books, string id) {
    for (Book& book : books) {
        if (book.id == id) {
            return &book;
        }
    }
    return nullptr;
}

int main() {
    vector<Book> books;
    loadBooks(books);

    if (books.empty()) {
        cout << "No books available." << endl;
        return 1;
    }

    int choice;
    string id;

    while (true) {
        cout << "\n===== Book Manager =====" << endl;
        cout << "1. View all books" << endl;
        cout << "2. View one book" << endl;
        cout << "3. Borrow a book" << endl;
        cout << "4. Return a book" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cout << "Please enter a number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (choice == 5) {
            cout << "Goodbye!" << endl;
            break;
        }

        if (choice == 1) {
            for (Book& book : books) {
                book.showBook();
            }
            continue;
        }

        if (choice >= 2 && choice <= 4) {
            cout << "Enter book ID (e.g. 001): ";
            cin >> id;

            Book* book = findBook(books, id);

            if (book == nullptr) {
                cout << "Book not found." << endl;
                continue;
            }

            if (choice == 2) {
                book->showBook();
            }
            else if (choice == 3) {
                if (book->borrowed) {
                    cout << "Book is already borrowed." << endl;
                } else {
                    book->borrowed = true;
                    saveBooks(books);
                    cout << "Book borrowed successfully!" << endl;
                }
            }
            else if (choice == 4) {
                if (!book->borrowed) {
                    cout << "Book is already available." << endl;
                } else {
                    book->borrowed = false;
                    saveBooks(books);
                    cout << "Book returned successfully!" << endl;
                }
            }
        }
        else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
