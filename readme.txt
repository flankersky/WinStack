说明：
	代码完全是从ReactOS-0.3.15上拿来的。除了修改了几处编译时的error外，无其它任何修改。
	尝试移植此协议栈的目的，只是为了测试有没有移植开源协议栈到windows下的可能。所以，对于协议栈的安装及卸载时出现的问题，
	如果以后本人还继续研究的话，会进一步完善之。
	
编译步骤：
	测试环境：win7 x64版本，WDK-7600.**** ,测试环境 WinXP SP3(务必要在虚拟机环境中进行测试)。
	对于卸载xp sp3下的协议栈的方法，可以参考此处。
	
	<a> 首先编译lwip。
		cd lwip/src/api; build
		cd lwip/src/core/ipv4; build
		cd lwip/src/core/snmp; build
		cd lwip/src/core; build
		cd lwip/src; build
	<b>
		cd #代码根目录#; build
测试：
	生成的sys会在objs/i386下；
	用reactos的nettcpip.inf测试，安装失败。
	用xp的nettcpip.inf测试，安装失败。
	用DriverMonitor 用Driverstudio可以安装，测试可以生成\DEVICE\Tcp等设备对象。调试发现，驱动对象也会接收到上层发来的IRP请求。
	但是在卸载的时候偶尔会出现BSOD的情况。