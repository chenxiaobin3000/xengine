/**
 * desc: 
 * auth: chenxiaobin
 * data: 2015-10-29
 */

#ifndef _XEVORONOI_H_
#define _XEVORONOI_H_

namespace XE {

class CVoronoi
{
private:
	struct SPoint {
		int						x;
		int						y;
		byte					data;
	};

	typedef std::vector<SPoint>							SPointList;

public:
	CVoronoi();
	virtual ~CVoronoi();

	void AddPoint(int x, int y, byte data);

	void Clear();

	void Generate(int nWidth, int nHeight, byte* szData);

private:
	float EuclideanDistance(float p1x, float p1y, float p2x, float p2y);

	float ManhattanDistance(float p1x, float p1y, float p2x, float p2y);

private:
	static const float			s_fInfinite;
	SPointList					m_List;
};

}

#endif //_XEVORONOI_H_
