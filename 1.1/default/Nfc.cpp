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

#include "Nfc.h"

namespace android {
namespace hardware {
namespace nfc {
namespace V1_1 {
namespace implementation {

// Methods from ::android::hardware::nfc::V1_0::INfc follow.
Return<::android::hardware::nfc::V1_0::NfcStatus> Nfc::open(const sp<::android::hardware::nfc::V1_0::INfcClientCallback>& clientCallback) {
    // TODO implement
    return ::android::hardware::nfc::V1_0::NfcStatus {};
}

Return<uint32_t> Nfc::write(const hidl_vec<uint8_t>& data) {
    // TODO implement
    return uint32_t {};
}

Return<::android::hardware::nfc::V1_0::NfcStatus> Nfc::coreInitialized(const hidl_vec<uint8_t>& data) {
    // TODO implement
    return ::android::hardware::nfc::V1_0::NfcStatus {};
}

Return<::android::hardware::nfc::V1_0::NfcStatus> Nfc::prediscover() {
    // TODO implement
    return ::android::hardware::nfc::V1_0::NfcStatus {};
}

Return<::android::hardware::nfc::V1_0::NfcStatus> Nfc::close() {
    // TODO implement
    return ::android::hardware::nfc::V1_0::NfcStatus {};
}

Return<::android::hardware::nfc::V1_0::NfcStatus> Nfc::controlGranted() {
    // TODO implement
    return ::android::hardware::nfc::V1_0::NfcStatus {};
}

Return<::android::hardware::nfc::V1_0::NfcStatus> Nfc::powerCycle() {
    // TODO implement
    return ::android::hardware::nfc::V1_0::NfcStatus {};
}


// Methods from ::android::hardware::nfc::V1_1::INfc follow.
Return<void> Nfc::factoryReset() {
    // TODO implement
    return Void();
}

Return<::android::hardware::nfc::V1_0::NfcStatus> Nfc::closeForPowerOffCase() {
    // TODO implement
    return ::android::hardware::nfc::V1_0::NfcStatus {};
}

Return<::android::hardware::nfc::V1_0::NfcStatus> Nfc::open_1_1(const sp<::android::hardware::nfc::V1_1::INfcClientCallback>& clientCallback) {
    // TODO implement
    return ::android::hardware::nfc::V1_0::NfcStatus {};
}


// Methods from ::android::hidl::base::V1_0::IBase follow.

//INfc* HIDL_FETCH_INfc(const char* /* name */) {
//    return new Nfc();
//}

}  // namespace implementation
}  // namespace V1_1
}  // namespace nfc
}  // namespace hardware
}  // namespace android
