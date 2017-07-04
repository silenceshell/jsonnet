#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include <libjsonnet.h>
}
// #include <libjsonnet.h>

int main(int argc, const char **argv)
{
      struct JsonnetVm *vm;
      char *out = "hahaha";
      int error;
      const char *filename = argv[1];

      printf("input filename: %s\n", filename);

      vm = jsonnet_make();
      out = jsonnet_evaluate_snippet(vm, filename, "{}", &error);
      if (error)
      {
            printf("Error %d\n", error);
      }
      printf("%s\n", out);

      jsonnet_realloc(vm, out, 0);
      jsonnet_destroy(vm);

      return 0;
}


// javac JJsonnet.java
// javah -jni JJsonnet
// gcc -I ../include -I /usr/lib/jvm/java-7-openjdk-amd64/include/linux/ -I /usr/lib/jvm/java-7-openjdk-amd64/include/ -fPIC -shared -o libjjsonnet.so JJsonnet.c
// export LD_LIBRARY_PATH=.
// java JJsonnet


// g++ -g -O3 -Wall -Wextra -Woverloaded-virtual -pedantic -std=c++0x -fPIC -Iinclude -Ithird_party/md5  java/Jsonnet.cpp libjsonnet.so -o xxx