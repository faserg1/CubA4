#include <mainFrame.hpp>

constexpr const wxWindowID LaunchClientBtnId = 1;
constexpr const wxWindowID LaunchServerBtnId = 2;
constexpr const wxWindowID WebViewId = 3;

MainFrame::MainFrame()
    : wxFrame(NULL, wxID_ANY, "CubA4 launcher")
{
    mainBox_ = new wxBoxSizer(wxVERTICAL);
    buttonsBox_ = new wxBoxSizer(wxHORIZONTAL);
    this->SetSizer(mainBox_);
    buttonPanel_ = std::make_unique<wxPanel>(this);
	buttonClient_ = std::make_unique<wxButton>(buttonPanel_.get(), LaunchClientBtnId, "Launch client");
    buttonServer_ = std::make_unique<wxButton>(buttonPanel_.get(), LaunchServerBtnId, "Launch server");
	buttonPanel_->SetSizer(buttonsBox_);
	webView_ = std::unique_ptr<wxWebView>(wxWebView::New(this, WebViewId, "https://www.google.com"));
    buttonsBox_->Add(buttonClient_.get(), 1, wxEXPAND, 20);
    buttonsBox_->Add(buttonServer_.get(), 1, wxEXPAND, 20);
	mainBox_->Add(webView_.get(), 1, wxEXPAND, 600);
	mainBox_->Add(buttonPanel_.get(), 0, wxSTRETCH_NOT, 0);
}

void MainFrame::LaunClient(wxCommandEvent& event)
{
    wxExecute("./bin/CubA4Loader");
    this->Close();
}

void MainFrame::LaunchServer(wxCommandEvent& event)
{
    wxExecute("./bin/CubA4Server");
    this->Close();
}

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
    EVT_BUTTON(LaunchClientBtnId, MainFrame::LaunClient)
    EVT_BUTTON(LaunchServerBtnId, MainFrame::LaunchServer)
wxEND_EVENT_TABLE()