//Justin Alcaraz
//Lesson 2 Assignment

#include <iostream>
#include <cctype>
using namespace std;


void printMenu(string);
string getInput();

//The book class contains constructors that can be used to create book objects. The private members describe each book's
// title, author, ISBN number, and availability.
class Book{
private:
    string title;
    string author;
    int ISBN;
    bool availability;
public:
    Book(){
        title = "None";
        author = "None";
        ISBN = 0;
        availability = false;
    }
    Book(string t, string a, int i) :
    title {t},
    author {a},
    ISBN {i},
    availability {true}
    {
    }
    void displayBook(){
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "ISBN: " << ISBN << endl;
        if (availability == true){
            cout << "Available? True" << endl;
        }
        else{
            cout << "Available? False" << endl;
        }
    }
    bool getAvailability(){
        return availability;
    }
    void setAvailability(bool b){
        availability = b;
    }
    string getTitle(){
        return title;
    }
    string getAuthor(){
        return author;
    }
};

//The user class is a parent class to the student and faculty classes. The user class contains members that every student and
// faculty object have, name and userID.
class User{
protected:
    string name;
    int userID;
    string booksBorrowed[500];
public:
    User(){
        name = "None";
        userID = -1;
    }
    User(int index, string username){
        name = username;
        userID = index;
    }
    int getUserID(){
        return userID;
    }
};
// Student is a derived class of User, it has access to the user constructor to allow students to have a name and userID.
// In addition, the student class provides each student with the userType "Student"
class Student : public User
{
private:
    string userType;
public:
    Student()
    {
        userType = "Student";
    }
    Student(int index, string username) : User(index, username){
        userType = "Student";
        userID = index;
        name = username;
    }
    string getUserType(){
        return userType;
    }
    void displayStudent(){
        cout << "User Name: " << name << endl;
        cout << "User ID: " << userID << endl;
        cout << "Class: " << userType << endl;
    }
    int getStudentID(){
        return userID;
    }
};
// Faculty is also a derived class of User, it has access to the user constructor to allow Faculty to have a name and userID.
// In addition, the Faculty class provides each Faculty person with the userType "Faculty"

class Faculty : public User
{
private:
    string userType;
public:
    Faculty(){
        userType = "Faculty";
    }
    Faculty(int index, string username) : User((index+500), username){
        userType = "Faculty";
    }
    string getUserType(){
        return userType;
    }
    void displayFaculty(){
        cout << "User Name: " << name << endl;
        cout << "User ID: " << userID << endl;
        cout << "Class: " << userType << endl;
    }
    int getFacultyID(){
        return userID;
    }
};

//The Library class here is a singleton. Using methods from our provided lesson on the singleton, this class utilizes references
// and pointers to make sure that there is always only one instance of Library.
//Its constructor is private so that new instances may not be created.
class Library{
private:
    Library(){};
    static Library* instance;
public:
    Book booksInLibrary[500];
    Student StudentsInLibrary[500];
    Faculty FacultyInLibrary[500];
    static Library *getInstance();
    void addBook(int index, string title, string author, int ISBN){
        booksInLibrary[index] = {Book(title, author, ISBN)};
    }
    void addUserS(int index, string name){
        StudentsInLibrary[index] = {Student(index, name)};
    }
    void addUserF(int index, string name){
        FacultyInLibrary[index] = {Faculty(index, name)};
    }
};

//Initializing Library instance with nullptr and then making sure that the same instance is always returned with getInstance
Library* Library::instance = nullptr;

Library *Library::getInstance(){
    if (instance == nullptr){
        instance = new Library();
    }
    return instance;
}

//Three function declarations that control the three main options of the library menu
string manage_books(Library*);
string manage_users(Library*);
string manage_transactions(Library*);

int main(){
    //First and only time that the library instance is created
    Library* L = Library::getInstance();
    
    string userChoice = "";
    
    while (userChoice != "4"){
        printMenu("Library");
        cout << "Enter your choice: ";
        getline(cin, userChoice);
        
        //Switch menu to switch between the different library options
        switch(stoi(userChoice)){
            case 1:
                while(userChoice != "4"){
                    userChoice = manage_books(L);
                    continue;
                }
                userChoice = "";
                break;
            case 2:
                while(userChoice != "4"){
                    userChoice = manage_users(L);
                    continue;
                }
                userChoice = "";
                break;
            case 3:
                while(userChoice != "5"){
                    userChoice = manage_transactions(L);
                    continue;
                }
                userChoice = "";
                break;
        }
    }
    cout << endl << "Thank you for using the Library System!" << endl << endl;
    return 0;
    
}

