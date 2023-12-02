#pragma once

#pragma warning( disable : 4100 ) 

#include "RE/Skyrim.h"
#include "SKSE/SKSE.h"
#include <spdlog/sinks/basic_file_sink.h>
#include <windows.h>
#include <shlobj.h>

//#define LOG(...)
#define LOG(...)    {SKSE::log::info(__VA_ARGS__);}
#define WARN(...)   {SKSE::log::warn(__VA_ARGS__);}
#define ERROR(...)  {SKSE::log::error(__VA_ARGS__);}
#define DEBUG(...)  {SKSE::log::debug(__VA_ARGS__);}

#include <FissesPlugin.h>
#include <fiss_xml.h>

using namespace std::literals;
