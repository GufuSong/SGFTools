README

# SongGuFu Effect Tools 使用文档



## 前言

> 本插件完全开源，旨在为特效个人开发者提供一套相对完整的生产环境支持方案。其核心目标是在灵感出现的第一时间，帮助你快速进入创作流程，而不必因为缺乏 Shader、Niagara Content等基础系统而停滞在起步阶段。
>
> 同时，也希望为正在求职或进行作品测试的开发者减少环境搭建成本，将精力更多集中在视觉表现与美术创作本身，而不是分散在工具链与实现方案的搜索与搭建上。




### 引擎适配版本

- 插件目前支持 Unreal Engine 5.7 及以上版本;



### 当前最新版本 :  可行性测试版 - v 260627001

- 已实现功能 :

  - 材质实例  Hierarchy Details 高级细节面板 ;
  - 通用 Shader 与  序列帧播放材质

  

- 待实现功能 :

  - Niagara Group ;

  > 批量管理 Niagara Emitter 的工具;

  - Niagara Emitter 模板 ;
  - simple shader 模板 ;
  - 可视化性能优化工具 ;







---

## Ⅰ. Material 材质系统

### $. Hierarchy Details 高级细节面板

> - 传统的 Material Instance 会将所有模块参数平铺在同一个界面中。当模块数量增多时，大量参数会集中堆叠，导致查找、调整和维护成本显著增加。
>
> - SGF Effect Tools 提供的 **Hierarchy Details** 高级细节面板解决了这一痛点。它会将所有模块以层级结构排列在界面上方，强化模块之间的可视化关系，使参数管理更加清晰、高效。
>
> - 用户可以在任意 Material Instance 编辑器上方的 **Window** 菜单中打开 **Hierarchy Details** 面板。







### Ⅱ. M_SongGuFuGeneric_VFX_v1 通用特效Shader使用文档

##### &. 参数体系概述

> 参数的命名规则为 :  功能 _ 作用域



**1. 功能词缀概述 :**

- `UVScale&Panner` :  作用于UV ,  R , G 控制 UV范围 与 偏移 ;
- `UVSpeed&Strech` :  控制UV 偏移速度 ( 此参数与 Time 耦合) ,  Strech ,  控制UV拉伸 (指数) .

- `InTex` :  输入纹理 ;
- `Noise Intensity` :  扭曲强度 ;
- `Color` :  调整纹理颜色 ;
- `Color Adjust` :  参照Allen的函数 ,  `lerp(power(Tex , X) * Y , Tex * Z , W)` ;





- `Select Blend Mode` :  选择混合模式 .

  - `Multiply` :  使用乘法混合 .

  - `Add` :  使用加法混合 .

  - `Blend_overlay` :  使用更复杂的混合方法 .

  - `Min` :  取最小值 .

  - `Max` :  取最大值 .

  - `Lerp_0.5` :  线性插值 0.5 ;





##### &. 010_BASESETTING

- `GenericVFX` :  启用通用特效Shader ;
- `SequenceFrame` :  启用序列帧Shader ;



##### &. GenericVFX

> 通用 shader 概述 :
>
> - 采用了模块化的思想 ,  将所有功能划分为 Noise ,  Mask(Opacity) ,  Texture ,  Specular ,  MeshFresnel ,  Dissolve ,  Refraction .
> - 启用模块的数量决定Shader 的 instructions数量与材质分支数量 ;
> - shader 支持 运行中数据可视化 ,  可以在调整参数的过程中直接可视化浏览纹理渲染结果 .



###### 110_GlobalUV

> 全局UV控制 ,  控制接下来所有模块使用的uv数据 .



**1. 参数列表 :**

- `Enable Polar Coordinates` :  是否启用极坐标系 ?
- `Filp_UV` :  镜像 / 翻转 UV
  - `None Filp` :  不反转UV ;
  - `Filp X` :  仅翻转 X 轴 ;
  - `Filp Y` :  仅反转 Y 轴 ;
  - `Filp XY` :  全部反转 



###### 120_UV Noise

> 本模块可以根据需求 ,  在静态编译阶段选择是否启用 ,  最低可以直接不启用 ,  最高可以采样 2 张 noise 贴图 .
>
> 支持 5 种混合模式 



- `UVInstance_Noise` :  分别控制UV 两个通道的扭曲强度 .
- `NormalStrength` :  控制`Normal` 贴图的强度 .
- `Select Blend Mode` :  选择混合模式 .
  - `Multiply` :  使用乘法混合 .
  - `Add` :  使用加法混合 .
  - `Blend_overlay` :  使用更复杂的混合方法 .
  - `Min` :  取最小值 .
  - `Max` :  取最大值 .
  - `Lerp_0.5` :  线性插值 0.5 ;



###### 150_Tex

> 核心模块 ,  纹理采样模块 .  
>
> - 主要纹理的像素信息会写进Opacity ,  并且与 Mask 模块 (可选项) 进行混合 .
> - 第二与第三纹理采样只会影响最终输出的颜色 ,  不会对Opacity 产生影响 .
> - 三层纹理的混合关系为层级堆叠关系 ,  同样支持五种混合模式 .



- `select color mode` :  选择使用 多通道 还是 单通道纹理 .
  - `RGB` :  使用多通道颜色贴图 .
  - `R` :  使用R通道 ;
  - `G` :  使用G通道 ;
  - `B` :  使用B通道 ;
  - `A` :  使用A通道 ;



- `Desaturation` :  在`select color mode` 为 `RGB` 时 ,  控制他的饱和度 .



###### 140_Mask

> 对Main Tex 写入的 Opacity 进行混合 .
>
> - 为了兼顾性能 ,  Mask 模块采取了隐式几何图案 机制 ,  可以避免GPU 在采样纹理时造成的带宽瓶颈 , 只读取Uniform buffer的数据 .
> - 如果选择使用纹理控制Mask ,  隐式几何图形与纹理的混合方式为乘法 .



-  `Use Implicit Geometry` :  使用隐式几何图形 .
- `Select Mask` :  选择隐式几何图形 :
  - `0_BaseTextureMask` :  仅仅使用基础纹理 ,  当`Use Implicit Geometry` 为 Ture 时 ,  结果为 1 .
  - `1_BaseSphere` :  圆形 .
  - `2_WeaponMask` :  刀光专用模式 ,  模型首尾淡入淡出 .
  - `3_UVMask` :  UV方向混合遮罩 .
  - `4_UMask` :  U 方向遮罩 .
  - `5_VMask` :  V方向遮罩 .
- `Center Point && Radial && Hardness &&SphereMask` 

##### &. SequenceFrame 



