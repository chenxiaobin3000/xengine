/**
 * desc: 
 * auth: chenxiaobin
 * data: 2015-10-22
 */

#ifndef _XEIRENDERTARGET_H_
#define _XEIRENDERTARGET_H_

namespace XE {

class CCamera;
class CMatrix;
class CMaterial;
class CTexture;

// 基础渲染元素
class IRenderTarget
{
public:
	virtual ~IRenderTarget() {}

	virtual void Render(CCamera* camera) = 0;
	virtual void Draw() = 0;

	virtual void SetVisible(bool b) = 0;
	virtual bool IsVisible() = 0;
	virtual void SetVisibleForShadow(bool b) = 0;
	virtual bool IsVisibleForShadow() = 0;

	virtual CMatrix& GetModelViewProj() = 0;
    virtual void SetMaterial(CMaterial* pMaterial) = 0;
    virtual CMaterial* GetMaterial() = 0;
    virtual void SetTexture(CTexture* pTexture) = 0;
    virtual CTexture* GetTexture() = 0;
};

}

#endif //_XEIRENDERTARGET_H_
