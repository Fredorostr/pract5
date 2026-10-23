#include <ios>
#include <limits>
#include <memory>
#include <string>
#include <vector>
#include <iostream>

class Book {
    private:
        std::string Book_name;
        std::string Autist; 
        int year;
        bool givenNot;
    public:
        Book(std::string N, std::string A, int y) : Book_name(N), Autist(A), year(y), givenNot(false){}
        
        std::string getBook_name() const{
            return Book_name;
        } 
        void setBook_name(const std::string& newBook_name){
            Book_name = newBook_name;
        }
        std::string getAutist() const{
            return Autist;
        }
        void setAutist(const std::string& NewAutist){
            Autist = NewAutist;
        }
        int getYear() const{
            return year;
        }
        void setYear(int newYear){
            year = newYear;
        }
        bool getgivenNot() const{
            return givenNot;
        }
        void setgivenNot(bool newGiven){
            givenNot = newGiven;
        }

};

class Reader{
    private: 
        std::string Name;
        std::vector<std::shared_ptr<Book>> takenBook; 
        int IdReader;
    public: 
        Reader(const std::string& name, int id) : IdReader(id), Name(name){}
        std::string getName() const{
            return Name;
        }
        void setName (const std::string& newName){
            Name = newName;
        }
        const std::vector<std::shared_ptr<Book>>& getTakenBook() const{
            return takenBook;
        }
        void setTakenBook(const std::vector<std::shared_ptr<Book>>& newTakenBook){
            takenBook = newTakenBook;
        }
        int getIdReader() const{
            return IdReader;
        }
        void setIdReader(int newId){
            IdReader = newId;
        }
        void takeBook(std::shared_ptr<Book> book){
            takenBook.push_back(book);
        }
        void returnBook(std::shared_ptr<Book> book){
            for(auto it = takenBook.begin(); it != takenBook.end(); ++it){
                if (*it == book ) {
                    takenBook.erase(it);
                    return;
                }
            }
        }
};

class library {
    private:
        std::vector<std::shared_ptr<Book>> Books;
        std::vector<std::shared_ptr<Reader>> Readers;
    public:
        int findBook(const std::string& Bname) const{
        for (int i = 0; i < Books.size(); i++){
            if (Books[i] -> getBook_name() == Bname){
                return i;
            }
        }
        return -1;
    }
    int findIdReader(int Idname) const{
        for (int i = 0; i < Readers.size(); i++){
            if (Readers[i] -> getIdReader() == Idname){
                return i;
            }
        }
        return -1;
    }
    void addBook(std::shared_ptr<Book> newBook){
        if (findBook(newBook -> getBook_name()) != -1){
            std::cout<<"Такая уже есть питекантроп\n";
            return;
        }
        Books.push_back(newBook);
        std::cout<<"Добавлена";
    }
    void addReader(std::shared_ptr<Reader> newReader){
        if (findIdReader(newReader -> getIdReader()) != -1) {
            std::cout<<"есть такой уже\n";
            return;
        }
        Readers.push_back(newReader);
        std::cout<<"добавлен\n";
    }
    void delitBook(const std::string& book_name){
        int id = findBook(book_name);

        if (id == -1) {
            std::cout<<"Нет такого\n";
            return;
        }

        if (Books[id] -> getgivenNot() == true) {
            std::cout<<"Нельзя удалить книгу выдали\n";
            return;
        }

        Books.erase(Books.begin() + id);
        std::cout<<"Удалена\n";
    }
    void delitReader(int id){
        int ind = findIdReader(id);

        if (ind == -1) {
            std::cout<<"нет такого удалять нечего\n";
            return;
        }
        if (!Readers[ind]->getTakenBook().empty()) {
            std::cout<<"нельзя удалить у него есть книги\n";
            return;
        }

        Readers.erase(Readers.begin() + ind);
        std::cout<<"удалили супостата\n";
    }

