# KuiperInfer

## 使用的技术和开发环境
* 开发语言：C++ 17
* 数学库：Armadillo + OpenBlas(或者更快的Intel MKL)
* 加速库：OpenMP
* 单元测试：Google Test
* 性能测试：Google Benchmark

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
