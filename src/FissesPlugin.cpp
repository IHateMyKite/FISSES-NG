static CFISS* CFissObjectUnpack(const char* objstr)
{
    static CFISS* ret = NULL;
    sscanf_s(objstr, "%p", &ret);
    return ret;
}
static RE::BSFixedString CFissObjectPack(const void* obj)
{
    char buf[64];
    snprintf(buf, sizeof(buf), "%p", obj);
    return RE::BSFixedString(buf);
}

////////////////////////////////////////////////////////////////////////////////////////////

namespace FissesPlugin 
{
    using RE::BSFixedString;
    using RE::StaticFunctionTag;
    BSFixedString CFissBeginLoad(StaticFunctionTag *base, std::string filename)
    {
        LOG("CFissBeginLoad({})", filename)
        CFISS* obj = (CFISS*)calloc(1, sizeof(CFISS));
        unsigned int enc_name_size = cfiss_filename_encode(filename.c_str(), NULL, 0) + 8;
        char* enc_name = (char*)malloc(enc_name_size);
        if (enc_name!=NULL) cfiss_filename_encode(filename.c_str(), enc_name, enc_name_size);

        cfiss_beginLoad(obj, (enc_name==NULL)?filename.c_str():enc_name);
        LOG("cfiss_beginLoad({}) return {:016X}", (enc_name==NULL)?filename.c_str():enc_name, (uintptr_t)obj);
        if (enc_name!=NULL) free(enc_name);

        return CFissObjectPack(obj);
    }
    BSFixedString CFissLoadString(StaticFunctionTag *base, std::string obj, std::string name)
    {
        LOG("CFissLoadString({},{})", obj, name)
        CFISS* cobj = CFissObjectUnpack(obj.c_str());
        const char *result = cfiss_loadString(cobj, name.c_str());
        BSFixedString ret = BSFixedString(result);
        cfiss_xml_decoder((char*)ret.c_str());

        LOG("({:016X})->cfiss_loadString({}) return >>>>>>>>>>\n{}", (uintptr_t)cobj, name.c_str(), ret.c_str());
        return ret;
    }
    bool CFissLoadBool(StaticFunctionTag *base, std::string obj, std::string name)
    {
        LOG("CFissLoadBool({},{})", obj, name)
        CFISS* cobj = CFissObjectUnpack(obj.c_str());
        bool result = cfiss_loadBool(cobj, name.c_str());
        
        LOG("({:016X})->cfiss_loadBool({}) return {}", (uintptr_t)cobj, name.c_str(), (result)?"true":"false");
        return result;
    }
    float CFissLoadFloat(StaticFunctionTag *base, std::string obj, std::string name)
    {
        LOG("CFissLoadFloat({},{})", obj, name)
        CFISS* cobj = CFissObjectUnpack(obj.c_str());
        float result = cfiss_loadFloat(cobj, name.c_str());

        LOG("({:016X})->cfiss_loadFloat({}) return {}", (uintptr_t)cobj, name.c_str(), result);
        return result;
    }
    int32_t CFissLoadInt(StaticFunctionTag *base, std::string obj, std::string name)
    {
        LOG("CFissLoadInt({},{})", obj, name)
        CFISS* cobj = CFissObjectUnpack(obj.c_str());
        int result = cfiss_loadInt(cobj, name.c_str());

        LOG("({:016X})->cfiss_loadInt({}) return {}", (uintptr_t)cobj, name.c_str(), result);
        return result;
    }
    BSFixedString CFissEndLoad(StaticFunctionTag *base, std::string obj)
    {
        LOG("CFissEndLoad({})", obj)
        CFISS* cobj = CFissObjectUnpack(obj.c_str());
        const char *result = cfiss_endLoad(cobj);
        if (cobj!=NULL) free(cobj);

        LOG("({:016X})->cfiss_endLoad() return {}", (uintptr_t)cobj, result);
        return BSFixedString(result);
    }
    
