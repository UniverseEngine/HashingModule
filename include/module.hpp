#pragma once

#include <ModuleAPI/ModuleAPI.hpp>

#include <SDK/ScriptAPI.hpp>

#include <memory>

#pragma once

#ifdef _WIN32
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT __attribute__((visibility("default")))
#endif

using namespace Universe::ModuleAPI;

namespace HashingModule
{
    class ModuleHandler : public IModuleHandler {
    public:
        void OnModuleLoad(ModuleDetails& details, IModuleInterface* moduleInterface) override;
        void OnModuleTick() override {}
    };
    static std::unique_ptr<ModuleHandler> m_moduleHandler = std::make_unique<ModuleHandler>();

} // namespace HashingModule

void RegisterFunctions(Universe::Scripting::API::IVM* vm);
