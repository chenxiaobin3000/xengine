/**
 * desc: 
 * auth: chenxiaobin
 * data: 2015-10-29
 */

#ifndef _XEVERTEX_H_
#define _XEVERTEX_H_

namespace XE {

class CVertex
{
public:
	CVertex();

	CVertex(const CVertex& o);

	CVertex(float x, float y, float z);

	virtual ~CVertex();

	CVertex& operator+=(const CVertex& v);

	CVertex& operator-=(const CVertex& v);

	bool operator==(const CVertex& v);

	bool operator!=(const CVertex& v);

	void Set(float ix, float iy, float iz);

	void Identity();

	void Normalise();

	float Length();

	void MultNum(float n);

	void DivNum(float n);

	float DotMult(const CVertex& v);

	void CrossMult(const CVertex& v);

	void CalcNormal(const CVertex& v1, const CVertex& v2, const CVertex& v3);

public:
	float						x;
	float						y;
	float						z;
};

typedef std::vector<CVertex>						CVertexList;

}

#endif //_XEVERTEX_H_
