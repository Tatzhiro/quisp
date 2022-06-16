/** \file QNIC.h
 *  \authors cldurand
 *  \date 2018/06/29
 *
 *  \brief QNIC
 */
#ifndef QUISP_MODULES_QNIC_H_
#define QUISP_MODULES_QNIC_H_

#include <omnetpp.h>
#include <nlohmann/json.hpp>
using namespace omnetpp;

namespace quisp {
namespace modules {

using json = nlohmann::json;
typedef enum : int {
  QNIC_E, /**< Emitter QNIC          */
  QNIC_R, /**< Receiver QNIC         */
  QNIC_RP, /**< Passive Receiver QNIC */
  QNIC_N, /** Just to make the size of the array = the number of qnics*/
} QNIC_type;

NLOHMANN_JSON_SERIALIZE_ENUM(QNIC_type, {
                                            {QNIC_E, "QNIC_E"},
                                            {QNIC_R, "QNIC_R"},
                                            {QNIC_RP, "QNIC_RP"},
                                        })

static const char* QNIC_names[QNIC_N] = {
    "qnic",
    "qnic_r",
    "qnic_rp",
};

typedef struct {
  QNIC_type type;
  int index;
  int address;
  bool isReserved;
} QNIC_id;

typedef struct {
  QNIC_id fst;
  QNIC_id snd;
} QNIC_pair_info;

typedef struct QNIC : QNIC_id {
  cModule* pointer;  // Pointer to that particular QNIC.
  int address;
} QNIC;

// Table to check the qnic is reserved or not.
typedef std::map<int, std::map<int, bool>> QNIC_reservation_table;

}  // namespace modules
}  // namespace quisp

#endif  // QUISP_MODULES_QNIC_H_
