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
CND_PLATFORM=GNU-Linux
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
	${OBJECTDIR}/_ext/86c28bc0/Flx_Mdi_Internal.o \
	${OBJECTDIR}/_ext/86c28bc0/main.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f1

# Test Object Files
TESTOBJECTFILES= \
	${TESTDIR}/_ext/d140939c/newsimpletest.o

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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/flx_mdi

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/flx_mdi: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/flx_mdi ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/86c28bc0/Flx_Mdi_Internal.o: /home/max/cpp/fltk/Flx_Mdi/src/Flx_Mdi_Internal.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/86c28bc0
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/86c28bc0/Flx_Mdi_Internal.o /home/max/cpp/fltk/Flx_Mdi/src/Flx_Mdi_Internal.cpp

${OBJECTDIR}/_ext/86c28bc0/main.o: /home/max/cpp/fltk/Flx_Mdi/src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/86c28bc0
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/86c28bc0/main.o /home/max/cpp/fltk/Flx_Mdi/src/main.cpp

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-tests-subprojects .build-conf ${TESTFILES}
.build-tests-subprojects:

${TESTDIR}/TestFiles/f1: ${TESTDIR}/_ext/d140939c/newsimpletest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS} 


${TESTDIR}/_ext/d140939c/newsimpletest.o: /home/max/cpp/fltk/PuRRechner/PuRRechner/src/tests/newsimpletest.cpp 
	${MKDIR} -p ${TESTDIR}/_ext/d140939c
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I. -MMD -MP -MF "$@.d" -o ${TESTDIR}/_ext/d140939c/newsimpletest.o /home/max/cpp/fltk/PuRRechner/PuRRechner/src/tests/newsimpletest.cpp


${OBJECTDIR}/_ext/86c28bc0/Flx_Mdi_Internal_nomain.o: ${OBJECTDIR}/_ext/86c28bc0/Flx_Mdi_Internal.o /home/max/cpp/fltk/Flx_Mdi/src/Flx_Mdi_Internal.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/86c28bc0
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/86c28bc0/Flx_Mdi_Internal.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/86c28bc0/Flx_Mdi_Internal_nomain.o /home/max/cpp/fltk/Flx_Mdi/src/Flx_Mdi_Internal.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/86c28bc0/Flx_Mdi_Internal.o ${OBJECTDIR}/_ext/86c28bc0/Flx_Mdi_Internal_nomain.o;\
	fi

${OBJECTDIR}/_ext/86c28bc0/main_nomain.o: ${OBJECTDIR}/_ext/86c28bc0/main.o /home/max/cpp/fltk/Flx_Mdi/src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/86c28bc0
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/86c28bc0/main.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/86c28bc0/main_nomain.o /home/max/cpp/fltk/Flx_Mdi/src/main.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/86c28bc0/main.o ${OBJECTDIR}/_ext/86c28bc0/main_nomain.o;\
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

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
