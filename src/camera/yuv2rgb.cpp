#include "yuv2rgb.h"

#include <QtCore/qmath.h>

Yuv2Rgb::Yuv2Rgb()
    : m_bits(0)
    , m_width(0)
    , m_height(0)
{
    preCalculateValues();
}

Yuv2Rgb::~Yuv2Rgb()
{
    if (m_v1)
        delete m_v1;

    if (m_v2)
        delete m_v2;

    if (m_v3)
        delete m_v3;

    if (m_v4)
        delete m_v4;
}

uchar *Yuv2Rgb::bits()
{
    return m_bits;
}

int Yuv2Rgb::width()
{
    return m_width;
}

int Yuv2Rgb::height()
{
    return m_height;
}

void Yuv2Rgb::convert(const uchar *bits, const int &width, const int &height)
{
#if defined(Q_OS_HARMATTAN)
    if ((m_bits == 0) || (width != m_width) || (height != m_height)) {
        if (m_bits != 0)
            delete[] m_bits;

        m_width = width;
        m_height = height;
        m_bits = new uchar[m_width * m_height * 4];
    }

    int iterations = (m_width / 2) * m_height;
    uchar *destination = m_bits;
    const uchar *source = bits;
    int r;
    int g;
    int b;
    int u;
    int y1;
    int v;
    int y2;

    for (int i = 0; i < iterations; ++i) {
        // Get UYVY chrominance and luminance values
        u = *source;
        y1 = *(source + 1);
        v = *(source + 2);
        y2 = *(source + 3);

        // Apply formula from the 1st two bytes
        applyFormula(r, g, b, y1, u, v);

        *destination = b;
        *(destination + 1) = g;
        *(destination + 2) = r;
        *(destination + 3) = 0;

        destination += 4;

        // Apply formula from the next two bytes
        applyFormula(r, g, b, y2, u, v);

        *destination = b;
        *(destination + 1) = g;
        *(destination + 2) = r;
        *(destination + 3) = 0;

        destination += 4;
        source += 4;
    }
#endif
}

void Yuv2Rgb::preCalculateValues()
{
#if defined(Q_OS_HARMATTAN)
    int i;
    qreal x;

    m_v1 = new int[256];
    m_v2 = new int[256];
    m_v3 = new int[256];
    m_v4 = new int[256];
    for (i = 0; i < 256; i++) {
        // m_v1 = 1.370705 * (V - 128.0)
        x = 1.370705 * (i - 128.0);
        m_v1[i] = x;

        // m_v2 = 0.698001 * (V - 128.0)
        x = 0.698001 * (i - 128.0);
        m_v2[i] = x;

        // m_v3 = 0.337633 * (U - 128.0)
        x = 0.337633 * (i - 128.0);
        m_v3[i] = x;

        // m_v4 = 1.732446 * (U - 128.0)
        x = 1.732446 * (i - 128.0);
        m_v4[i] = x;
    }
#endif
}

void Yuv2Rgb::applyFormula(int &r, int &g, int &b,
                           const int &y, const int &u, const int &v)
{
    //  Formula:
    //  R = Y + 1.370705 * (V - 128.0)
    //  G = Y - 0.698001 * (V - 128.0) - 0.337633 * (U - 128.0)
    //  B = Y + 1.732446 * (U - 128.0)
    r = y + m_v1[v];
    g = y - m_v2[v] - m_v3[u];
    b = y + m_v4[u];

    // Clamping
    r = (r < 0) ? 0 : ((r > 255) ? 255 : r);
    g = (g < 0) ? 0 : ((g > 255) ? 255 : g);
    b = (b < 0) ? 0 : ((b > 255) ? 255 : b);
}
