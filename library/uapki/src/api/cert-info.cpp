/*
 * Copyright (c) 2021, The UAPKI Project Authors.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#define FILE_MARKER "uapki/api/cert-info.cpp"

#include "api-json-internal.h"
#include "global-objects.h"
#include "parson-ba-utils.h"
#include "parson-helper.h"
#include "store-json.h"
#include "uapki-errors.h"
#include "uapki-ns.h"


using namespace UapkiNS;


int uapki_cert_info (JSON_Object* joParams, JSON_Object* joResult)
{
    int ret = RET_OK;
    SmartBA sba_certid, sba_encoded;

    if (sba_encoded.set(json_object_get_base64(joParams, "bytes"))) {
        Cert::CerItem* cer_item = nullptr;
        DO(Cert::parseCert(sba_encoded.get(), &cer_item));

        DO(Cert::detailInfoToJson(joResult, cer_item));
        delete cer_item;
    }
    else {
        LibraryConfig* lib_config = get_config();
        Cert::CerStore* cer_store = get_cerstore();

        if (!lib_config || !cer_store) return RET_UAPKI_GENERAL_ERROR;
        if (!lib_config->isInitialized()) return RET_UAPKI_NOT_INITIALIZED;

        if (sba_certid.set(json_object_get_base64(joParams, "certId"))) {
            Cert::CerItem* cer_item = nullptr;
            DO(cer_store->getCertByCertId(sba_certid.get(), &cer_item));
            DO(Cert::detailInfoToJson(joResult, cer_item));
        }
        else {
            SET_ERROR(RET_UAPKI_INVALID_PARAMETER);
        }
    }

cleanup:
    return ret;
}
