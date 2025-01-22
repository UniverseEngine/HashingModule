#pragma once

#include <ModuleAPI/ModuleAPI.hpp>

#include <SDK/ScriptAPI.hpp>

#include <memory>

#pragma once

using namespace Universe::ModuleAPI;

namespace HashingModule
{
    class ModuleHandler : public IModuleHandler {
    public:
        void OnModuleLoad(ModuleDetails&, IModuleInterface&) override;
        void OnModuleTick() override {};
    };
    static std::unique_ptr<ModuleHandler> m_moduleHandler = std::make_unique<ModuleHandler>();

} // namespace HashingModule
