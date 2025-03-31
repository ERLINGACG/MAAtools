# MAAtools


本项目根据 GNU 宽通用公共许可证 v3.0 - 有关详细信息，请参阅 LGPL-3.0 
[`LGPL-3.0`](./LICENSE.md) 文件。

⚠️ **本项目目前处于早期开发阶段，API 可能会发生重大变更，暂不建议用于生产环境**

## 项目概述

基于 [MaaFramework 框架](https://github.com/MaaXYZ/MaaFramework) 的二次开发工具库，提供对原有的 C++ API 进行二次封装，包含以下核心模块：

### 核心功能模块
▫ **控制器管理**  
- 控制器实例生命周期管理（创建/销毁）
- 设备连接状态监控（WaitConnect）
- 控制器句柄与 ID 管理

▫ **资源管理**  
- 资源路径配置（SetResoursePath）
- 资源加载状态监控（WaitResource）
- 资源句柄与 ID 管理

▫ **任务系统**  
- 任务实例生命周期管理（创建/销毁）
- 任务处理器初始化（TaskerInit）
- 多任务提交接口（PostTask/PostTaskOnce）
- 任务状态追踪（GetTaskerDetial）

### 实验性功能
▪ 二次封装原有的图像识别功能（OCRClick/TemplateMatchClick）  
▪ 调试用测试方法（TestDoSomething 系列）

### 当前状态
`开发预览版 0.x`  
⚠️ 注意：
- 核心 API 仍在持续开发中
- 存在未完善的接口定义(以及可能出现的拼写错误，本人英语不好，见谅)
- 部分功能尚未通过完整测试
- 暂不建议用于生产环境

### 🙏 致谢
- 特别感谢 [**MAA Framework**](https://github.com/MaaXYZ/MaaFramework) 开源的核心技术
- 以及所有对MaaFramework框有所贡献的开发者
