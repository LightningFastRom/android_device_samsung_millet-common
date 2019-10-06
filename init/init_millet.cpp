/*
   Copyright (c) 2016, The Linux Foundation. All rights reserved.
   Copyright (c) 2017-2018, The LineageOS Project. All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the following
      disclaimer in the documentation and/or other materials provided
      with the distribution.
    * Neither the name of The Linux Foundation nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
   ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
   BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
   BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
   OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
   IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdlib.h>
#include <stdio.h>

#include <android-base/logging.h>
#include <android-base/properties.h>

#include "property_service.h"
#include "vendor_init.h"

#include "init_msm8226.h"

using android::base::GetProperty;
using android::init::property_set;


void connect_properties(std::string network, std::string type)
{
    if (network =="GSM") {
         /* GSM */
         if (type == "3G") {
            /* 3G */
            property_override("ro.telephony.default_network", "3");
            property_override("telephony.lteOnGsmDevice", "0");
        } else if (network =="LTE") {
            /* LTE */
            property_override("ro.telephony.default_network", "9");
            property_override("telephony.lteOnGsmDevice", "1");
        }
    } else if (network =="cdma") {
         /* CDMA */            
        if (network =="LTE") {
            /* LTE */
            property_override("ro.telephony.default_network", "9");
            property_override("telephony.lteOnGsmDevice", "1");
        } else {
            /* 3G */
            property_override("ro.telephony.default_network", "3");
            property_override("telephony.lteOnGsmDevice", "0");
        }
    } else if (network =="wcdma") {
         /* WCDMA */
        if (network =="LTE") {
            /* LTE */
            property_override("ro.telephony.default_network", "9");
            property_override("telephony.lteOnGsmDevice", "1");
        } else {
            /* 3G */
            property_override("ro.telephony.default_network", "3");
            property_override("telephony.lteOnGsmDevice", "0");
        }
    } else  {
        /* WiFi Only */
        property_override("ro.carrier", "wifi-only");
        property_override("ro.radio.noril", "1");
	}
}

void init_target_properties()
{
    std::string platform = GetProperty("ro.board.platform", "");
    if (platform != ANDROID_TARGET)
        return;

    std::string bootloader = GetProperty("ro.bootloader", "");
    if (bootloader.find("T330NU") == 0) {
        /* milletwifixx */
        property_override_dual("ro.build.fingerprint", "ro.vendor.build.fingerprint", "samsung/milletwifixx/milletwifi:5.0.2/LRX22G/T330XXU1BOJ4:user/release-keys");
        property_override_dual("ro.build.description", "ro.vendor.build.description", "milletwifixx-user 5.0.2 LRX22G T330XXU1BOJ4 release-keys");
        property_override("ro.product.model", "SM-T330");
        property_override_dual("ro.product.device", "ro.vendor.device", "milletwifi");
        connect_properties("", "");
    } else if (bootloader.find("T330XX") == 0) {
        /* milletwifixx */
        property_override_dual("ro.build.fingerprint", "ro.vendor.build.fingerprint", "samsung/milletwifixx/milletwifi:5.0.2/LRX22G/T330XXU1BOJ4:user/release-keys");
        property_override_dual("ro.build.description", "ro.vendor.build.description", "milletwifixx-user 5.0.2 LRX22G T330XXU1BOJ4 release-keys");
        property_override("ro.product.model", "SM-T330");
        property_override_dual("ro.product.device", "ro.vendor.device", "milletwifi");
        connect_properties("", "");
    } else if (bootloader.find("T331XX") == 0) {
        /* milletltetmo */
        property_override_dual("ro.build.fingerprint", "ro.vendor.build.fingerprint", "samsung/millet3gxx/millet3g:5.0.2/LRX22G/T331XXU1BOD8:user/release-keys");
        property_override_dual("ro.build.description", "ro.vendor.build.description", "millet3gxx-user 5.0.2 LRX22G T331XXU1BOD8 release-keys");
        property_override("ro.product.model", "SM-T331");
        property_override_dual("ro.product.device", "ro.vendor.device", "millet3g");
        connect_properties("GSM", "3G");
    } else if (bootloader.find("T335XX") == 0) {
        /* milletltexx */
        property_override_dual("ro.build.fingerprint", "ro.vendor.build.fingerprint", "samsung/milletltexx/milletlte:5.0.2/LRX22G/T335XXU1BOD8:user/release-keys");
        property_override_dual("ro.build.description", "ro.vendor.build.description", "milletltexx-user 5.0.2 LRX22G T335XXU1BOD8 release-keys");
        property_override("ro.product.model", "SM-T335");
        property_override_dual("ro.product.device", "ro.vendor.device", "milletlte");
        connect_properties("GSM", "LTE");
    } else if (bootloader.find("T337T") == 0) {
        /* milletltetmo */
        property_override_dual("ro.build.fingerprint", "ro.vendor.build.fingerprint", "samsung/milletltetmo/milletltetmo:5.1.1/LMY47X/T337TUVS1CPL1:user/release-keys");
        property_override_dual("ro.build.description", "ro.vendor.build.description", "milletltetmo-user 5.1.1 LMY47X T337TUVS1CPL1 release-keys");
        property_override("ro.product.model", "SM-T337T");
        property_override_dual("ro.product.device", "ro.vendor.device", "milletltetmo");
        connect_properties("GSM", "LTE");
    } else {
        connect_properties("GSM", "3G");
    }

    std::string device = GetProperty("ro.product.device", "");
    LOG(ERROR) << "Found bootloader id " << bootloader <<  " setting build properties for "
        << device <<  " device" << std::endl;
}
