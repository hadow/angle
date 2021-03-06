//
// Copyright 2017 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// logging.h: Compatiblity hacks for importing Chromium's MRUCache.

#ifndef BASE_LOGGING_H_
#define BASE_LOGGING_H_

#include "common/debug.h"

#ifndef DCHECK
#define DCHECK(X) ASSERT(X)
#endif

#ifndef CHECK
#define CHECK(X) ASSERT(X)
#endif

// Unfortunately ANGLE relies on ASSERT being an empty statement, which these libs don't respect.
#ifndef NOTREACHED
#define NOTREACHED() UNREACHABLE()
#endif

#endif  // BASE_LOGGING_H_
