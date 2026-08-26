# 基于 openvela 的视障随行视觉辅助胸牌

> 2026 首届 openvela AI 硬件开发者大赛 · 队伍 441 · AI 硬件产品创新赛道

面向具有独立出行能力的视障用户，项目拟用 **ESP32-S3-EYE** 制作免手持视觉辅助胸牌。在用户到达目标区域后，设备按需拍摄前方场景，通过 Wi-Fi 将单帧 JPEG 发送至 MiMo 多模态服务，识别入口、门牌、站点标识和公共服务设施，并以语音或振动反馈关键信息。

当前仓库处于“方案冻结、应用骨架已建立、完整 openvela 构建与真机待验证”阶段。未完成的摄像头取帧、云端请求、语音和振动后端会明确返回 `-ENOSYS`，不会伪造硬件结果。

## 一、为什么选择 ESP32-S3-EYE

ESP32-S3-EYE 已有 openvela/NuttX BSP 和官方构建配置，并集成摄像头、数字麦克风、LCD、Wi-Fi 和外部 PSRAM。项目因此不宣称“新增 ESP32-S3-EYE 平台移植”，而把工作集中在：

- V4L2 单帧采集与 JPEG 数据管理；
- Wi-Fi/HTTPS 与 MiMo 多模态请求；
- 板载麦克风采集和外接 I2S 音频输出；
- GPIO/PWM 振动反馈；
- Camera、JPEG、TLS、JSON、Audio 并行时的峰值内存与碎片控制。

详细规划见 [docs/项目开发规划.md](docs/项目开发规划.md)。

## 二、最小技术闭环

```text
用户触发
  → ESP32-S3-EYE Camera
  → /dev/video0（V4L2 单帧）
  → JPEG
  → Wi-Fi / HTTPS
  → MiMo Vision
  → 有界结构化结果
  → 控制台 / 语音 / 振动反馈
```

第一阶段不持续上传视频，也不在端侧部署大型视觉模型。M1～M6 的可验收定义见 [docs/MVP验收标准.md](docs/MVP验收标准.md)。

## 三、目录结构

```text
├── app/vision_badge/       # 原生应用、服务接口和闭环状态机
├── board/esp32s3-eye/      # 队伍专用 board config 与使用说明（非新 BSP）
├── docs/                   # 规划、架构、资源预算、验收与测试场景
├── logs/                   # 按大赛规范导出的 AI Coding 日志
├── scripts/                # 环境检查、构建、烧录、串口监视
└── contest2026_441_buzhidaojiaoshenmemingzi.xml
                            # repo manifest 与 linkfile 映射
```

模板中的 `hello_app`、快应用和虚拟板级示例已移除，避免评委把无关样例误认为作品内容。

## 四、拉取、构建与运行

### 1. 拉取完整 openvela 工作区

```bash
repo init -u https://github.com/open-vela/contest2026_441_buzhidaojiaoshenmemingzi \
  -b dev-ai-contest-2026 -m contest2026_441_buzhidaojiaoshenmemingzi.xml
repo sync -c -j8
```

同步后，队伍仓位于工作区的 `contest2026_441_buzhidaojiaoshenmemingzi/`，`nuttx/`、`packages/`、`vendor/` 等公共仓位于其上一级。

### 2. 检查环境并构建

```bash
cd contest2026_441_buzhidaojiaoshenmemingzi
bash scripts/check-env.sh
bash scripts/build.sh -j8
```

队伍 manifest 会做两项映射：

- `app/vision_badge` → `packages/demos/contest2026_441_vision_badge`
- 队伍专用 defconfig → `vendor/espressif/boards/esp32s3/esp32s3-eye/configs/contest2026_441_vision_badge`

该 defconfig 基于大赛分支现有 ESP32-S3-EYE `openvela` 配置，并启用 `vision_badge`。预期固件产物为 `../nuttx/nuttx.bin`；当前仓尚未同步整套工作区，因此本次只完成源码级检查，完整固件构建仍待执行并留存日志。

### 3. 烧录与串口

```bash
bash scripts/flash.sh /dev/ttyACM0
bash scripts/monitor.sh /dev/ttyACM0
```

进入 NSH 后可先运行：

```text
vision_badge status
vision_badge selftest
```

`status` 只报告真实设备节点探测结果。`run` 命令要到 M3/M5/M6 后端完成后才形成有效闭环。

## 五、当前进度

| 项目 | 状态 | 证据 |
| --- | --- | --- |
| 方案、功能边界与板卡选择 | 已冻结 | `docs/项目开发规划.md` |
| 应用构建接入与模块接口 | 已完成骨架 | `app/vision_badge/` |
| 队伍专用 ESP32-S3-EYE 配置 | 已建立 | `board/esp32s3-eye/` |
| 完整 openvela 固件构建 | 待验证 | 后续构建日志 |
| M1～M6 最小视觉闭环 | 待真机逐项验证 | `docs/MVP验收标准.md` |
| M7～M10 完整语音交互 | 第二阶段 | `docs/MVP验收标准.md` |

## 六、安全与 AI Coding 说明

- Wi-Fi SSID/密码、MiMo API Key、证书私钥不得写入代码、defconfig、文档或日志；运行期凭据采用串口或受控配置注入。
- 公共 `nuttx`、`packages`、`vendor` 的后续改动按比赛规则单独走上游 PR；队伍仓仅保存自身代码、配置、补丁和证据。
- AI 用于需求拆解、方案核查、接口骨架、资源预算和文档生成。真实导出的会话日志按 [logs/README.md](logs/README.md) 归档，提交前人工检查敏感信息。

仓库提交采用“本地变更 → 团队审核 → commit/push → Pull Request”的顺序；未经审核的内容不推送。
