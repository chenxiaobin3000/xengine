#include "stdafx.h"
#include "XeVertexBuffer.h"
#include "XeCgProgram.h"

namespace XE {

CVertexBuffer::CVertexBuffer() : m_nVertexCount(0),
								 m_nIndexCount(0),
								 m_nVBOVertices(0),
								 m_pVBOVertices(NULL),
								 m_nVBOTexCoords(0),
								 m_pVBOTexCoords(NULL),
								 m_nVBONormals(0),
								 m_pVBONormals(NULL),
								 m_pIndexList(NULL) {
	
}

CVertexBuffer::~CVertexBuffer() {
	if (0 != m_nVBOVertices)	{ glDeleteBuffers(1, &m_nVBOVertices); }
	if (m_pVBOVertices)			{ delete m_pVBOVertices; }
	if (0 != m_nVBOTexCoords)	{ glDeleteBuffers(1, &m_nVBOTexCoords); }
	if (m_pVBOTexCoords)		{ delete m_pVBOTexCoords; }
	if (0 != m_nVBONormals)		{ glDeleteBuffers(1, &m_nVBONormals); }
	if (m_pVBONormals)			{ delete m_pVBONormals; }
	if (m_pIndexList)			{ delete m_pIndexList; }
}

void CVertexBuffer::Render() {
	glBindBuffer(GL_ARRAY_BUFFER, m_nVBOVertices);
	glVertexAttribPointer(CCgProgram::E_ATTRIB_VERTEX, 3, GL_FLOAT,
		GL_FALSE, 0, NULL);

	glBindBuffer(GL_ARRAY_BUFFER, m_nVBOTexCoords);
	glVertexAttribPointer(CCgProgram::E_ATTRIB_TEXCOORD, 2, GL_FLOAT,
		GL_FALSE, 0, NULL);

	glBindBuffer(GL_ARRAY_BUFFER, m_nVBONormals);
	glVertexAttribPointer(CCgProgram::E_ATTRIB_NORMAL, 3, GL_FLOAT,
		GL_FALSE, 0, NULL);

	if (0 == m_nIndexCount) {
		if (0 != m_nVertexCount) {
			glDrawArrays(GL_TRIANGLES, 0, m_nVertexCount);
		}
	} else {
		glDrawElements(GL_TRIANGLES, m_nIndexCount*3, GL_UNSIGNED_INT, m_pIndexList);
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDisableVertexAttribArray(CCgProgram::E_ATTRIB_VERTEX);
	glDisableVertexAttribArray(CCgProgram::E_ATTRIB_TEXCOORD);
	glDisableVertexAttribArray(CCgProgram::E_ATTRIB_NORMAL);
}
	
bool CVertexBuffer::SetCount(int nVertexCount, int nIndexCount) {
	m_nVertexCount = nVertexCount;
	m_nIndexCount = nIndexCount;

	// 生成顶点
	if (0 == m_nVBOVertices || 0 == m_nVBOTexCoords 
   	|| 0 == m_nVBONormals || !m_pVBOVertices 
	|| !m_pVBOTexCoords ||  !m_pVBONormals) {
		glGenBuffers(1, &m_nVBOVertices);
		glGenBuffers(1, &m_nVBOTexCoords);
		glGenBuffers(1, &m_nVBONormals);
		m_pVBOVertices	= XENEW(float[m_nVertexCount*3]);
		m_pVBOTexCoords	= XENEW(float[m_nVertexCount*2]);
		m_pVBONormals	= XENEW(float[m_nVertexCount*3]);
		if (0 == m_nVBOVertices || 0 == m_nVBOTexCoords 
	   	|| 0 == m_nVBONormals || !m_pVBOVertices 
   		|| !m_pVBOTexCoords ||  !m_pVBONormals) {
			return false;
		}
	}

	// 处理索引
	if (0 != m_nIndexCount || !m_pIndexList) {
		m_pIndexList = XENEW(GLuint[m_nIndexCount * 3]);
		if (!m_pIndexList) {
			return false;
		}
	}
	
    return true;
};
	
int CVertexBuffer::GetVertexCount() {
    return m_nVertexCount;
}

int CVertexBuffer::GetIndexCount() {
	return m_nIndexCount;
}

bool CVertexBuffer::Lock(float*& pVertexs, float*& pTexCoords, float*& pNormals, unsigned int*& pIndexs) {
	pVertexs = m_pVBOVertices;
	pTexCoords = m_pVBOTexCoords;
	pNormals = m_pVBONormals;
	pIndexs = m_pIndexList;
	return true;
}

void CVertexBuffer::Unlock() {
	glBindBuffer(GL_ARRAY_BUFFER, m_nVBOVertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*m_nVertexCount*3, 
		m_pVBOVertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, m_nVBOTexCoords);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*m_nVertexCount*2, 
		m_pVBOTexCoords, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, m_nVBONormals);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*m_nVertexCount*3, 
		m_pVBONormals, GL_STATIC_DRAW);
}
	
}
