// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

#pragma once

#include <jni.h>

namespace jutils
{
class jthrow
{
public:
    static jint exception(
        JNIEnv* env, const char* clazz_str, const char* message);

    static jint illegal_argument_exception(JNIEnv* env, const char* message);
    static jint illegal_state_exception(JNIEnv* env, const char* message);
    static jint null_pointer_exception(JNIEnv* env, const char* message);
    static jint io_exception(JNIEnv* env, const char* message);
};
}
