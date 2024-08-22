#include "module.hpp"

#include <cryptopp/cryptlib.h>
#include <cryptopp/sha.h>
#include <cryptopp/base64.h>
#include <cryptopp/whrlpool.h>
#include <cryptopp/hex.h>

namespace module
{
    DLLEXPORT void OnLoad(String* name, String* description, String* author, ModuleAPI::IModuleAPI* api)
    {
        *name        = "Hashing Module";
        *description = "";
        *author      = "lucx";

        m_api = api;
    }

    DLLEXPORT void RegisterFunctions(Scripting::API::IVM* vm)
    {
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

    DLLEXPORT void OnPulse()
    {
    }
} // namespace module
