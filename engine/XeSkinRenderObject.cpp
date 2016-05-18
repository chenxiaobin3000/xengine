#include "stdafx.h"
#include "XeSkinRenderObject.h"

namespace XE {

CSkinRenderObject::CSkinRenderObject() : m_pSkeleton(NULL) {

}

CSkinRenderObject::~CSkinRenderObject() {

}

void CSkinRenderObject::SetSkeleton(CSkeleton* pSkeleton) {
    m_pSkeleton = pSkeleton;
}

CSkinAssign& CSkinRenderObject::GetSkinAssign() {
    return m_SkinAssign;
}

}

