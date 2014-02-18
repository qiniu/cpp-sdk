Qiniu C++sdk

Windows :

主工程
依赖：boost，openssl，curl，zlib 第三方库。


由于boost头文件太大，3rdParty/include/ 下缺少boost库的头文件 当要编译的时候，
请下载boost库将头文件放在3rdParty/include下，或者设定在项目中配置头文件引用。其版本为boost1.55
其他需要的第三方库，在vs2012下，已经编译好了。

visual studio 2102 是默认的IDE。
在其下：已经编译了需要的第三方库。
工程使用要的编译的boost库放在 3rdParty/lib/windows 下（使用静态链接，无dll)
openSSL, curl, zlib 头文件放在 3rdPartyinclude/windows下
openSSL  curl, zlib lib文件放在3rdParty/lib/windows下
openssL, curl, zlib dll文件放在bin/windows/vs2012下

测试工程：
依赖：主工程，和gtest第三方库
visual studio 2102 是默认的工程。
gtest 头文件放在 3rdParty/include下
gtest lib文件放在3rdParty/lib/windows下（使用静态链接，无dll)

Mac OS X :

Xcode是默认IDE。

主工程：

依赖：boost 第三方库。（openssl，curl，zlib Mac OS X系统已经提供）
请下载boost，并编译。


测试工程：
依赖：主工程，和gtest第三方库
请下载gtest，并编译。


linux :

Netbeans 7.4 是默认IDE。

主工程：

依赖：boost openssl，curl，zlib
请下载 boost openssl，curl，zlib，等第三方库。（可以下载源代码自己编译，也可用类似apt-get，yum 得到开发包)

测试工程：
依赖：主工程，和gtest第三方库
请下载 test等第三方库.（可以下载源代码自己编译，也可用类似apt-get，yum 得到开发包)
