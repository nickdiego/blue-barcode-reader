#ifndef YUV2RGB_H
#define YUV2RGB_H

#include <QtCore/QObject>

class Yuv2Rgb : public QObject
{
    Q_OBJECT

public:
    Yuv2Rgb();
    ~Yuv2Rgb();

public:
    void convert(const uchar *bits, const int &width, const int &height);

    uchar *bits();
    int width();
    int height();

private:
    void preCalculateValues();

    // Defined as an inline function for performance reasons
    inline void applyFormula(int &r, int &g, int &b,
                             const int &y, const int &u, const int &v);

    uchar *m_bits;
    int *m_v1;
    int *m_v2;
    int *m_v3;
    int *m_v4;
    int m_width;
    int m_height;
};

#endif
