#include "ArgParser.h"

namespace ArgumentParser {
    ArgParser::ArgParser(const std::string name)
    :   _name(name),
        _hasHelp(0),
        _isPositional(0),
        _namePositional(""),
        _showedHelp(0)
    {}
    ArgParser::~ArgParser(){}

    // Help
    ArgParser& ArgParser::AddHelp(){
        std::cerr << "No options provided for help" << std::endl;
        return *this;
    }

    ArgParser& ArgParser::AddHelp(const char shortArg, const std::string& description){
        return ArgParser::AddHelp(shortArg, " ", description);
    }

    ArgParser& ArgParser::AddHelp(const std::string& longArg, const std::string& description){
        return ArgParser::AddHelp('\0', longArg, description);
    }

    ArgParser& ArgParser::AddHelp(const char shortArg, const std::string& longArg, const std::string& description){
        Args<std::string> args(shortArg, longArg, description);
        _helpValues.push_back(args);
        _hasHelp = 1;
        return *this;
    }

    bool ArgParser::Help(){
        return _hasHelp;
    }

    std::string ArgParser::HelpDescription(){
        std::string result;
        for(auto elem: _helpValues){
            result+=
            (elem.GetShortArg()!='\0' ? "\n-" + std::string(1, elem.GetShortArg()) + " ":"\n") +
            (elem.GetLongArg()!=" " ? "--" + elem.GetLongArg() + " ": "") + 
            elem.GetDescription() + "\n";
        }
        return result;
    }

    // Flags
    Args<bool>& ArgParser::AddFlag(const char shortName, const std::string& longName){
        return ArgParser::AddFlag(shortName, longName, "");
    }

    Args<bool>& ArgParser::AddFlag(const std::string& longName){
        return ArgParser::AddFlag('\0', longName, "");
    }

    Args<bool>& ArgParser::AddFlag(const char shortName){
        return ArgParser::AddFlag(shortName, "", "");
    }

    ArgParser& ArgParser::AddFlag(){
        std::cerr << "Empty flag options";
        
        return *this;
    }

    Args<bool>& ArgParser::AddFlag(const std::string& longName, const std::string& description){
        return ArgParser::AddFlag('\0', longName, description);
    }

    Args<bool>& ArgParser::AddFlag(const char shortName, const std::string& longName, const std::string& description){
        _longArgs[longName] = new Args<bool>(shortName, longName, description);

        if(shortName!='\0'){
            _shortArgs[shortName] = _longArgs[longName];
        }
        return *dynamic_cast<Args<bool>*>(_longArgs[longName]);
    }

    bool ArgParser::GetFlag(const char shortName){
        return std::any_cast<bool>(_shortArgs[shortName]->GetValue());
    }

    bool ArgParser::GetFlag(const std::string longName){
        return std::any_cast<bool>(_longArgs[longName]->GetValue());
    }


    // Int
    Args<int>& ArgParser::AddIntArgument(const std::string& longArg, const std::string& description){
        return ArgParser::AddIntArgument('\0', longArg, description);
    }

    Args<int>& ArgParser::AddIntArgument(const char shortArg, const std::string& longArg){
        return ArgParser::AddIntArgument(shortArg, longArg, "");
    }

    Args<int>& ArgParser::AddIntArgument(const std::string& longArg){
        return ArgParser::AddIntArgument('\0', longArg, "");
    }

    Args<int>& ArgParser::AddIntArgument(const char shortArg){
        return ArgParser::AddIntArgument(shortArg, "", "");
    }

    ArgParser& ArgParser::AddIntArgument(){
        std::cerr << "No options provided for int arg" << std::endl;
        return *this;
    }

    Args<int>& ArgParser::AddIntArgument(const char shortArg, const std::string& longArg, const std::string& description){
        _longArgs[longArg] = new Args<int>(shortArg, longArg, description);

        if(shortArg!='\0'){
            _shortArgs[shortArg] = _longArgs[longArg];
        }
        return *dynamic_cast<Args<int>*>(_longArgs[longArg]);
    }

    int ArgParser::GetIntValue(const char shortArg, size_t index){
        if(_shortArgs[shortArg]->IfMulti() && index < _shortArgs[shortArg]->GetVectorSize()){
            return std::any_cast<int>(_shortArgs[shortArg]->GetValue(index));
        }
        return std::any_cast<int>(_shortArgs[shortArg]->GetValue());
    }

    int ArgParser::GetIntValue(const std::string& longArg, size_t index){
        if(_longArgs[longArg]->IfMulti() && index < _longArgs[longArg]->GetVectorSize()){
            return std::any_cast<int>(_longArgs[longArg]->GetValue(index));
        }
        return std::any_cast<int>(_longArgs[longArg]->GetValue());
    }

    // String
    Args<std::string>& ArgParser::AddStringArgument(const char shortArg, const std::string& longArg){
        return ArgParser::AddStringArgument(shortArg, longArg, "");
    }

    Args<std::string>& ArgParser::AddStringArgument(const std::string& longArg){
        return ArgParser::AddStringArgument('\0', longArg, "");
    }

    Args<std::string>& ArgParser::AddStringArgument(const char shortArg){
        return ArgParser::AddStringArgument(shortArg, "", "");
    }

    Args<std::string>& ArgParser::AddStringArgument(const std::string& longArg, const std::string& description){
        return ArgParser::AddStringArgument('\0', longArg, description);
    }

