#ifndef MENU_OPTIONS_HPP
#define MENU_OPTIONS_HPP

#include <string>
#include <vector>
#include <memory>

class MenuOptionAbstract {
public:
    // constructor
    MenuOptionAbstract() = default;

    // // getters
    // std::string getLabel() const { return label;}
    virtual std::string getData() const { return "NA"; }
    // // methods
    // virtual void exec(std::vector<int>) {};
    
    // destructor
    virtual ~MenuOptionAbstract() = default ;
};

class TextOption : public MenuOptionAbstract {
    std::string text;
public:
    TextOption(std::string text) : MenuOptionAbstract(), text(text) {}
    std::string getData() const override {return text;}
    virtual ~TextOption() = default ;
};

#endif