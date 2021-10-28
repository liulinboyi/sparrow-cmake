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

规范：
- 复合数据结构一律大写
