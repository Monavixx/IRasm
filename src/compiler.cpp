#include "compiler.h"

void Compiler::build() noexcept
{
    fout.write((char*)balib::intToBytes(version), 4);
}