    // ===================================================================================================================================================
    BSFixedString CFissBeginSave(StaticFunctionTag *base, std::string filename, std::string modname)
    {
        LOG("CFissBeginSave({},{})", filename, modname)
        CFISS* obj = (CFISS*)calloc(1, sizeof(CFISS));
        unsigned int enc_name_size = cfiss_filename_encode(filename.c_str(), NULL, 0) + 8;
        char* enc_name = (char*)malloc(enc_name_size);
        if (enc_name!=NULL) cfiss_filename_encode(filename.c_str(), enc_name, enc_name_size);

        cfiss_beginSave(obj, (enc_name==NULL)?filename.c_str():enc_name, modname.c_str());
        LOG("cfiss_beginSave({}, {}) return {:016X}", (enc_name==NULL)?filename.c_str():enc_name, modname.c_str(), (uintptr_t)obj);
        if (enc_name!=NULL) free(enc_name);

        return CFissObjectPack(obj);
    }
    void CFissSaveBool(StaticFunctionTag *base, std::string obj, std::string name, bool value)
    {
        LOG("CFissSaveBool({},{},{})", obj, name, value)
        CFISS* cobj = CFissObjectUnpack(obj.c_str());
        cfiss_saveBool(cobj, name.c_str(), value);

        LOG("({:016X})->cfiss_saveBool({}, {})", (uintptr_t)cobj, name.c_str(), (value)?"true":"false");
    }
    void CFissSaveString(StaticFunctionTag *base, std::string obj, std::string name, std::string value)
    {
        LOG("CFissSaveString({},{},{})", obj, name, value)
        CFISS* cobj = CFissObjectUnpack(obj.c_str());
        char* data = cfiss_xml_encoder(value.c_str());
        cfiss_saveString(cobj, name.c_str(), data);

        LOG("({:016X})->cfiss_saveString({}, {})", (uintptr_t)cobj, name.c_str(), data); 
        if (data!=value.c_str()) free(data);
    }
    void CFissSaveFloat(StaticFunctionTag *base, std::string obj, std::string name, float value)
    {
        LOG("CFissSaveFloat({},{},{})", obj, name, value)
        CFISS* cobj = CFissObjectUnpack(obj.c_str());
        cfiss_saveFloat(cobj, name.c_str(), value);

        LOG("({:016X})->cfiss_saveFloat({}, {})", (uintptr_t)cobj, name.c_str(), value);
    }
    void CFissSaveInt(StaticFunctionTag *base, std::string obj, std::string name, int32_t value)
    {
        LOG("CFissSaveInt({},{},{})", obj, name, value)
        CFISS* cobj = CFissObjectUnpack(obj.c_str());
        cfiss_saveInt(cobj, name.c_str(), value);

        LOG("({:016X})->cfiss_saveInt({}, {})", (uintptr_t)cobj, name.c_str(), value);
    }
    BSFixedString CFissEndSave(StaticFunctionTag *base, std::string obj)
    {
        LOG("CFissEndSave({})", obj)
        CFISS* cobj = CFissObjectUnpack(obj.c_str());
        const char *result = cfiss_endSave(cobj);
        if (cobj!=NULL) free(cobj);

        LOG("({:016X})->cfiss_endSave() return {}", (uintptr_t)cobj, result);
        return BSFixedString(result);
    }
    BSFixedString CFissSaveTextToTxtFile(StaticFunctionTag *base, std::string filename, std::string text)
    {
        LOG("CFissSaveTextToTxtFile({},{})", filename, text)
        const char *result = cfiss_saveTextToTxtFile(filename.c_str(), text.c_str()); 
        return BSFixedString(result);
    }
    
    // ===================================================================================================================================================
    bool RegisterFuncs(RE::BSScript::IVirtualMachine *vm) 
    {
        #define REGISTERPAPYRUSFUNC(name) {vm->RegisterFunction(#name, "FISSScript", FissesPlugin::name,true);}
        REGISTERPAPYRUSFUNC(CFissBeginLoad) // Function beginLoad(string filename)
        REGISTERPAPYRUSFUNC(CFissEndLoad)   // string Function endLoad()
        REGISTERPAPYRUSFUNC(CFissLoadBool)  // bool Function loadBool(string name)
        REGISTERPAPYRUSFUNC(CFissLoadString)// string Function loadString(string name)
        REGISTERPAPYRUSFUNC(CFissLoadFloat) // float Function loadFloat(string name)
        REGISTERPAPYRUSFUNC(CFissLoadInt)   // int Function loadInt(string name)
        REGISTERPAPYRUSFUNC(CFissBeginSave) // Function beginSave(string filename, string modname)
        REGISTERPAPYRUSFUNC(CFissEndSave)   // string Function endSave()
        REGISTERPAPYRUSFUNC(CFissSaveBool)  // Function saveBool(string name, bool value)
        REGISTERPAPYRUSFUNC(CFissSaveString)// Function saveString(string name, string value)
        REGISTERPAPYRUSFUNC(CFissSaveFloat) // Function saveFloat(string name, float value)
        REGISTERPAPYRUSFUNC(CFissSaveInt)   // Function saveInt(string name, int value)
        REGISTERPAPYRUSFUNC(CFissSaveTextToTxtFile)  // string Function saveTextToTxtFile(string filename, string text)

        #undef REGISTERPAPYRUSFUNC

        LOG("Papyrus funtions registered")
        return true;
    }
} 