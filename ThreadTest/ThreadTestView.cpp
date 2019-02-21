
// ThreadTestView.cpp : CThreadTestView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "ThreadTest.h"
#endif

#include "ThreadTestDoc.h"
#include "ThreadTestView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CThreadTestView

IMPLEMENT_DYNCREATE(CThreadTestView, CView)

BEGIN_MESSAGE_MAP(CThreadTestView, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CThreadTestView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CThreadTestView ����/�Ҹ�

CThreadTestView::CThreadTestView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CThreadTestView::~CThreadTestView()
{
}

BOOL CThreadTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CThreadTestView �׸���

void CThreadTestView::OnDraw(CDC* /*pDC*/)
{
	CThreadTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
}


// CThreadTestView �μ�


void CThreadTestView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CThreadTestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CThreadTestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CThreadTestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}

void CThreadTestView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CThreadTestView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CThreadTestView ����

#ifdef _DEBUG
void CThreadTestView::AssertValid() const
{
	CView::AssertValid();
}

void CThreadTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CThreadTestDoc* CThreadTestView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CThreadTestDoc)));
	return (CThreadTestDoc*)m_pDocument;
}
#endif //_DEBUG


// CThreadTestView �޽��� ó����

UINT ThreadFunc(LPVOID pParam)
{
	//LPVOID���� UINT������ ĳ����
	UINT n = (UINT)pParam;

	UINT sum = 0;
	for(UINT i=1; i<n; i++){
		sum += i;
		//������� �����ϴ� ���� Ȯ���ϱ� ���ؼ�
		//0.01�ʰ� ��� �ð��� �д�.
		Sleep(10);
	}

	//������� ����Ѵ�.
	CString str;
	str.Format(_T("�����= %d "), sum);
	AfxMessageBox(str);
	return 0;
}

void CThreadTestView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	UINT n=600;

	//�����带 ����� ���
	AfxBeginThread(ThreadFunc, (LPVOID)n );

	//�����带 ������� ���� ���
	//ThreadFunc( (LPVOID) n );
	CView::OnLButtonDown(nFlags, point);
}
