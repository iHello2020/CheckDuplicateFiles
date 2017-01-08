#include "crc32.h"
#ifdef _DEBUG
#include <QDebug>
#endif

CRC32::CRC32()
{
    reset();
}

void CRC32::update(QByteArray &data, QString oldComputeHash)
{
    Q_UNUSED(oldComputeHash)

    int len = data.length();
    char *stdChar = data.data();
    unsigned char* buffer = (unsigned char *)stdChar;
    for(;len >0 ;len--)
        m_crc32Str = (m_crc32Str >> 8) ^ crc32_table[(m_crc32Str & 0xFF) ^ *buffer++];
}

QString CRC32::getFinalResult()
{
    // Exclusive OR the result with the beginning value.
    unsigned long resultData = m_crc32Str ^ 0xffffffff;

#ifdef _DEBUG
    printf(" resultData %X", resultData);
#endif
    char hexChar[10] = {0};
    int hexCharLength = sprintf(hexChar,  "%X",  resultData);
    QByteArray byteChar(hexChar, hexCharLength);
    return QString(byteChar);
}

void CRC32::reset()
{
    m_crc32Str = 0xffffffff;
    initCRC32Table();
}

util::ComputeType CRC32::getType()
{
    return util::CRC32;
}

QString CRC32::getTypeName()
{
    return QString("CRC32");
}

void CRC32::initCRC32Table()
{
    // This is the official polynomial used by CRC-32 in PKZip, WinZip and Ethernet.
    unsigned long ulPolynomial = 0x04c11db7;

    // 256 values representing ASCII character codes.
    for(int i = 0; i <= 0xFF; i++)
    {
        crc32_table[i]=reflect(i, 8) << 24;
        for (int j = 0; j < 8; j++)
         crc32_table[i] = (crc32_table[i] << 1) ^ (crc32_table[i] & (1 << 31) ? ulPolynomial : 0);
        crc32_table[i] = reflect(crc32_table[i], 32);
    }
}

unsigned long CRC32::reflect(unsigned long ref, char ch)
{
    unsigned long value = 0;

    for(int i = 1; i < (ch + 1); i++)
    {
        if(ref & 1)
            value |= 1 << (ch - i);
        ref >>= 1;
    }
    return value;
}
