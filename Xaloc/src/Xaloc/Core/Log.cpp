#include "xapch.h"
#include "Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"
#include "Xaloc/ImGui/Modules/ImGuiConsoleSink.h"

namespace Xaloc {

	Ref<spdlog::logger> Log::s_CoreLogger;
	Ref<spdlog::logger> Log::s_ClientLogger;

	void Log::Init()
	{
		// create the sinks
		std::vector<spdlog::sink_ptr> sinks;
		sinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>()); // VS debug console
		sinks.emplace_back(std::make_shared<ImGuiConsoleSink_mt>(true)); // ImGuiConsole

		// create the loggers
		s_CoreLogger = CreateRef<spdlog::logger>("XALOC", begin(sinks), end(sinks));
		spdlog::register_logger(s_CoreLogger);
		s_ClientLogger = CreateRef<spdlog::logger>("APP  ", begin(sinks), end(sinks));
		spdlog::register_logger(s_ClientLogger);

		// configure the loggers
		spdlog::set_pattern("%^[%T] %n: %v%$");
		s_CoreLogger->set_level(spdlog::level::trace);
		s_ClientLogger->set_level(spdlog::level::trace);
	}
}