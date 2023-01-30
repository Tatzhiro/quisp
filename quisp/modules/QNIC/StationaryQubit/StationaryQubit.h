/** \file StationaryQubit.h
 *  \authors cldurand,takaakimatsuo
 *  \date 2018/03/14
 *
 *  \brief StationaryQubit
 */
#pragma once

#include <PhotonicQubit_m.h>
#include <backends/Backends.h>
#include <modules/common_types.h>
#include <utils/ComponentProvider.h>
#include <string>
#include "IStationaryQubit.h"
#include "QubitId.h"
#include "backends/interfaces/IQuantumBackend.h"

namespace quisp::modules {

#define STATIONARYQUBIT_PULSE_BEGIN 0x01
#define STATIONARYQUBIT_PULSE_END 0x02
#define STATIONARYQUBIT_PULSE_BOUND (STATIONARYQUBIT_PULSE_BEGIN | STATIONARYQUBIT_PULSE_END)

/** \class StationaryQubit StationaryQubit.h
 *
 *  \brief StationaryQubit.
 *  \ref https://arxiv.org/abs/1908.10758
 */

using quisp::modules::common::IBackendQubit;
using quisp::modules::common::IConfiguration;
using quisp::modules::common::IQuantumBackend;

class StationaryQubit : public IStationaryQubit {
 protected:
  IBackendQubit *qubit_ref;

 public:
  StationaryQubit();
  void setFree(bool consumed) override;
  /*In use. E.g. waiting for purification result.*/
  void Lock(unsigned long rs_id, int rule_id, int action_id) override;
  void Unlock() override;
  bool isLocked() override;

  /**
   * \brief Emit photon.
   * \param pulse is 1 for the beginning of the burst, 2 for the end.
   */
  void emitPhoton(int pulse) override;

  virtual types::EigenvalueResult measureX() override;
  virtual types::EigenvalueResult measureY() override;
  virtual types::EigenvalueResult measureZ() override;
  virtual types::MeasurementOutcome measureRandomPauliBasis() override;

  /**
   * \brief Two qubit CNOT gate.
   * \param Need to specify the control qubit as an argument.
   */
  void gateCNOT(IStationaryQubit *control_qubit) override;

  /**
   * \brief Single qubit Hadamard gate
   * \param X error transforms to Z, and vise-versa.
   */
  void gateHadamard() override;
  void gateZ() override;
  void gateX() override;

  /*GOD parameters*/
  void setEntangledPartnerInfo(IStationaryQubit *partner) override;
  void setCompletelyMixedDensityMatrix();
  void setRelaxedDensityMatrix();
  void setExcitedDensityMatrix();
  void addXerror();
  void addZerror();
  backends::IQubit *getEntangledPartner() const override;
  backends::IQubit *getBackendQubitRef() const override;
  int getPartnerStationaryQubitAddress() const override;

  // for debugging
  void assertEntangledPartnerValid() override;

  double emission_success_probability;

  bool locked;
  unsigned long locked_ruleset_id;
  unsigned long locked_rule_id;

 protected:
  void initialize() override;
  void finish() override;
  void handleMessage(omnetpp::cMessage *msg) override;
  messages::PhotonicQubit *generateEntangledPhoton();
  void setBusy();
  Eigen::Matrix2cd getErrorMatrix(StationaryQubit *qubit);

  /**
   * get the default backend configuration from the Bcakend module.
   * if overwrite arg is true, collect StationaryQubit's backend qubit config
   * and overwrite the default configuration with it.
   * if you want to use different qubit configuration, it's useful.
   */
  std::unique_ptr<IConfiguration> prepareBackendQubitConfiguration(bool overwrite);

  // this is for debugging. class internal use only.
  // and it's different from QubitRecord's one.
  bool is_busy;
  // photon emitted at
  omnetpp::simtime_t emitted_time = -1;
  // Standard deviation
  double emission_jittering_standard_deviation;
  int stationary_qubit_address;
  int node_address;

  utils::ComponentProvider provider;
  IQuantumBackend *backend;
};

}  // namespace quisp::modules
