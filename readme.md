## stm32智能小车
大三小学期大作业。。。


### 7月2日开发日志
1. 确认我们组的蜂鸣器模块存在问题。
> 问题大概出现在扩展板的Arduino的A3口和扩展板的PC3口之间。。

2. 完成了LED灯模块驱动的代码。

3. 完成了两个电机驱动代码的编写。

4. 完成了Arduino排母和扩展板之间的焊接（防止出现接触不良）
> 在未焊接之前容易出现led灯不亮、电机不动等情况。猜测可能是排母与扩展板之间接触不良。。

5. 在不使用中断的前提之下完成了按键控制小车是否前进的测试。

6. 完成了左右循迹模块的输出驱动小车运动模式的代码框架。
> 目前存在问题：
>> a. 小车运动太快
>>
>> b. 小车转向不灵活
