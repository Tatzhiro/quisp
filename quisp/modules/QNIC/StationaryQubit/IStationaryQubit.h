#pragma once

#include <PhotonicQubit_m.h>
#include <backends/Backends.h>
#include <Eigen/Eigen>
#include <unordered_set>

namespace quisp {

namespace types {
using quisp::backends::EigenvalueResult;
using quisp::backends::MeasurementOutcome;
using quisp::backends::MeasureXResult;
using quisp::backends::MeasureYResult;
using quisp::backends::MeasureZResult;

enum class CliffordOperator : int {
  Id = 0,
  X,
  Y,
  Z,
  RX_INV,
  RX,
  Z_RX_INV,
  Z_RX,
  RY_INV,
  RY,
  H,
  Z_RY,
  S_INV,
  S,
  X_S_INV,
  X_S,
  S_INV_RX_INV,
  S_INV_RX,
  S_RX_INV,
  S_RX,
  S_INV_RY_INV,
  S_INV_RY,
  S_RY_INV,
  S_RY,
};

}  // namespace types

namespace modules {
// Matrices of single qubit errors. Used when conducting tomography.
struct single_qubit_error {
  Eigen::Matrix2cd X;  // double 2*2 matrix
  Eigen::Matrix2cd Y;  // complex double 2*2 matrix
  Eigen::Matrix2cd Z;
  Eigen::Matrix2cd I;
};

class IStationaryQubit : public omnetpp::cSimpleModule {
 public:
  IStationaryQubit(){};
  virtual ~IStationaryQubit(){};

  // RTC
  virtual void setFree(bool consumed) = 0;
  /*In use. E.g. waiting for purification result.*/
  virtual void Lock(unsigned long rs_id, int rule_id, int action_id) = 0;
  virtual void Unlock() = 0;
  virtual bool isLocked() = 0;

  /**
   * \brief Emit photon.
   * \param pulse is 1 for the beginning of the burst, 2 for the end.
   */
  virtual void emitPhoton(int pulse) = 0;
  virtual types::MeasureXResult correlationMeasureX() = 0;
  virtual types::MeasureYResult correlationMeasureY() = 0;
  virtual types::MeasureZResult correlationMeasureZ() = 0;

  virtual types::EigenvalueResult localMeasureX() = 0;
  virtual types::EigenvalueResult localMeasureY() = 0;
  virtual types::EigenvalueResult localMeasureZ() = 0;

  /**
   * Performs measurement and returns +(true) or -(false) based on the density matrix of the state. Used for tomography.
   * */
  // RandomMeasureAction
  virtual types::MeasurementOutcome measure_density_independent() = 0; /*Separate dm calculation*/

  // graph internal
  virtual void cnotGate(IStationaryQubit *control_qubit) = 0;
  virtual void hadamardGate() = 0;
  virtual void zGate() = 0;
  virtual void xGate() = 0;
  virtual void sGate() = 0;
  virtual void sdgGate() = 0;
  virtual void excite() = 0;
  virtual void relax() = 0;

  // SwappingAction, SimultaneousSwappingAction
  virtual void CNOT_gate(IStationaryQubit *control_qubit) = 0;
  // SimultaneousSwappingAction
  virtual void Hadamard_gate() = 0;
  // RTC
  virtual void Z_gate() = 0;
  virtual void X_gate() = 0;
  // Action
  virtual bool Xpurify(IStationaryQubit *resource_qubit) = 0;
  virtual bool Zpurify(IStationaryQubit *resource_qubit) = 0;

  /*GOD parameters*/
  // SwappingAction
  virtual void setEntangledPartnerInfo(IStationaryQubit *partner) = 0;
  virtual backends::IQubit *getEntangledPartner() const = 0;
  virtual backends::IQubit *getBackendQubitRef() const = 0;
  virtual int getPartnerStationaryQubitAddress() const = 0;
  virtual void assertEntangledPartnerValid() = 0;

  int qnic_address;
  int qnic_type;
  int qnic_index;
  int action_index;
};
}  // namespace modules
}  // namespace quisp