//This function does not return anything and takes a string as a parameter to determine what menu should be outputted
void printMenu(string s){
    if (s == "Library"){
        cout << endl << "Welcome to the Library:" << endl << "1. Manage Books" << endl << "2. Manage Users" << endl << "3. Manage Transactions" << endl << "4. Exit" << endl << endl;
    }
    if (s == "Manage Books"){
        cout << endl << "Manage Books:" << endl << "1. Add a Book" << endl << "2. Edit a Book" << endl << "3. Remove a Book" << endl << "4. Go Back" << endl << endl;
    }
    if (s == "Manage Users"){
        cout << endl << "Manage Users:" << endl << "1. Add a User" << endl << "4. Go Back" << endl;
    }
    if (s == "Manage Transactions"){
        cout << endl << "Manage Transactions:" << endl << "1. Check Out A Book" << endl << "2. Check In A Book" << endl << "3. Search for a Book" << endl << "5. Go Back" << endl;
    }
}

//getInput() returns a string after prompting the user to enter a choice
string getInput(){
    string userChoice = "";
    cout << "Enter your choice: ";
    getline (cin, userChoice);
    return userChoice;
}

//manage_books is one of the main functions, it returns the user choice to the main function and takes a library pointer as a
//parameter. This way, manage_books is able to call functions in the library class as well as modify the list of books in library.
string manage_books(Library* L){
    printMenu("Manage Books");
    string userChoice = getInput();
    if (userChoice == "4"){
        return userChoice;
    }
    switch(stoi(userChoice)){
        case 1: //Add a book
        {
            cout << "Add a Book" << endl;
            cout << "Enter the Title (0 to cancel): ";
            string title;
            getline(cin, title);
            if (title == "0"){
                return userChoice;
            }
            cout << "Enter the Author (0 to cancel): ";
            string author;
            getline(cin, author);
            if (author == "0"){
                return userChoice;
            }
            cout << "Enter the ISBN (0 to cancel): ";
            int ISBN;
            cin >> ISBN;
            if (ISBN == 0){
                return userChoice;
            }
            for (int i = 0; i < 500; i++){
                if(L->booksInLibrary[i].getAvailability() == false){
                    L->addBook(i, title, author, ISBN);
                    cout << "Book Added" << endl;
                    break;
                }
            }
            break;
        }
        case 2: //Edit a Book
        {
            cout << "Enter the title or author of the book you would like to edit: ";
            string editBook;
            getline(cin, editBook);
            for (int j = 0; j < 500; j++){
                if(L->booksInLibrary[j].getTitle() == editBook || L->booksInLibrary[j].getAuthor() == editBook){
                    cout << "Book found!" << endl;
                    cout << "Please enter new information for the Book" << endl;
                    cout << "Enter the Title (0 to cancel): ";
                    string title;
                    getline(cin, title);
                    if (title == "0"){
                        return userChoice;
                    }
                    cout << "Enter the Author (0 to cancel): ";
                    string author;
                    getline(cin, author);
                    if (author == "0"){
                        return userChoice;
                    }
                    cout << "Enter the ISBN (0 to cancel): ";
                    int ISBN;
                    cin >> ISBN;
                    if (ISBN == 0){
                        return userChoice;
                    }
                    L->addBook(j, title, author, ISBN);
                    //L->booksInLibrary[j] = {Book(title, author, ISBN)};
                    cout << "Book Successfully Changed" << endl;
                    cin.ignore();
                    return userChoice;
                }
            }
            cout << "Book not found" << endl;
            return userChoice;
        }
        case 3: //Remove a Book
        {
            bool foundBook = false;
            cout << "Enter the title or author of the book you would like to remove: ";
            string editBook;
            getline(cin, editBook);
            for (int j = 0; j < 500; j++){
                if(L->booksInLibrary[j].getTitle() == editBook || L->booksInLibrary[j].getAuthor() == editBook){
                    foundBook = true;
                    cout << "Book found!" << endl;
                    cout << "The book will now be removed from the library." << endl;
                    L->booksInLibrary[j] = Book();
                    break;
                }
            }
            if (foundBook == false){
                cout << "Book not in Library" << endl;
            }
            return userChoice;
        }
    }
    cin.ignore();
    return userChoice;
}

//manage_users returns a string to main which is the userChoice. This function takes a library pointer as a parameter as well
//in order to modify the list of faculty users and student users
string manage_users(Library* L){
    printMenu("Manage Users");
    string userChoice = getInput();
    if (userChoice == "4"){
        return userChoice;
    }
    switch(stoi(userChoice)){
        case 1: //Add a user
        {
            cout << "Add a User" << endl;
            cout << "Enter 1 for Student or 2 for Faculty (0 to cancel): ";
            string input;
            getline(cin, input);
            if (input == "0"){
                return userChoice;
            }
            if (input == "1"){
                cout << "Enter name (0 to cancel): ";
                string name;
                getline(cin, name);
                if (name == "0"){
                    return userChoice;
                }
                for (int n = 0; n < 500; n++){
                    if(L->StudentsInLibrary[n].getStudentID() == -1){
                        L->addUserS(n, name);
                        cout << "User Added" << endl;
                        L->StudentsInLibrary[n].displayStudent();
                        break;
                    }
                }
                break;
            }
            
            if (input == "2"){
                cout << "Enter name (0 to cancel): ";
                string facultyname;
                getline(cin, facultyname);
                if (facultyname == "0"){
                    return userChoice;
                }
                for (int num = 0; num < 500; num++){
                    if(L->FacultyInLibrary[num].getFacultyID() == -1){
                        L->addUserF(num, facultyname);
                        L->FacultyInLibrary[num].displayFaculty();
                        break;
                    }
                }
                break;
            }
        }
            return userChoice;
    }
    return userChoice;
}

