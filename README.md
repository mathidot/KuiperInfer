# KuiperInfer

## 使用的技术和开发环境
* 开发语言：C++ 17
* 数学库：Armadillo + OpenBlas(或者更快的Intel MKL)
* 加速库：OpenMP
* 单元测试：Google Test
* 性能测试：Google Benchmark

## 安装过程(使用Docker)
1. docker pull registry.cn-hangzhou.aliyuncs.com/hellofss/kuiperinfer:latest
2. sudo docker run -t -i registry.cn-hangzhou.aliyuncs.com/hellofss/kuiperinfer:latest /bin/bash
3. cd code 
4. git clone --recursive https://github.com/zjhellofss/KuiperInfer.git 
5. cd KuiperInfer
6. **git checkout -b 你的新分支 study_version_0.02 (如果想抄本项目的代码，请使用这一步切换到study tag)**
7. mkdir build 
8. cd build 
9. cmake -DCMAKE_BUILD_TYPE=Release -DDEVELOPMENT=OFF .. 
10. make -j16

**Tips:**

1. **如果需要对KuiperInfer进行开发**，请使用 git clone  --recursive https://github.com/zjhellofss/KuiperInfer.git 同时下载子文件夹tmp, 并在cmake文件中设置`$DEVELOPMENT`或者指定`-DDEVELOPMENT=ON`
2. **如果国内网速卡顿**，请使用 git clone https://gitee.com/fssssss/KuiperInferGitee.git 
3. **如果想获得更快地运行体验**，请在本机重新编译openblas或apt install intel-mkl

##  安装过程(不使用docker)
1. git clone --recursive https://github.com/zjhellofss/KuiperInfer.git
2. **git checkout -b 你的新分支 study_version_0.01 (如果想抄本项目的代码，请使用这一步切换到study tag)**
3. 安装必要环境(openblas推荐编译安装，可以获得更快的运行速度，或者使用apt install intel-mkl替代openblas)
```shell
 apt install cmake, openblas-devel, lapack-devel, arpack-devel, SuperLU-devel
```
4. 下载并编译armadillo https://arma.sourceforge.net/download.html
5. 编译安装glog\google test\google benchmark
6. 余下步骤和上述一致

**Tips:**
1. google benchmark编译过程中，如果遇到关于gtest缺失的报错，可以在google benchmark的cmake中关闭gtest选项

## 如何运行Yolov5的推理

请在demos文件夹下的yolo_test.cpp文件夹中以下代码进行修改

```cpp
const std::string& image_path = "imgs/car.jpg";
const std::string& param_path = "tmp/yolo/demo/yolov5s_batch8.pnnx.param";
const std::string& bin_path = "tmp/yolo/demo/yolov5s_batch8.pnnx.bin";
```

- `image_path`指定图像目录，`param_path`为模型的参数文件，`bin_path`为模型的权重文件，请替换为自己本地的路径。

- 模型定义和权重下载地址如下： https://cowtransfer.com/s/9bc43e0905cb40 

- 编译完成后，在项目目录调用 `./build/demos/yolo_test`

### 效果图
<img src="https://i.imgur.com/JkZ9KiE.jpg" alt="output0" style="zoom:50%;" />

## 已经支持的算子
**总体理念：逐步优化已经有的算子；有需要的时候再对未实现的算子进行开发**

- Convolution 
- AdaptivePooling 
- MaxPooling 
- Expression(抽象语法树)
- Flatten, View(维度展平和变形)
- Sigmoid 
- HardSigmoid 
- HardSwish 
- ReLU
- Linear(矩阵相乘)
- Softmax 
- BatchNorm
- Upsample
- SiLU
- Concat

## 目录
source是源码目录

1. **data/** 是张量类Tensor的实现和Tensor初始化方法
2. **layer/** 是算子的实现
3. **parser/** 是Pnnx表达式的解析类
4. **runtime/** 是计算图结构，解析和运行时相关

**test**是单元测试目录，基本做到public方法单元测试权覆盖

**bench**是google benchmark, 包含对MobilenetV3, Resnet18和yolov5s的性能测试。

## 性能测试
### 测试设备

15 核心的AMD EPYC 7543(霄龙) 32-Core Processor (Docker 容器，宿主机共有32核心)

### 编译环境

gcc (Ubuntu 9.4.0-1ubuntu1~20.04.1) 9.4.0

### 性能结果
耗时通过连续五次运行,并以求平均的方式计算

| **input size**         | **模型名称**     | **计算设备**              | **耗时**           |
|------------------------| ---------------- | ------------------------- |------------------|
| 224×224 batch = 8      | MobileNetV3Small | CPU(armadillo + openblas) | 6.76ms / image   |
| 224×224 batch = 8      | ResNet18         | CPU(armadillo + openblas) | 23.53ms / image  |
| 224×224 batch =16      | ResNet18         | CPU(armadillo + openblas) | 13.52ms / image  |
| 640×640 batch = 8      | Yolov5nano       | CPU(armadillo + openblas) | 78.37ms / image  |
| **640×640** batch = 8  | **Yolov5s**      | CPU(armadillo + openblas) | 177.54ms / image |
| **640×640** batch = 16 | **Yolov5s**      | CPU(armadillo + openblas) | 134.57ms / image |

## 致谢

推理框架NCNN，已经在借鉴的代码中保留了NCNN的BSD协议 https://github.com/Tencent/ncnn

优秀的数学库Openblas: https://github.com/xianyi/OpenBLAS

优秀的数学库Armadillo: https://arma.sourceforge.net/docs.html

给予我灵感的Caffe框架: https://github.com/BVLC/caffe
