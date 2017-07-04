
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "JJsonnet.h"

#include <libjsonnet.h>

JNIEXPORT jstring JNICALL Java_JJsonnet_evaluateFile(JNIEnv *env, jobject obj, jstring jstr)
{
      struct JsonnetVm *vm;
      char *out = "hahaha";
      int error;
      unsigned max_stack = 500, gc_min_objects = 1000, max_trace = 20;
      double gc_growth_trigger = 2;
      jboolean isCopy;
      const char *filename = (*env)->GetStringUTFChars(env, jstr, 0);
      // const char *filename = (*env)->GetStringUTFChars(env, jstr, &isCopy);
      char buf[128];

      memset(buf, 0, 128);

      memcpy(buf, filename, strlen(filename));
      printf("input filename: %s\n", buf);

      vm = jsonnet_make();
      //jsonnet_max_stack(vm, max_stack);
      //jsonnet_gc_min_objects(vm, gc_min_objects);
      //jsonnet_max_trace(vm, max_trace);
      //jsonnet_gc_growth_trigger(vm, gc_growth_trigger);

      //     out = jsonnet_evaluate_file(vm, buf, &error);
      out = jsonnet_evaluate_snippet(vm, filename, "", &error);
      (*env)->ReleaseStringUTFChars(env, jstr, 0);
      if (error)
      {
            printf("Error %d\n", error);
      }
      else
      {
            printf("out~~%s~~\n", out);

            char *buf2 = (char *)calloc(1, strlen(out) + 1);
            strcpy(buf2, out); // with the null terminator the string adds up to 10 bytes
      }

      jstring jstrBuf = (*env)->NewStringUTF(env, out);
      //     jstring jstrBuf = (*env)->NewStringUTF(env, buf2);

      jsonnet_realloc(vm, out, 0);
      jsonnet_destroy(vm);


      return jstrBuf;
}

JNIEXPORT jstring JNICALL Java_JJsonnet_evaluateSnippet(JNIEnv *env, jobject obj, jstring jstr)
{
      struct JsonnetVm *vm;
      char *out = "hahaha";
      int error;
      unsigned max_stack = 500, gc_min_objects = 1000, max_trace = 20;
      double gc_growth_trigger = 2;
      jboolean isCopy;
      const char *str = (*env)->GetStringUTFChars(env, jstr, &isCopy);
      char buf[128];

      memset(buf, 0, 128);

      //printf("isCopy:%d\n",isCopy);
      //const char *str = (*env)->GetStringUTFChars(env, jstr, JNI_FALSE );

      //printf("%d", strlen(str));
      printf("~~~");
      memcpy(buf, str, strlen(str));
      printf("input: %s~~~\n", buf);
      (*env)->ReleaseStringUTFChars(env, jstr, str);
      printf("~~~");

      vm = jsonnet_make();
      printf("~123~~");
      //jsonnet_max_stack(vm, max_stack);
      //jsonnet_gc_min_objects(vm, gc_min_objects);
      //jsonnet_max_trace(vm, max_trace);
      //jsonnet_gc_growth_trigger(vm, gc_growth_trigger);

      out = jsonnet_evaluate_snippet(vm, "snx", buf, &error);
      //     out = jsonnet_evaluate_file(vm, str, &error);
      printf("out~~%s~~\n", out);

      char *buf2 = (char *)malloc(strlen(out) + 1);
      memset(buf2, 0, strlen(out) + 1);
      strcpy(buf2, out); // with the null terminator the string adds up to 10 bytes
      //jstring jstrBuf = (*env)->NewStringUTF(env, "xxx");
      jstring jstrBuf = (*env)->NewStringUTF(env, buf2);

      //     jsonnet_realloc(vm, out, 0);
      jsonnet_destroy(vm);

      return jstrBuf;
}

// javac JJsonnet.java
// javah -jni JJsonnet
// gcc -I ../include -I /usr/lib/jvm/java-7-openjdk-amd64/include/linux/ -I /usr/lib/jvm/java-7-openjdk-amd64/include/ -fPIC -shared -o libjjsonnet.so JJsonnet.c
// export LD_LIBRARY_PATH=.
// java JJsonnet
