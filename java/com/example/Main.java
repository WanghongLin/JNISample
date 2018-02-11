package com.example;

import java.io.File;

public class Main {

    static {
        System.load(new File("../cmake-build-debug/libjni_sample.so").getAbsolutePath());
    }

    public static void main(String[] args) {
        System.out.println("Hello World!");
        System.out.println(new Main().jniWeakUser().toString());
        System.out.println(new Main().helloFromJNI());
    }

    private native User jniWeakUser();
    private native String helloFromJNI();
}