#include <jni.h>
#include <string.h>
#include <iostream>
#include <android/log.h>

#define TAG "JNIDemo"
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN,TAG,__VA_ARGS__))

extern "C"
JNIEXPORT jstring JNICALL
Java_com_nativedemo_JniLib_JniDemo_stringFromJNI(
        JNIEnv *env,
        jobject obj/* this */) {
    std::string hello = "Hello world from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_nativedemo_JniLib_JniDemo_sum(
        JNIEnv *env,jobject obj,jintArray arrayInt){
    jint* arr;
    int sum = 0;
    //对于整形数组的处理，主要有GetIntArrayElements与GetIntArrayRegion
    //第一种方法
    arr = env->GetIntArrayElements(arrayInt,NULL); //得到一个指向原始数据类型内容的指针
    jint length = env->GetArrayLength(arrayInt); //得到数组的长度
    int i = 0;
    for (i = 0; i < length; ++i) {
        std::cout<<"arr["<<i<<"]="<<arr[i]<<std::endl;
        sum += arr[i];
    }

    //第二种方法
    jint buf[]={0,0,0,0,0};//定义一个jint类型的buffer把原始的数组copy到这个buf中去
    env->GetIntArrayRegion(arrayInt,0,length,buf);
    for(i=0;i<length;i++){
        std::cout<<"buf["<<i<<"]="<<buf[i]<<std::endl;
        LOGW("jniDemo buf = %d",buf[i]);
        sum+=buf[i];
    }

    //返回一个jint类型的数组

//可以先往一个数组中输入值，然后把这个数组copy到jintArray中
    jintArray iarr =env->NewIntArray(length);//新建一个jintArray
    env->SetIntArrayRegion(iarr, 0, length, buf);//将buf中的值复制到jintArray中去，数组copy

    //打印新的数组值
    jint* arr2;
    arr2=env->GetIntArrayElements(iarr,NULL);
    for(i=0;i<env->GetArrayLength(iarr);i++){
        std::cout<<"arr2["<<i<<"]="<<arr2[i]<<std::endl;
    }
    return sum;
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_nativedemo_JniLib_JniDemo_sumStr(
        JNIEnv *env,jobject obj,jobjectArray strArray){
    //在java中，String[]类型是对象，所以对应C++中的数组为jobjectArray
    // 把jobjectArray数组中的值取出来
    int size = env->GetArrayLength(strArray);
    int i = 0;
    for (i = 0; i < size; ++i) {
        jstring objStr = (jstring)env->GetObjectArrayElement(strArray,i);
        const char* chars = env->GetStringUTFChars(objStr,NULL);//将jstring类型转换成char类型输出
        LOGW("jniDemo chars = %s",chars);
    }

    //复制数组到新的数组中
    jclass cls = env->FindClass("java/lang/String"); //定义数组中元素类型
    //创建一个数组类型为String类型
    jobjectArray texts = env->NewObjectArray(size,cls,0);
    jstring jstr;
    for (i = 0; i < size; i++) {
        jstr = (jstring)env->GetObjectArrayElement(strArray, i);
        env->SetObjectArrayElement(texts,i,jstr); //放入到texts数组中去，必须放入jstring
    }
    for (i = 0; i < size; i++) {
        jstring str1 = (jstring)env->GetObjectArrayElement(texts,i);
        const char* chars1 = env->GetStringUTFChars(str1,NULL);
        LOGW("jniDemo chars1 = %s",chars1);
    }
    return 0;
}


typedef enum {
    NOISE_NONE = 0,
    NOISE_BASELINEWANDER = 1,
    NOISE_POWERLINE = 2,
    NOISE_EMG = 3,
    NOISE_LEADOFF = 4
} NoiseType;

typedef struct tagNoiseInfo{
    NoiseType eNoiseType;
    char cNoiseIntensity;
} NoiseInfo;

extern "C" void
Java_com_nativedemo_JniLib_JniDemo_getNoiseInfoJNI(JNIEnv* env,jobject obj,jobjectArray mNoiseInfos/* this */) {
    NoiseInfo **pNoiseInfo = new NoiseInfo *[12];
    for (int i = 0; i < 12; ++i) {
        pNoiseInfo[i] = new NoiseInfo[10];
        memset(pNoiseInfo[i], 0, sizeof(NoiseInfo) * 10);
    }
    int iClen = 10 * 2;
    char *pCNoise = new char[iClen * sizeof(char)];
    for (int i = 0; i < iClen; i++) {
        pCNoise[i] = i + 5;
    }
    for (int i = 0; i < 12; ++i) {
        for (int j = 0; j < 10; ++j) {
            char cType = pCNoise[j * 2];
            char cIntensity = pCNoise[j * 2 + 1];
            pNoiseInfo[i][j].eNoiseType = (NoiseType) cType;
            pNoiseInfo[i][j].cNoiseIntensity = cIntensity;
        }
    }
/////////////////////////////////////////////////////////////
    int noiseLeng = env->GetArrayLength(mNoiseInfos); //获取二维数组的长度
    jclass jclz = env->FindClass("com/nativedemo/entity/NoiseInfo");
    for (int i = 0; i < noiseLeng; i++) {
        jobjectArray array = (jobjectArray) env->GetObjectArrayElement(mNoiseInfos, i);
        int noiseLeng1 = env->GetArrayLength(array);
        for (int j = 0; j < noiseLeng1; j++) {
            jmethodID jm_id = env->GetMethodID(jclz, "<init>", "()V");
            jobject item = env->NewObject(jclz, jm_id);
//            jmethodID j_seteNoiseType = env->GetMethodID(jclz,"seteNoiseType","(S)V");
//            env->CallShortMethod(item,j_seteNoiseType,1);
//            jmethodID j_setcNoiseIntensity = env->GetMethodID(jclz,"setcNoiseIntensity","(B)V");
//            env->CallByteMethod(item,j_setcNoiseIntensity,2);

            jfieldID j_f_Id1 = env->GetFieldID(jclz, "eNoiseType", "S");
            env->SetShortField(item, j_f_Id1, pNoiseInfo[i][j].eNoiseType);
            jfieldID j_f_Id = env->GetFieldID(jclz, "cNoiseIntensity", "B");
            env->SetByteField(item, j_f_Id, pNoiseInfo[i][j].cNoiseIntensity);

            env->SetObjectArrayElement(array, j, item);
            env->DeleteLocalRef(item);
        }
    }
}