    void upBook(const std::string& Bname){
        int id = findBook(Bname);
        if (id == -1) {
            std::cout<<"нет такой";
            return;
        }
        
        int choice;
        std::cout<<"что изменить\n 1.название \n2. автора\n3.год\n4. Выдана или нет\n Выбор: ";
        std::cin>>choice;
        if (choice == 1) {
            std::string newName;
            std::cout<<"Новое название: ";
            std::cin.ignore();
            std::getline(std::cin, newName);
            Books[id]->setBook_name(newName);
        }
        else if (choice == 2) {
            std::string newAut;
            std::cout<<"Новый автор: ";
            std::cin.ignore();
            std::getline(std::cin, newAut);
            Books[id]->setAutist(newAut);
        }
        else if (choice == 3) {
            int newYear;
            std::cout<<"Введите новый год, только числа";
            std::cin>>newYear;
            Books[id]->setYear(newYear);
        }
        else if (choice == 4) {
            bool newStatus;
            std::cout<<"Выдана ? 1-да 0-нет";
            std::cin>>newStatus;
            Books[id]->setgivenNot(newStatus);
        }
        else {
            std::cout<<"Не корректное значение";
        return;
        }
    }
    void UpdateReader(int id){
        int ind = findIdReader(id);
        if (ind == -1) {
            std::cout<<"Нет такого";
            return;
        }
    
        std::string newName;
        std::cout<<"введите новое имя: ";
        std::cin.ignore();
        std::getline(std::cin, newName);
        Readers[ind]-> setName(newName);
        std::cout<<"Имя обновлено";

    }
    void showBooksFull(){
        if (Books.empty()) {
            std::cout<<"пустая\n";
            return;
        }
        for (const auto&book : Books) {
            std::cout<<"Название: "<< book->getBook_name()<<"\n"<<"Автор: "<<book->getAutist()<<"\n"<<"Год: "<<book->getYear()<<"\n";
            if (book->getgivenNot()) {
                std::cout<<"[ВЫДАНА]\n";
            }
            else {
                std::cout<<"[СВОБОДНА]\n";
            }
        }
    }
    void showReadersFull(){
        if (Readers.empty()) {
            std::cout<<"Нет такого\n";
            return;
        }
        for (const auto& reader : Readers) {
            std::cout<<"ID: "<< reader ->getIdReader()<<"\n"<<"Имя: "<< reader->getName()<<"\n";
        }
    }
    void readersBook(int id){
        int idx = findIdReader(id);
        if (idx == -1) {
            std::cout<<"Нет такого";
            return;
        }
        
        const auto& books = Readers[idx] -> getTakenBook();

        if (books.empty()) {
            std::cout<<"У него книг нету\n";
            return;
        }
        
        std::cout<<"Книги читателя "<< Readers[idx]->getName()<<"\n";
        for (const auto& book : books) {
            std::cout<<"- "<<book->getBook_name()<<"\n";
        }

    }
    void statistic(){

        int totalBook = Books.size();
        int givenBooks = 0;

        for (const auto& book : Books){
            if (book->getgivenNot()) {
                givenBooks++;
            }
        }
        int freeBook = totalBook - givenBooks;
        int ReadersTotal = Readers.size();

        std::cout<<"Всего книг: "<<totalBook<<"\n";
        std::cout<<"Свободно: "<<freeBook<<"\n";
        std::cout<<"Выдано:"<<givenBooks<<"\n";
        std::cout<<"Читателей: " <<ReadersTotal<<"\n";
    }
    void manageBook(const std::string& bookName, int readerId){
        int bIdx = findBook(bookName);
        int rIdx = findIdReader(readerId);
        if (bIdx == -1) {
            std::cout<<"Нет такой книги";
            return;
        }
        if (rIdx == -1) {
            std::cout<<"нет такого читателя";
            return;
        }
        int action;
        std::cout<<"1 - выдать книгу \n 2 - вернуть книгу: ";
        std::cin>>action;
        if (action == 1) {
            if (Books[bIdx]->getgivenNot() == true) {
                std::cout<<"уже выдана";
                return;
            }
            Books[bIdx]->setgivenNot(true);
            Readers[rIdx]->takeBook(Books[bIdx]);
            std::cout<<"Книга выдана\n";
        }
        else if (action == 2) {
            if (Books[bIdx]->getgivenNot() == false) {
                std::cout<<"уже в библиотеке";
                return;
            }
            Books[bIdx]->setgivenNot(false);
            Readers[rIdx]->returnBook(Books[bIdx]);
            std::cout<<"возвращена";
        }
        }
        void testDynamic(){
            Reader* temp = new Reader("Временный", 999);
            std::cout<<"Создан читатель: "<< temp ->getName()<<"\n";
            delete temp;
            std::cout<<"Удалён\n";
        }
    };

int main(){
    library MyLib;
    int answer = -1;
    while (answer != 0) {
        std::cout<<"Введите действие:\n 1.Добавить читателя  \n 2. добавить книгу\n 3. изменить книгу\n 4. изменить читателя \n 5. удалить книгу \n 6. удалить читателя \n 7. показать все книги \n 8. показать всех читателей \n 9. показать книги читателя \n 10. показать статистику\n 11. Выдать или принять книгу\n 12. тест работы \n 0 - выход\n";
        std::cin>>answer;
        switch (answer) {
            case 1:{
                std::string Nameread;
                int id;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout<<"Введите имя читателя: ";
                std::getline(std::cin, Nameread);
                std::cout<<"\nВведите id читателя: ";
                std::cin>>id;
                auto newReadr = std::make_shared<Reader>(Nameread, id);
                MyLib.addReader(newReadr);
                std::cout<<"Добавлен\n";
                break;
            }
            case 2:{
                std::string Bname;
                int year;
                std::string author;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout<<"Введите название: ";
                std::getline(std::cin, Bname);
                std::cout<<"\nВведите автора: ";
                std::getline(std::cin, author);
                std::cout<<"\nВведите год: ";
                std::cin>>year;
                auto Newbook = std::make_shared<Book>(Bname, author, year);
                MyLib.addBook(Newbook);
                break;

            }
            case 3: {
                std::string Bname;
                std::cout<<"Введите название книги: ";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, Bname);
                MyLib.upBook(Bname);
                break;
            }
            case 4: {
                int id;
                std::cout<<"Введите id цифрами: ";
                std::cin>>id;
                MyLib.UpdateReader(id);
                break;
            }
            case 5:{
                std::string Bname;
                std::cout<<"Введите название книги: ";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, Bname);
                MyLib.delitBook(Bname);
                break;
            }
            case 6: {
                int id;
                std::cout<<"Введите id читателя: ";
                std::cin>>id;
                MyLib.delitReader(id);
                break;
            }
            case 7:{
                MyLib.showBooksFull();
                break;
            }
            case 8:{
                MyLib.showReadersFull();
                break;
            }
            case 9:{
                int ind;
                std::cout<<"Введите id читателя: ";
                std::cin>>ind;
                MyLib.readersBook(ind);
                break;
            }
            case 10:{
                MyLib.statistic();
                break;
            }
            case 11: {
                std::string NameBook;
                int readerId;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout<<"введите название книги: ";
                std::getline(std::cin, NameBook);
                std::cout<<"введите id читателя";
                std::cin>>readerId;
                MyLib.manageBook(NameBook, readerId);
                break;
            }
            case 12:
                MyLib.testDynamic();

        }       
    }
}