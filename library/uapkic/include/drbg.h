/*
 * Copyright 2021 The UAPKI Project Authors.
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

#ifndef UAPKIC_DRBG_H
#define UAPKIC_DRBG_H

#include "byte-array.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Заповнює масив випадковими байтами, використовуючи КСГПВЧ криптографічної бібліотеки.
 * Максимальний розмір масиву для заповнення — 64 КіБ.
 *
 * @param random масив для розміщення випадкових байтів
 * @return код помилки
 */
UAPKIC_EXPORT int drbg_random(ByteArray* random);

/**
 * Перезерновує КСГПВЧ криптографічної бібліотеки.
 *
 * @param entropy масив байтів, що містить додаткову ентропію (зерно); може бути NULL
 * @return код помилки
 */
UAPKIC_EXPORT int drbg_reseed(const ByteArray* entropy);

/**
 * Виконує самотестування КСГПВЧ криптографічної бібліотеки.
 *
 * @return код помилки
 */
UAPKIC_EXPORT int drbg_self_test(void);

#ifdef __cplusplus
}
#endif

#endif
