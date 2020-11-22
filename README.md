README
---

dwm 是一个快速, 小巧并使用动态管理窗口的窗口管理器

[dwm项目主页](https://suckless.org/dwm)  
dwm 安装：

    git clone https://git.suckless.org/dwm

这个仓库下的dwm是我在TheCW的dwm配置基础上进行定制的版本  
- TheCW配置的版本在[这里](https://github.com/theniceboy/dwm)  
- 大佬的脚本存放在 [此仓库](https://github.com/theniceboy/scripts)  
- 我在大佬基础上修改过的脚本在[这里](https://github.com/hyl-xidian/scripts)

### 向偶然看到这个页面的朋友安利一波
**TheCW是一名b站up主，现在频道上主要发布一些关于linux的教学和安利视频，干货满满。大佬是个重度vimer，还是个学霸加帅哥！**
[大佬b站主页戳这里](https://space.bilibili.com/13081489/)


### 介绍
TheCW大佬用的是colemak键盘，并非常人用的qwert。  
我的改动大部分都是关于快捷键改键的,也修改了一些小细节。  
不想折腾的朋友可以直接用我改好的configure.h文件

-------------

个人dwm 快捷键备忘
---
### 一、基础操作
| 快捷键                   | 操作                                         |
|--------------------------|----------------------------------------------|
| win + j                  | 顺时针切换focus的窗口                        |
| win + k                  | 逆时针切换focus的窗口                        |
| win + shift + j/k        | focus当前窗口 顺/逆时针 旋转调整所有窗口位置 |
| win + h/l                | 向左/右 切换focus的桌面（标签页tap）         |
| win + shift + h/l        | 将focus的窗口 移动到左/右侧的桌面中          |
| 新的排列顺序遵从栈的规则 |                                              |
| win + 数字               | 切换到对应的标签页面                         |
| win + shift + num        | 将focus的页面切换到第num桌面的主窗口位置     |
| win + shift + u/i        | 改变窗口布局( 可改成垂直布局慎用！)          |
| win + u/i                | 改变focus的窗口的尺寸                        |
| win + ,/.                 | focus到前一个或下一个显示器                  |
| win + shift + ,/.        | 将当前focus的窗口移动到前一个或下一个显示器  |

### 二、进阶操作
| 快捷键          | 操作                                 |
|-----------------|--------------------------------------|
| win + m         | 将focus的窗口占据整个屏幕            |
| win + space     | 恢复原有的平铺格局                   |
| win + n         | 隐藏focus的窗口                      |
| win + shift + n | 恢复隐藏的窗口                       |
| win + '         | 屏幕中间打开一个窗口(再次按下则恢复) |
| win + p         | 隐藏其他所有的窗口                   |
| win + shift + p | 恢复隐藏的窗口                       |
| win + shift + e | 将当前focus窗口全屏                  |

### 三、其他操作
| 快捷键          | 功能                 |
|-----------------|----------------------|
| win + q         | 关闭一个窗口         |
| win + ctrl + q  | 关闭xserver 慎用！！ |
| win + crtl + l  | 锁屏幕               |
| win + crtl + r | suspend              |
| win + b         | 切换壁纸             |
| win + [         | 减少音量             |
| win + \         | 静音                 |
| win + t         | 关闭触摸板           |
| win + shift + t | 打开触摸板           |

### 四、改动备忘

1. 开启Xserver后会自动将caps大写锁定键跟esc互换----->
    - 将caps-swapescape.sh添加到了auto_start.sh中
2. 添加了触摸板禁用和启用的脚本 ----->
    - 暂时定为快捷键win + t 和win + shift + t
