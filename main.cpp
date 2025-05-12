#include<bits/stdc++.h>
using namespace std;

#include<thread>

#define fast_io  ios_base::sync_with_stdio(false); cin.tie(NULL)
#define pb push_back
#define int long long int

class IDGenerator{
public:
    static int cnt;

    static string generate_id(string author){

        cnt ++;
        string str = "";
        if(author.size() < 3){
            str += author;
        } else{
            for(int i = author.size() - 3; i < author.size(); ++i){
                str += author[i];
            }
        }

        str += to_string(cnt);
        return str;
    }
};

class User{
private:
    string name;
    int id;
public:
    User(string name, int id){
        this -> name = name;
        this -> id = id;
    }

    string get_name() const{
        return name;
    }

    int get_id() const{
        return id;
    }
};

class Book{
private:
    string name;
    string author;
    string id;
public:
    Book(string name, string author){
        this -> name = name;
        this -> author = author;
        this -> id = IDGenerator :: generate_id(author);
    }

    string get_name() const{
        return name;
    }

    string get_author() const {
        return author;
    }

    string get_id() const{

        return id;
    }
};

class FineManager{
private:
    unordered_map<int, int> fine;
    const int FINE_PER_DAY = 20;
public:

    void add_fine(int user_id, int days_extra){

        if(fine.find(user_id) == fine.end()){
            fine[user_id] = 0;
        }

        fine[user_id] += days_extra * FINE_PER_DAY;
    }

    void pay_fine(int user_id, int amt){

        if(amt < 0){

            cout << "Amount cannot be negative \n";
            return;
        }
        if(fine.find(user_id) == fine.end()){

            cout << "Fine amount due : $0, No need to pay \n";
            return;
        } else{

            if(fine[user_id] < amt){

                cout << "$" << fine[user_id] << "Amount paid towards fine \n";
                cout << "Returning $" << amt - fine[user_id] << '\n';
                fine[user_id] = 0;

            } else{
                cout << "Paid : $" << amt << " ";
                fine[user_id] -= amt;
                cout << "Pending Fine is $" << fine[user_id] << '\n';
            }
        }
    }

    void display_fines(){

        for(auto ele : fine){
            cout << ele.first << ": $" << ele.second << '\n';
        }
    }
};

class WaitListManager{
private:

    unordered_map<string, queue<int> > wait_queue;
public:

    void add_to_queue(const string& book_id, int user_id){
        wait_queue[book_id].push(user_id);
    }

    bool is_empty(string book_id){
        if(wait_queue[book_id].empty()){
            return true;
        }
        return false;
    }

    int get_next_user(string book_id){

        int user_id = wait_queue[book_id].front();
        wait_queue[book_id].pop();

        return user_id;
    }
};

class ReservationManager{
private:

    unordered_map<string, pair<int, int> > reserved_books;
    WaitListManager wait_list_manager;
    FineManager fine_manager;
public:

    void borrow_book(const string &book_id, int user_id, int day){

        if(reserved_books.find(book_id) == reserved_books.end()){

            // reserve under user's name
            reserved_books[book_id] = make_pair(user_id, day + 14);
        } else{

            // add to waitlist
            wait_list_manager.add_to_queue(book_id, user_id);
        }
    }

    void return_book(const string& book_id, int day){

        auto ele = reserved_books[book_id];

        int user_id = ele.first;

        if(day > ele.second){
            fine_manager.add_fine(user_id, day - ele.second);
        }

        reserved_books.erase(book_id);

        if(wait_list_manager.is_empty(book_id)){

            // do ntg
        } else{

            int top_user_id = wait_list_manager.get_next_user(book_id);
            reserved_books[book_id] = make_pair(top_user_id, day + 14);
        }
    }

    void pay_fine(int user_id, int amt){
        fine_manager.pay_fine(user_id, amt);
    }

    void show_fines(){
        fine_manager.display_fines();
    }
};

class LibraryManagementSystem{
private:

    unordered_map<string, Book*> id_to_book;
    unordered_map<int, User*> id_to_user;

    ReservationManager reservation_manager;
public:

    void add_book(string name, string author){
        Book* book = new Book(name, author);
        id_to_book[book -> get_id()] = book;
    }

    void register_user(string name, int id){

        if(id_to_user.find(id) != id_to_user.end()){

            cout << "User already registered !! \n";
            return;
        }
        User* user = new User(name, id);
        id_to_user[id] = user;
    }

    void unregister_user(int id){

        if(id_to_user.find(id) == id_to_user.end()){
            cout << "User doesnot exist \n";
            return;
        }

        id_to_user.erase(id);
    }

    void borrow_book(const string& book_id, int user_id, int day){
        reservation_manager.borrow_book(book_id, user_id, day);
    }

    void return_book(const string& book_id, int day){
        reservation_manager.return_book(book_id, day);
    }

    void pay_fine(int user_id, int amt){
        reservation_manager.pay_fine(user_id, amt);
    }

    void show_fines(){

        reservation_manager.show_fines();
    }
};

int IDGenerator :: cnt = 0;

signed main(){

    fast_io;

    LibraryManagementSystem library;
    library.register_user("Alice", 101);
    library.register_user("Bob", 102);

    library.add_book("Harry Potter", "Rowling");
    library.add_book("Chamber of Secrets", "Rowling");

    library.borrow_book( "ing1", 101,  0);
    library.borrow_book( "ing1",102,  1); // Waitlisted

    library.return_book("ing1", 20); // Fine for user 101, handover to 102
    library.pay_fine(101, 100);

    library.show_fines();
}
