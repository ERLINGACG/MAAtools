# MAAtools


本项目根据 GNU 宽通用公共许可证 v3.0 - 有关详细信息，请参阅 LGPL-3.0 
[`LGPL-3.0`](./LICENSE.md) 文件。

⚠️ **本项目目前处于早期开发阶段，API 可能会发生重大变更，暂不建议用于生产环境**

## 项目概述

基于 [MaaFramework 框架](https://github.com/MaaXYZ/MaaFramework) 的二次开发工具库，提供面 C++ API 封装，包含以下核心模块：

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
▪ 图像识别功能（OCRClick/TemplateMatchClick）  
▪ 调试用测试方法（TestDoSomething 系列）
