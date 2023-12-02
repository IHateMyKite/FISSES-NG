#pragma once

namespace FissesPlugin
{
    using RE::BSFixedString;
    using RE::StaticFunctionTag;
    BSFixedString    CFissBeginLoad(StaticFunctionTag *base, std::string filename);
    BSFixedString    CFissLoadString(StaticFunctionTag *base, std::string obj, std::string name);
    bool             CFissLoadBool(StaticFunctionTag *base, std::string obj, std::string name);
    float            CFissLoadFloat(StaticFunctionTag *base, std::string obj, std::string name);
    int32_t          CFissLoadInt(StaticFunctionTag *base, std::string obj, std::string name);
    BSFixedString    CFissEndLoad(StaticFunctionTag *base, std::string obj);

    BSFixedString    CFissBeginSave(StaticFunctionTag *base, std::string filename, std::string modname);
    void             CFissSaveBool(StaticFunctionTag *base, std::string obj, std::string name, bool value);
    void             CFissSaveString(StaticFunctionTag *base, std::string obj, std::string name, std::string value);
    void             CFissSaveFloat(StaticFunctionTag *base, std::string obj, std::string name, float value);
    void             CFissSaveInt(StaticFunctionTag *base, std::string obj, std::string name, int32_t value);
    BSFixedString    CFissEndSave(StaticFunctionTag *base, std::string obj);
    BSFixedString    CFissSaveTextToTxtFile(StaticFunctionTag *base, std::string filename, std::string text);

    
    bool RegisterFuncs(RE::BSScript::IVirtualMachine *registry);
}