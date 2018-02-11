//
//  Copyright (c) 2018 mutter
//
//  This file is part of untitled.
//
//  untitled is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  untitled is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with untitled.  If not, see <http://www.gnu.org/licenses/>.
//  
//
// Created by mutter on 2/10/18.
//

#include <jni.h>
#include <iostream>

/**
 * Check for jni exception
 * @param jniEnv jni environment
 */
static void ensureNoException(JNIEnv* jniEnv) {
    if (jniEnv) {
        if (jniEnv->ExceptionCheck()) {
            jniEnv->ExceptionDescribe();
            jniEnv->ExceptionClear();
        }
    }
}

static JavaVM* createJavaVM() {
    auto* vmOption = new JavaVMOption;
    vmOption->optionString = const_cast<char*>("-Djava.class.path=" CLASS_PATH);

    JavaVMInitArgs vmInitArgs{};
    vmInitArgs.options = vmOption;
    vmInitArgs.nOptions = 1;
    vmInitArgs.version = JNI_VERSION_1_8;
    vmInitArgs.ignoreUnrecognized = 0;

    JavaVM* javaVM;
    JNIEnv* jniEnv;
    JNI_CreateJavaVM(&javaVM, (void**) &jniEnv, &vmInitArgs);

    return javaVM;
}

/**
 * a pthread routine to create JVM
 * @param arg the arg from pthread_create
 * @return java virtual machine
 */
void* secondRoutine(void* arg) {
    JavaVM* javaVM = createJavaVM();
    return javaVM;
}

/**
 * A pthread routine to execute java code
 * @param arg the arg from pthread_create
 * @return java virtual machine
 */
void* thirdRoutine(void* arg) {
    pthread_t* wait = (pthread_t*)(*(&arg));

    JavaVM* javaVM;
    pthread_join(*wait, reinterpret_cast<void**>(&javaVM));

    JNIEnv* jniEnv;
    javaVM->AttachCurrentThread(reinterpret_cast<void**>(&jniEnv), nullptr);

    jclass clz = jniEnv->FindClass("com/example/User");
    jmethodID mid = jniEnv->GetStaticMethodID(clz, "main", "([Ljava/lang/String;)V");
    jniEnv->CallStaticVoidMethod(clz, mid);
    ensureNoException(jniEnv);

    javaVM->DetachCurrentThread();
    return javaVM;
}

int main(int argc, char *argv[])
{
    pthread_t second_thread;
    pthread_t third_thread;

    pthread_attr_t joinable_attr{};
    pthread_attr_init(&joinable_attr);
    pthread_attr_setdetachstate(&joinable_attr, PTHREAD_CREATE_JOINABLE);

    pthread_create(&second_thread, &joinable_attr, secondRoutine, nullptr);
    pthread_create(&third_thread, &joinable_attr, thirdRoutine, &second_thread);

    pthread_join(third_thread, nullptr);

    return 0;
}
