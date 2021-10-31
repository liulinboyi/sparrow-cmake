# 交叉编辑Windows

在build目录下执行
64位
```
cmake -H"../src" -B"./" -DCMAKE_BUILD_TYPE=MinSizeRel -DCMAKE_TOOLCHAIN_FILE=windows.toolchain.cmake -DUSE_32BITS=0
make
```
32位
```
cmake -H"../src" -B"./" -DCMAKE_BUILD_TYPE=MinSizeRel -DCMAKE_TOOLCHAIN_FILE=windows.toolchain.cmake -DUSE_32BITS=1
```

# 编译linux

在build目录下执行
64位
```
cmake -H"../src" -B"./" -DCMAKE_BUILD_TYPE=MinSizeRel -DUSE_32BITS=0
make
```
32位
```
cmake -H"../src" -B"./" -DCMAKE_BUILD_TYPE=MinSizeRel -DUSE_32BITS=1
```

# [发行 Release](https://github.com/liulinboyi/sparrow-cmake/releases/latest)


# 尝试添加单步调试

参考[翻译：用Visual Studio Code编写你自己的调试器和语言扩展](https://www.yuque.com/docs/share/e5e33947-2e09-4de0-b43c-71f23769b246?#)尝试做单步调试，失败了，C语言用的还是不顺手。

具体思路我看了下，大概就是使用socket在vscode和REPL之间进行通信。在服务端，将调试的文件加载，然后分成一行一行，根据客户端(vscode)的调试指令，送上REPL运行，然后返回结果，说起来容易，但是用C语言做起来难呀。

# Mock debug

使用cscs-debuger

[cscs-debugger](https://github.com/vassilych/cscs-debugger)

[debug-demo](./debug-demo)

# 资料
[英文文章原地址](https://www.codemag.com/article/1809051/Writing-Your-Own-Debugger-and-Language-Extensions-with-Visual-Studio-Code)

[cscs C#](https://github.com/vassilych/cscs)

[cscs-debugger TypeScript](https://github.com/vassilych/cscs-debugger)

规范：
- 复合数据结构一律大写
