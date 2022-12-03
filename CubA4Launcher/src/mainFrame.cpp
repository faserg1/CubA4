#include <mainFrame.hpp>

constexpr const wxWindowID LaunchClientBtnId = 1;
constexpr const wxWindowID LaunchServerBtnId = 2;

MainFrame::MainFrame()
    : wxFrame(NULL, wxID_ANY, "CubA4 launcher")
{
    buttonsBox_ = new wxBoxSizer(wxHORIZONTAL);
    this->SetSizer(buttonsBox_);
    buttonClient_ = std::make_unique<wxButton>(this, LaunchClientBtnId, "Launch client");
    buttonServer_ = std::make_unique<wxButton>(this, LaunchClientBtnId, "Launch server");
    buttonsBox_->Add(buttonClient_.get(), 1, wxEXPAND, 20);
    buttonsBox_->Add(buttonServer_.get(), 1, wxEXPAND, 20);
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