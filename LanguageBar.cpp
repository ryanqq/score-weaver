
#include "Globals.h"
#include "TextService.h"
#include "Resource.h"
#include "LanguageBarItemButton.h"

BOOL CTextService::_InitLanguageBar()
{
    ITfLangBarItemMgr *pLangBarItemMgr;
    BOOL fRet;

    if (_pThreadMgr->QueryInterface(IID_ITfLangBarItemMgr, (void **)&pLangBarItemMgr) != S_OK)
        return FALSE;

    fRet = FALSE;

	//��ӿ��ذ�ť
	if ((_pPowerButton = new PowerButton(this)) == NULL)
        goto Exit;
	
	if (pLangBarItemMgr->AddItem(_pPowerButton) != S_OK)
	{
		_pPowerButton->Release();
		_pPowerButton = NULL;
		goto Exit;
	}

	//���ȫ��ǰ�ť
	if ((_pModeButton = new ModeButton(this)) == NULL)
        goto Exit;
	
	if (pLangBarItemMgr->AddItem(_pModeButton) != S_OK)
	{
		_pModeButton->Release();
		_pModeButton = NULL;
		goto Exit;
	}

	//�����Ӣ��㰴ť
	if ((_pPunctButton = new PunctButton(this)) == NULL)
        goto Exit;
	
	if (pLangBarItemMgr->AddItem(_pPunctButton) != S_OK)
	{
		_pPunctButton->Release();
		_pPunctButton = NULL;
		goto Exit;
	}

	//��ӹ���
	if ((_pToolButton = new ToolButton(this)) == NULL)
        goto Exit;
	
	if (pLangBarItemMgr->AddItem(_pToolButton) != S_OK)
	{	
		_pToolButton->Release();
		_pToolButton = NULL;
		goto Exit;
	}

    fRet = TRUE;

Exit:
    pLangBarItemMgr->Release();
    return fRet;
}

//+---------------------------------------------------------------------------
//
// _UninitLanguageBar
//
//----------------------------------------------------------------------------

void CTextService::_UninitLanguageBar()
{
    ITfLangBarItemMgr *pLangBarItemMgr;

	if (_pThreadMgr->QueryInterface(IID_ITfLangBarItemMgr, (void **)&pLangBarItemMgr) != S_OK){
		return;
	}

	//���ٰ�ť
	CLangBarItemButton *buttons[] = {_pToolButton, _pPunctButton, _pModeButton, _pPowerButton};

	for(int i = 0; i < 4; i++){
		if (buttons[i] != NULL){
			pLangBarItemMgr->RemoveItem(buttons[i]);

			buttons[i]->Release();
			buttons[i] = NULL;
		}
	}

	pLangBarItemMgr->Release();
}
