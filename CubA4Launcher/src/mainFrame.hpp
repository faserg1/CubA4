#pragma once

#include <wx/wxprec.h>
 
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
    wxBoxSizer *buttonsBox_;
    std::unique_ptr<wxButton> buttonClient_;
    std::unique_ptr<wxButton> buttonServer_;

    wxDECLARE_EVENT_TABLE();
};