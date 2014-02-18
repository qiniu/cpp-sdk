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
	${OBJECTDIR}/_ext/2214214/IQiniuRemoteBatchFilesTestCase.o \
	${OBJECTDIR}/_ext/2214214/IQiniuRemoteFileTestCase.o \
	${OBJECTDIR}/_ext/2214214/LogTestCase.o \
	${OBJECTDIR}/_ext/2214214/UploadCallBack.o


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
LDLIBSOPTIONS=/home/wxt/Desktop/QiniuC++SDK/project/Linux/QiniuStatic/dist/Release/GNU-Linux-x86/libqiniustatic.a /usr/local/lib/libgtest_main.a /usr/local/lib/libgtest.a `pkg-config --libs libcrypto` `pkg-config --libs libcurl` `pkg-config --libs zlib` -lpthread   

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/qiniuunittest

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/qiniuunittest: /home/wxt/Desktop/QiniuC++SDK/project/Linux/QiniuStatic/dist/Release/GNU-Linux-x86/libqiniustatic.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/qiniuunittest: /usr/local/lib/libgtest_main.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/qiniuunittest: /usr/local/lib/libgtest.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/qiniuunittest: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/qiniuunittest ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/2214214/IQiniuRemoteBatchFilesTestCase.o: ../../../unittest/src/IQiniuRemoteBatchFilesTestCase.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2214214
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../../../include `pkg-config --cflags libcrypto` `pkg-config --cflags libcurl` `pkg-config --cflags zlib`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2214214/IQiniuRemoteBatchFilesTestCase.o ../../../unittest/src/IQiniuRemoteBatchFilesTestCase.cpp

${OBJECTDIR}/_ext/2214214/IQiniuRemoteFileTestCase.o: ../../../unittest/src/IQiniuRemoteFileTestCase.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2214214
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../../../include `pkg-config --cflags libcrypto` `pkg-config --cflags libcurl` `pkg-config --cflags zlib`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2214214/IQiniuRemoteFileTestCase.o ../../../unittest/src/IQiniuRemoteFileTestCase.cpp

${OBJECTDIR}/_ext/2214214/LogTestCase.o: ../../../unittest/src/LogTestCase.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2214214
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../../../include `pkg-config --cflags libcrypto` `pkg-config --cflags libcurl` `pkg-config --cflags zlib`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2214214/LogTestCase.o ../../../unittest/src/LogTestCase.cpp

${OBJECTDIR}/_ext/2214214/UploadCallBack.o: ../../../unittest/src/UploadCallBack.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2214214
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../../../include `pkg-config --cflags libcrypto` `pkg-config --cflags libcurl` `pkg-config --cflags zlib`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2214214/UploadCallBack.o ../../../unittest/src/UploadCallBack.cpp

# Subprojects
.build-subprojects:
	cd /home/wxt/Desktop/QiniuC++SDK/project/Linux/QiniuStatic && ${MAKE}  -f Makefile CONF=Release

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/qiniuunittest

# Subprojects
.clean-subprojects:
	cd /home/wxt/Desktop/QiniuC++SDK/project/Linux/QiniuStatic && ${MAKE}  -f Makefile CONF=Release clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
