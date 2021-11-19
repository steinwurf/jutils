// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

#include "byte_buffer.hpp"

#include <jni.h>

namespace jutils
{
uint8_t* byte_buffer::data(JNIEnv* env, jobject jbuffer)
{
    jclass cls = env->GetObjectClass(jbuffer);
    if (is_direct(env, jbuffer))
    {
        return (uint8_t*)env->GetDirectBufferAddress(jbuffer) +
               position(env, jbuffer);
    }
    else if (has_array(env, jbuffer))
    {

        return (uint8_t*)env->GetByteArrayElements(
                   get_array(env, jbuffer), JNI_FALSE) +
               array_offset(env, jbuffer);
    }
    else
    {
        return nullptr;
    }
}

jint byte_buffer::limit(JNIEnv* env, jobject jbuffer)
{
    jclass cls = env->GetObjectClass(jbuffer);
    return env->CallIntMethod(jbuffer, env->GetMethodID(cls, "limit", "()I"));
}

jint byte_buffer::position(JNIEnv* env, jobject jbuffer)
{
    jclass cls = env->GetObjectClass(jbuffer);
    return env->CallIntMethod(
        jbuffer, env->GetMethodID(cls, "position", "()I"));
}

jint byte_buffer::capacity(JNIEnv* env, jobject jbuffer)
{
    jclass cls = env->GetObjectClass(jbuffer);
    return env->CallIntMethod(
        jbuffer, env->GetMethodID(cls, "capacity", "()I"));
}

jint byte_buffer::remaining(JNIEnv* env, jobject jbuffer)
{
    jclass cls = env->GetObjectClass(jbuffer);
    return env->CallIntMethod(
        jbuffer, env->GetMethodID(cls, "remaining", "()I"));
}

jint byte_buffer::array_offset(JNIEnv* env, jobject jbuffer)
{
    jclass cls = env->GetObjectClass(jbuffer);
    return env->CallIntMethod(
        jbuffer, env->GetMethodID(cls, "arrayOffset", "()I"));
}

jbyteArray byte_buffer::get_array(JNIEnv* env, jobject jbuffer)
{
    jclass cls = env->GetObjectClass(jbuffer);
    return (jbyteArray)env->CallObjectMethod(
        jbuffer, env->GetMethodID(cls, "array", "()[B"));
}

jboolean byte_buffer::has_array(JNIEnv* env, jobject jbuffer)
{
    jclass cls = env->GetObjectClass(jbuffer);
    return env->CallBooleanMethod(
        jbuffer, env->GetMethodID(cls, "hasArray", "()Z"));
}

jboolean byte_buffer::is_direct(JNIEnv* env, jobject jbuffer)
{
    jclass cls = env->GetObjectClass(jbuffer);
    return env->CallBooleanMethod(
        jbuffer, env->GetMethodID(cls, "isDirect", "()Z"));
}

void byte_buffer::set_position(JNIEnv* env, jobject jbuffer, jint new_position)
{
    jclass cls = env->GetObjectClass(jbuffer);
    jmethodID set_position_method =
        env->GetMethodID(cls, "position", "(I)Ljava/nio/ByteBuffer;");
    env->CallObjectMethod(jbuffer, set_position_method, new_position);
}

}
