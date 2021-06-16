#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

class Login_Info {
protected:
    string username;
    string password;
public:
    void set_value(string iuser, string ipass) {
        username = iuser;
        password = ipass;
    }
    void display() {
        cout << username << " " << password << endl;
    }
    void login_input() {
        cout << "Enter Your Username: ";
        cin >> username;
        cout << "Enter Your Password: ";
        cin >> password;
    }
};

class Signup {
public:
    string gender;
    string mobi_num;
    string address;
    string email;
    string first_name;
    string last_name;
    void signup_input() {
        cout << "Enter Your First Name: ";
        cin >> first_name;
        cout << "Enter Your Last Name: ";
        cin >> last_name;
        cout << "Enter Your Gender: ";
        cin >> gender;
        cout << "Enter Your Mobile Number: ";
        cin >> mobi_num;
        cout << "Enter Your Address: ";
        cin >> address;
        cout << "Enter Your Email Address: ";
        cin >> email;
    }
};

class Ticket_info {
public:
    string day;
    string train_name;
    string train_time;
    int available_seat;
    string station_from, station_to;
    int seat;
    int fare;
    void purchase_ticket() {
        cout << "Station From (Dhaka or Rajshahi): ";
        cin >> station_from;
        cout << "Station To (Dhaka or Rajshahi): ";
        cin >> station_to;
        cout << "Journey Day: ";
        cin >> day;
        read_seat:
        cout << "Number of Seats: ";
        cin >> seat;
        if (seat > 4) {
            cout << "You cannot buy more than 4 tickets at once." << endl;
            goto read_seat;
        }
    }
};


class Account : public Login_Info , public Signup, public Ticket_info {
public:
    friend int validation_check(Account ob, string user, string pass);
    friend string user_name(Account ob);
    friend string pass_word(Account ob);
    friend int username_check(Account ob, string iuser);
    void userinfo_display() {
        cout << "Username: " << username << endl;
        cout << "First Name: " << first_name << endl;
        cout << "Last Name: " << last_name << endl;
        cout << "Mobile Number: " << mobi_num << endl;
        cout << "Gender: " << gender << endl;
        cout << "Address: " << address << endl;
        cout << "Email Address: " << email << endl;
    }
    void menu_display() {
        cout << "1. Purchase Ticket" << endl;
        cout << "2. Display Ticket Booking Records" << endl;
        //cout << "3. Clear Ticket Booking Records" << endl;
        cout << "3. Display User Information" << endl;
        //cout << "5. Edit User Information" << endl;
        cout << "4. Logout" << endl;
    }
    void display_booking_records(string location_from, string location_to, string day_name, string trainname, string traintime, int seat_taken, int totalfare) {
        /* train_name = trainname;
        station_from = location_from;
        station_to = location_to;
        day = day_name;
        train_time = traintime;
        seat = seat_taken;

        cout << "Train Name: " << train_name << endl;
        cout << "Station from: " << station_from << endl;
        cout << "Station to: " << station_to << endl;
        cout << "Day of Departure: " << day << endl;
        cout << "Time of Departure: " << train_time << endl;
        cout << "Number of Seats Booked: " << seat << endl; */
        cout << "Train Name: " << trainname << endl;
        cout << "Station from: " << location_from << endl;
        cout << "Station to: " << location_to << endl;
        cout << "Day of Departure: " << day_name << endl;
        cout << "Time of Departure: " << traintime << endl;
        cout << "Number of Seats Booked: " << seat_taken << endl;
        cout << "Fare: " << totalfare << "/=" << endl << endl;
    }
};

int username_check(Account ob, string iuser) {
    if (iuser == ob.username) {
        return -1;
    }
    else {
        return 1;
    }
}

int validation_check(Account ob, string user, string pass) {

    if(ob.username == user && ob.password == pass) {
        return 1;
    }
    else {
        return -1;
    }
}
string user_name(Account ob) {
    string iusername;
    iusername = ob.username;
    return iusername;
}

string pass_word(Account ob) {
    string ipass;
    ipass = ob.password;
    return ipass;
}

