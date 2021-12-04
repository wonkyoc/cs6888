#ifndef DB_HPP
#define DB_HPP

#include <iostream>

using namespace std;

class DataBaseConnect {
public:
    virtual bool aeroSpike(string username, string password) { return true; }
    virtual bool mysql(string username, string password) { return true; }
    virtual bool redis(string username) { return true; }
    virtual int fetchRecord() { return -1; }

};

class MyDatabase {
    DataBaseConnect & dbConnect;
public:
    MyDatabase(DataBaseConnect & _dbC) : dbConnect(_dbC) {    }
//    int Init(string uname, string passwd) {
//        int randno = rand() % 2;
//        if (randno == 0) {
//            cout << "Even random number called..." << endl;
//            return dbConnect.login2(uname, passwd) == true;
//        }
//        else {
//            cout << "Odd random number called..." << endl;
//            if (dbConnect.login(uname, passwd) != true) {
//                cout << "Failure 2nd time... returning..." << endl;
//                return -1;
//            }
//            else {
//                cout << "Success!" << endl;
//                return 1;
//            }
//        }
//
//    }


    bool loginWrapper(){
        if(dbConnect.redis("x")){
            //case 1
            return true;
        }
        else if(dbConnect.aeroSpike("x","y")){
            //case 2
            return false;
        }
        else{
            if(dbConnect.mysql("x","y")){
                //case 3
                return true;
            }
            else{
                //case 4
                return false;
            }
        }
    }
};

#endif
