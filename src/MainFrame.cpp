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
	
	m_menubar1 = new wxMenuBar( 0 );
	tools_menu = new wxMenu();
	wxMenuItem* SettingsMenuItem;
	SettingsMenuItem = new wxMenuItem( tools_menu, wxID_ANY, wxString( wxT("Settings") ) , wxEmptyString, wxITEM_NORMAL );
	tools_menu->Append( SettingsMenuItem );
	
	wxMenuItem* CalibrateMenuItem;
	CalibrateMenuItem = new wxMenuItem( tools_menu, wxID_ANY, wxString( wxT("Calibrate") ) , wxEmptyString, wxITEM_NORMAL );
	tools_menu->Append( CalibrateMenuItem );
	
	wxMenuItem* GetStarParamMenuItem;
	GetStarParamMenuItem = new wxMenuItem( tools_menu, wxID_ANY, wxString( wxT("Measure star size") ) , wxEmptyString, wxITEM_NORMAL );
	tools_menu->Append( GetStarParamMenuItem );
	
	wxMenuItem* CameraSettingsMenuItem;
	CameraSettingsMenuItem = new wxMenuItem( tools_menu, wxID_ANY, wxString( wxT("Camera settings") ) , wxEmptyString, wxITEM_NORMAL );
	tools_menu->Append( CameraSettingsMenuItem );
	
	m_menubar1->Append( tools_menu, wxT("Tools") ); 
	
	this->SetMenuBar( m_menubar1 );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxVERTICAL );
	
	StartCaptureButton = new wxToggleButton( this, wxID_ANY, wxT("Capture"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer6->Add( StartCaptureButton, 0, wxALL, 5 );
	
	CorrectionButton = new wxToggleButton( this, wxID_ANY, wxT("Correction"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer6->Add( CorrectionButton, 0, wxALL, 5 );
	
	
	bSizer2->Add( bSizer6, 0, wxALIGN_CENTER_VERTICAL, 5 );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );
	
	StreamPlayerPanel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxSize( 100,100 ), wxTAB_TRAVERSAL );
	bSizer3->Add( StreamPlayerPanel, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	
	bSizer2->Add( bSizer3, 1, wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer1->Add( bSizer2, 1, wxTOP|wxBOTTOM|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxVERTICAL );
	
	ExitButton = new wxButton( this, wxID_ANY, wxT("Exit"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer8->Add( ExitButton, 0, wxALIGN_BOTTOM|wxALL, 5 );
	
	
	bSizer1->Add( bSizer8, 0, wxALIGN_RIGHT, 5 );
	
	
	this->SetSizer( bSizer1 );
	this->Layout();
	m_statusBar1 = this->CreateStatusBar( 1, wxST_SIZEGRIP, wxID_ANY );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	StartCaptureButton->Connect( wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, wxCommandEventHandler( MainFrame::OnToggleCapture ), NULL, this );
	CorrectionButton->Connect( wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, wxCommandEventHandler( MainFrame::OnToggleCorrection ), NULL, this );
	StreamPlayerPanel->Connect( wxEVT_PAINT, wxPaintEventHandler( MainFrame::OnFramePaint ), NULL, this );
	ExitButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::OnClickExit ), NULL, this );
}

MainFrame::~MainFrame()
{
	// Disconnect Events
	StartCaptureButton->Disconnect( wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, wxCommandEventHandler( MainFrame::OnToggleCapture ), NULL, this );
	CorrectionButton->Disconnect( wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, wxCommandEventHandler( MainFrame::OnToggleCorrection ), NULL, this );
	StreamPlayerPanel->Disconnect( wxEVT_PAINT, wxPaintEventHandler( MainFrame::OnFramePaint ), NULL, this );
	ExitButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::OnClickExit ), NULL, this );
	
}
