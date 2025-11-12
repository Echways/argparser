#pragma once
#include <string>
#include <unordered_map>
#include <map>
#include <asm-generic/errno.h>
#include <cctype>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>
#include <algorithm>
#include "Args.h"

namespace ArgumentParser {
    class ArgParser{
        public:
        ArgParser(const std::string name);
        ~ArgParser();

        ArgParser& AddHelp(const char shortArg, const std::string& longArg, const std::string& description);
        ArgParser& AddHelp(const std::string& longArg, const std::string& description);
        ArgParser& AddHelp(const char shortArg, const std::string& description);
        ArgParser& AddHelp();
        bool Help();
        std::string HelpDescription();
        
        Args<bool>& AddFlag(const char shortName, const std::string& longName, const std::string& description);
        Args<bool>& AddFlag(const char shortName, const std::string& longName);
        Args<bool>& AddFlag(const std::string& longName, const std::string& description);
        Args<bool>& AddFlag(const std::string& longName);
        Args<bool>& AddFlag(const char shortName);
        ArgParser& AddFlag();
        bool GetFlag(const char shortName);
        bool GetFlag(const std::string longName);

        Args<int>& AddIntArgument(const char shortArg, const std::string& longArg, const std::string& description);
        Args<int>& AddIntArgument(const char shortArg, const std::string& longArg);
        Args<int>& AddIntArgument(const std::string& longArg, const std::string& description);
        Args<int>& AddIntArgument(const std::string& longArg);
        Args<int>& AddIntArgument(const char shortArg);
        ArgParser& AddIntArgument();
        int GetIntValue(const char shortArg, size_t index = 0);
        int GetIntValue(const std::string& longArg, size_t index = 0);

        Args<std::string>& AddStringArgument(const char shortArg, const std::string& longArg, const std::string& description);
        Args<std::string>& AddStringArgument(const char shortArg, const std::string& longArg);
        Args<std::string>& AddStringArgument(const std::string& longArg, const std::string& description);
        Args<std::string>& AddStringArgument(const std::string& longArg);
        Args<std::string>& AddStringArgument(const char shortArg);
        ArgParser& AddStringArgument();
        std::string GetStringValue(const char shortArg, size_t index = 0);
        std::string GetStringValue(const std::string& longArg, size_t index = 0);

        bool Parse(int argc, char** argv);
        bool Parse(const std::vector<std::string>& argv);
        bool IfPositional();

        struct StateTrue{};
        struct StateFalse{};

        private:
        std::string _name;
        bool _hasHelp;
        bool _isPositional;
        std::string _namePositional;
        bool _showedHelp;

        void HandleFlags(std::string& currarg, StateFalse);
        void HandleFlags(std::string& currarg, StateTrue);
        void HandleValueArgs(std::string& currarg, StateFalse);
        void HandleValueArgs(std::string& currarg, StateTrue);
        void HandlePositional(std::string& currarg);
        void HandleShortValues(std::string& currarg);
        void HandleLongValues(std::string& currarg);
        bool CheckIfCorrect();

        std::unordered_map<std::string, BaseArgs*> _longArgs;
        std::unordered_map<char, BaseArgs*> _shortArgs;
        std::vector<Args<std::string>> _helpValues;
    };
}
