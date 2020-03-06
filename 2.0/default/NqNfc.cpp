/*
 * Copyright (c) 2017-2019, The Linux Foundation. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer in the documentation and/or other materials provided
 *       with the distribution.
 *     * Neither the name of The Linux Foundation nor the names of its
 *       contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * Not a contribution.
 */

/*
 *  Copyright 2018-2020 NXP
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#include <hardware/hardware.h>
#include <log/log.h>
#include "NqNfc.h"
#include "eSEClientExtns.h"
#include "eSEClientIntf.h"
#include "phNxpNciHal.h"
#include "phNxpNciHal_Adaptation.h"
#include "phNxpNciHal_IoctlOperations.h"

namespace vendor {
namespace nxp {
namespace hardware {
namespace nfc {
namespace V2_0 {
namespace implementation {

// Methods from ::vendor::nxp::hardware::nfc::V1_0::INqNfc follow.
Return<void> NqNfc::ioctl(uint64_t ioctlType, const hidl_vec<uint8_t>& inputData, ioctl_cb _hidl_cb) {
    uint32_t status;
    nfc_nci_IoctlInOutData_t inpOutData;
    V1_0::NfcData  outputData;

    nfc_nci_IoctlInOutData_t *pInOutData = (nfc_nci_IoctlInOutData_t*)&inputData[0];

    /*
     * data from proxy->stub is copied to local data which can be updated by
     * underlying HAL implementation since its an inout argument
     */
    memcpy(&inpOutData, pInOutData, sizeof(nfc_nci_IoctlInOutData_t));
    if (ioctlType == (long)NfcEvent2::HAL_NFC_IOCTL_SET_TRANSIT_CONFIG) {
      /*
       * As transit configurations are appended at the end of
       * nfc_nci_IoctlInOutData_t, Assign appropriate pointer to TransitConfig
       */
      if (inpOutData.inp.data.transitConfig().len == 0) {
        inpOutData.inp.data.transitConfig().val = NULL;
      } else {
        memcpy(&(inpOutData.inp.data.transitConfig().val), (pInOutData + sizeof(nfc_nci_IoctlInOutData_t)),
               inpOutData.inp.data.transitConfig().len);
      }
    }
    status = phNxpNciHal_ioctl(ioctlType, &inpOutData);

    /*
     * copy data and additional fields indicating status of ioctl operation
     * and context of the caller. Then invoke the corresponding proxy callback
     */
    inpOutData.out.ioctlType = ioctlType;
    inpOutData.out.result = status;
    outputData.setToExternal((uint8_t*)&inpOutData.out, sizeof(nfc_nci_ExtnOutputData_t));
    _hidl_cb(outputData);
    return Void();
}

// Methods from ::vendor::nxp::hardware::nfc::V1_1::INqNfc follow.
Return<void> NqNfc::getNfcChipId(getNfcChipId_cb _hidl_cb) {
    std::string value = phNxpNciHal_getNfcChipId();
    _hidl_cb(value);
    return Void();
}

Return<void> NqNfc::getNfcFirmwareVersion(getNfcFirmwareVersion_cb _hidl_cb) {
    std::string value = phNxpNciHal_getNfcFirmwareVersion();
    _hidl_cb(value);
    return Void();
}

// Methods from ::vendor::nxp::hardware::nfc::V2_0::INqNfc follow.
Return<void> NqNfc::getSystemProperty(const ::android::hardware::hidl_string& key,
        getSystemProperty_cb _hidl_cb){
    string val = phNxpNciHal_getSystemProperty(key);
    _hidl_cb(val);
    return Void();
}

Return<bool> NqNfc::setSystemProperty(const ::android::hardware::hidl_string& key,
        const ::android::hardware::hidl_string& value){
    return phNxpNciHal_setSystemProperty(key, value);
}

Return<void> NxpNfc::getVendorParam(const ::android::hardware::hidl_string &key,
                          getVendorParam_cb _hidl_cb) {
    string val = phNxpNciHal_getSystemProperty(key);
    _hidl_cb(val);
    return Void();
}

Return<bool> NxpNfc::setVendorParam(const ::android::hardware::hidl_string &key,
                          const ::android::hardware::hidl_string &value) {
    return phNxpNciHal_setSystemProperty(key, value);
}

Return<bool> NxpNfc::resetEse(uint64_t resetType) {
    NFCSTATUS status = NFCSTATUS_FAILED;
    bool ret = false;

    ALOGD("NxpNfc::resetEse Entry");
    if((uint64_t)Constants::HAL_NFC_ESE_HARD_RESET == resetType) {
        status = phNxpNciHal_resetEse();
        if(NFCSTATUS_SUCCESS == status) {
            ret = true;
            status = NFCSTATUS_SUCCESS;
            ALOGD("HAL_NFC_ESE_HARD_RESET completed");
        } else {
            ALOGD("HAL_NFC_ESE_HARD_RESET failed");
        }
    } else {
        ALOGD("reset called with %lu type", resetType);
    }
    ALOGD("NxpNfc::resetEse Exit");
    return ret;
}

Return<bool> NxpNfc::setEseUpdateState(NxpNfcHalEseState eSEState) {
    int ret = -1;
    bool status = false;

    ALOGD("NxpNfc::setEseUpdateState Entry");
    ret = phNxpNciHal_nfcTriggerSavedCb((uint8_t)NxpNfcEvents::HAL_NFC_HCI_RESET);
    if(ret == 0) {
        status = true;
    }

    if(eSEState == NxpNfcHalEseState::HAL_NFC_ESE_JCOP_UPDATE_COMPLETED
            || eSEState == NxpNfcHalEseState::HAL_NFC_ESE_LS_UPDATE_COMPLETED) {
        ALOGD("NxpNfc::setEseUpdateState state == HAL_NFC_ESE_JCOP_UPDATE_COMPLETED");
        seteSEClientState((uint8_t)eSEState);
        eSEClientUpdate_NFC_Thread();
    }
    if (eSEState == NxpNfcHalEseState::HAL_NFC_ESE_UPDATE_COMPLETED) {
        phNxpNciHal_nfcTriggerSavedCb((uint8_t)NxpNfcEvents::HAL_NFC_RESTART);
    }
    ALOGD("NxpNfc::setEseUpdateState Exit");
    return status;
}

Return<bool> NxpNfc::setNxpTransitConfig(const ::android::hardware::hidl_string &strval) {
    bool status = true;

    ALOGD("NxpNfc::setNxpTransitConfig Entry");
    status = phNxpNciHal_setNxpTransitConfig((char *)strval.c_str());
    ALOGD("NxpNfc::setNxpTransitConfig Exit");
    return status;
}

Return<bool> NxpNfc::isJcopUpdateRequired() {
    bool status = 0;

    ALOGD("NxpNfc::isJcopUpdateRequired Entry");
    status = getJcopUpdateRequired();
    ALOGD("NxpNfc::isJcopUpdateRequired Exit");
    return status;
}

Return<bool> NxpNfc::isLsUpdateRequired() {
    bool status = 0;

    ALOGD("NxpNfc::isLsUpdateRequired Entry");
    status = getLsUpdateRequired();
    ALOGD("NxpNfc::isLsUpdateRequired Exit");
    return status;
}

}  // namespace implementation
}  // namespace V2_0
}  // namespace nfc
}  // namespace hardware
}  // namespace nxp
}  // namespace vendor
