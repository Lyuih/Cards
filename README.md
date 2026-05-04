# Cards - 纸牌匹配消除游戏

基于 **Cocos2d-x 3.17** 开发的纸牌匹配消除游戏，采用 **MVC 架构**。

## 目录

- [如何运行](#如何运行)
- [项目介绍](#项目介绍)
- [界面介绍](#界面介绍)
- [游戏规则](#游戏规则)
- [项目架构](#项目架构)
- [待实现功能](#待实现功能)

---

## 如何运行

### 环境要求

- Visual Studio 2019/2022（Windows）
- CMake 3.6+
- Python 2.7（Cocos2d-x 构建脚本依赖）

### Windows 构建步骤

1. **克隆项目并初始化子模块**

```bash
git clone https://github.com/Lyuih/Cards.git
cd Cards
git submodule update --init --recursive
```

2. **打开解决方案**

直接打开 `proj.win32/Cards.sln`，在 Visual Studio 中编译运行。

3. **CMake 方式构建**

```bash
mkdir build && cd build
cmake ..
cmake --build .
```

4. **运行**

编译成功后运行 `proj.win32/Debug.win32/Cards.exe`。

### 关卡配置

关卡文件位于 `Resources/levels/` 目录下，当前为 `level_1.json`。可通过修改 JSON 配置新增关卡，调用 `startLevel(levelId)` 切换。

---

## 项目介绍

这是一个纸牌匹配消除游戏。玩家从主牌区选择纸牌，与手牌区顶部的牌进行匹配（点数差 1 即可消除），并支持撤销回退操作。

### 核心玩法

- 主牌区有若干张翻开的纸牌
- 手牌区有一张底牌
- 点击主牌区的牌，如果点数比手牌顶牌大 1 或小 1，则匹配成功
- 匹配成功后，被点击的牌飞到手牌区成为新的顶牌
- 主牌区全部消除即为通关

### 开发技术栈

| 技术 | 说明 |
|------|------|
| Cocos2d-x 3.17 | 游戏引擎 |
| C++ | 开发语言 |
| MVC | 软件架构模式 |
| RapidJSON | JSON 解析库 |
| CMake | 构建系统 |

---

## 界面介绍

游戏分辨率为 **1080 × 2080**（竖屏），界面分为以下区域：

```
┌─────────────────────┐  y=2080
│                     │
│    主牌区 (深绿色)    │
│                     │
│  六张纸牌排列成      │
│  倒 V / 形          │
│                     │
│                     │
├─────────────────────┤  y=580
│  牌堆区 (更深绿色)    │
│                     │
│  [备用牌堆] [手牌区] │
│                     │
└─────────────────────┘  y=0
```

### 主牌区（上半部分）

- 展示待消除的纸牌，当前关卡为 6 张
- 纸牌按倒 V 形排列，每张牌可独立点击操作
- 所有牌均为翻开状态（正面朝上）

### 牌堆区（下半部分）

- **备用牌堆**（左侧）：存放待抽取的牌，主牌区无可匹配牌时可从中翻新牌
- **手牌区**（右侧）：显示当前手牌顶牌，匹配成功时新牌飞入此处

### 控制按钮

- **Undo 按钮**（右上角）：撤销上一步匹配操作

---

## 游戏规则

### 匹配规则

1. **点击主牌区**中翻开的纸牌
2. 选中牌的**点数比手牌顶部牌大 1 或小 1** 则匹配成功
3. 没有花色限制（任意花色均可匹配）
4. 匹配的牌平移到手牌区，替换成为新的顶牌

### 匹配示例

| 手牌顶牌 | 可匹配的牌 |
|----------|-----------|
| 8 (Eight) | 7 或 9 |
| 5 (Five) | 4 或 6 |
| A (Ace) | 2 |
| K (King) | Q |

### 撤销规则

- 每次匹配操作都记录在撤销栈中
- 点击 Undo 反向移动卡牌回原来的位置
- 可连续多次撤销

### 备用牌堆

当主牌区没有可匹配的牌时，可从备用牌堆翻一张新手牌。

---

## 项目架构

项目采用 MVC（Model-View-Controller）架构，代码结构如下：

```
Classes/
├── configs/         # 静态配置
│   ├── models/      # 配置数据结构 (LevelConfig, CardResConfig)
│   └── loaders/     # 配置加载逻辑 (LevelConfigLoader)
├── models/          # 运行时数据模型
│   ├── CardModel.h    # 单张卡牌（ID、花色、点数、朝向）
│   ├── CardDeckModel.h # 牌堆容器
│   ├── GameModel.h    # 游戏整体状态
│   ├── UndoModel.h    # 撤销/重做栈
│   └── UndoAction.h   # 撤销动作记录
├── views/           # 视图层（界面显示）
│   ├── CardView.h     # 单张卡牌的视觉表现
│   ├── CardDeckView.h # 牌堆视图容器
│   ├── GameView.h     # 游戏主视图
│   ├── HUDView.h      # 按钮等界面元素
│   └── DeckLayoutInfo.h # 牌堆布局配置
├── controllers/     # 控制器层
│   ├── GameController.h  # 主游戏流程控制
│   ├── CardController.h  # 卡牌交互逻辑
│   └── HUDController.h   # HUD 事件处理
├── managers/        # 管理器
│   ├── UndoManager.h  # 撤销功能管理
│   └── SaveManager.h  # 存档管理（待实现）
├── services/        # 无状态服务
│   ├── MoveValidator.h      # 移动合法性校验
│   └── GameModelGenerator.h # 关卡配置转运行时模型
└── utils/           # 工具类
```

### 数据流

```
关卡 JSON
  ↓ LevelConfigLoader
LevelConfig（静态配置）
  ↓ GameModelGenerator
GameModel（运行时数据模型）
  ↓ bindModel()
CardDeckView / CardView（视图展示）
  ↓ 用户点击 → 回调
CardController（业务逻辑处理）
  ↓ 更新 Model + 驱动 View 动画
```

### 设计原则

- **models 层**：只存储数据，不包含业务逻辑
- **views 层**：只负责显示，不包含业务逻辑
- **controllers 层**：协调 model 和 view，处理用户操作
- **managers 层**：可持有 model 数据，作为 controller 的成员，禁止单例
- **services 层**：无状态服务，不持有数据，可单例或静态方法

---

## 待实现功能

### 1. 游戏胜利和失败判定

  - **胜利条件**：主牌区和备用牌堆全部清空
  - **失败条件**：主牌区无牌可匹配且备用牌堆为空
  - **UI 反馈**：弹出胜利/失败提示框，提供重玩或返回菜单选项

### 2. 存档功能

  - 完整的 GameModel 序列化/反序列化
  - 本地文件读写（自动存档 / 读档）
  - 游戏恢复：重新打开应用时回到上次进度

### 3. 实现关卡选择界面

- 添加多个 JSON 关卡文件

