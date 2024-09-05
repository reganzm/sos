编译链接
```
//编译
gcc -c -O2 -o main.o main.c
gcc -c -O2 -o say.o say.c

//链接
gcc main.o say.o
//使用ld链接
ld -dynamic-linker /lib64/ld-linux-x86-64.so.2 /usr/lib/x86_64-linux-gnu//crt1.o /usr/lib/x86_64-linux-gnu/crti.o main.o say.o -lc /usr/lib/x86_64-linux-gnu/crtn.o


crt*指的是c runtime相关的库
ld是动态链接的库，用于运行时加载动态链接
ls指的是动态链接glibc

```

### 使用gdb调试程序
```
gdb a.out

starti // 启动并在第一条指令暂停

bt f // backtrce full 打印堆栈信息
info inferiors // 打印进程、线程信息

!cat /proc/process_id/maps //打印进程的内存信息


b _start // breakpoint 在符号_start设置断点
c // continue 继续执行
```

### strace 系统调用监控
```
strace ./a.out
```
