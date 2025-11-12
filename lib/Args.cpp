#include "Args.h"

namespace ArgumentParser {
    
    // Constructor
    BaseArgs::BaseArgs(const char shortArg, const std::string& longArg, const std::string& description)
    :
        shortArgument(shortArg),
        longArgument(longArg),
        description(description),
        isSum(0),
        isMulti(0),
        isPositional(0),
        isStore(0),
        isMultiStore(0),
        hasValue(0),
        minArgsCount(0)
    {}

    BaseArgs::BaseArgs()
    : shortArgument('\0'),
        longArgument("")
    {}

    template <typename T>
    Args<T>::Args():
        _value(T()),
        _valueVector(std::vector<T>{}),
        _storedValue(nullptr),
        _storedVectorValue(nullptr)
    {}

    template <typename T>
    Args<T>::Args(const char shortName, const std::string& longName, const std::string& description)
    :   BaseArgs(shortName, longName, description),
        _value(T()),
        _valueVector(std::vector<T>{}),
        _storedValue(nullptr),
        _storedVectorValue(nullptr)
    {}

    // Operator
    bool BaseArgs::operator==(const BaseArgs& rhs) const {
        return (BaseArgs::shortArgument == rhs.shortArgument || BaseArgs::longArgument == rhs.longArgument);
    }

    // Store
    template <typename T>
    Args<T>& Args<T>::StoreValue(T& value){
        _storedValue = &value;
        isStore = 1;
        return *this;
    }

    template <typename T>
    Args<T>& Args<T>::StoreValues(std::vector<T>& valueVector){
        _storedVectorValue = &valueVector;
        isMultiStore = 1;
        return *this;
    }

    // Mini args
    template <typename T>
    Args<T>& Args<T>::Default(const T& value){
        SetValue(value);
        return *this;
    }

    template <typename T>
    Args<T>& Args<T>::Positional(){
        isPositional = true;
        return *this;
    }

    template <typename T>
    Args<T>& Args<T>::Positional(const bool value){
        isPositional = value;
        return *this;
    }

    template <typename T>
    Args<T>& Args<T>::MultiValue(const int value){
        isMulti = true;
        minArgsCount = value;
        return *this;
    }

    template <typename T>
    Args<T>& Args<T>::MultiValue(){
        isMulti = true;
        return *this;
    }

    template <typename T>
    void Args<T>::SetValue(const std::any& val) {
        T value = std::any_cast<T>(val);
        hasValue = true;
        if(isMulti){
            if(isMultiStore){
                _storedVectorValue->push_back(value);
            }
            _valueVector.push_back(value);
            if(_valueVector.size()>=static_cast<size_t>(minArgsCount)){
                minArgsCount=0;
            }
        }

        if(isStore){
            *this->_storedValue = value;
        }
        _value = value;
    }

    // Getters
    template <typename T>
    std::any Args<T>::GetValue(){
        return this->_value;
    }

    template <typename T>
    std::any Args<T>::GetValue(const size_t index){
        return this->_valueVector[index];
    }

    template <typename T>
    size_t Args<T>::GetVectorSize(){
        return this->_valueVector.size();
    }

    bool BaseArgs::IfMulti() const{
        return this->isMulti;
    }

    char BaseArgs::GetShortArg() const{
        return this->shortArgument;
    }

    std::string BaseArgs::GetLongArg() const{
        return this->longArgument;
    }

    std::string BaseArgs::GetDescription() const{
        return this->description;
    }

    bool BaseArgs::IfPositional() const{
        return this->isPositional;
    }

    bool BaseArgs::IfValue() const{
        return this->hasValue;
    }

    int BaseArgs::GetMinArgsCount() const{
        return this->minArgsCount;
    }

    // Setter
    template <typename T>
    void Args<T>::InitValue(const std::any& value){
        this->_value=std::any_cast<T>(value);
    }

    template struct Args<int>;
    template struct Args<bool>;
    template struct Args<std::string>;
}