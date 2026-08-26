# vision_badge 应用骨架

该目录通过队伍 manifest 映射到
`packages/demos/contest2026_441_vision_badge`，提供 ESP32-S3-EYE
视障视觉辅助胸牌的 openvela 原生应用骨架。

当前版本固定了四个服务边界：

- `camera_service`：V4L2 设备探测与单帧 JPEG 采集接口；
- `vision_service`：MiMo 图像问答请求与有界结果接口；
- `audio_service`：板载麦克风 PCM 采集接口；
- `feedback_service`：控制台、语音和振动反馈接口。

除设备节点探测和控制台反馈外，硬件/云端后端暂时明确返回 `-ENOSYS`，
避免把未经过真机验证的占位逻辑标成已完成。命令行入口为：

```text
vision_badge status
vision_badge selftest
vision_badge run "入口在哪里"
```

`run` 已串起“采集 → 云端理解 → 反馈”的状态机；在 M3、M5、M6
后端依次实现前，它会在对应阶段失败并输出错误，而不会返回伪造结果。
