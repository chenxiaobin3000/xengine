#include "stdafx.h"
#include "XeVertexIndex.h"

namespace XE {

CVertexIndex::CVertexIndex() : m_n1(0), m_n2(0), m_n3(0) {

}

CVertexIndex::CVertexIndex(VertexIndexType n1, VertexIndexType n2, VertexIndexType n3) : m_n1(n1), m_n2(n2), m_n3(n3) {
	
}

CVertexIndex::~CVertexIndex() {

}

}
