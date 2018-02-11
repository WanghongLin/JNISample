# JNISample

Sample code to use JNI

`javac` should be located in your `PATH`

```bash
$ mkdir build
$ cd build
$ cmake ../
$ make -j4

# execute java program
$ java -cp ../java com.example.Main

# execute standalone jvm program
$ ./standalone_jvm
```