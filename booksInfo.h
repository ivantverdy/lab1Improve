//
// Created by aboba on 9/27/2023.
//

#ifndef LABB1_BOOKSINFO_H
#define LABB1_BOOKSINFO_H

#include <iostream>
#include <string>
#include "vectorList.h"
#include "nodeList.h"
#include "arrList.h"

using namespace std;

class character;


class book {
private:
    string nameOfBook{}, releaseDate{}, annotation{};
    vectorList<string> authorsName{};
    int numOfPages{};
    vectorList<character> characters{};
public:

    book() = default;

    book(const string &nameOfBook1, const string &releaseDate1, const string &annotation1,
         const vectorList<string> &authorsName1, const int numOfPages1, const vectorList<character> &characters1) {
        nameOfBook = nameOfBook1;
        releaseDate = releaseDate1;
        annotation = annotation1;
        authorsName = authorsName1;
        numOfPages = numOfPages1;
        characters = characters1;
    }

    vectorList<character> getCharacters() {
        return characters;
    }

    void setCharacters(vectorList<character> &characters1) {
        characters = characters1;
    }

    string getNameOfBook() { return nameOfBook; }

    void setNameOfBook(string nameOfBook1) {
        nameOfBook = (nameOfBook1);
    }

    string getReleaseDate() { return releaseDate; }

    void setReleaseDate(string releaseDate1) {
        releaseDate = releaseDate1;
    }

    string getAnnotation() { return annotation; }

    void setAnnotation(string annotation1) {
        annotation = annotation1;
    }

    vectorList<string> getVectorOfAuthorsName() { return authorsName; }

    void setAuthorsName(vectorList<string> authorsName1) {
        authorsName = authorsName1;
    }

    int getNumOfPages() { return numOfPages; }

    void setNumOfPages(int numOfPages1) {
        numOfPages = numOfPages1;
    }

    void showBook() {
        cout << this;
    }

    template<class T>

    friend ostream &operator<<(ostream &out, vectorList<T> &nameOfBook1);
    friend ostream &operator<<(ostream &out, book &book1);

    bool operator<(book &book1);

    bool operator<=(book &book1);

    bool operator>(book &book1);

    bool operator>=(book &book1);

    bool operator==(book &book1);

};


class character {
private:
    string characterName{};
    string participation{}; // main, secondary, etc
public:
    character() = default;

    character(const string &characterName1, const string &participation1) {
        characterName = characterName1;
        participation = participation1;
    }

    string getCharacterName() { return characterName; }

    void setCharacterName(string &characterName1) {
        characterName = characterName1;
    }

    string getParticipation() { return participation; }

    void setParticipation(string &participation1) {
        participation = participation1;
    }

    friend ostream &operator<<(ostream &out, character &character1);

};

//дві книги належать до однієї серії, якщо у них є спільний головний чи другорядний персонаж

class series : public book{
private:
    vectorList<book> seriesOfBooks{};

