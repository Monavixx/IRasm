QT -= gui

CONFIG += c++2a console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../Class.cpp \
    ../Compiler.cpp \
    ../Exit.cpp \
    ../Field.cpp \
    ../Method.cpp \
    ../OpAdd.cpp \
    ../OpBase.cpp \
    ../OpCallMethod.cpp \
    ../OpCast.cpp \
    ../OpDeref.cpp \
    ../OpDiv.cpp \
    ../OpDup.cpp \
    ../OpEqual.cpp \
    ../OpGc.cpp \
    ../OpGet.cpp \
    ../OpGetarr.cpp \
    ../OpGetfield.cpp \
    ../OpJmp.cpp \
    ../OpJmpif.cpp \
    ../OpLocal.cpp \
    ../OpMaxStack.cpp \
    ../OpMul.cpp \
    ../OpNew.cpp \
    ../OpNewarr.cpp \
    ../OpPushBool.cpp \
    ../OpPushFloat.cpp \
    ../OpPushInt32.cpp \
    ../OpPushStr.cpp \
    ../OpRef.cpp \
    ../OpReturn.cpp \
    ../OpSet.cpp \
    ../OpSetarr.cpp \
    ../OpSetfield.cpp \
    ../OpSetpd.cpp \
    ../OpSub.cpp \
    ../OpThis.cpp \
    ../Parameter.cpp \
    ../Parser.cpp \
    ../Program.cpp \
    ../main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    ../AccessModifier.h \
    ../Class.h \
    ../Compiler.h \
    ../ConsoleTextStream.h \
    ../Exception.h \
    ../Exit.h \
    ../ExitException.h \
    ../Field.h \
    ../Instruction.h \
    ../IsStatic.h \
    ../Method.h \
    ../OpAdd.h \
    ../OpBase.h \
    ../OpCallMethod.h \
    ../OpCast.h \
    ../OpCodes.h \
    ../OpDeref.h \
    ../OpDiv.h \
    ../OpDup.h \
    ../OpEqual.h \
    ../OpGc.h \
    ../OpGet.h \
    ../OpGetarr.h \
    ../OpGetfield.h \
    ../OpJmp.h \
    ../OpJmpif.h \
    ../OpLocal.h \
    ../OpMaxStack.h \
    ../OpMul.h \
    ../OpNew.h \
    ../OpNewarr.h \
    ../OpPushBool.h \
    ../OpPushFloat.h \
    ../OpPushInt32.h \
    ../OpPushStr.h \
    ../OpRef.h \
    ../OpReturn.h \
    ../OpSet.h \
    ../OpSetarr.h \
    ../OpSetfield.h \
    ../OpSetpd.h \
    ../OpSub.h \
    ../OpThis.h \
    ../Parameter.h \
    ../Parser.h \
    ../Program.h \
    ../Signature.h
