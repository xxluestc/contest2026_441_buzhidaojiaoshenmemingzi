# ESP32-S3-EYE 队伍配置

本目录不是新的 BSP。项目直接复用 `vendor/espressif` 在大赛分支提供的 ESP32-S3-EYE 板级实现，只保存队伍专用的 `defconfig`。

manifest 将：

```text
board/esp32s3-eye/configs/contest2026_441_vision_badge
  → vendor/espressif/boards/esp32s3/esp32s3-eye/configs/contest2026_441_vision_badge
```

队伍配置以大赛分支的 `configs/openvela/defconfig` 为基线，并增加：

- `CONFIG_LVX_USE_DEMO_CONTEST2026_441_VISION_BADGE=y`
- 应用栈、摄像头/音频设备路径、JPEG 和结果缓冲上限。

若上游 ESP32-S3-EYE 配置变化，应先对比并重新生成本文件，而不是静默覆盖。任何 Wi-Fi 密码、API Key 或私钥都不得写入 defconfig。
