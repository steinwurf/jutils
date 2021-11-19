======
jutils
======

Shared toolbox for native java libraries.

Android CMake Integration
=========================

The following will explain how to integrate the jutils library into your native android code.

CMake Integration
-----------------

The easiest approach is to simply add the jutils folder with the CMake command
``add_subdirectory``.

::

   add_subdirectory("/path/to/jutils" jutils)
   target_link_libraries(<my_target> steinwurf::jutils)

Where ``<my_target>`` is replaced by your target.

Doing so will make Android Studio/Gradle build jutils which means when a new 
platform is added or remove this change will automatically be mitigated.

The downside of this is that your build may end up taking longer - this can be a
problem if you find yourself rebuilding your application frequently.

As a Pre-built Static Library
-----------------------------
If the above approach doesn't fit your use case, an alternative is to pre-build
the jutils library and depend on that in your application.

.. note:: This guide is written using Linux command-line tools and with the
          assumption that your android studio has been setup for native 
          development.

To do so, first you need to build the jutils library for the desired platforms.

Here we'll assume you need the following ABIs:

* arm64-v8a
* armeabi-v7a
* x86
* x86_64


::

    git clone git@github.com:steinwurf/jutils.git

    cd jutils


Download CMake using Android Studio, and use it to build the various version of
the library::

   mkdir cmake_build && cd cmake_build

   # arm64-v8a
   ~/Android/Sdk/cmake/3.18.1/bin/cmake -DCMAKE_TOOLCHAIN_FILE=~/Android/Sdk/ndk-bundle/build/cmake/android.toolchain.cmake -DANDROID_ABI="arm64-v8a" ../
   ~/Android/Sdk/cmake/3.18.1/bin/cmake --build . && cd ..
   cp libjutils.a /path/to/your/android_app/app/src/main/cpp/libs/arm64-v8a

   # armeabi-v7a
   ~/Android/Sdk/cmake/3.18.1/bin/cmake -DCMAKE_TOOLCHAIN_FILE=~/Android/Sdk/ndk-bundle/build/cmake/android.toolchain.cmake -DANDROID_ABI="armeabi-v7a" ../
   ~/Android/Sdk/cmake/3.18.1/bin/cmake --build . && cd ..
   cp libjutils.a /path/to/your/android_app/app/src/main/cpp/libs/armeabi-v7a

   # x86
   ~/Android/Sdk/cmake/3.18.1/bin/cmake -DCMAKE_TOOLCHAIN_FILE=~/Android/Sdk/ndk-bundle/build/cmake/android.toolchain.cmake -DANDROID_ABI="x86" ../
   ~/Android/Sdk/cmake/3.18.1/bin/cmake --build . && cd ..
   cp libjutils.a /path/to/your/android_app/app/src/main/cpp/libs/x86

   # x86_64
   ~/Android/Sdk/cmake/3.18.1/bin/cmake -DCMAKE_TOOLCHAIN_FILE=~/Android/Sdk/ndk-bundle/build/cmake/android.toolchain.cmake -DANDROID_ABI="x86" ../
   ~/Android/Sdk/cmake/3.18.1/bin/cmake --build . && cd ..
   cp libjutils.a /path/to/your/android_app/app/src/main/cpp/libs/x86_64

   cd ..

Copy the jutils public headers::

    cp src/jutils/*.hpp /path/to/your/android_app/app/src/main/cpp/libs/include/jutils/

And finally here's how to set it up your CMakeLists.txt file in Android Studio::

    add_library(jutils STATIC IMPORTED)
    set_property(TARGET jutils PROPERTY IMPORTED_LOCATION
    ${CMAKE_SOURCE_DIR}/libs/${ANDROID_ABI}/libjutils.a)

    include_directories(${CMAKE_SOURCE_DIR}/libs/include)

    target_link_libraries(<your_target> jutils)

You should now be able to use jutils in your native code.

Running Unit Tests
------------------
Follow the step in the previous section for the platform where you wish to run
the tests.

Now copy over the unit test executable with adb::

    adb push /path/to/built/unit/test/jutils_test /data/local/tmp

Run the test::

    adb shell /data/local/tmp/jutils_test
