#pragma once

#include <cstddef>
#include <cstdint>
#include <any>
#include <string>
#include <vector>

namespace ArgumentParser {
    class BaseArgs{
        protected:
        char shortArgument;
        std::string longArgument;
        std::string description;
        
        bool isSum;
        bool isMulti;
        bool isPositional;
        bool isStore;
        bool isMultiStore;
        bool hasValue;
        int minArgsCount;
        
        BaseArgs();
        BaseArgs(const char shortArg, const std::string& longArg, const std::string& description);
        virtual ~BaseArgs() = default;

        bool operator==(const BaseArgs& rhs) const;

        public:
        virtual std::any GetValue() = 0;
        virtual std::any GetValue(const size_t index) = 0;
        virtual size_t GetVectorSize() = 0;
        virtual void InitValue(const std::any& value) = 0;
        virtual void SetValue(const std::any& val) = 0;
        bool IfValue() const;
        bool IfMulti() const;
        bool IfPositional() const;
        char GetShortArg() const;
        std::string GetLongArg() const;
        std::string GetDescription() const;
        int GetMinArgsCount() const;
    };

    template <typename T>
    class Args: public BaseArgs{
        public:
        Args();
        Args(const char shortName, const std::string& longName, const std::string& description);
        ~Args() = default;

        Args<T>& StoreValue(T& value);
        Args<T>& StoreValues(std::vector<T>& valueVector);
        Args<T>& MultiValue(const int value);
        Args<T>& MultiValue();
        Args<T>& Positional();
        Args<T>& Positional(const bool value);
        Args<T>& Default(const T& value);

        void SetValue(const std::any& val) override;
        void InitValue(const std::any& value) override;
        std::any GetValue() override;
        std::any GetValue(const size_t index) override;
        size_t GetVectorSize() override;

        private:
        T _value;
        std::vector<T> _valueVector;
        T* _storedValue;
        std::vector<T>* _storedVectorValue;
    };
}