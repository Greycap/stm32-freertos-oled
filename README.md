STM32 FreeRTOS 多任务 OLED 显示系统



基于 STM32F103C8T6 的 FreeRTOS 多任务应用示例，使用 HAL 库与硬件 I2C 驱动 SSD1306 OLED 屏幕，实现系统运行时间的实时显示与 LED 周期闪烁。

&#x20;项目功能

1\. 多任务调度：创建两个同优先级任务，通过 FreeRTOS 的时间片轮转调度机制运行。

2\. 任务1（LED闪烁）：控制板载 LED 周期性闪烁，指示系统运行状态。

3\. 任务2（OLED显示）：实时显示系统运行时间（秒级刷新）。

4\. 硬件I2C驱动：使用 STM32 硬件 I2C 接口，通信速率配置为 400KHz（Fast Mode），降低 CPU 占用。



&#x20;技术亮点与个人贡献

RTOS 任务设计：独立设计两个同优先级任务，使用 `vTaskDelay` 实现任务周期控制，验证时间片轮转调度。

系统集成：使用 STM32CubeMX 完成引脚、时钟、I2C、FreeRTOS 中间件的配置，搭建完整的工程框架。

驱动适配与优化：在 HAL 库基础上适配硬件 I2C 接口（400KHz），替换原有软件模拟 I2C，提升通信效率。



硬件与软件环境

硬件平台：STM32F103C8T6 核心板 + 0.96寸 OLED（SSD1306，I2C接口）

开发环境：STM32CubeMX + Keil MDK (uVision5)

软件库：STM32 HAL 库 + FreeRTOS (CMSIS-RTOS V2)

编程语言：C 语言



&#x20;第三方代码声明

本项目中的 OLED 驱动层文件（`oled.c`、`oled.h`、`font.c`、`font.h`）移植自 \*\*波特律动OLED驱动\*\*，遵循 MIT 开源协议。

原作者：keysking（波特律动）

原项目地址：https://docs.baud-dance.com/docs/stm32/example/I2C\_OLED/ \*(如果你有更精确的 GitHub 仓库地址，请在此处替换)\*

原项目许可证：MIT License

移植者：\[Greycap](https://github.com/Greycap)

本项目中所做的修改与未修改的部分：

继承自原项目：OLED 基础驱动逻辑、字体数据、显存缓存机制（先写缓存再批量刷新，降低 I2C 通信压力）。

&#x20;本人修改/适配：适配 STM32 HAL 库硬件 I2C 接口，将 I2C 通信速率配置为 400KHz。

本人未修改：驱动核心逻辑、字体数据与显存缓存机制保持原样，未做改动。

总结：本项目对驱动层的核心贡献在于HAL 库移植与硬件 I2C 适配，RTOS 双任务设计、系统集成与驱动配置由本人独立完成。



目录结构

```text

├── Core/            # 核心业务代码（main.c, freertos.c, oled.c, i2c.c 等）

├── Drivers/         # STM32 HAL 库与 CMSIS 底层驱动

├── MDK-ARM/         # Keil MDK 工程文件

├── Middlewares/     # FreeRTOS 中间件源码

├── F260908test.ioc  # STM32CubeMX 工程配置文件

└── README.md        # 项目说明文档

