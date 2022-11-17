import taichi as ti
ti.init(arch=ti.vulkan)
x = ti.ndarray(ti.f32, shape=(8192))


@ti.kernel
def init(x: ti.types.ndarray(field_dim=1)):
    for i in x:
        x[i] = 0

@ti.kernel
def add_base(x: ti.types.ndarray(field_dim=1), base: ti.f32):
    for i in range(x.shape[0]):
        x[i] += base


target_dir = "./asset/"
mod = ti.aot.Module(ti.vulkan)
mod.add_kernel(init, template_args={'x': x})
mod.add_kernel(add_base, template_args={'x': x})
mod.save(target_dir, '')
