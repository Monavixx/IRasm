#include "OpPushStr.h"

OpPushStr::OpPushStr(const QString& data) : data(data)
{
    this->data.replace("\\\\", "\\");
    this->data.replace("\\n", "\n");
    this->data.replace("\\t", "\t");
}

QByteArray OpPushStr::Compile()
{
    QByteArray code;
    QDataStream ds(&code, QIODevice::WriteOnly);
    ds << byteOpCode;
    ds << data;
    return code;
}
