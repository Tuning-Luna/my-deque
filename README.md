更多合肥工业大学学习资料：https://github.com/Tuning-Luna/HFUT_XC_Study_Things

# 一. 需求和规格说明

双端队列(deque)容器内部数据表示为分段数组，并提供相应的索引数组来维护多个分段数组。 双端队列(deque)容器的基本功能要求：

## （1）容器的通用功能：

- 用默认构造函数构造空容器

- 支持关系运算符：==、!=、<、<=、>、>=

- begin()、end()：获得容器首、尾迭代器

- clear()：将容器清空

- empty()：判断容器是否为空

- size()：得到容器元素个数

s1.swap(s2)：将s1和s2两容器内容交换

## （2）相关数据类型（S表示deque容器类型）:

- S::iterator：指向容器元素的迭代器类型

- S::const_iterator：常迭代器类型

## （3）可逆容器功能:

- rbegin() ：指向容器尾的逆向迭代器
- rend()： 指向容器首的逆向迭代器

## （4）随机访问容器功能 ：

- s[n]：获得容器s的第n个元素

## （5）顺序容器的接口功能赋值 assign

- 插入函数 insert， push_front， push_back

- 删除函数 erase，clear，pop_front ，pop_back

- 其他顺序容器访问函数 front，back

- 改变大小resize
