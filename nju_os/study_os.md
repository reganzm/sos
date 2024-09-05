### 查看磁盘主引导扇区数据
```
cat /dev/sda |head -c 512 |ndisasm -b 16 -
cat /dev/sda2 |head -c 512 |ndisasm -b 16 -
```
### 用C语言实现动态绑定(c++中的虚函数和多态)
```
// 实现OOP
struct foo{
int (*bar)(struct foo *this,int a,int b);// 函数指针
}
void baz(){
struct foo * ptr = get_obj();
ptr->bar(ptr,3,4);
}

// 实现dynamic binding
struct object_header{
void **vptr;
};

struct foo{
struct object_header header;
};

void baz{

struct foo* ptr = get_obj();
(int (*)(void *,int,int))(ptr->header.vptr[INDEX_OF_BAR])(ptr,3,4);
}

```
