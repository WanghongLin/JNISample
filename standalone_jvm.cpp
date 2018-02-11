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

/**
 * A simple example to show how to use the JNI invocation API
 */

#include <jni.h>
#include <iostream>

int main(int argc, char *argv[])
{
    auto* vmOption = new JavaVMOption[2];
    vmOption[0].optionString = const_cast<char*>("-Djava.class.path=" CLASS_PATH);
    vmOption[1].optionString = const_cast<char*>("-verbose:gc");

    std::cout << vmOption[0].optionString << std::endl;

    JavaVMInitArgs vmInitArgs{};
    vmInitArgs.ignoreUnrecognized = JNI_FALSE;
    vmInitArgs.version = JNI_VERSION_1_8;
    vmInitArgs.options = vmOption;
    vmInitArgs.nOptions = 2;

    JavaVM* javaVM;
    JNIEnv* jniEnv;
    if (JNI_CreateJavaVM(&javaVM, reinterpret_cast<void**>(&jniEnv), &vmInitArgs) != JNI_OK) {
        std::cerr << "Create JVM failed" << std::endl;
        exit(EXIT_FAILURE);
    }
    delete vmOption;

    jclass clz = jniEnv->FindClass("com/example/Main");
    if (clz == nullptr) {
        std::cerr << "class not found" << std::endl;
        exit(EXIT_FAILURE);
    }

    jmethodID mainMethodId = jniEnv->GetStaticMethodID(clz, "main", "([Ljava/lang/String;)V");

    if (mainMethodId == nullptr) {
        std::cerr << "main method id not found" << std::endl;
        exit(EXIT_FAILURE);
    }

    jniEnv->CallStaticVoidMethod(clz, mainMethodId);

    return 0;
}

