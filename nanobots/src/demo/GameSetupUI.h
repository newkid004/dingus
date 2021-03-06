#ifndef __GAME_SETUP_UI_H
#define __GAME_SETUP_UI_H

#include <dingus/gfx/gui/Gui.h>
#include "net/NetMessages.h"
#include "game/GameTypes.h"


class CGameSetupDialog : public boost::noncopyable {
public:
	enum eDlgState { STATE_ACTIVE, STATE_START, /*STATE_EXIT, STATE_HIDDEN*/ };

public:
	CGameSetupDialog();
	~CGameSetupDialog();
	
	//void		showDialog();
	//void		hideDialog() { mState = STATE_HIDDEN; }
	CUIDialog&	getDialog() { return *mDlg; }
	eDlgState	getState() const { return mState; }


	void	updateViewer( SMatrix4x4& viewer, float& tilt, float& zoom );
	//void		update();


	static void CALLBACK dialogCallback( UINT evt, int ctrlID, CUIControl* ctrl );
	static void CALLBACK renderCallback( CUIDialog& dlg );
	
private:
	static CGameSetupDialog*	mSingleInstance;

	CUIDialog*	mDlg;
	eDlgState	mState;

	CUIButton*	mBtnJoin[G_MAX_PLAYERS];
	CUIButton*	mBtnStart;
	int			mJoinAcceptedForPlayer;
	bool		mStartClicked;
};


#endif