    ArgParser& ArgParser::AddStringArgument(){
        std::cerr << "No options provided for string arg" << std::endl;
        return *this;
    }

    Args<std::string>& ArgParser::AddStringArgument(const char shortArg, const std::string& longArg, const std::string& description){
        _longArgs[longArg] = new Args<std::string>(shortArg, longArg, description);

        if(shortArg!='\0'){
            _shortArgs[shortArg] = _longArgs[longArg];
        }

        return *dynamic_cast<Args<std::string>*>(_longArgs[longArg]);
    }

    std::string ArgParser::GetStringValue(const char shortArg, size_t index){
        if(_shortArgs[shortArg]->IfMulti() && index < _shortArgs[shortArg]->GetVectorSize()){
            return std::any_cast<std::string>(_shortArgs[shortArg]->GetValue(index));
        }

        return std::any_cast<std::string>(_shortArgs[shortArg]->GetValue());
    }

    std::string ArgParser::GetStringValue(const std::string& longArg, size_t index){
        if(_longArgs[longArg]->IfMulti() && index < _longArgs[longArg]->GetVectorSize()){
            return std::any_cast<std::string>(_longArgs[longArg]->GetValue(index));
        }
        
        return std::any_cast<std::string>(_longArgs[longArg]->GetValue());
    }

    // Positional
    bool ArgParser::IfPositional(){
        for (const auto& elem : _longArgs) {
            if (elem.second->IfPositional()) {
                _namePositional = elem.second->GetLongArg();
                return 1;
            }
        }
        return 0;
    }

    //Parser
    bool ArgParser::Parse(int argc, char** argv){
        std::vector<std::string> vector;

        for(int i = 0; i<argc; ++i){
            vector.push_back(argv[i]);
        }
        return Parse(vector);
    }
    
    bool ArgParser::Parse(const std::vector<std::string>& argv){
        _isPositional = IfPositional();
        for(size_t i = 1; i<argv.size(); ++i){
            std::string currarg = argv[i];
            if(std::count(currarg.begin(), currarg.end(), '-')==1 && !_isPositional){
                HandleShortValues(currarg);
                if(_showedHelp){
                    return 1;
                }
            }else if(std::count(currarg.begin(), currarg.end(), '-')==2){
                HandleLongValues(currarg);
                if(_showedHelp){
                    return 1;
                }
            }else{
                HandlePositional(currarg);
            }
        }
        return CheckIfCorrect();
    }

    void ArgParser::HandleShortValues(std::string& currarg){
        currarg.erase(0,1);
        if(currarg.contains("=")){
            HandleValueArgs(currarg, StateFalse());
        }else{
            HandleFlags(currarg, StateFalse());
        }
    }

    void ArgParser::HandleLongValues(std::string& currarg){
        currarg.erase(0,2);
        if(currarg.contains("=")){
            HandleValueArgs(currarg, StateTrue());
        }else{
            HandleFlags(currarg, StateTrue());
        }
    }

    bool ArgParser::CheckIfCorrect(){
        for(auto c:_longArgs){
            if(!c.second->IfValue()){
                return 0;
            }
            if(c.second->IfMulti() && c.second->GetMinArgsCount()!=0){
                return 0;
            }
        }
        return 1;
    }

    void ArgParser::HandleFlags(std::string& currarg, StateFalse){
        for(size_t j = 0; j<currarg.size(); ++j){
            char key = currarg[j];
            if(_shortArgs.contains(key)){
                _shortArgs[key]->SetValue(true);
            } else if(key=='h'){
                std::cout << HelpDescription();
                _showedHelp = 1;
            }
        }
    }

    void ArgParser::HandleFlags(std::string& currarg, StateTrue){
        std::string key = currarg;
        if(_longArgs.contains(key)){
            _longArgs[key]->SetValue(true);
        }else if(key == "help"){
            std::cout << HelpDescription();
            _showedHelp = 1;
        }
    }

    void ArgParser::HandleValueArgs(std::string& currarg, StateFalse){
        size_t pos = currarg.find('=');
        char key = currarg[0];
        std::string val = currarg.substr(pos + 1); 

        if(_shortArgs.contains(key) && !std::isdigit(val[0])){
            _shortArgs[key]->SetValue(val);
        }else if(std::isdigit(val[0])){
            _shortArgs[key]->SetValue(std::stoi(val));
        }
    }

    void ArgParser::HandleValueArgs(std::string& currarg, StateTrue){
        size_t pos = currarg.find('=');
        std::string key = currarg.substr(0, pos);
        std::string val = currarg.substr(pos + 1);

        if(_longArgs.contains(key) && !std::isdigit(val[0])){
            _longArgs[key]->SetValue(val);
        }else if(std::isdigit(val[0])){
            _longArgs[key]->SetValue(std::stoi(val));
        }
    }

    void ArgParser::HandlePositional(std::string& currarg){
        int key = std::stoi(currarg);

        if (Args<int>* intArg = dynamic_cast<Args<int>*>(_longArgs[_namePositional])) {
            intArg->SetValue(key);
        }else if (Args<std::string>* stringArg = dynamic_cast<Args<std::string>*>(_longArgs[_namePositional])) {
            stringArg->SetValue(currarg);
        }
    }
}
