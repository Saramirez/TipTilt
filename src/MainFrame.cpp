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
	wxMenuItem* CalibrateMenuItem;
	CalibrateMenuItem = new wxMenuItem( tools_menu, wxID_ANY, wxString( wxT("Calibrate") ) , wxEmptyString, wxITEM_NORMAL );
	tools_menu->Append( CalibrateMenuItem );
	
	wxMenuItem* CameraSettingsMenuItem;
	CameraSettingsMenuItem = new wxMenuItem( tools_menu, wxID_ANY, wxString( wxT("Camera settings") ) , wxEmptyString, wxITEM_NORMAL );
	tools_menu->Append( CameraSettingsMenuItem );
	
	m_menubar1->Append( tools_menu, wxT("Tools") ); 
	
	this->SetMenuBar( m_menubar1 );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );
	
	wxGridSizer* gSizer1;
	gSizer1 = new wxGridSizer( 2, 2, 0, 0 );
	
	StartCaptureButton = new wxToggleButton( this, wxID_ANY, wxT("Capture"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer1->Add( StartCaptureButton, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	CamDeviceComboBox = new wxComboBox( this, wxID_ANY, wxT("Combo!"), wxDefaultPosition, wxDefaultSize, 0, NULL, 0 ); 
	gSizer1->Add( CamDeviceComboBox, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	CorrectionButton = new wxToggleButton( this, wxID_ANY, wxT("Correction"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer1->Add( CorrectionButton, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
	
	TTDeviceComboBox = new wxComboBox( this, wxID_ANY, wxT("Combo!"), wxDefaultPosition, wxDefaultSize, 0, NULL, 0 ); 
	gSizer1->Add( TTDeviceComboBox, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	bSizer2->Add( gSizer1, 1, wxALIGN_CENTER_VERTICAL, 0 );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );
	
	StreamPlayerPanel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxSize( 100,100 ), wxSTATIC_BORDER|wxTAB_TRAVERSAL );
	bSizer3->Add( StreamPlayerPanel, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 10 );
	
	
	bSizer2->Add( bSizer3, 1, wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer1->Add( bSizer2, 0, wxTOP|wxBOTTOM|wxEXPAND, 5 );
	
	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer1->Add( m_staticline1, 0, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer18;
	bSizer18 = new wxBoxSizer( wxVERTICAL );
	
	wxGridSizer* gSizer2;
	gSizer2 = new wxGridSizer( 0, 2, 0, 0 );
	
	m_staticText1 = new wxStaticText( this, wxID_ANY, wxT("Threshold (0 - 255)"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
	m_staticText1->Wrap( -1 );
	gSizer2->Add( m_staticText1, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	ThrsTxCtrl = new wxTextCtrl( this, wxID_ANY, wxT("150"), wxDefaultPosition, wxSize( 40,-1 ), wxTE_CENTRE|wxTE_NO_VSCROLL|wxTE_PROCESS_ENTER);
	#ifdef __WXGTK__
	if ( !ThrsTxCtrl->HasFlag( wxTE_MULTILINE ) )
	{
	ThrsTxCtrl->SetMaxLength( 3 );
	}
	#else
	ThrsTxCtrl->SetMaxLength( 3 );
	#endif
	gSizer2->Add( ThrsTxCtrl, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxALIGN_RIGHT, 5 );
	
	m_staticText11 = new wxStaticText( this, wxID_ANY, wxT("Show threshold image"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
	m_staticText11->Wrap( -1 );
	gSizer2->Add( m_staticText11, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_checkBox1 = new wxCheckBox( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT );
	gSizer2->Add( m_checkBox1, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxRIGHT, 15 );
	
	m_staticText12 = new wxStaticText( this, wxID_ANY, wxT("Star size"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
	m_staticText12->Wrap( -1 );
	gSizer2->Add( m_staticText12, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxBoxSizer* bSizer19;
	bSizer19 = new wxBoxSizer( wxHORIZONTAL );
	
	GetStarSizeButton = new wxButton( this, wxID_ANY, wxT("Get"), wxDefaultPosition, wxSize( -1,-1 ), wxBU_EXACTFIT|wxNO_BORDER );
	bSizer19->Add( GetStarSizeButton, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	StrSzTxCtrl = new wxTextCtrl( this, wxID_ANY, wxT("13.0"), wxDefaultPosition, wxSize( 40,-1 ), wxTE_CENTRE|wxTE_NO_VSCROLL );
	#ifdef __WXGTK__
	if ( !StrSzTxCtrl->HasFlag( wxTE_MULTILINE ) )
	{
	StrSzTxCtrl->SetMaxLength( 4 );
	}
	#else
	StrSzTxCtrl->SetMaxLength( 4 );
	#endif
	bSizer19->Add( StrSzTxCtrl, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	
	gSizer2->Add( bSizer19, 0, wxALIGN_RIGHT, 5 );
	
	
	bSizer18->Add( gSizer2, 1, wxEXPAND|wxLEFT, 10 );
	
	DefaultButton = new wxButton( this, wxID_ANY, wxT("Default"), wxDefaultPosition, wxSize( -1,-1 ), wxBU_EXACTFIT );
	bSizer18->Add( DefaultButton, 0, wxALIGN_RIGHT|wxALL, 5 );
	
	
	bSizer8->Add( bSizer18, 1, wxEXPAND|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticline2 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL );
	bSizer8->Add( m_staticline2, 0, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer14;
	bSizer14 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText10 = new wxStaticText( this, wxID_ANY, wxT("Bumps"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText10->Wrap( -1 );
	bSizer14->Add( m_staticText10, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxBoxSizer* bSizer15;
	bSizer15 = new wxBoxSizer( wxVERTICAL );
	
	m_bitmap1 = new wxStaticBitmap( this, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer15->Add( m_bitmap1, 0, wxALIGN_CENTER_HORIZONTAL|wxTOP|wxRIGHT|wxLEFT, 5 );
	
	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer( wxHORIZONTAL );
	
	m_bitmap2 = new wxStaticBitmap( this, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer13->Add( m_bitmap2, 0, wxALL, 5 );
	
	
	bSizer13->Add( 20, 0, 1, wxEXPAND, 5 );
	
	m_bitmap3 = new wxStaticBitmap( this, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer13->Add( m_bitmap3, 0, wxALL, 5 );
	
	
	bSizer15->Add( bSizer13, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_bitmap4 = new wxStaticBitmap( this, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer15->Add( m_bitmap4, 0, wxALIGN_CENTER_HORIZONTAL|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	
	bSizer15->Add( 200, 0, 1, wxEXPAND, 5 );
	
	
	bSizer14->Add( bSizer15, 0, wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer12->Add( bSizer14, 0, wxALIGN_CENTER_HORIZONTAL|wxTOP, 5 );
	
	
	bSizer12->Add( 0, 0, 1, wxEXPAND, 5 );
	
	ExitButton = new wxButton( this, wxID_ANY, wxT("Exit"), wxDefaultPosition, wxSize( -1,25 ), wxBU_EXACTFIT );
	bSizer12->Add( ExitButton, 0, wxALIGN_BOTTOM|wxALIGN_RIGHT|wxALL, 5 );
	
	
	bSizer8->Add( bSizer12, 1, wxEXPAND, 5 );
	
	
	bSizer1->Add( bSizer8, 1, wxALIGN_RIGHT|wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer1 );
	this->Layout();
	m_statusBar1 = this->CreateStatusBar( 1, wxST_SIZEGRIP, wxID_ANY );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( CameraSettingsMenuItem->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnSelectCameraSettings ) );
	StartCaptureButton->Connect( wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, wxCommandEventHandler( MainFrame::OnToggleCapture ), NULL, this );
	CorrectionButton->Connect( wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, wxCommandEventHandler( MainFrame::OnToggleCorrection ), NULL, this );
	StreamPlayerPanel->Connect( wxEVT_PAINT, wxPaintEventHandler( MainFrame::OnFramePaint ), NULL, this );
	ThrsTxCtrl->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( MainFrame::OnThrshTextSet ), NULL, this );
	m_checkBox1->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MainFrame::OnShowThresholdChecked ), NULL, this );
	GetStarSizeButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::OnGetStarSizeClicked ), NULL, this );
	StrSzTxCtrl->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( MainFrame::OnStrSzTextSet ), NULL, this );
	DefaultButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::OnDefaultClicked ), NULL, this );
	ExitButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::OnClickExit ), NULL, this );
}

MainFrame::~MainFrame()
{
	// Disconnect Events
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnSelectCameraSettings ) );
	StartCaptureButton->Disconnect( wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, wxCommandEventHandler( MainFrame::OnToggleCapture ), NULL, this );
	CorrectionButton->Disconnect( wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, wxCommandEventHandler( MainFrame::OnToggleCorrection ), NULL, this );
	StreamPlayerPanel->Disconnect( wxEVT_PAINT, wxPaintEventHandler( MainFrame::OnFramePaint ), NULL, this );
	ThrsTxCtrl->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( MainFrame::OnThrshTextSet ), NULL, this );
	m_checkBox1->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MainFrame::OnShowThresholdChecked ), NULL, this );
	GetStarSizeButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::OnGetStarSizeClicked ), NULL, this );
	StrSzTxCtrl->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( MainFrame::OnStrSzTextSet ), NULL, this );
	DefaultButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::OnDefaultClicked ), NULL, this );
	ExitButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::OnClickExit ), NULL, this );
	
}
