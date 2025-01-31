#include "module.hpp"

#include <cryptopp/cryptlib.h>
#include <cryptopp/sha.h>
#include <cryptopp/base64.h>
#include <cryptopp/whrlpool.h>
#include <cryptopp/hex.h>

using namespace Universe;

// Module API
static IServerModuleInterface* gModuleInterface;

// Module details
const static std::string NAME    = "Hashing Module";
const static std::string DESC    = "Provides hashing functionality";
const static std::string VERSION = "1.0.0-rc.1";
const static std::string AUTHOR  = "lucx, perikiyoxd";

void HashingModule::ModuleHandler::OnModuleLoad(ServerModuleDetails& details, IServerModuleInterface* moduleInterface)
{
    details.moduleName        = NAME;
    details.moduleDescription = DESC;
    details.moduleAuthor      = VERSION;
    details.moduleVersion     = AUTHOR;

    gModuleInterface = moduleInterface;
}

// Module API entry point
extern "C" DLLEXPORT void RegisterFunctions(Scripting::API::IVM* vm)
{
    auto& globalCtx = vm->Global();

    vm->RegisterGlobalFunction("sha256", [](Scripting::API::ICallbackInfo& info) {
        CryptoPP::SHA256 hash;

        std::string input { info[0].ToString() };
        std::string digest;
        std::string output;

        CryptoPP::StringSource ss1(input, true, new CryptoPP::HashFilter(hash, new CryptoPP::StringSink(digest)));
        CryptoPP::StringSource ss2(digest, true, new CryptoPP::HexEncoder(new CryptoPP::StringSink(output)));

        info.GetReturnValue().Set(output);
    });

    vm->RegisterGlobalFunction("sha512", [](Scripting::API::ICallbackInfo& info) {
        CryptoPP::SHA512 hash;

        std::string input { info[0].ToString() };
        std::string digest;
        std::string output;

        CryptoPP::StringSource ss1(input, true, new CryptoPP::HashFilter(hash, new CryptoPP::StringSink(digest)));
        CryptoPP::StringSource ss2(digest, true, new CryptoPP::HexEncoder(new CryptoPP::StringSink(output)));

        info.GetReturnValue().Set(output);
    });

    vm->RegisterGlobalFunction("whirlpool", [](Scripting::API::ICallbackInfo& info) {
        CryptoPP::Whirlpool hash;

        std::string input { info[0].ToString() };
        std::string digest;
        std::string output;

        CryptoPP::StringSource ss1(input, true, new CryptoPP::HashFilter(hash, new CryptoPP::StringSink(digest)));
        CryptoPP::StringSource ss2(digest, true, new CryptoPP::HexEncoder(new CryptoPP::StringSink(output)));

        info.GetReturnValue().Set(output);
    });

    vm->RegisterGlobalFunction("base64_encode", [](Scripting::API::ICallbackInfo& info) {
        std::string input { info[0].ToString() };
        std::string output;

        CryptoPP::Base64Encoder encoder(new CryptoPP::StringSink(output), false);
        CryptoPP::StringSource  pip(input, true, new CryptoPP::Redirector(encoder));

        info.GetReturnValue().Set(output);
    });

    vm->RegisterGlobalFunction("base64_decode", [](Scripting::API::ICallbackInfo& info) {
        std::string input { info[0].ToString() };
        std::string output;

        CryptoPP::Base64Decoder decoder(new CryptoPP::StringSink(output));
        CryptoPP::StringSource  pip(input, true, new CryptoPP::Redirector(decoder));

        info.GetReturnValue().Set(output);
    });
}
