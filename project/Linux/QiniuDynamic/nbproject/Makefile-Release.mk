#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/1102919413/CurlHttpBaseClass.o \
	${OBJECTDIR}/_ext/1102919413/CurlHttpGetBase.o \
	${OBJECTDIR}/_ext/1102919413/CurlHttpPostBase.o \
	${OBJECTDIR}/_ext/1102919413/CurlHttpPutBase.o \
	${OBJECTDIR}/_ext/1102919413/CurlWrapperClass.o \
	${OBJECTDIR}/_ext/1926742074/HttpAccessAuxiliaryStrcut.o \
	${OBJECTDIR}/_ext/1926742074/HttpAccessUtils.o \
	${OBJECTDIR}/_ext/534584118/LogUtils.o \
	${OBJECTDIR}/_ext/607786022/EncodeAndDecode.o \
	${OBJECTDIR}/_ext/607786022/FileDefine.o \
	${OBJECTDIR}/_ext/607786022/TimeStr.o \
	${OBJECTDIR}/_ext/957150543/QiniuCurlGet.o \
	${OBJECTDIR}/_ext/957150543/QiniuCurlPost.o \
	${OBJECTDIR}/_ext/957150543/QiniuCurlPostForm.o \
	${OBJECTDIR}/_ext/957173479/IUpLoadProgressDecoration.o \
	${OBJECTDIR}/_ext/957173479/QiniuMisc.o \
	${OBJECTDIR}/_ext/957173479/QiniuRemoteBatchFilesImpl.o \
	${OBJECTDIR}/_ext/957173479/QiniuRemoteFileImpl.o \
	${OBJECTDIR}/_ext/957173479/QiniuUploadFileImpl.o \
	${OBJECTDIR}/_ext/1115969400/b64.o \
	${OBJECTDIR}/_ext/1115969400/urlsafe_b64.o \
	${OBJECTDIR}/_ext/957209007/jsoncpp.o \
	${OBJECTDIR}/_ext/1665187080/QiniuDestoryFunction.o \
	${OBJECTDIR}/_ext/1665187080/QiniuFactory.o \
	${OBJECTDIR}/_ext/1665187080/QiniuStrcut.o \
	${OBJECTDIR}/_ext/1665187080/QiniuUtils.o \
	${OBJECTDIR}/_ext/1386528437/WindowsDllMain.o \
	${OBJECTDIR}/_ext/1083673653/IDestoryFunction.o \
	${OBJECTDIR}/_ext/1083673653/WorkThreadBaseClass.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libQiniuDynamic.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libQiniuDynamic.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libQiniuDynamic.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -fPIC

${OBJECTDIR}/_ext/1102919413/CurlHttpBaseClass.o: ../../../src/HttpAccess/Curl/CurlHttpBaseClass.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1102919413
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../../../include -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1102919413/CurlHttpBaseClass.o ../../../src/HttpAccess/Curl/CurlHttpBaseClass.cpp

${OBJECTDIR}/_ext/1102919413/CurlHttpGetBase.o: ../../../src/HttpAccess/Curl/CurlHttpGetBase.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1102919413
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../../../include -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1102919413/CurlHttpGetBase.o ../../../src/HttpAccess/Curl/CurlHttpGetBase.cpp

${OBJECTDIR}/_ext/1102919413/CurlHttpPostBase.o: ../../../src/HttpAccess/Curl/CurlHttpPostBase.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1102919413
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../../../include -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1102919413/CurlHttpPostBase.o ../../../src/HttpAccess/Curl/CurlHttpPostBase.cpp

${OBJECTDIR}/_ext/1102919413/CurlHttpPutBase.o: ../../../src/HttpAccess/Curl/CurlHttpPutBase.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1102919413
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../../../include -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1102919413/CurlHttpPutBase.o ../../../src/HttpAccess/Curl/CurlHttpPutBase.cpp

${OBJECTDIR}/_ext/1102919413/CurlWrapperClass.o: ../../../src/HttpAccess/Curl/CurlWrapperClass.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1102919413
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../../../include -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1102919413/CurlWrapperClass.o ../../../src/HttpAccess/Curl/CurlWrapperClass.cpp

${OBJECTDIR}/_ext/1926742074/HttpAccessAuxiliaryStrcut.o: ../../../src/HttpAccess/HttpAccessAuxiliaryStrcut.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1926742074
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../../../include -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1926742074/HttpAccessAuxiliaryStrcut.o ../../../src/HttpAccess/HttpAccessAuxiliaryStrcut.cpp

${OBJECTDIR}/_ext/1926742074/HttpAccessUtils.o: ../../../src/HttpAccess/HttpAccessUtils.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1926742074
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../../../include -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1926742074/HttpAccessUtils.o ../../../src/HttpAccess/HttpAccessUtils.cpp

${OBJECTDIR}/_ext/534584118/LogUtils.o: ../../../src/Log/LogUtils.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/534584118
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../../../include -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/534584118/LogUtils.o ../../../src/Log/LogUtils.cpp

${OBJECTDIR}/_ext/607786022/EncodeAndDecode.o: ../../../src/Misc/EncodeAndDecode.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/607786022
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../../../include -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/607786022/EncodeAndDecode.o ../../../src/Misc/EncodeAndDecode.cpp

${OBJECTDIR}/_ext/607786022/FileDefine.o: ../../../src/Misc/FileDefine.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/607786022
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../../../include -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/607786022/FileDefine.o ../../../src/Misc/FileDefine.cpp

