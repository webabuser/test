#pragma once
#include "dynamic_array.h"
#include "user.h"
#include "message.h"

class Chat {
 public:    
    Chat() = default;  
    void Start();    
      
    void ShowMenu();
  
    void Login();
    void SignUp();
    void Logout();
    User* getUserByLogin(const std::string& login);

    void ShowUserMenu();
    void ShowAllMessages();
    void ShowPersonMessages();
    void ShowAllUsers();
    
    void SendMessageToAll();
    void SendPersonalMessage();    
    
 private:
   DynamicArray<User> users_;
   DynamicArray<Message> messages_;
   User* current_user_ = nullptr;
   bool chat_work_ = true; 
};


void Chat::Start()
{
    std::cout << "Добро пожаловать в чат!" << std::endl;
    
    while (chat_work_) 
    { 
        ShowMenu();
        while(current_user_){
            ShowUserMenu(); 
        }
    }
}


User* Chat::getUserByLogin(const std::string& login)
{
    std::size_t length = users_.getLength();
    
    for(std::size_t i = 0; i < length; ++i){
        if(users_[i].getLogin() == login){
           return &users_[i];
        }
    }
    return nullptr;
}


void Chat::ShowMenu()
{
    std::cout << "Выберите опцию: Регистрация юзера (1), Вход по логину и паролю (2), Quit (0): " << std::endl;
    
    char choise;
    std::cin >> choise;
    
    switch(choise)
    {
        case '1':
            SignUp();
            break;
        case '2':
            Login();
            break;
        case '3':
            Logout();
            break;
        case '0':
            chat_work_ = false;
            break;
        default:
            std::cout << "Вы не верно выбрали опцию, попробуйте снова." << std::endl;
            break;
    }
}

void Chat::Login(){
    if(current_user_){
        std::cout << "Вы вошли как " << current_user_->getLogin() << std::endl;
        return;
    } 
    
    std::string login;
    std::string password;
    
    std::cout << "Введите ваш логин: ";
    std::cin >> login;
    std::cout << "Пароль: ";
    std::cin >> password;
    
    if((current_user_ = getUserByLogin(login)) && (current_user_->getPassword() == password)){
        std::cout << "Вы удачно авторизовались." << std::endl;
    }else{
        std::cout << "Вы не верно ввели логин или пароль. " << std::endl;
        current_user_ = nullptr;
    }
}

void Chat::SignUp()
{
    std::string login;
    std::string password;
    
    std::cout << "Введите ваш логин: ";
    std::cin >> login;
    std::cout << "Пароль: ";
    std::cin >> password;
    
    if(getUserByLogin(login)){
        std::cout << "Данный логин уже существует, выберите новый или авторизуйтесь."<< std::endl;
        return;
    };

    User newuser{login, password}; 
    User* registered_user = &users_.PushBack(newuser);

    std::cout <<"Регистрация успешна: " << *registered_user << std::endl;
}


void Chat::Logout(){
    current_user_ = nullptr;
}

void Chat::ShowUserMenu() {
    if(!current_user_){
        return;
    }
    
    std::cout << "Показать все сообщения (1), Показать личные сообщения(2), " 
                 "Послать сообщения в чат(3), Послать личное сообщение(4), Выйти(0)" << std::endl;
                 
    int choise;
    std::cin >> choise;
    
    switch(choise){
        case 1:
            ShowAllMessages();
            break;
        case 2:
            ShowPersonMessages();
            break;
        case 3:
            SendMessageToAll();
            break;
        case 4:
            SendPersonalMessage();
            break;
        case 0:
            current_user_ = nullptr;
            break;
        default:
            std::cout << "Вы не верно сделали выбор, повторите > ";
            break;
    }
                 
}

void Chat::ShowAllUsers(){
    
    for(size_t i = 0; i < users_.getLength(); ++i){
        std::cout << users_[i].getLogin() << ", ";
    }
    std::cout << std::endl;
}


void Chat::SendMessageToAll()
{
    std::string message;
    std::cin.ignore(); //Очистка буфера перед следующим вводом.
    std::getline(std::cin, message);
    
    Message messagetoall(current_user_->getLogin(), "all", message );
    messages_.PushBack(messagetoall);
}

void Chat::SendPersonalMessage()
{
    std::cout << "Выберите пользователя: ";
    ShowAllUsers();
    
    std::string login;
    std::cin >> login;
    
    std::string message;
    std::cin.ignore(); //Очистка буфера перед следующим вводом.
    std::getline(std::cin, message);
    
    Message messagetoall(current_user_->getLogin(), login, message );
    messages_.PushBack(messagetoall);
    
}

void Chat::ShowAllMessages()
{
    for(size_t i = 0; i < messages_.getLength(); ++i){
        std::cout << messages_[i].getText() << ", ";
    }
    std::cout << std::endl;
}

void Chat::ShowPersonMessages()
{
    for(size_t i = 0; i < messages_.getLength(); ++i){
        if(messages_[i].getTo() == current_user_->getLogin())
        std::cout << messages_[i].getText() << ", ";
    }
    std::cout << std::endl;
};
