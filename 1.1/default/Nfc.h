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

#ifndef ANDROID_HARDWARE_NFC_V1_1_NFC_H
#define ANDROID_HARDWARE_NFC_V1_1_NFC_H

#include <android/hardware/nfc/1.1/INfc.h>
#include <hidl/MQDescriptor.h>
#include <hidl/Status.h>

namespace android {
namespace hardware {
namespace nfc {
namespace V1_1 {
namespace implementation {

using ::android::hardware::hidl_array;
using ::android::hardware::hidl_memory;
using ::android::hardware::hidl_string;
using ::android::hardware::hidl_vec;
using ::android::hardware::Return;
using ::android::hardware::Void;
using ::android::sp;

struct Nfc : public INfc {
    // Methods from ::android::hardware::nfc::V1_0::INfc follow.
    Return<::android::hardware::nfc::V1_0::NfcStatus> open(const sp<::android::hardware::nfc::V1_0::INfcClientCallback>& clientCallback) override;
    Return<uint32_t> write(const hidl_vec<uint8_t>& data) override;
    Return<::android::hardware::nfc::V1_0::NfcStatus> coreInitialized(const hidl_vec<uint8_t>& data) override;
    Return<::android::hardware::nfc::V1_0::NfcStatus> prediscover() override;
    Return<::android::hardware::nfc::V1_0::NfcStatus> close() override;
    Return<::android::hardware::nfc::V1_0::NfcStatus> controlGranted() override;
    Return<::android::hardware::nfc::V1_0::NfcStatus> powerCycle() override;

    // Methods from ::android::hardware::nfc::V1_1::INfc follow.
    Return<void> factoryReset() override;
    Return<::android::hardware::nfc::V1_0::NfcStatus> closeForPowerOffCase() override;
    Return<::android::hardware::nfc::V1_0::NfcStatus> open_1_1(const sp<::android::hardware::nfc::V1_1::INfcClientCallback>& clientCallback) override;

    // Methods from ::android::hidl::base::V1_0::IBase follow.

};

// FIXME: most likely delete, this is only for passthrough implementations
// extern "C" INfc* HIDL_FETCH_INfc(const char* name);

}  // namespace implementation
}  // namespace V1_1
}  // namespace nfc
}  // namespace hardware
}  // namespace android

#endif  // ANDROID_HARDWARE_NFC_V1_1_NFC_H
