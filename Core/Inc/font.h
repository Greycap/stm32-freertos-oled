/*
 * ============================================================
 * 项目集成说明
 * ============================================================
 * 本文件移植自“波特律动OLED驱动”，作为本项目的一部分进行使用。
 * 原作者：keysking（波特律动）
 * 原项目地址：https://docs.baud-dance.com/docs/stm32/example/I2C_OLED/
 * 原项目许可证：MIT License
 *
 * 【特别声明】
 * 本文件（oled.c, oled.h, font.c, font.h）的**核心逻辑、字体数据、
 * 显存缓存机制均完全保留原样，本人未做任何代码修改**。
 *
 * 本项目中与该驱动相关的适配工作说明：
 *   - 在 STM32CubeMX 中配置了硬件 I2C 外设，通信速率为 400KHz。
 *   - 在系统集成层完成了该驱动与 FreeRTOS 任务的对接调用。
 * ============================================================
 */

#ifndef __FONT_H
#define __FONT_H
#include "stdint.h"
#include "string.h"
typedef struct ASCIIFont {
  uint8_t h;
  uint8_t w;
  uint8_t *chars;
} ASCIIFont;

extern const ASCIIFont afont8x6;
extern const ASCIIFont afont12x6;
extern const ASCIIFont afont16x8;
extern const ASCIIFont afont24x12;

/**
 * @brief 字体结构体
 * @note  字库前4字节存储utf8编码 剩余字节存储字模数据
 * @note 字库数据可以使用波特律动LED取模助手生成(https://led.baud-dance.com)
 */
typedef struct Font {
  uint8_t h;              // 字高度
  uint8_t w;              // 字宽度
  const uint8_t *chars;   // 字库 字库前4字节存储utf8编码 剩余字节存储字模数据
  uint8_t len;            // 字库长度 超过256则请改为uint16_t
  const ASCIIFont *ascii; // 缺省ASCII字体 当字库中没有对应字符且需要显示ASCII字符时使用
} Font;

extern const Font font16x16;

/**
 * @brief 图片结构体
 * @note  图片数据可以使用波特律动LED取模助手生成(https://led.baud-dance.com)
 */
typedef struct Image {
  uint8_t w;           // 图片宽度
  uint8_t h;           // 图片高度
  const uint8_t *data; // 图片数据
} Image;

extern const Image bilibiliImg;

#endif // __FONT_H
