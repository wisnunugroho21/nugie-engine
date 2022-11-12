#include "app.hpp"

namespace nugiEngine {
    void EngineApp::run() {
        while (!this->window.shouldClose()) {
            this->window.pollEvents();
        }
    }
}