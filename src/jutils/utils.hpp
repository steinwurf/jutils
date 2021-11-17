// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

#pragma once

#include <cassert>
#include <jni.h>
#include <string>
#include <vector>

namespace jutils
{

// Register this thread with the VM
JNIEnv* attach_current_thread();

// Unregister this thread from the VM
void detach_current_thread(void* value);

JNIEnv* init(JavaVM* vm);

JNIEnv* get_jni_env();

jclass get_class(JNIEnv* env, const std::string& name);

jmethodID get_static_method(
    JNIEnv* env, jclass clazz, const std::string& name,
    const std::string& signature);

jmethodID get_method(
    JNIEnv* env, jclass clazz, const std::string& name,
    const std::string& signature);

jboolean get_boolean(JNIEnv* env, jobject object, const std::string& name);
jbyte get_byte(JNIEnv* env, jobject object, const std::string& name);
jshort get_short(JNIEnv* env, jobject object, const std::string& name);
jint get_int(JNIEnv* env, jobject object, const std::string& name);
jlong get_long(JNIEnv* env, jobject object, const std::string& name);
jfloat get_float(JNIEnv* env, jobject object, const std::string& name);
jdouble get_double(JNIEnv* env, jobject object, const std::string& name);
jstring get_string(JNIEnv* env, jobject object, const std::string& name);

jstring string_to_java_string(JNIEnv* env, const std::string string);
std::string java_string_to_string(JNIEnv* env, jstring java_string);
jobjectArray string_vector_to_java_string_array(
    JNIEnv* env, const std::vector<std::string>& strings);
jlong get_jlong_pointer_field(JNIEnv* env, jobject object);

std::vector<uint8_t> java_byte_array_to_vector(JNIEnv* env, jbyteArray jbuffer);

template <class T>
T* get_native_pointer(JNIEnv* env, jobject object)
{
    jlong pointer = get_jlong_pointer_field(env, object);
    auto native_object = reinterpret_cast<T*>(pointer);
    assert(native_object);
    return native_object;
}

template <class T>
T& get_native(jlong pointer)
{
    assert(pointer != 0);
    auto native_object = reinterpret_cast<T*>(pointer);
    assert(native_object);
    return *native_object;
}

template <class T>
T& get_native(JNIEnv* env, jobject object)
{
    jlong pointer = get_jlong_pointer_field(env, object);
    return get_native<T>(pointer);
}
} // namespace jutils
