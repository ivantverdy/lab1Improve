//
// Created by aboba on 10/1/2023.
//

#ifndef LABB1_FUNCFORSIMPLEINTERFACE_H
#define LABB1_FUNCFORSIMPLEINTERFACE_H

#include "vectorList.h"

book writeBookData() {
    string nameOfBook, releaseDate, annotation;
    vectorList<string> authorsName;
    int numOfPages, numOfCharacters, numOfAuthors;
    vectorList<character> characters;

    cout << "What`s the name of the new book? " << endl;
    getline(cin >> ws, nameOfBook);

    cout << "When the book was released? " << endl;
    getline(cin >> ws, releaseDate);

    cout << "What`s the book's annotation? " << endl;
    getline(cin >> ws, annotation);

    cout << "What`s the pages count of book? " << endl;
    cin >> numOfPages;

    cout << "What`s count of authors in this book and count of characters? " << endl;
    cin >> numOfAuthors >> numOfCharacters;

    cout << "Write authors 1 by 1(Wrote first, use enter, second, use enter and so on)" << endl;
    for (int i = 0; i < numOfAuthors; i++) {
        cout << i + 1 << "st author: ";
        string nameOfAuthorIter;
        getline(cin >> ws, nameOfAuthorIter);
        authorsName.add(nameOfAuthorIter);
    }
    cout
            << "Write characters 1 by 1(Wrote first`s data (1st name, use enter, than participation), use enter, second, use enter and so on)"
            << endl;
    for (int i = 0; i < numOfCharacters; i++) {
        cout << i + 1 << "st character name: ";
        character characterIter;
        string nameOfCharacterIter, participation;
        getline(cin >> ws, nameOfCharacterIter);
        cout << i + 1 << "st character participation: ";
        getline(cin >> ws, participation);
        characterIter.setCharacterName(nameOfCharacterIter);
        characterIter.setParticipation(participation);
        characters.add(characterIter);
    }

    book newBook;
    newBook.setNameOfBook(nameOfBook);
    newBook.setReleaseDate(releaseDate);
    newBook.setAnnotation(annotation);
    newBook.setNumOfPages(numOfPages);
    newBook.setAuthorsName(authorsName);
    newBook.setCharacters(characters);

    return newBook;
}

database writeBook(database &Library) {
    book newBook = writeBookData();
    Library.addBook(newBook);
    return Library;
}

database readBook(database &library, const string &fileName) {
    ifstream reading(fileName);
    if (reading) {
        int numOfBooksInFile;
        reading >> numOfBooksInFile;
        reading.ignore(); // consume newline

        for (int i = 0; i < numOfBooksInFile; i++) {
            string nameOfBook, releaseDate, annotation;
            int numOfPages, numOfCharacters, numOfAuthors;

            getline(reading >> ws, nameOfBook);
            getline(reading >> ws, releaseDate);
            getline(reading >> ws, annotation);

            reading >> numOfPages >> numOfAuthors;


            vectorList<string> authorsName;
            for (int j = 0; j < numOfAuthors; j++) {
                string nameOfAuthorIter;
                getline(reading >> ws, nameOfAuthorIter);
                authorsName.add(nameOfAuthorIter);
            }

            reading >> numOfCharacters;

            vectorList<character> characters;
            for (int j = 0; j < numOfCharacters; j++) {
                character characterIter;
                string nameOfCharacterIter, participation;
                getline(reading >> ws, nameOfCharacterIter);
                getline(reading >> ws, participation);
                characterIter.setCharacterName(nameOfCharacterIter);
                characterIter.setParticipation(participation);
                characters.add(characterIter);
            }

            book newBook;
            newBook.setNameOfBook(nameOfBook);
            newBook.setReleaseDate(releaseDate);
            newBook.setAnnotation(annotation);
            newBook.setNumOfPages(numOfPages);
            newBook.setAuthorsName(authorsName);
            newBook.setCharacters(characters);

            library.addBook(newBook);
        }
    }
    return library;
}

database changeBookData(database &library) {
    cout << "What you want to do with your book? " << endl;
    cout << "Write 1 to edit book " << endl;
    cout << "Write 2 to delete book " << endl;
    cout << "Write 3 to search book " << endl;
    cout << "Write 4 to add author" << endl;
    cout << "Write 5 to edit author" << endl;
    cout << "Write 6 to delete author" << endl;
    cout << "Write 7 to search author" << endl;

    int actions = 0;
    cin >> actions;
    string bookName;
    book book1;

    switch (actions) {
        case 1: {
            cout << "Temporarily not working, need to be fixed ";
            cout << "Enter the name of the book you want to edit: ";
            getline(cin >> ws, bookName);

            book updatedBook = writeBookData();
            library.editBook(bookName, updatedBook);
            break;
        }
        case 2: {
            cout << "Enter the name of the book you want to delete: ";
            getline(cin >> ws, bookName);

            library.deleteBook(bookName);
            break;
        }
        case 3: {
            cout << "Enter the name of the book you want to search for: ";
            getline(cin >> ws, bookName);

            book foundBook;
            foundBook = library.searchBook(bookName);
            foundBook.showBook();
            break;
        }
        case 4: {
            cout << "Enter the name of the book which you want to add an author to: ";
            getline(cin >> ws, bookName);

            cout << "How many authors do you want to add? ";
            int numAuthors;
            cin >> numAuthors;

            vectorList<string> authorsToAdd;
            for (int i = 0; i < numAuthors; ++i) {
                string authorName;
                cout << "Enter author " << i + 1 << "'s name: ";
                getline(cin >> ws, authorName);
                authorsToAdd.add(authorName);
            }

            library.addAuthor(authorsToAdd, bookName);
            break;
        }
        case 5: {
            cout << "Enter the name of the book you want to edit author into: ";
            getline(cin >> ws, bookName);

            string oldAuthor;
            cout << "Enter the name of the author you want to edit: ";
            getline(cin >> ws, oldAuthor);

            string newAuthor;
            cout << "Enter the new author name: ";
            getline(cin >> ws, newAuthor);

            library.editAuthor(bookName, oldAuthor, newAuthor);
            break;
        }
        case 6: {
            cout << "Enter the name of the book from which you want to delete an author: ";
            getline(cin >> ws, bookName);

            string authorToDelete;
            cout << "Enter the name of the author you want to delete: ";
            getline(cin >> ws, authorToDelete);

            library.deleteAuthor(bookName, authorToDelete);
            break;
        }
        case 7: {
            cout << "Enter the name of the book to search for an author: ";
            getline(cin >> ws, bookName);

            string foundAuthor = library.searchAuthor(bookName);
            cout << "Author found: " << foundAuthor << endl;
            break;
        }
    }
    return library;
}


void sortLibrary(database &library) {
    library.getLibrary().quickSort();
    library.getLibrary().showList();
} // need to be fixed

void saveInFile(database &library, string &fileName) {
    ofstream record(fileName);
    int numOfBooksInFile;
    cin >> numOfBooksInFile;
    record << numOfBooksInFile;
    if (record) {
        for (int i = 0; i < library.getLibrary().getVectorList().size(); i++) {
            record << library.getNameOfBook();
            record << library.getReleaseDate();
            record << library.getAnnotation();
            record << library.getNumOfPages();
            record << library.getReleaseDate()[i];
            record << library.getAnnotation()[i];
            record << library.getNumOfPages(); //<< library.getVectorOfAuthorsName();overload for vectorList authors
        }
    }
}


#endif //LABB1_FUNCFORSIMPLEINTERFACE_H
