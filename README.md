# JNI_NDK
JNI、NDK、HOOK技术

- ffmpeg视频的解码
- ffmpeg视频的编码
- ffmpeg视频的推流
- JNI ART实现底层HOOK技术
- Java层通过放射修改对象属性值，替换回调函数

    使用了method.setAccessible(true)后 性能有了20倍的提升 
    Accessable属性是继承自AccessibleObject 类. 功能是启用或禁用安全检查 
- Java层HookActivity启动流程
   
   - - 反射
   - - 动态代理
   - - 深入理解Activity启动流程
- SO创建
  创建SO 有两种方式，一种AndroidStudio生成，一种是通过ndk-build jni工程生成
  1. ndk-build jni工程生成
    - build AndroidStudio项目
    - 在java目录像通过 javah 包名.类名生成.h文件
    - copy .h文件到jni源码目录下，并进行引用
    - 配置jni 目录下的Android.mk 和Application.mk
    - 终端在jni目录下执行ndk-bulid
    - 注意：

                sourceSets.main {
                    jniLibs.srcDirs = ['src/main/libs']     //指定设置项目要加载的so路径
                    jni.srcDirs = [] //disable automatic ndk-build call//  取消ndk-build call 自动调用,因为自动调用会报类库找不到错误，所以只能通过命令行ndk-build
                }
        

    - 例子 CreateSo
  2. 通过
    - gradle.properties 

            android.useDeprecatedNdk=true

    - local.properties

            sdk.dir=/Users/qiyue/Library/Android/sdk
            ndk.dir=/Users/qiyue/ndk/android-ndk-r10d

    - build AndroidStudio项目
    - 在java目录像通过 javah 包名.类名生成.h文件
    - copy .h文件到jni源码目录下，并进行引用

    - 添加build.gradle配置

            android {
                defaultConfig {
                    ....
                    ndk{
                        moduleName "JniLibName"         //生成的so名字
                        abiFilters "armeabi", "armeabi-v7a", "x86"  //输出指定三种abi体系结构下的so库。
                        ldLibs "log"
                    }

                }

            
                sourceSets {
                    main {
                        jniLibs.srcDirs = ['libs']
                    }

                }
            }
    - 运行即可
    - 例子 TestJNIBaseß

1、寻找Hook点的原则

Android中主要是依靠分析系统源码类来做到的，首先我们得找到被Hook的对象，我称之为Hook点；什么样的对象比较好Hook呢？自然是容易找到的对象。什么样的对象容易找到？静态变量和单例；在一个进程之内，静态变量和单例变量是相对不容易发生变化的，因此非常容易定位，而普通的对象则要么无法标志，要么容易改变。我们根据这个原则找到所谓的Hook点。




