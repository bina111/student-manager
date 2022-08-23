
// StudentStatusSystemView.h: CStudentStatusSystemView 类的接口
//

#pragma once


class CStudentStatusSystemView : public CView
{
protected: // 仅从序列化创建
	CStudentStatusSystemView() noexcept;
	DECLARE_DYNCREATE(CStudentStatusSystemView)

// 特性
public:
	CStudentStatusSystemDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CStudentStatusSystemView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // StudentStatusSystemView.cpp 中的调试版本
inline CStudentStatusSystemDoc* CStudentStatusSystemView::GetDocument() const
   { return reinterpret_cast<CStudentStatusSystemDoc*>(m_pDocument); }
#endif

