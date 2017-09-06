///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 28 2017)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "../include/MainFrame.h"

///////////////////////////////////////////////////////////////////////////

MainFrame::MainFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxVERTICAL );
	
	StartCaptureButton = new wxButton( this, wxID_ANY, wxT("Capture"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer6->Add( StartCaptureButton, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	StartCorrectionButton = new wxButton( this, wxID_ANY, wxT("Correction"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer6->Add( StartCorrectionButton, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	bSizer2->Add( bSizer6, 0, wxALIGN_CENTER_VERTICAL, 5 );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );
	
	StreamPlayerPanel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxSize( 100,100 ), wxTAB_TRAVERSAL );
	bSizer3->Add( StreamPlayerPanel, 0,wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	
	bSizer2->Add( bSizer3, 1, wxEXPAND, 5 );
	
	
	bSizer1->Add( bSizer2, 0, wxEXPAND|wxTOP|wxBOTTOM, 5 );
	
	m_panel4 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	bSizer1->Add( m_panel4, 1, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxVERTICAL );
	
	ExitButton = new wxButton( this, wxID_ANY, wxT("Exit"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer8->Add( ExitButton, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	
	bSizer1->Add( bSizer8, 0, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer1 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	StartCaptureButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::OnClickStartCapture ), NULL, this );
	StartCorrectionButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::OnClickStartCorrection ), NULL, this );
	StreamPlayerPanel->Connect( wxEVT_PAINT, wxPaintEventHandler( MainFrame::OnFramePaint ), NULL, this );
	ExitButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::OnClickExit ), NULL, this );
}

MainFrame::~MainFrame()
{
	// Disconnect Events
	StartCaptureButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::OnClickStartCapture ), NULL, this );
	StartCorrectionButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::OnClickStartCorrection ), NULL, this );
	StreamPlayerPanel->Disconnect( wxEVT_PAINT, wxPaintEventHandler( MainFrame::OnFramePaint ), NULL, this );
	ExitButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::OnClickExit ), NULL, this );
	
}
