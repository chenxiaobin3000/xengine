/**
 * desc: 
 * auth: chenxiaobin
 * data: 2015-11-26
 */

#ifndef _XECOLOR_H_
#define _XECOLOR_H_

namespace XE {

#define COLOR_RED		CColor_b(255, 0, 0)
#define COLOR_GREEN		CColor_b(0, 255, 0)
#define COLOR_BLUE		CColor_b(0, 0, 255)
#define COLOR_WRITE		CColor_b(255, 255, 255)

class CColorB
{
public:
	CColorB(unsigned int color) : m_color(color) {
		a = (m_color >> 24) & 0xFF;
		r = (m_color >> 16) & 0xFF;
		g = (m_color >> 8) & 0xFF;
		b = m_color & 0xFF;
	}

	CColorB(byte ir, byte ig, byte ib, byte ia=0xFF) {
		r = ir;  g = ig;  b = ib;  a = ia;
		m_color = ia<<24 | ir<<16 | ig<<8 | ib;
	}

public:
	unsigned int	m_color;
	byte			r;
	byte			g;
	byte			b;
	byte			a;
};

class CColorF
{
public:
	CColorF() {
		r = 0;  g = 0;  b = 0;  a = 0;
	}

	CColorF(float ir, float ig, float ib, float ia=1.0f) {
		r = ir;  g = ig;  b = ib;  a = ia;
	}

public:
	float			r;
	float			g;
	float			b;
	float			a;
};

}

#endif //_XECOLOR_H_
