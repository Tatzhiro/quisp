#pragma once
#include <modules/common_types.h>
#include <omnetpp.h>
#include <pybind11/embed.h>
#include <memory>
#include "RNG.h"

namespace quisp::modules::backend {
using quisp::modules::common::ErrorTrackingBackend;
using quisp::modules::common::IQuantumBackend;
using rng::RNG;

class BackendContainer : public omnetpp::cSimpleModule {
 public:
  BackendContainer();
  ~BackendContainer();

  void initialize() override {
    auto backend_type = std::string(par("backendType").stringValue());
    if (backend_type == "ErrorTrackingBackend") {
      backend = std::make_unique<ErrorTrackingBackend>(std::make_unique<RNG>(this));
    } else {
      throw omnetpp::cRuntimeError("Unknown backend type: %s", backend_type.c_str());
    }
  }

  void finish() override {}

  IQuantumBackend* getQuantumBackend() {
    if (backend == nullptr) {
      throw omnetpp::cRuntimeError("Backend is not initialized");
    }
    return backend.get();
  }

 protected:
  void configureErrorTrackingBackend();
  std::unique_ptr<IQuantumBackend> backend = nullptr;
  pybind11::scoped_interpreter interpreter;
};

Define_Module(BackendContainer);
}  // namespace quisp::modules::backend