//manage_transactions, like the previous two functions, returns the userChoice as a string and takes a library pointer to handle
//checking out, checking in, and searching for books.
string manage_transactions(Library* L){
    printMenu("Manage Transactions");
    string userChoice = getInput();
    if (userChoice == "1"){
        cout << "Check Out A Book: " << endl;
        bool foundBook = false;
        cout << "Enter the title or author of the book you would like to check out: ";
        string editBook;
        getline(cin, editBook);
        for (int j = 0; j < 500; j++){
            if((L->booksInLibrary[j].getTitle() == editBook || L->booksInLibrary[j].getAuthor() == editBook) && L->booksInLibrary[j].getAvailability() == true){
                foundBook = true;
                cout << "Book found!" << endl;
                cout << "Enter 1 for Student or 2 for Faculty (0 to cancel): ";
                string input;
                getline(cin, input);
                if (input == "0"){
                    return userChoice;
                }
                if (input == "1"){
                    cout << "Please enter your Student ID: ";
                    int studentID;
                    cin >> studentID;
                    for(int m = 0; m < 500; m++){
                        if(L->StudentsInLibrary[m].getStudentID() == studentID){
                            L->booksInLibrary[j].setAvailability(false);
                            cout << "ID found! Your book has been checked out" << endl;
                            cin.ignore();
                            return userChoice;
                        }
                    }
                    cout << "User not found" << endl;
                    cin.ignore();
                    return userChoice;
                }
                if (input == "2"){
                    cout << "Please enter your Faculty ID: ";
                    int facultyID;
                    cin >> facultyID;
                    for(int s = 0; s < 500; s++){
                        if(L->FacultyInLibrary[s].getFacultyID() == facultyID){
                            L->booksInLibrary[j].setAvailability(false);
                            cout << "ID found! Your book has been checked out." << endl;
                            cin.ignore();
                            return userChoice;
                        }
                    }
                    cout << "User not found" << endl;
                    cin.ignore();
                    return userChoice;
                }
                return userChoice;
            }
        }
        if (foundBook == false){
            cout << "Book not in Library" << endl;
        }
        return userChoice;
    }
    if (userChoice == "2"){
        cout << "Check In A Book: " << endl;
        bool foundBook = false;
        cout << "Enter the title or author of the book you would like to check in: ";
        string editBook;
        getline(cin, editBook);
        for (int j = 0; j < 500; j++){
            if((L->booksInLibrary[j].getTitle() == editBook || L->booksInLibrary[j].getAuthor() == editBook) && L->booksInLibrary[j].getAvailability() == false){
                foundBook = true;
                cout << "Book found!" << endl;
                cout << "Enter 1 for Student or 2 for Faculty (0 to cancel): ";
                string input;
                getline(cin, input);
                if (input == "0"){
                    return userChoice;
                }
                if (input == "1"){
                    cout << "Please enter your Student ID: ";
                    int studentID;
                    cin >> studentID;
                    for(int m = 0; m < 500; m++){
                        if(L->StudentsInLibrary[m].getStudentID() == studentID){
                            L->booksInLibrary[j].setAvailability(true);
                            cout << "ID found! Your book has been checked in" << endl;
                            cin.ignore();
                            return userChoice;
                        }
                    }
                    cout << "User not found" << endl;
                    cin.ignore();
                    return userChoice;
                }
                if (input == "2"){
                    cout << "Please enter your Faculty ID: ";
                    int facultyID;
                    cin >> facultyID;
                    for(int s = 0; s < 500; s++){
                        if(L->FacultyInLibrary[s].getFacultyID() == facultyID){
                            L->booksInLibrary[j].setAvailability(true);
                            cout << "ID found! Your book has been checked in." << endl;
                            cin.ignore();
                            return userChoice;
                        }
                    }
                    cout << "User not found" << endl;
                    cin.ignore();
                    return userChoice;
                }
                return userChoice;
            }
        }
        if (foundBook == false){
            cout << "Book not in Library" << endl;
        }
        return userChoice;
    }
    if (userChoice == "3"){
        cout << "Enter the title or author of the book you would like to search: ";
        string editBook;
        getline(cin, editBook);
        for (int j = 0; j < 500; j++){
            if(L->booksInLibrary[j].getTitle() == editBook || L->booksInLibrary[j].getAuthor() == editBook){
                cout << "Book found!" << endl;
                L->booksInLibrary[j].displayBook();
                return userChoice;
            }
        }
        return userChoice;
    }
            

    if (userChoice == "5"){
        return userChoice;
    }
    return userChoice;
}
