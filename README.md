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

1、寻找Hook点的原则

Android中主要是依靠分析系统源码类来做到的，首先我们得找到被Hook的对象，我称之为Hook点；什么样的对象比较好Hook呢？自然是容易找到的对象。什么样的对象容易找到？静态变量和单例；在一个进程之内，静态变量和单例变量是相对不容易发生变化的，因此非常容易定位，而普通的对象则要么无法标志，要么容易改变。我们根据这个原则找到所谓的Hook点。