int main() {
    string week_day[100];
    string name_train[100];
    string time_train[100];
    int seat_available[100];
    int total_fare[100];
    string location_from[100], location_to[100];

    Account obj[100];

    int i, j, k;
    int l, m, n;
    int x, y;
    int status, num;
    string str;

    fstream login;
    fstream add_login;
    fstream user_info;
    fstream edit_user_info;
    fstream train_info;
    fstream edit_train_info;
    fstream user_record;
    fstream edit_user_record;

    string iuser, ipass;
    i = 0;
    login.open("login.txt", ios :: in);
    while(login.good()) {
        login >> iuser >> ipass;
        obj[i].set_value(iuser, ipass);
        i++;
    }
    l = i;

    j = 0;
    train_info.open("Train_Info.txt", ios :: in);
    while(train_info.good()) {
        train_info >> location_from[j] >> location_to[j] >> week_day[j] >> name_train[j] >> time_train[j] >> seat_available[j];
        j++;
    }
    m = j;

    j = 0;
    user_info.open("user_info.txt", ios :: in);
    while(user_info.good()) {
        user_info >> iuser >> obj[j].first_name >> obj[j].last_name >> obj[j].gender >> obj[j].mobi_num >> obj[j].address >> obj[j].email;
        j++;
    }
    n = j;

    string user, pass;
    system("color 2");
    cout << "Already have an account? (yes / no)" << endl;
    cin >> str;
    if (str == "yes") {
        login_read:
        system("color 2");
        cout << "Enter Your Username: ";
        cin >> user;
        cout << "Enter Your Password: ";
        cin >> pass;

        status = 0;
        for (j = 0; j < l; j++) {
            status = validation_check(obj[j], user, pass);
            if (status == 1) {
                break;
            }
        }
        if (status == 1) {
            system("cls");
            cout << "Login succeeded" << endl;
            system("pause");
            system("cls");
            cout << "\t\t\tWELCOME TO DHAKA-RAJSHAHI RAILWAY E-TICKETING SERVICE\t\t\t\n";
            obj[j].menu_display();
            cout << "Enter Your Choice: ";
            cin >> num;
            system("cls");
            switch(num) {
            case 1:
                system("color 2");
                read_purchase_ticket:
                obj[j].purchase_ticket();
                for (k = 0; k < m; k++) {
                if (obj[j].station_from == location_from[k] && obj[j].station_to == location_to[k] && obj[j].day == week_day[k]) {
                    obj[j].train_name = name_train[k];
                    obj[j].train_time = time_train[k];
                    system("color 2");
                    if (obj[j].seat <= seat_available[k]) {
                        cout << "Name of The Train: " << obj[j].train_name << endl;
                    cout << "Time of Departure: " << obj[j].train_time << endl;
                    cout << "Number of Seats Available: " << seat_available[k] << endl;
                    cout << "Number of Booking Seats: " << obj[j].seat << endl;
                    cout << "Press 1 to Confirm: ";
                    cin >> num;
                    if (num == 1) {
                        system("color 2");
                        cout << "Number of Seats Booked: " << obj[j].seat << endl;
                        seat_available[k] -= obj[j].seat;
                        obj[j].fare = 340 * obj[j].seat;
                        cout << "Fare: " << obj[j].fare << "/=" << endl;
                        cout << "Number of Seats Available Now: " << seat_available[k] << endl;

                        edit_train_info.open("Train_Info.txt", ios :: out);
                        for (x = 0; x < m; x++) {
                            if (x == m-1) {
                                edit_train_info << location_from[x] << " " << location_to[x] << " " << week_day[x] << " " << name_train[x] << " " << time_train[x] << " " << seat_available[x];
                            }
                            else {
                                edit_train_info << location_from[x] << " " << location_to[x] << " " << week_day[x] << " " << name_train[x] << " " << time_train[x] << " " << seat_available[x] << endl;
                            }
                        }

                        edit_user_record.open("User_Record.txt", ios :: app);
                        edit_user_record << endl << user_name(obj[j]) << " " << obj[j].station_from << " " << obj[j].station_to << " " << obj[j].day << " " << obj[j].train_name << " " << obj[j].train_time << " " << obj[j].seat << " " << obj[j].fare;
                     }
                    }
                    else if (obj[j].seat > seat_available[k]) {
                         cout << "Only " << seat_available[k] << "  seats are available at that time." << endl;
                         goto read_purchase_ticket;
                    }
                    else if (seat_available[k] <= 0) {
                        cout << "Sorry No Seat is available at that time." << endl;
                    }

                  }
                }
                break;
            case 2:
                user_record.open("User_Record.txt", ios :: in);
                x = 0;
                while(user_record.good()) {
                    user_record >> iuser >> location_from[x] >> location_to[x] >> week_day[x] >> name_train[x] >> time_train[x] >> seat_available[x] >> total_fare[x];
                    if ( iuser != user_name(obj[j]) ) {
                        x++;
                        continue;
                    }
                    else {
                         obj[j].display_booking_records(location_from[x], location_to[x], week_day[x], name_train[x], time_train[x], seat_available[x], total_fare[x]);
                   }
                }
                break;
            case 3:
                system("color 2");
                cout << "User Information: " << endl;
                obj[j].userinfo_display();
            case 4:
                return 0;
            }

        }
        else {
            system("color 2");
            cout << "Login failed. Please try again." << endl;
            goto login_read;
        }
    }
    if (str == "no") {
        system("color 2");
        cout << "Want to Register? (yes / no)" << endl;
        cin >> str;
        system("cls");
        if (str == "yes") {
            signup_read:
            obj[i].login_input();
            user = user_name(obj[i]);

            status = 1;
            for (j = 0; j < l; j++) {
                status = username_check(obj[j], user);
                if (status == -1) {
                    break;
                }
            }
            if (status == -1) {
                system("cls");
                system("color 2");
                cout << "This username already exists. Please try again." << endl;
                goto signup_read;
            }

            obj[i].signup_input();

            add_login.open("login.txt", ios :: app);

            user = user_name(obj[i]);
            pass = pass_word(obj[i]);

            add_login << user << " " << pass << endl;

            edit_user_info.open("user_info.txt", ios :: app);
            edit_user_info << user << " " << obj[i].first_name << " " << obj[i].last_name << " " << obj[i].gender << " " << obj[i].mobi_num << " " << obj[i].address << " " << obj[i].email << endl;

            system("cls");
            system("color 2");
            cout << "Account has successfully created." << endl;
            system("pause");
        }
        else {
            return 0;
        }
    }

    return 0;
}

