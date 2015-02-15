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
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/2034070592/Flx_Mdi_Internal.o \
	${OBJECTDIR}/_ext/2034070592/main.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f1

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
LDLIBSOPTIONS=-L/usr/lib -L/usr/local/lib -L../../fltk-1.3.2/lib -L/home/max/cpp/fltk/Flx_1/lib/Debug -L/home/max/cpp/My_1_5/lib/Debug -lflx_1 -lmy_1_5

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/flx_mdi

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/flx_mdi: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	g++ -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/flx_mdi ${OBJECTFILES} ${LDLIBSOPTIONS} `fltk-config --ldstaticflags` `mysql_config --libs`

${OBJECTDIR}/_ext/2034070592/Flx_Mdi_Internal.o: /home/max/cpp/fltk/Flx_Mdi/src/Flx_Mdi_Internal.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2034070592
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../My_1_5 -I../../fltk-1.3.2 -I../Flx_1 -I. -I/usr/include/mysql -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2034070592/Flx_Mdi_Internal.o /home/max/cpp/fltk/Flx_Mdi/src/Flx_Mdi_Internal.cpp

${OBJECTDIR}/_ext/2034070592/main.o: /home/max/cpp/fltk/Flx_Mdi/src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2034070592
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../My_1_5 -I../../fltk-1.3.2 -I../Flx_1 -I. -I/usr/include/mysql -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2034070592/main.o /home/max/cpp/fltk/Flx_Mdi/src/main.cpp

# Subprojects
.build-subprojects:
	cd /home/max/cpp/My_1_5 && ${MAKE}  -f Makefile CONF=Debug
	cd /home/max/cpp/fltk/Flx_1 && ${MAKE}  -f Makefile CONF=Debug

# Build Test Targets
.build-tests-conf: .build-conf ${TESTFILES}
${TESTDIR}/TestFiles/f1: ${TESTDIR}/_ext/784297060/newsimpletest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS} 


${TESTDIR}/_ext/784297060/newsimpletest.o: /home/max/cpp/fltk/PuRRechner/PuRRechner/src/tests/newsimpletest.cpp 
	${MKDIR} -p ${TESTDIR}/_ext/784297060
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../My_1_5 -I../../fltk-1.3.2 -I../Flx_1 -I. -I/usr/include/mysql -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${TESTDIR}/_ext/784297060/newsimpletest.o /home/max/cpp/fltk/PuRRechner/PuRRechner/src/tests/newsimpletest.cpp


${OBJECTDIR}/_ext/2034070592/Flx_Mdi_Internal_nomain.o: ${OBJECTDIR}/_ext/2034070592/Flx_Mdi_Internal.o /home/max/cpp/fltk/Flx_Mdi/src/Flx_Mdi_Internal.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2034070592
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/2034070592/Flx_Mdi_Internal.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -I../../My_1_5 -I../../fltk-1.3.2 -I../Flx_1 -I. -I/usr/include/mysql -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2034070592/Flx_Mdi_Internal_nomain.o /home/max/cpp/fltk/Flx_Mdi/src/Flx_Mdi_Internal.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/2034070592/Flx_Mdi_Internal.o ${OBJECTDIR}/_ext/2034070592/Flx_Mdi_Internal_nomain.o;\
	fi

${OBJECTDIR}/_ext/2034070592/main_nomain.o: ${OBJECTDIR}/_ext/2034070592/main.o /home/max/cpp/fltk/Flx_Mdi/src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2034070592
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/2034070592/main.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -I../../My_1_5 -I../../fltk-1.3.2 -I../Flx_1 -I. -I/usr/include/mysql -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2034070592/main_nomain.o /home/max/cpp/fltk/Flx_Mdi/src/main.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/2034070592/main.o ${OBJECTDIR}/_ext/2034070592/main_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f1 || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/flx_mdi

# Subprojects
.clean-subprojects:
	cd /home/max/cpp/My_1_5 && ${MAKE}  -f Makefile CONF=Debug clean
	cd /home/max/cpp/fltk/Flx_1 && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
