/******************************************************************************
 *
 *  Copyright 2018 NXP
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
 *
 ******************************************************************************/
/*
 * Copyright (c) 2018, The Linux Foundation. All rights reserved.
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

#define LOG_TAG "android.hardware.nfc@1.1-impl"

#include <log/log.h>
#include "Nfc.h"
extern "C" {
#include "phNxpNciHal_Adaptation.h"
}

#define UNUSED(x) (void)(x)
#define HALSTATUS_SUCCESS (0x0000)
#define HALSTATUS_FAILED  (0x00FF)

typedef uint32_t HALSTATUS;

namespace android {
namespace hardware {
namespace nfc {
namespace V1_1 {
namespace implementation {

sp<INfcClientCallback> Nfc::mCallback = nullptr;

Return<V1_0::NfcStatus> Nfc::open_1_1(const sp<V1_1::INfcClientCallback>& clientCallback) {
    if (clientCallback == nullptr) {
        return V1_0::NfcStatus::FAILED;
    }
    return open(clientCallback);
}

// Methods from ::android::hardware::nfc::V1_0::INfc follow.
Return<V1_0::NfcStatus> Nfc::open(const sp<INfcClientCallback>& clientCallback) {
    ALOGD("Nfc::open Enter");
    HALSTATUS status = HALSTATUS_FAILED;
    if (clientCallback == nullptr) {
        return V1_0::NfcStatus::FAILED;
    } else {
        mCallback = clientCallback;
        mCallback->linkToDeath(this, 0 /*cookie*/);
    }

    status = phNxpNciHal_open(eventCallback, dataCallback);
    ALOGD("Nfc::open Exit");
    if(status != HALSTATUS_SUCCESS) {
        return V1_0::NfcStatus::FAILED;
    } else {
        return V1_0::NfcStatus::OK;
    }
}

Return<uint32_t> Nfc::write(const hidl_vec<uint8_t>& data) {
    hidl_vec<uint8_t> copy = data;
    return phNxpNciHal_write(copy.size(), &copy[0]);
}

Return<V1_0::NfcStatus> Nfc::coreInitialized(const hidl_vec<uint8_t>& data) {
    HALSTATUS status = HALSTATUS_FAILED;
    hidl_vec<uint8_t> copy = data;
    status = phNxpNciHal_core_initialized(&copy[0]);
    if(status != HALSTATUS_SUCCESS) {
        return V1_0::NfcStatus::FAILED;
    } else {
        return V1_0::NfcStatus::OK;
    }
}

Return<V1_0::NfcStatus> Nfc::prediscover() {
    HALSTATUS status = HALSTATUS_FAILED;
    status = phNxpNciHal_pre_discover();
    return V1_0::NfcStatus {};
}

Return<V1_0::NfcStatus> Nfc::close() {
    HALSTATUS status = HALSTATUS_FAILED;

    if (mCallback == nullptr) {
        return V1_0::NfcStatus::FAILED;
    } else {
        mCallback->unlinkToDeath(this);
    }

    status = phNxpNciHal_close();
    if(status != HALSTATUS_SUCCESS) {
        return V1_0::NfcStatus::FAILED;
    } else {
        return V1_0::NfcStatus::OK;
    }
}

Return<V1_0::NfcStatus> Nfc::controlGranted() {
    HALSTATUS status = HALSTATUS_FAILED;
    status = phNxpNciHal_control_granted();
    if(status != HALSTATUS_SUCCESS) {
        return V1_0::NfcStatus::FAILED;
    } else {
        return V1_0::NfcStatus::OK;
    }
}

Return<V1_0::NfcStatus> Nfc::powerCycle() {
    HALSTATUS status = HALSTATUS_FAILED;
    status = phNxpNciHal_power_cycle();
    if(status != HALSTATUS_SUCCESS) {
        return V1_0::NfcStatus::FAILED;
    } else {
        return V1_0::NfcStatus::OK;
    }
}

// Methods from ::android::hardware::nfc::V1_1::INfc follow.
Return<void> Nfc::factoryReset() {
    phNxpNciHal_do_factory_reset();
    return Void();
}

Return<V1_0::NfcStatus> Nfc::closeForPowerOffCase() {
    HALSTATUS status = HALSTATUS_FAILED;
    status = phNxpNciHal_shutdown();
    if(status != HALSTATUS_SUCCESS) {
        return V1_0::NfcStatus::FAILED;
    } else {
        return V1_0::NfcStatus::OK;
    }
}

Return<void> Nfc::getConfig(getConfig_cb hidl_cb) {
  NfcConfig nfcVendorConfig;
  hidl_cb(nfcVendorConfig);
  return Void();
}


}  // namespace implementation
}  // namespace V1_1
}  // namespace nfc
}  // namespace hardware
}  // namespace android
