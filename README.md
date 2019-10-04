# QEMU-BitmapTrace
QEMU BitmapTrace mechanism for profiling VM memory accesses ("shadow" Migration)  
*Currently supports pre-copy technique only (without optimizations)*

<br />

QMP  command example: 

1) Verify that QEMU started in KVM mode as well as QMP on a TCP socket, so that telnet can be used : 
```
$ qemu […] -enable-kvm […] -qmp tcp:localhost:4444,server,nowait 
```
2) Run telnet 
```
$ telnet localhost 4444 
```
3) You should see QMP's greeting banner : 
```
{"QMP": {"version": {"qemu": {"micro": 0, "minor": 6, "major": 1}, "package": ""}, "capabilities": []}}
```
4) Issue the qmp_capabilities command, so that QMP enters command mode : 
```
{ "execute": "qmp_capabilities" }  
```
5) You can now issue commands. So, to enable BitmapTrace mechanism, you should issue  bitmap-trace with the appropriate arguments, as shown below: 
```
{ "execute": "bitmap-trace", "arguments": { "state": true, "filename": "/home/user/dirty_pages_profiling.log", "iterations": 10, "period": 1000 } } 
```
6) Once BitmapTrace is finished successfully, results are displayed on HMP and are logged to filename specified. 

<br />
<br />

QEMU monitor(or HMP) command example: 

1) Verify that QEMU started in KVM mode : 
```
$ qemu […] -enable-kvm 
```
2) With “help bitmap-trace", you can get details the command: 
```
(qemu) help bitmap-trace  

bitmap-trace state filename iterations period -- Enable/Disable the bitmap tracking mechanism 

   filename: file where the dirty pages per iteration will be logged 

   iterations: number of times the dirty pages will be logged 

   period: time interval in milliseconds between two consecutive iterations 
```
3) Enable BitmapTrace mechanism, by issuing “bitmap-trace” with the appropriate arguments 
```
(qemu) bitmap-trace on "/home/user/dirty_pages_profiling.log" 10 1000 
```
4) Once BitmapTrace is finished successfully, results are displayed on HMP and are logged to filename specified. 

<br />
<br />

The arguments for using BitmapTrace commands are the following: 

**state**: trace enabled or disabled(on/off) (mandatory) 

**filename**: name of the file where the dirty pages per iteration will be logged (mandatory) 

**iterations**: number of times the dirty pages will be logged. The min and max values are 3 and 100000 respectively. The default value is 3, if the “iterations” parameter is not stated. 

**period**: time interval in milliseconds between two consecutive iterations. The min and max values are 10 and 100000 respectively. The default value is 10, if the “period” parameter is not stated. 
