//
//  Copyright (c) 2018 mutter
//
//  This file is part of JNISample.
//
//  JNISample is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  JNISample is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with JNISample.  If not, see <http://www.gnu.org/licenses/>.
//  
//
// Created by mutter on 2/10/18.
//

#include <jni.h>
#include "com_example_Main.h"

jobject Java_com_example_Main_jniWeakUser(JNIEnv* env, jobject obj) {
    jclass clz = env->FindClass("com/example/User");
    jmethodID ctorId =  env->GetMethodID(clz, "<init>", "(Ljava/lang/String;I)V");
    jstring name = env->NewStringUTF("amigo");
    jint age = 23;
    jobject user = env->NewObject(clz, ctorId, name, age);

    env->DeleteLocalRef(name);

    jobject localRef = env->NewLocalRef(user);
    env->DeleteLocalRef(localRef);

    return user;
}

jstring Java_com_example_Main_helloFromJNI(JNIEnv* env, jobject obj) {
    jstring s = env->NewStringUTF("jack");
    return s;
}
