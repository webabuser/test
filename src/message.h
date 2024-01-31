#pragma once

#include <iostream>
#include <string>

class Message {
 public:
    Message() = default;
    ~Message() = default;
 
    Message(const std::string& from, const std::string& to, const std::string& text) 
        :from_(from), to_(to), text_(text){
    }
    Message(const Message& mess);
    Message& operator=(const Message& mess);
  
    const std::string& getFrom() const;
    const std::string& getTo() const;
    const std::string& getText() const;
    
    void setFrom(const std::string& from);
    void setTo(const std::string& to);
    void setText(const std::string& text);
    
 private:
    std::string from_;
    std::string to_;
    std::string text_;
};

Message::Message(const Message& mess){
    //if(this == &mess) return;
    
    from_ = mess.from_;
    to_   = mess.to_;
    text_ = mess.text_;
}

Message& Message::operator=(const Message& mess){
     if(this == &mess) return *this;
     
    from_ = mess.from_;
    to_   = mess.to_;
    text_ = mess.text_;
    
    return *this;
}

const std::string& Message::getFrom() const {return from_; }
const std::string& Message::getTo() const {return to_; }
const std::string& Message::getText() const {return text_; }

void Message::setFrom(const std::string& from) { from_ = from; }
void Message::setTo(const std::string& to) { to_ = to; };
void Message::setText(const std::string& text) { text_ = text; }
