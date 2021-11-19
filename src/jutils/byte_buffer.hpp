// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

#pragma once

#include <jni.h>

namespace jutils
{
class byte_buffer
{
public:
    static uint8_t* direct_data(JNIEnv* env, jobject jbuffer);
    static jint limit(JNIEnv* env, jobject jbuffer);
    static jint position(JNIEnv* env, jobject jbuffer);
    static jint capacity(JNIEnv* env, jobject jbuffer);
    static jint remaining(JNIEnv* env, jobject jbuffer);
    static jint array_offset(JNIEnv* env, jobject jbuffer);
    static jbyteArray get_array(JNIEnv* env, jobject jbuffer);
    static jboolean has_array(JNIEnv* env, jobject jbuffer);
    static jboolean is_direct(JNIEnv* env, jobject jbuffer);
    static void set_position(JNIEnv* env, jobject jbuffer, jint new_position);
};
}
