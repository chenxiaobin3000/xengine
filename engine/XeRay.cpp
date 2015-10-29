#include "stdafx.h"
#include "XeRay.h"

namespace XE {

CRay::CRay() {

}

CRay::CRay(const CRay& o) {
	p = o.p;  d = o.d;
}

CRay::CRay(CVertex& ip, CVertex& id) : p(ip), d(id) {

}

CRay::~CRay() {

}

bool CRay::operator==(const CRay& r) {
	return ((p == r.p) && (d == r.d));
}

bool CRay::operator!=(const CRay& r) {
	return ((p != r.p) || (d != r.d));
}

void CRay::Set(CVertex& ip, CVertex& id) {
	p = ip;  d = id;
}

void CRay::Identity() {
	p.Identity();
	d.Identity();
}

}
