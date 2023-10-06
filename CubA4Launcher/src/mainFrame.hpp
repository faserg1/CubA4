#pragma once

#include <wx/wxprec.h>
#include <wx/webview.h>
 
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

class MainFrame : public wxFrame
{
public:
    MainFrame();

    void LaunClient(wxCommandEvent& event);
    void LaunchServer(wxCommandEvent& event);
private:
	// managed by window
    wxBoxSizer *mainBox_;
    wxBoxSizer *buttonsBox_;
    std::unique_ptr<wxPanel> buttonPanel_;
    std::unique_ptr<wxButton> buttonClient_;
    std::unique_ptr<wxButton> buttonServer_;
    std::unique_ptr<wxWebView> webView_;

    wxDECLARE_EVENT_TABLE();
};