${OBJECTDIR}/_ext/607786022/TimeStr.o: ../../../src/Misc/TimeStr.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/607786022
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../../../include -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/607786022/TimeStr.o ../../../src/Misc/TimeStr.cpp

${OBJECTDIR}/_ext/957150543/QiniuCurlGet.o: ../../../src/Qiniu/Http/QiniuCurlGet.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/957150543
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../../../include -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/957150543/QiniuCurlGet.o ../../../src/Qiniu/Http/QiniuCurlGet.cpp

${OBJECTDIR}/_ext/957150543/QiniuCurlPost.o: ../../../src/Qiniu/Http/QiniuCurlPost.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/957150543
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../../../include -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/957150543/QiniuCurlPost.o ../../../src/Qiniu/Http/QiniuCurlPost.cpp

${OBJECTDIR}/_ext/957150543/QiniuCurlPostForm.o: ../../../src/Qiniu/Http/QiniuCurlPostForm.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/957150543
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../../../include -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/957150543/QiniuCurlPostForm.o ../../../src/Qiniu/Http/QiniuCurlPostForm.cpp

${OBJECTDIR}/_ext/957173479/IUpLoadProgressDecoration.o: ../../../src/Qiniu/Impl/IUpLoadProgressDecoration.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/957173479
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../../../include -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/957173479/IUpLoadProgressDecoration.o ../../../src/Qiniu/Impl/IUpLoadProgressDecoration.cpp

${OBJECTDIR}/_ext/957173479/QiniuMisc.o: ../../../src/Qiniu/Impl/QiniuMisc.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/957173479
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../../../include -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/957173479/QiniuMisc.o ../../../src/Qiniu/Impl/QiniuMisc.cpp

${OBJECTDIR}/_ext/957173479/QiniuRemoteBatchFilesImpl.o: ../../../src/Qiniu/Impl/QiniuRemoteBatchFilesImpl.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/957173479
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../../../include -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/957173479/QiniuRemoteBatchFilesImpl.o ../../../src/Qiniu/Impl/QiniuRemoteBatchFilesImpl.cpp

${OBJECTDIR}/_ext/957173479/QiniuRemoteFileImpl.o: ../../../src/Qiniu/Impl/QiniuRemoteFileImpl.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/957173479
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../../../include -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/957173479/QiniuRemoteFileImpl.o ../../../src/Qiniu/Impl/QiniuRemoteFileImpl.cpp

${OBJECTDIR}/_ext/957173479/QiniuUploadFileImpl.o: ../../../src/Qiniu/Impl/QiniuUploadFileImpl.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/957173479
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../../../include -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/957173479/QiniuUploadFileImpl.o ../../../src/Qiniu/Impl/QiniuUploadFileImpl.cpp

${OBJECTDIR}/_ext/1115969400/b64.o: ../../../src/Qiniu/Impl/b64/b64.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1115969400
	${RM} "$@.d"
	$(COMPILE.c) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1115969400/b64.o ../../../src/Qiniu/Impl/b64/b64.c

${OBJECTDIR}/_ext/1115969400/urlsafe_b64.o: ../../../src/Qiniu/Impl/b64/urlsafe_b64.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1115969400
	${RM} "$@.d"
	$(COMPILE.c) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1115969400/urlsafe_b64.o ../../../src/Qiniu/Impl/b64/urlsafe_b64.c

${OBJECTDIR}/_ext/957209007/jsoncpp.o: ../../../src/Qiniu/Json/jsoncpp.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/957209007
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../../../include -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/957209007/jsoncpp.o ../../../src/Qiniu/Json/jsoncpp.cpp

${OBJECTDIR}/_ext/1665187080/QiniuDestoryFunction.o: ../../../src/Qiniu/QiniuDestoryFunction.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1665187080
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../../../include -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1665187080/QiniuDestoryFunction.o ../../../src/Qiniu/QiniuDestoryFunction.cpp

${OBJECTDIR}/_ext/1665187080/QiniuFactory.o: ../../../src/Qiniu/QiniuFactory.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1665187080
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../../../include -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1665187080/QiniuFactory.o ../../../src/Qiniu/QiniuFactory.cpp

${OBJECTDIR}/_ext/1665187080/QiniuStrcut.o: ../../../src/Qiniu/QiniuStrcut.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1665187080
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../../../include -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1665187080/QiniuStrcut.o ../../../src/Qiniu/QiniuStrcut.cpp

${OBJECTDIR}/_ext/1665187080/QiniuUtils.o: ../../../src/Qiniu/QiniuUtils.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1665187080
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../../../include -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1665187080/QiniuUtils.o ../../../src/Qiniu/QiniuUtils.cpp

${OBJECTDIR}/_ext/1386528437/WindowsDllMain.o: ../../../src/WindowsDllMain.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1386528437
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../../../include -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1386528437/WindowsDllMain.o ../../../src/WindowsDllMain.cpp

${OBJECTDIR}/_ext/1083673653/IDestoryFunction.o: ../../../src/WorkThread/IDestoryFunction.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1083673653
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../../../include -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1083673653/IDestoryFunction.o ../../../src/WorkThread/IDestoryFunction.cpp

${OBJECTDIR}/_ext/1083673653/WorkThreadBaseClass.o: ../../../src/WorkThread/WorkThreadBaseClass.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1083673653
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../../../include -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1083673653/WorkThreadBaseClass.o ../../../src/WorkThread/WorkThreadBaseClass.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libQiniuDynamic.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
