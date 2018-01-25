

#include <jni.h>
#include<malloc.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include "com_wangpos_andfixcore_MainActivity.h"
#include "art_method.h"


JNIEXPORT void JNICALL Java_com_wangpos_andfixcore_MainActivity_replaceNative(JNIEnv *env,
                                                                         jobject instance,
                                                                         jobject wrongMethod,
                                                                         jobject rightMethod) {

    art::mirror::ArtMethod *wrong = (art::mirror::ArtMethod *) env->FromReflectedMethod(wrongMethod);
    art::mirror::ArtMethod *right = (art::mirror::ArtMethod *) env->FromReflectedMethod(rightMethod);

    wrong->declaring_class_=right->declaring_class_;

    wrong->dex_cache_resolved_methods_=right->dex_cache_resolved_methods_;
    wrong->dex_cache_resolved_types_=right->dex_cache_resolved_types_;

    wrong->dex_code_item_offset_=right->dex_code_item_offset_;
    wrong->method_index_=right->method_index_;
    wrong->dex_method_index_=right->dex_method_index_;

    wrong->ptr_sized_fields_.entry_point_from_jni_=right->ptr_sized_fields_.entry_point_from_jni_;
    wrong->ptr_sized_fields_.entry_point_from_quick_compiled_code_=right->ptr_sized_fields_.entry_point_from_quick_compiled_code_;

}