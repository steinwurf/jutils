// Copyright (c) Steinwurf ApS 2016.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

#include "jthrow.hpp"
#include "utils.hpp"

#include <jni.h>

namespace jutils
{
jint jthrow::exception(JNIEnv* env, const char* clazz_str, const char* message)
{
    auto cls = jutils::get_class(env, clazz_str);
    return env->ThrowNew(cls, message);
}

jint jthrow::illegal_argument_exception(JNIEnv* env, const char* message)
{
    return exception(env, "java/lang/IllegalArgumentException", message);
}

jint jthrow::illegal_state_exception(JNIEnv* env, const char* message)
{
    return exception(env, "java/lang/IllegalStateException", message);
}

jint jthrow::null_pointer_exception(JNIEnv* env, const char* message)
{
    return exception(env, "java/lang/NullPointerException", message);
}

jint jthrow::io_exception(JNIEnv* env, const char* message)
{
    return exception(env, "java/io/IOException", message);
}
}
