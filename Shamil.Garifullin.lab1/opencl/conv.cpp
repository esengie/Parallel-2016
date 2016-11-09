#include <chrono>
#include <iostream>
#include <fstream>
#include <algorithm>

#include <CL/cl.h>
#include <CL/cl.hpp>

#include "conv.h"


matrix create_matrix(size_t n) {
	matrix res;
	ELEM** arr = new ELEM*[n];
	ELEM* buf = new ELEM[n * n];
	for (int i = 0; i < n * n; ++i) {
		buf[i] = 0;
	}
	for (size_t i = 0; i < n; ++i) {
		arr[i] = buf + i * n;
	}

	res.dim = n;
	res.arr = arr;
	return res;
}

matrix compute(matrix const& a, matrix const& b) {
  std::vector<cl::Platform> platforms;
  std::vector<cl::Device> devices;
  std::vector<cl::Kernel> kernels;

  cl::Platform::get(&platforms);
  platforms[0].getDevices(CL_DEVICE_TYPE_GPU, &devices);

  cl::Context context(devices);
  cl::CommandQueue queue(context, devices.front());

  std::ifstream cl_program("conv.cl");

  std::string code(std::istreambuf_iterator<char>(cl_program), (std::istreambuf_iterator<char>()));

  cl::Program::Sources sourceCode(1, std::make_pair(code.c_str(), code.length() + 1));
  cl::Program program(context, sourceCode);

  program.build(devices);

  matrix c = create_matrix(std::max(a.dim, b.dim));

  size_t a_buf_size = sizeof(ELEM) * a.dim * a.dim;
  size_t b_buf_size = sizeof(ELEM) * b.dim * b.dim;
  size_t c_buf_size = sizeof(ELEM) * c.dim * c.dim;

  cl::Buffer dev_in_a(context, CL_MEM_READ_ONLY, a_buf_size);
  cl::Buffer dev_in_b(context, CL_MEM_READ_ONLY, b_buf_size);
  cl::Buffer dev_output(context, CL_MEM_WRITE_ONLY, c_buf_size);

  queue.enqueueWriteBuffer(dev_in_a, CL_TRUE, 0, a_buf_size, &a.arr[0][0]);
  queue.enqueueWriteBuffer(dev_in_b, CL_TRUE, 0, b_buf_size, &b.arr[0][0]);
  queue.flush();

  cl::Kernel kernel(program, "eval");
  kernel.setArg(0, dev_in_a);
  kernel.setArg(1, dev_in_b);
  kernel.setArg(2, dev_output);
  kernel.setArg(3, int(a.dim));
  kernel.setArg(4, int(b.dim));

  queue.enqueueNDRangeKernel(kernel, 0, cl::NDRange(c.dim * c.dim));
  queue.enqueueReadBuffer(dev_output, CL_TRUE, 0, c_buf_size, &c.arr[0][0]);

  cl_program.close();
  return c;
}
