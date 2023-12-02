#include <FissesPlugin.h>

void SetupLog() {
    auto logsFolder = SKSE::log::log_directory();
    if (!logsFolder) SKSE::stl::report_and_fail("SKSE log_directory not provided, logs disabled.");
    auto pluginName = SKSE::PluginDeclaration::GetSingleton()->GetName();
    auto logFilePath = *logsFolder / std::format("{}.log", pluginName);
    auto fileLoggerPtr = std::make_shared<spdlog::sinks::basic_file_sink_mt>(logFilePath.string(), true);
    auto loggerPtr = std::make_shared<spdlog::logger>("log", std::move(fileLoggerPtr));
    spdlog::set_default_logger(std::move(loggerPtr));
    spdlog::set_level(spdlog::level::trace);
    spdlog::flush_on(spdlog::level::trace);
}

SKSEPluginLoad(const SKSE::LoadInterface *skse) {
    SKSE::Init(skse);

	wchar_t szBuff[256];
	LPCTSTR lpFileName = L"Data\\SKSE\\Plugins\\fiss.ini";
	DWORD nLen = GetPrivateProfileString(L"FISS", L"DebugMsg", L"0", szBuff, sizeof(szBuff), lpFileName);
	int RecordDebug = std::stoi(szBuff);

    SetupLog();

	LOG("FISS Plugin load");

	if (RecordDebug) {
		LOG("FISS Plugin debug messages on");
	}
	else {
		LOG("FISS Plugin debug messages off");
	}

    SKSE::GetPapyrusInterface()->Register(FissesPlugin::RegisterFuncs);

    return true;
}