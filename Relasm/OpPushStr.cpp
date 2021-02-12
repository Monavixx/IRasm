#include "OpPushStr.h"

OpPushStr::OpPushStr(const QString& data) : data(data)
{
    this->data.replace("\\n", "\n");
}

QByteArray OpPushStr::Compile()
{
    QByteArray code;
    QDataStream ds(&code, QIODevice::WriteOnly);
    ds << byteOpCode;
    ds << data.toUtf8();
    return code;
}
