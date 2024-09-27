## Keil5项目搭建以及相关配置（STM32F1系列）

### 1.下载模板文件

- 下载模板文件到本地（项目名可以自己命名），模板文件就在仓库中的[模板](https://github.com/krslk/Keil/tree/main/%E6%A8%A1%E6%9D%BF/ProjectName)文件夹下。

<img src=".\Keil5项目搭建.assets\image-20240927112301248.png" alt="image-20240927112301248" style="zoom:50%;" />

### 2.新建项目

1. 打开keil，创建新项目

    <img src="E:\KeilCode_Git\Keil\Keil5项目搭建.assets\image-20240927112411687.png" alt="image-20240927112411687" style="zoom:50%;" />

2. 选择自己刚才下载的模板文件的保存地址下的mdk文件夹（文件名可以与刚才项目名不同，但是推荐相同），保存

    <img src="E:\KeilCode_Git\Keil\Keil5项目搭建.assets\image-20240927112901718.png" alt="image-20240927112901718" style="zoom:50%;" />

3. 选择开发板，这里使用的是`STM32F103ZET6`型号开发板，根据自己的开发板型号选择，点击`OK`。（如果有提示添加`startup_stm32f10x_hd.s`等启动文件选否，因为模板文件中的`startup`文件夹中已经存在。）

    <img src="E:\KeilCode_Git\Keil\Keil5项目搭建.assets\image-20240927113251459.png" alt="image-20240927113251459" style="zoom:50%;" />

4. 完成后会建立如图所示项目文件，这里还需要配置文件组织结构等，点击蓝筐中的图标，进入项目管理。

    ![image-20240927114250374](E:\KeilCode_Git\Keil\Keil5项目搭建.assets\image-20240927114250374.png)

5. 在`Project Targets`中将默认的文件名自己的项目名并在`Groups`下添加四个群组，分别对应项目文件夹中的`user、startup、cmsis、lib`(除`mdk`文件夹)。

    <img src="E:\KeilCode_Git\Keil\Keil5项目搭建.assets\image-20240927114728567.png" alt="image-20240927114728567" style="zoom:67%;" />

6. 在各个群组下添加对应文件,添加`startup`组中文件时将文件类型改为`All files`,以便添加`.s`启动文件，`lib`组中要添加的文件在`src`子文件夹中（均为全选），添加完成如下图所示，点击`OK`。

    <img src="E:\KeilCode_Git\Keil\Keil5项目搭建.assets\image-20240927115431322.png" alt="image-20240927115431322" style="zoom:67%;" />

    <img src="E:\KeilCode_Git\Keil\Keil5项目搭建.assets\image-20240927120114542.png" alt="image-20240927120114542" style="zoom:67%;" />

7. 添加完成如图所示，此时还不能编译，需要配置编译配置

    <img src="E:\KeilCode_Git\Keil\Keil5项目搭建.assets\image-20240927120757620.png" alt="image-20240927120757620" style="zoom: 33%;" />

### 3.配置编译环境

1. 点击如图所示配置目标选项图标

    <img src="E:\KeilCode_Git\Keil\Keil5项目搭建.assets\image-20240927121257127.png" alt="image-20240927121257127" style="zoom:50%;" />

2. 在`Target`选项中勾选`Use MicroLIB`

    <img src="E:\KeilCode_Git\Keil\Keil5项目搭建.assets\image-20240927121413056.png" alt="image-20240927121413056" style="zoom:50%;" />

3. 在`Output`中勾选`Create HEX File`文件以便后续烧录程序，可以自定义输出文件名称。

    <img src="E:\KeilCode_Git\Keil\Keil5项目搭建.assets\image-20240927121605577.png" alt="image-20240927121605577" style="zoom:50%;" />

4. 选择`C/C++`选项卡，添加`Define`内容为(注意英文标点符号)：`USE_STDPERIPH_DRIVER,STM32F10X_HD`，添加`Include Paths`头文件路径，如图所示步骤在`Setup Compiler Include Paths`中添加三条路径，分别对应项目中三个包含`.h`头文件的文件夹。

    <img src="E:\KeilCode_Git\Keil\Keil5项目搭建.assets\image-20240927122732920.png" alt="image-20240927122732920" style="zoom:50%;" />

    <img src="E:\KeilCode_Git\Keil\Keil5项目搭建.assets\image-20240927123346054.png" alt="image-20240927123346054" style="zoom:50%;" />

5. 最后点击`OK`完成配置，至此模板文件中的所有文件均已添加到项目中了。