    //seriesOfBookIter.getCharacters().getVectorList() need to get vector of characters from vectorList<character> characters
    bool checkToAddBook(book &book1) {
        for (auto &seriesOfBookIter: seriesOfBooks.getVectorList()) {
            for (auto &characterIter: seriesOfBookIter.getCharacters().getVectorList()) {
                for (auto &j: book1.getCharacters().getVectorList()) {
                    if (characterIter.getCharacterName() == j.getCharacterName() and
                        ((characterIter.getParticipation() == "main" or
                          characterIter.getParticipation() == "secondary") and
                         (j.getParticipation() == "main" or j.getParticipation() == "secondary"))) {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    bool checkIfBookInSeriesAlready(book &book1) {
        for (auto &seriesOfBook: seriesOfBooks.getVectorList()) {
            {
                if (seriesOfBook == book1)
                    return true;
            }
        }
        return checkToAddBook(book1);
    }

    static bool comparatorToSortByReleaseDate(book &book1, book &book2) {
        return book1.getReleaseDate() < book2.getReleaseDate();
    }
public:
    vectorList<book> getSeriesOfBooks() {
        return seriesOfBooks;
    }

    void setSeriesOfBooks(vectorList<book> &seriesOfBooks1) {
        seriesOfBooks = seriesOfBooks1;
    }

    void showSeriesOfBooks() {
        cout << "SERIESOFBOOK SIZE " << seriesOfBooks.getSize() << endl;
        for (auto &item: seriesOfBooks.getVectorList()) {
            item.showBook();
        }
    }

    void addBookToSeries(book &book1) {
        if (seriesOfBooks.getSize() < 1) { seriesOfBooks.add(book1); }

        else if (checkIfBookInSeriesAlready(book1)) {
            cout << book1.getNameOfBook() << ": this book is already in series! " << endl;
        } else {
            seriesOfBooks.add(book1);
        }
    }

    void sortByReleaseDate() {
        sort(this->seriesOfBooks.getVectorList().begin(), seriesOfBooks.getVectorList().end(),
             comparatorToSortByReleaseDate);
    }

    friend ostream &operator<<(ostream &out, book &book1);

};

class database :  public character, public series{
private:
    vectorList<book> library;
    vectorList<series> booksSeries;
public:
    vectorList<book> getLibrary() {
        return library;
    }

    vectorList<series> getBookSeries() {
        return booksSeries;
    }

    void addBook(book &newBook) {
        library.add(newBook);
        for (auto &bookInSeries : booksSeries.getVectorList()) {
            bookInSeries.addBookToSeries(newBook);
        }
    }

    void editBook(string &bookName, book &updatedBook) {
        for (auto &bookInLibrary: library.getVectorList()) {
            if (bookInLibrary.getNameOfBook() == bookName) {
                bookInLibrary = updatedBook;
                cout << "Book with the name " << bookName << " was successfully modified" << endl;
                return;
            }
        }
        cout << "Book with the name " << bookName << " isn't found" << endl;
    } // need to fix it

    void deleteBook(string &bookName) {
        for (auto &bookInLibrary: library.getVectorList()) {
            if (bookInLibrary.getNameOfBook() == bookName) {
                library.remove(bookInLibrary);
                cout << "Book with the name " << bookName << " was successfully deleted" << endl;
                return;
            }
        }
        cout << "Book with the name " << bookName << " isn't found" << endl;
    }

    book searchBook(string &bookName) {
        for (auto &bookInLibrary: library.getVectorList()) {
            if (bookInLibrary.getNameOfBook() == bookName)
                return bookInLibrary;
        }
        cout << "Book with the name " << bookName << " isn't found" << endl;
    }

    void showLibrary() {
        for (auto &bookInLibrary: library.getVectorList()) {
                cout << bookInLibrary;
                }
        }

    void showSeries() {
        for (auto &bookInSeries: booksSeries.getVectorList()) {
            bookInSeries.showSeriesOfBooks();
        }
    }

    void addAuthor(vectorList<string> &authorsName, string &bookName) {
        for (auto &bookInLibrary: library.getVectorList()) {
            for (int i = 0; i < library.getVectorList().size(); i++) {
                if (bookInLibrary.getNameOfBook() == bookName) {
                    bookInLibrary.setAuthorsName(authorsName);
                    cout << "Author(s) was successfully added in the book" << bookName << endl;
                    return;
                }
            }
        }
    }

    void editAuthor(string &bookName, string &oldAuthor, string &newAuthor) {
        for (auto &bookInLibrary : library.getVectorList()) {
            if (bookInLibrary.getNameOfBook() == bookName) {
                vectorList<string> authors = bookInLibrary.getVectorOfAuthorsName();
                for (int i = 0; i < authors.getSize(); i++) {
                    if (authors.getVectorList()[i] == oldAuthor) {
                        authors.getVectorList()[i] = newAuthor;
                        cout << "Author with the name " << oldAuthor << " was successfully edited" << endl;
                        return;
                    }
                }
                cout << "Author with the name " << oldAuthor << " isn't found in the book" << endl;
                return;
            }
        }
        cout << "Book with the name " << bookName << " isn't found" << endl;
    }

    //bookInLibrary.getVectorOfAuthorsName().getVectorList() need to get vector of authors from vectorList<string> authors
    void deleteAuthor(string &bookName, string &authorName) {
        for (auto &bookInLibrary : library.getVectorList()) {
            if (bookInLibrary.getNameOfBook() == bookName) {
                vectorList<string> authors = bookInLibrary.getVectorOfAuthorsName();
                for (int i = 0; i < authors.getSize(); i++) {
                    if (authors.getVectorList()[i] == authorName) {
                        authors.remove(authors.getVectorList()[i]);
                        cout << "Author " << authorName << " was successfully deleted from the book " << bookName << endl;
                        return;
                    }
                }
                cout << "Author with the name " << authorName << " isn't found in the book " << bookName  << endl;
                return;
            }
        }
        cout << "Book with the name " << bookName << " isn't found" << endl;
    }

    string searchAuthor(string &authorName) {
        for (auto &bookInLibrary: library.getVectorList()) {
            for (int i = 0; i < library.getVectorList().size(); i++) {
                if (bookInLibrary.getVectorOfAuthorsName().getVectorList()[i] == authorName) {
                    cout << "Author with the name " << authorName << " was successfully edited" << endl;
                    return bookInLibrary.getVectorOfAuthorsName().getVectorList()[i];
                }
            }
        }
        cout << "Book with the name " << authorName << " isn't found" << endl;
    }

};


#endif //LABB1_BOOKSINFO_H
