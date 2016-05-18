#include "stdafx.h"
#include "XeFaceIndex.h"

namespace XE {

CFaceIndex::CFaceIndex() : m_n1(0), m_n2(0), m_n3(0) {

}

CFaceIndex::CFaceIndex(FaceIndexType n1, FaceIndexType n2, FaceIndexType n3) : m_n1(n1), m_n2(n2), m_n3(n3) {

}

CFaceIndex::~CFaceIndex() {

}

}
