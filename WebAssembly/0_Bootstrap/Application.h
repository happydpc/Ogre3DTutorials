#ifndef APPLICATION_H
#define APPLICATION_H
#undef __APPLE__ //Unfortunatly this is only required to get VSCODE intellisense to work. Apparently it automatically sets this based on the intelliSenseMode. This breaks intellisense crosscompilation.
#include <emscripten/html5.h>
#include <emscripten/bind.h>

namespace e = emscripten;

class Application {
public:
    void Initialize();
    void SayHello();
};

EMSCRIPTEN_BINDINGS(EMTest) {
  e::class_<Application>("Application")
    .constructor()
      .function("Initialize", &Application::Initialize)
      .function("SayHello", &Application::SayHello);
}

#endif
