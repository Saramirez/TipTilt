///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 28 2017)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __MAINFRAME_H__
#define __MAINFRAME_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/button.h>
#include <wx/choice.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/statline.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/checkbox.h>
#include <wx/statusbr.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class MainFrame
///////////////////////////////////////////////////////////////////////////////
class MainFrame : public wxFrame 
{
	private:
	
	protected:
		wxMenuBar* m_menubar1;
		wxMenu* tools_menu;
		wxButton* CaptureButton;
		wxChoice* m_choice1;
		wxButton* CorrectionButton;
		wxChoice* m_choice2;
		wxPanel* StreamPlayerPanel;
		wxStaticLine* m_staticline1;
		wxStaticText* m_staticText1;
		wxTextCtrl* ThrsTxCtrl;
		wxStaticText* m_staticText11;
		wxCheckBox* m_checkBox1;
		wxStaticText* m_staticText12;
		wxButton* GetStarSizeButton;
		wxTextCtrl* StrSzTxCtrl;
		wxButton* DefaultButton;
		wxStaticLine* m_staticline2;
		wxStaticText* m_staticText10;
		wxButton* CenterTTButton;
		wxPanel* TTPositionPanel;
		wxButton* ExitButton;
		wxStatusBar* m_statusBar1;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnSelectCameraSettings( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnClickCapture( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnClickCorrection( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnFramePaint( wxPaintEvent& event ) { event.Skip(); }
		virtual void OnThrshTextSet( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnShowThresholdChecked( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnGetStarSizeClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnStrSzTextSet( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDefaultClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnClickCenterTT( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnTTPosPaint( wxPaintEvent& event ) { event.Skip(); }
		virtual void OnClickExit( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		MainFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("TipTilt Correction"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 680,420 ), long style = wxCAPTION|wxCLOSE_BOX|wxMINIMIZE_BOX|wxSYSTEM_MENU|wxTAB_TRAVERSAL );
		
		~MainFrame();
	
};

#endif //__MAINFRAME_H__
