#include <taichi/cpp/taichi.hpp>
#include <iostream>

struct App0_tutorial {
  static const uint32_t NPARTICLE = 8192 * 2;
  static const uint32_t N_ITER = 50;

  ti::Runtime runtime_;
  ti::AotModule module_;
  ti::Kernel k_init_;
  ti::Kernel k_add_base_;
  ti::NdArray<float> x_;

  App0_tutorial() {
    runtime_ = ti::Runtime(TI_ARCH_VULKAN);
    module_ = runtime_.load_aot_module("../assets/");
    k_init_ = module_.get_kernel("init");
    k_add_base_ = module_.get_kernel("add_base");
    x_ = runtime_.allocate_ndarray<float>({NPARTICLE}, {}, true);
    std::cout << "Initialized!" << std::endl;
  }

  bool run() {
    float base = 0.2;

    k_init_.push_arg(x_);
    k_init_.launch();
    k_add_base_.push_arg(x_);
    k_add_base_.push_arg(base);
    for (int i = 0; i < N_ITER; i++) {
      k_add_base_.launch();
    }
    runtime_.wait();
    return true;
  }
};

int main(int argc, const char** argv) {
  App0_tutorial app;
  app.run();
  return 0;
}
