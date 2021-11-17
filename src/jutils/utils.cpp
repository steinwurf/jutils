// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

#include "utils.hpp"

#include <cassert>
#include <jni.h>
#include <pthread.h>

#include "logging.hpp"

namespace jutils
{

JavaVM* java_vm = nullptr;
pthread_key_t current_jni_env;

// Register this thread with the VM
JNIEnv* attach_current_thread()
{
    JavaVMAttachArgs args;
    args.version = JNI_VERSION_1_4;
    args.name = NULL;
    args.group = NULL;

    JNIEnv* env;
    if (java_vm->AttachCurrentThread(&env, &args) < 0)
    {
        LOGE << "Failed to attach current thread";
        return NULL;
    }
    LOGI << "Attached current thread";

    return env;
}

// Unregister this thread from the VM
void detach_current_thread(void* value)
{
    JNIEnv* env = (JNIEnv*)value;
    if (env != NULL)
    {
        java_vm->DetachCurrentThread();
        pthread_setspecific(current_jni_env, NULL);
        LOGI << "Thread detached";
    }
}

JNIEnv* get_jni_env()
{
    JNIEnv* env = (JNIEnv*)pthread_getspecific(current_jni_env);

    if (env == NULL)
    {
        env = attach_current_thread();
        pthread_setspecific(current_jni_env, env);
    }

    return env;
}

jclass get_class(JNIEnv* env, const std::string& name)
{
    auto clazz = env->FindClass(name.c_str());
    if (!clazz)
    {
        LOGF << "Failed to find class " << name;
    }

    return clazz;
}

jmethodID get_static_method(
    JNIEnv* env, jclass clazz, const std::string& name,
    const std::string& signature)
{
    jmethodID method =
        env->GetStaticMethodID(clazz, name.c_str(), signature.c_str());

    if (!method)
    {
        LOGF << "Failed to find method " << name << signature;
    }

    return method;
}

jmethodID get_method(
    JNIEnv* env, jclass clazz, const std::string& name,
    const std::string& signature)
{
    jmethodID method = env->GetMethodID(clazz, name.c_str(), signature.c_str());

    if (!method)
    {
        LOGF << "Failed to find method " << name << signature;
    }

    return method;
}

jboolean get_boolean(JNIEnv* env, jobject object, const std::string& name)
{
    auto clazz = env->GetObjectClass(object);
    auto field_id = env->GetFieldID(clazz, name.c_str(), "Z");

    if (!field_id)
    {
        LOGF << "Failed to find field " << name << " Z";
    }

    return env->GetBooleanField(object, field_id);
}

jbyte get_byte(JNIEnv* env, jobject object, const std::string& name)
{
    auto clazz = env->GetObjectClass(object);
    auto field_id = env->GetFieldID(clazz, name.c_str(), "B");

    if (!field_id)
    {
        LOGF << "Failed to find field " << name << " B";
    }

    return env->GetByteField(object, field_id);
}

jshort get_short(JNIEnv* env, jobject object, const std::string& name)
{
    auto clazz = env->GetObjectClass(object);
    auto field_id = env->GetFieldID(clazz, name.c_str(), "S");

    if (!field_id)
    {
        LOGF << "Failed to find field " << name << " S";
    }

    return env->GetShortField(object, field_id);
}

jint get_int(JNIEnv* env, jobject object, const std::string& name)
{
    auto clazz = env->GetObjectClass(object);
    auto field_id = env->GetFieldID(clazz, name.c_str(), "I");

    if (!field_id)
    {
        LOGF << "Failed to find field " << name << " I";
    }

    return env->GetIntField(object, field_id);
}

jlong get_long(JNIEnv* env, jobject object, const std::string& name)
{
    auto clazz = env->GetObjectClass(object);
    auto field_id = env->GetFieldID(clazz, name.c_str(), "J");

    if (!field_id)
    {
        LOGF << "Failed to find field " << name << " J";
    }

    return env->GetLongField(object, field_id);
}

jfloat get_float(JNIEnv* env, jobject object, const std::string& name)
{
    auto clazz = env->GetObjectClass(object);
    auto field_id = env->GetFieldID(clazz, name.c_str(), "F");

    if (!field_id)
    {
        LOGF << "Failed to find field " << name << " F";
    }

    return env->GetFloatField(object, field_id);
}

jdouble get_double(JNIEnv* env, jobject object, const std::string& name)
{
    auto clazz = env->GetObjectClass(object);
    auto field_id = env->GetFieldID(clazz, name.c_str(), "D");

    if (!field_id)
    {
        LOGF << "Failed to find field " << name << " D";
    }

    return env->GetDoubleField(object, field_id);
}

jstring get_string(JNIEnv* env, jobject object, const std::string& name)
{
    auto clazz = env->GetObjectClass(object);
    auto field_id = env->GetFieldID(clazz, name.c_str(), "Ljava/lang/String;");

    if (!field_id)
    {
        LOGF << "Failed to find field " << name << " Ljava/lang/String;";
    }

    return (jstring)env->GetObjectField(object, field_id);
}

JNIEnv* init(JavaVM* vm)
{
    // make sure we only init once.
    assert(java_vm == nullptr);
    java_vm = vm;

    if (pthread_key_create(&current_jni_env, detach_current_thread))
    {
        LOGF << "Error initializing pthread key.";
    }

    JNIEnv* env = nullptr;
    if (java_vm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_4) !=
        JNI_OK)
    {
        LOGF << "Failed to get the environment using GetEnv()";
    }

    return env;
}

jstring string_to_java_string(JNIEnv* env, const std::string string)
{
    return env->NewStringUTF(string.c_str());
}

std::string java_string_to_string(JNIEnv* env, jstring java_string)
{
    const char* char_string = env->GetStringUTFChars(java_string, 0);
    auto std_string = std::string(char_string);
    env->ReleaseStringUTFChars(java_string, char_string);
    return std_string;
}

jobjectArray string_vector_to_java_string_array(
    JNIEnv* env, const std::vector<std::string>& strings)
{
    jobjectArray array = env->NewObjectArray(
        strings.size(), env->FindClass("java/lang/String"),
        env->NewStringUTF(""));

    for (uint32_t i = 0; i < strings.size(); ++i)
    {
        env->SetObjectArrayElement(
            array, i, env->NewStringUTF(strings[i].c_str()));
    }

    return array;
}

std::vector<uint8_t> java_byte_array_to_vector(JNIEnv* env, jbyteArray jbuffer)
{
    uint8_t* data_ptr = (uint8_t*)env->GetByteArrayElements(jbuffer, JNI_FALSE);
    jsize data_size = env->GetArrayLength(jbuffer);
    // The vector will copy the original data, so it is safe to release
    // the java byte array
    std::vector<uint8_t> data(data_ptr, data_ptr + data_size);
    env->ReleaseByteArrayElements(jbuffer, (jbyte*)data_ptr, JNI_ABORT);

    return data;
}

jlong get_jlong_pointer_field(JNIEnv* env, jobject object)
{
    return get_long(env, object, "pointer");
}
}
