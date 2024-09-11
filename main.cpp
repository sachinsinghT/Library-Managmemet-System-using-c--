#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

// Student class
class Student {
public:
    string name;
    int id;
    string stream;
    string book1, book2;
    int bookCount;

    Student(string name, int id, string stream) {
        this->name = name;
        this->id = id;
        this->stream = stream;
        this->book1 = "";
        this->book2 = "";
        this->bookCount = 0;
    }
};

// Book management
unordered_map<string, pair<int, int>> books; // {bookName: {totalQty, availableQty}}

// Student management
vector<Student> students;

// Function to add a book
void addBook(string bookName, int quantity) {
    if (books.find(bookName) != books.end()) {
        books[bookName].first += quantity;
        books[bookName].second += quantity;
    } else {
        books[bookName] = {quantity, quantity};
    }
    cout << "Book added successfully.\n";
}

// Function to delete a book
void deleteBook(string bookName) {
    if (books.find(bookName) != books.end()) {
        books.erase(bookName);
        cout << "Book deleted successfully.\n";
    } else {
        cout << "Book not found.\n";
    }
}

// Function to update book quantity
void updateBook(string bookName, int quantity) {
    if (books.find(bookName) != books.end()) {
        books[bookName].first += quantity;
        books[bookName].second += quantity;
        cout << "Book updated successfully.\n";
    } else {
        cout << "Book not found.\n";
    }
}

// Function to issue a book to a student
void issueBook(int studentID, string bookName) {
    for (auto& student : students) {
        if (student.id == studentID) {
            if (student.bookCount == 2) {
                cout << "You can't issue more than two books.\n";
                return;
            }
            if (books.find(bookName) != books.end() && books[bookName].second > 0) {
                books[bookName].second--;
                student.bookCount++;
                if (student.book1.empty()) {
                    student.book1 = bookName;
                } else {
                    student.book2 = bookName;
                }
                cout << "Book issued successfully.\n";
            } else {
                cout << "Book not available.\n";
            }
            return;
        }
    }
    cout << "Student not found.\n";
}

// Function to return a book
void returnBook(int studentID, string bookName) {
    for (auto& student : students) {
        if (student.id == studentID) {
            if (student.book1 == bookName || student.book2 == bookName) {
                books[bookName].second++;
                student.bookCount--;
                if (student.book1 == bookName) {
                    student.book1 = "";
                } else {
                    student.book2 = "";
                }
                cout << "Book returned successfully.\n";
            } else {
                cout << "Book not issued to this student.\n";
            }
            return;
        }
    }
    cout << "Student not found.\n";
}

// Function to display all books
void displayBooks() {
    cout << "\nBooks in the Library:\n";
    for (const auto& book : books) {
        cout << "Book: " << book.first
             << ", Total: " << book.second.first
             << ", Available: " << book.second.second << endl;
    }
}

// Function to display student details
void displayStudents() {
    cout << "\nStudents in the Library:\n";
    for (const auto& student : students) {
        cout << "Name: " << student.name
             << ", ID: " << student.id
             << ", Stream: " << student.stream
             << ", Books Issued: " << student.bookCount << endl;
    }
}

// Function to sort students by ID
void sortStudents() {
    sort(students.begin(), students.end(), [](Student a, Student b) {
        return a.id < b.id;
    });
}

int main() {
    // Sample students
    students.push_back(Student("Rajvi", 1741078, "B.Tech-ICT"));
    students.push_back(Student("Krushna", 1741086, "B.Tech-ICT"));
    students.push_back(Student("Kalagee", 1741052, "B.Tech-ICT"));

    bool exitFlag = false;
    while (!exitFlag) {
        cout << "\nLibrary Management System\n";
        cout << "1. Add Book\n";
        cout << "2. Delete Book\n";
        cout << "3. Update Book\n";
        cout << "4. Issue Book\n";
        cout << "5. Return Book\n";
        cout << "6. Display Books\n";
        cout << "7. Display Students\n";
        cout << "8. Sort Students by ID\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                string bookName;
                int quantity;
                cout << "Enter book name: ";
                cin >> bookName;
                cout << "Enter quantity: ";
                cin >> quantity;
                addBook(bookName, quantity);
                break;
            }
            case 2: {
                string bookName;
                cout << "Enter book name to delete: ";
                cin >> bookName;
                deleteBook(bookName);
                break;
            }
            case 3: {
                string bookName;
                int quantity;
                cout << "Enter book name: ";
                cin >> bookName;
                cout << "Enter quantity to add: ";
                cin >> quantity;
                updateBook(bookName, quantity);
                break;
            }
            case 4: {
                int studentID;
                string bookName;
                cout << "Enter student ID: ";
                cin >> studentID;
                cout << "Enter book name to issue: ";
                cin >> bookName;
                issueBook(studentID, bookName);
                break;
            }
            case 5: {
                int studentID;
                string bookName;
                cout << "Enter student ID: ";
                cin >> studentID;
                cout << "Enter book name to return: ";
                cin >> bookName;
                returnBook(studentID, bookName);
                break;
            }
            case 6:
                displayBooks();
                break;
            case 7:
                displayStudents();
                break;
            case 8:
                sortStudents();
                cout << "Students sorted by ID.\n";
                break;
            case 9:
                exitFlag = true;
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    }

    return 0;
}
