#pragma once
#include <iostream>
#include <string>

class User {
 public:    
    User();
    User(const std::string& login, const std::string& password)
        : login_(login), password_(password){
           // std::cout << "Конструктор User" << std::endl;
    }
    
    User(const User& us) = default;
    
    const std::string& getLogin() const {return login_;}
    const std::string& getPassword() const {return password_;}
    
    void setUserPassword(const std::string& password) {password_ = password;}
    
    friend std::ostream& operator<<(std::ostream& out, const User& usr);
    
 private:
     
    std::string login_;
    std::string password_;
};


User::User(){
   // std::cout << "Конструктор по умолчанию User" << std::endl;
}


std::ostream& operator<<(std::ostream& out, const User& usr)
{
    return out << usr.login_ <<" - " << usr.password_ << std::endl;
}
