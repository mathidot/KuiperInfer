// MIT License
// Copyright (c) 2022 - 傅莘莘
// Source URL: https://github.com/zjhellofss/KuiperInfer
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
    
// Created by fss on 23-2-2.
#include <benchmark/benchmark.h>
#include "runtime/runtime_ir.hpp"
const static int kIterationNum = 5;

static void BM_Yolov5nano_Batch4_320x320(benchmark::State &state) {
  using namespace kuiper_infer;
  RuntimeGraph graph("tmp/yolo/demo/yolov5n_small.pnnx.param",
                     "tmp/yolo/demo/yolov5n_small.pnnx.bin");

  graph.Build("pnnx_input_0", "pnnx_output_0");
  const uint32_t batch_size = 4;
  std::vector<std::shared_ptr<Tensor<float>>> inputs;

  for (int i = 0; i < batch_size; ++i) {
    std::shared_ptr<Tensor<float>> input = std::make_shared<Tensor<float>>(3, 320, 320);
    input->Ones();
    inputs.push_back(input);
  }

  for (auto _ : state) {
    std::vector<std::shared_ptr<Tensor<float>>> outputs = graph.Forward(inputs, false);
  }
}

static void BM_Yolov5s_Batch4_640x640(benchmark::State &state) {
  using namespace kuiper_infer;
  RuntimeGraph graph("tmp/yolo/demo/yolov5s_batch4.pnnx.param",
                     "tmp/yolo/demo/yolov5s_batch4.pnnx.bin");

  graph.Build("pnnx_input_0", "pnnx_output_0");
  const uint32_t batch_size = 4;
  std::vector<std::shared_ptr<Tensor<float>>> inputs;

  for (int i = 0; i < batch_size; ++i) {
    std::shared_ptr<Tensor<float>> input = std::make_shared<Tensor<float>>(3, 640, 640);
    input->Ones();
    inputs.push_back(input);
  }

  for (auto _ : state) {
    std::vector<std::shared_ptr<Tensor<float>>> outputs = graph.Forward(inputs, false);
  }
}

static void BM_Yolov5s_Batch8_640x640(benchmark::State &state) {
  using namespace kuiper_infer;
  RuntimeGraph graph("tmp/yolo/demo/yolov5s_batch8.pnnx.param",
                     "tmp/yolo/demo/yolov5s_batch8.pnnx.bin");

  graph.Build("pnnx_input_0", "pnnx_output_0");
  const uint32_t batch_size = 8;
  std::vector<std::shared_ptr<Tensor<float>>> inputs;

  for (int i = 0; i < batch_size; ++i) {
    std::shared_ptr<Tensor<float>> input = std::make_shared<Tensor<float>>(3, 640, 640);
    input->Ones();
    inputs.push_back(input);
  }

  for (auto _ : state) {
    std::vector<std::shared_ptr<Tensor<float>>> outputs = graph.Forward(inputs, false);
  }
}

BENCHMARK(BM_Yolov5nano_Batch4_320x320)->Unit(benchmark::kMillisecond);
BENCHMARK(BM_Yolov5s_Batch4_640x640)->Unit(benchmark::kMillisecond);
BENCHMARK(BM_Yolov5s_Batch8_640x640)->Unit(benchmark::kMillisecond);