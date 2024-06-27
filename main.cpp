#include <bits/stdc++.h>
using namespace std;

class Book {
  private:
    int id;
    string title;
    string author;
    bool status;
    string issuedTo;
    static atomic<int> nextID;

  public:
    Book(const string& bookTitle, const string& bookAuthor, bool bookStatus)
      : id(nextID++), title(bookTitle), author(bookAuthor), status(bookStatus) {}

    void printDetails() const {
      cout << "ID: " << id << "\n"
           << "Title: " << title << "\n"
           << "Author: " << author << "\n"
           << "Status: " << (status ? "Available" : "Checked Out") << endl;
    }

    int getID() const {
      return id;
    }

    string getTitle() {
      return title;
    }

    string getAuthor() const {
      return author;
    }

    bool getStatus() const {
      return status;
    }

    bool operator<(const Book& other) const {
        return id < other.id;
    }

    bool compareTitle(const Book& other) const {
        return title < other.title;
    }
    void issueBook(const string& studentName) {
        status = false;
        issuedTo = studentName;
    }

    // Getter for issuedTo
    string getIssuedTo() const {
        return issuedTo;
    }

    void returnBook() {
        status = true;
        issuedTo.clear();
    }
};

atomic<int> Book::nextID{1};

void addBook(vector<Book>& books, const string& title, const string& author, bool status){
  books.push_back({title,author,status});
}

void sortByID(vector<Book>& books) {
    sort(books.begin(), books.end());
}

// Function to sort books by Title
void sortByTitle(vector<Book>& books) {
    sort(books.begin(), books.end(), [](Book& a, Book& b) {
        return a.getTitle() < b.getTitle();
    });
}

int binarySearchByID(const vector<Book>& books, int id) {
    int left = 0;
    int right = books.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (books[mid].getID() == id) {
            return mid;
        } else if (books[mid].getID() < id) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1; // Not found
}

// Binary search by Title
int binarySearchByTitle(vector<Book>& books, const string& title) {
    int left = 0;
    int right = books.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (books[mid].getTitle() == title) {
            return mid;
        } else if (books[mid].getTitle() < title) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1; // Not found
}

void issueBook(vector<Book>& books, int id, const string& studentName, queue<Book>& issuedBooks) {
    int index = binarySearchByID(books, id);
    if (index != -1 && books[index].getStatus() == true) {
        books[index].issueBook(studentName);
        issuedBooks.push(books[index]);
        cout << "Book with ID " << id << " has been issued to " << studentName << "." << endl;
    } else if (index == -1) {
        cout << "Book with ID " << id << " not found." << endl;
    } else {
        cout << "Book with ID " << id << " is already issued." << endl;
    }
}

void returnBook(vector<Book>& books, int id, queue<Book>& issuedBooks) {
    int index = binarySearchByID(books, id);
    if (index != -1 && books[index].getStatus() == false) {
        books[index].returnBook();

        // Remove the book from the issuedBooks queue
        queue<Book> tempQueue;
        while (!issuedBooks.empty()) {
            Book book = issuedBooks.front();
            issuedBooks.pop();
            if (book.getID() != id) {
                tempQueue.push(book);
            }
        }
        swap(issuedBooks, tempQueue);

        cout << "Book with ID " << id << " has been returned and is now available." << endl;
    } else if (index == -1) {
        cout << "Book with ID " << id << " not found." << endl;
    } else {
        cout << "Book with ID " << id << " is already available." << endl;
    }
}

int main() {
    vector<Book> bookCollection;
    queue<Book> issuedBooks;

    addBook(bookCollection, "1984", "George Orwell", true);
    addBook(bookCollection, "To Kill a Mockingbird", "Harper Lee", false);
    addBook(bookCollection, "Brave New World", "Aldous Huxley", true);
    addBook(bookCollection, "The Catcher in the Rye", "J.D. Salinger", false);


    sortByID(bookCollection);

    // Perform binary search by ID
    int searchID = 2;
    int indexByID = binarySearchByID(bookCollection, searchID);
    if (indexByID != -1) {
        cout << "Book with ID " << searchID << " found:\n";
        bookCollection[indexByID].printDetails();
    } else {
        cout << "Book with ID " << searchID << " not found." << endl;
    }

    cout << endl;




    
    // Sort books by Title
    sortByTitle(bookCollection);

    // Perform binary search by Title
    string searchTitle = "1984";
    int indexByTitle = binarySearchByTitle(bookCollection, searchTitle);
    if (indexByTitle != -1) {
        cout << "Book with Title \"" << searchTitle << "\" found:\n";
        bookCollection[indexByTitle].printDetails();
    } else {
        cout << "Book with Title \"" << searchTitle << "\" not found." << endl;
    }


    int bookIDToIssue = 2;
    string studentName = "John Doe";
    issueBook(bookCollection, bookIDToIssue, studentName, issuedBooks);
    cout<<endl;

    int bookIDToReturn = 2;
    returnBook(bookCollection, bookIDToReturn, issuedBooks);

    cout << endl;


    for (const auto& book : bookCollection) {
      book.printDetails();
      cout << endl;
    }

    return 0;
}